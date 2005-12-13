/*
    jbig2dec
    
    Copyright (c) 2001 artofcode LLC.
    
    This software is distributed under license and may not
    be copied, modified or distributed except as expressly
    authorized under the terms of the license contained in
    the file LICENSE in this distribution.
                                                                                
    $Id: jbig2_huffman.h,v 1.2 2005/12/13 18:01:32 jemarch Exp $
*/

#include "jbig2_hufftab.h"

Jbig2HuffmanState *
jbig2_huffman_new (Jbig2WordStream *ws);

int32_t
jbig2_huffman_get (Jbig2HuffmanState *hs,
		   const Jbig2HuffmanTable *table, bool *oob);

Jbig2HuffmanTable *
jbig2_build_huffman_table (const Jbig2HuffmanParams *params);
