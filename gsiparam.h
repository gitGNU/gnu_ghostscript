/* Copyright (C) 1996, 1997 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU Ghostscript.
  
  GNU Ghostscript is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
  anyone for the consequences of using it or for whether it serves any
  particular purpose or works at all, unless he says so in writing.  Refer to
  the GNU General Public License for full details.
  
  Everyone is granted permission to copy, modify and redistribute GNU
  Ghostscript, but only under the conditions described in the GNU General
  Public License.  A copy of this license is supposed to have been given to
  you along with GNU Ghostscript so you can know your rights and
  responsibilities.  It should be in a file named COPYING.  Among other
  things, the copyright notice and this notice must be preserved on all
  copies.
  
  Aladdin Enterprises is not affiliated with the Free Software Foundation or
  the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
  does not depend on any other GNU software.
*/

/* gsiparam.h */
/* Image parameter definition */
/* Requires gsmatrix.h */

#ifndef gsiparam_INCLUDED
#  define gsiparam_INCLUDED

/* ---------------- Image parameters ---------------- */

/* Define an opaque type for a color space. */
#ifndef gs_color_space_DEFINED
#  define gs_color_space_DEFINED
typedef struct gs_color_space_s gs_color_space;
#endif

/*
 * Define the structure for specifying image data.  It follows closely
 * the discussion on pp. 219-223 of the PostScript Language Reference Manual,
 * Second Edition, with the following exceptions:
 *
 *	ColorSpace and ImageMask are added members from PDF.
 *
 *	DataSource and MultipleDataSources are not members of this
 *	structure, but are arguments of gs_image_init.
 *
 *	adjust, CombineWithColor, and HasAlpha are not PostScript or
 *	PDF standard (see the RasterOp section of language.doc for a
 *	discussion of CombineWithColor).
 */
typedef enum {
		/* Single plane, chunky pixels. */
	gs_image_format_chunky = 0,
		/* num_components planes, chunky components. */
	gs_image_format_component_planar = 1,
		/* BitsPerComponent * num_components planes, 1 bit per plane */
		/****** NOT SUPPORTED YET, DO NOT USE ******/
	gs_image_format_bit_planar = 2
} gs_image_format_t;

typedef struct gs_image_s {
		/*
		 * Define the width of source image in pixels.
		 */
	int Width;
		/*
		 * Define the height of source image in pixels.
		 */
	int Height;
		/*
		 * Define the transformation from user space to image space.
		 */
	gs_matrix ImageMatrix;
		/*
		 * Define B, the number of bits per pixel component.
		 * Currently this must be 1 for masks.
		 */
	int BitsPerComponent;
		/*
		 * Define the source color space (must be NULL for masks).
		 */
	const gs_color_space *ColorSpace;
		/*
		 * Define the linear remapping of the input values.
		 * For the I'th pixel component, we start by treating
		 * the B bits of component data as a fraction F between
		 * 0 and 1; the actual component value is then
		 * Decode[I*2] + F * (Decode[I*2+1] - Decode[I*2]).
		 * For masks, only the first two entries are used;
		 * they must be 1,0 for write-0s masks, 0,1 for write-1s.
		 */
#ifdef DPNEXT
	float Decode[10];	/* 4 colors + alpha */
#else
	float Decode[8];
#endif
		/*
		 * Define whether to smooth the image.
		 */
	bool Interpolate;
		/*
		 * Define whether this is a mask or a solid image.
		 */
	bool ImageMask;
		/***
		 *** The following are not PostScript standard.
		 ***/
		/*
		 * Define whether to expand each destination pixel, to make
		 * masked characters look better (only used for masks).
		 */
	bool adjust;
		/*
		 * Define whether to use the drawing color as the
		 * "texture" for RasterOp.  For more information,
		 * see the discussion of RasterOp in language.doc.
		 */
	bool CombineWithColor;
#ifdef DPNEXT
		/*
		 * Define whether there is an additional component providing
		 * alpha information for each pixel, in addition to (and
		 * following) the components implied by the color space.
		 * For masks, HasAlpha must be false.
		 */
	bool HasAlpha;
#endif
} gs_image_t;

/*
 * Define procedures for initializing a gs_image_t to default values.
 * For masks, write_1s = false paints 0s, write_1s = true paints 1s.
 * This is consistent with the "polarity" operand of the PostScript
 * imagemask operator.
 *
 * Note that because gs_image_t may add more members in the future, all
 * clients constructing gs_image_t values *must* start by initializing
 * the value by calling one of the following procedures.
 */
void
  gs_image_t_init_gray(P1(gs_image_t *pim)),
  gs_image_t_init_color(P1(gs_image_t *pim)),/* general color, initially RGB */
  gs_image_t_init_mask(P2(gs_image_t *pim, bool write_1s));

/****** REMAINDER OF FILE UNDER CONSTRUCTION. PROCEED AT YOUR OWN RISK. ******/

#if 0

/* ---------------- Services ---------------- */

/*
In order to make the driver's life easier, we provide the following callback
procedure:
*/

int gx_map_image_color(P5(gx_device *dev,
			  const gs_image_t *pim,
			  const gx_color_rendering_info *pcri,
			  const uint components[4],
			  gx_drawing_color *pdcolor));

/*
Map a source color to a drawing color.  The components are simply the pixel
component values from the input data, i.e., 1 to 4 B-bit numbers from the
source data.  Return 0 if the operation succeeded, or a negative error code.
*/

#endif	/****************************************************************/

#endif					/* gsiparam_INCLUDED */
