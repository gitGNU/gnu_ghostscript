/*
    jbig2dec
    
    Copyright (c) 2001-2003 artofcode LLC.
    
    This software is distributed under license and may not
    be copied, modified or distributed except as expressly
    authorized under the terms of the license contained in
    the file LICENSE in this distribution.
                                                                                
    For information on commercial licensing, go to
    http://www.artifex.com/licensing/ or contact
    Artifex Software, Inc.,  101 Lucas Valley Road #110,
    San Rafael, CA  94903, U.S.A., +1(415)492-9861.

    $Id: jbig2_image.c,v 1.1 2005/04/18 12:06:07 Arabidopsis Exp $
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 
#include "os_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy() */

#include "jbig2.h"
#include "jbig2_priv.h"
#include "jbig2_image.h"


/* allocate a Jbig2Image structure and its associated bitmap */
Jbig2Image* jbig2_image_new(Jbig2Ctx *ctx, int width, int height)
{
	Jbig2Image	*image;
	int		stride;
	
	image = (Jbig2Image *)jbig2_alloc(ctx->allocator, sizeof(*image));
	if (image == NULL) {
		jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1,
			       "could not allocate image structure");
		return NULL;
	}
	
	stride = ((width - 1) >> 3) + 1; /* generate a byte-aligned stride */
	image->data = (uint8_t *)jbig2_alloc(ctx->allocator, stride*height);
	if (image->data == NULL) {
                jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1,
                    "could not allocate image data buffer! [%d bytes]\n", stride*height);
		jbig2_free(ctx->allocator, image);
		return NULL;
	}
	
	image->width = width;
	image->height = height;
	image->stride = stride;
	image->refcount = 1;
	
	return image;
}

/* clone an image pointer by bumping its reference count */
Jbig2Image* jbig2_image_clone(Jbig2Ctx *ctx, Jbig2Image *image)
{
	image->refcount++;
	return image;
}

/* release an image pointer, freeing it it appropriate */
void jbig2_image_release(Jbig2Ctx *ctx, Jbig2Image *image)
{
	image->refcount--;
	if (!image->refcount) jbig2_image_free(ctx, image);
}

/* free a Jbig2Image structure and its associated memory */
void jbig2_image_free(Jbig2Ctx *ctx, Jbig2Image *image)
{
	jbig2_free(ctx->allocator, image->data);
	jbig2_free(ctx->allocator, image);
}

/* composite one jbig2_image onto another */
int jbig2_image_compose(Jbig2Ctx *ctx, Jbig2Image *dst, Jbig2Image *src, 
			int x, int y, Jbig2ComposeOp op)
{
    int i, j;
    int w, h;
    int leftbyte, rightbyte;
    int shift;
    uint8_t *s, *ss;
    uint8_t *d, *dd;
    uint8_t mask, rightmask;
    
    if (op != JBIG2_COMPOSE_OR) {
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1,
            "non-OR composition modes NYI");
    }

    /* clip */
    w = src->width;
    h = src->height;
    ss = src->data;
    /* FIXME: this isn't sufficient for the < 0 cases */
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; } 
    w = (x + w < dst->width) ? w : dst->width - x;
    h = (y + h < dst->height) ? h : dst->height - y;
#ifdef JBIG2_DEBUG    
    fprintf(stderr, "composting %dx%d at (%d, %d) afer clipping\n",
        w, h, x, y);
#endif
    
#if 0
    /* special case complete/strip replacement */
    /* disabled because it's only safe to do when the destination
       buffer is all-blank. */
    if ((x == 0) && (w == src->width)) {
        memcpy(dst->data + y*dst->stride, src->data, h*src->stride);
        return 0;
    }
#endif

    leftbyte = x >> 3;
    rightbyte = (x + w - 1) >> 3;
    shift = x & 7;
    
    /* general OR case */    
    s = ss;
    d = dd = dst->data + y*dst->stride + leftbyte;
    if (leftbyte == rightbyte) {
	mask = 0x100 - (0x100 >> w);
        for (j = 0; j < h; j++) {
            *d |= (*s & mask) >> shift;
            d += dst->stride;
            s += src->stride;
        }
    } else if (shift == 0) {
        for (j = 0; j < h; j++) {
	    for (i = leftbyte; i <= rightbyte; i++)
		*d++ |= *s++;
            d = (dd += dst->stride);
            s = (ss += src->stride);
	}
    } else {
	mask = 0x100 - (1 << shift);
	if (((w + 7) >> 3) < ((x + w + 7) >> 3) - (x >> 3))
	    rightmask = (0x100 - (0x100 >> ((x + w) & 7))) >> (8 - shift);
	else
	    rightmask = 0x100 - (0x100 >> (w & 7));
        for (j = 0; j < h; j++) {
	    *d++ |= (*s & mask) >> shift;
            for(i = leftbyte; i < rightbyte - 1; i++) {
		*d |= ((*s++ & ~mask) << (8 - shift));
		*d++ |= ((*s & mask) >> shift);
	    }
	    if (((w + 7) >> 3) < ((x + w + 7) >> 3) - (x >> 3))
		*d |= (s[0] & rightmask) << (8 - shift);
	    else
		*d |= ((s[0] & ~mask) << (8 - shift)) |
		    ((s[1] & rightmask) >> shift);
	    d = (dd += dst->stride);
	    s = (ss += src->stride);
	}
    }
            
    return 0;
}
