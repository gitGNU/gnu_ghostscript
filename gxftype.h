/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* gxftype.h */
/* Definition of font type and bitmap font behavior */

#ifndef gxftype_INCLUDED
#  define gxftype_INCLUDED

/* Define the known font types. */
/* These numbers must be the same as the values of FontType */
/* in font dictionaries. */
typedef enum {
	ft_composite = 0,
	ft_encrypted = 1,
	ft_CFF = 2,
	ft_user_defined = 3,
	ft_disk_based = 4,
	ft_CID_encrypted = 9,
	ft_CID_user_defined = 10,
	ft_CID_TrueType = 11,
	ft_Chameleon = 14,
	ft_bitmap = 32,
	ft_TrueType = 42
} font_type;

/* Define the bitmap font behaviors. */
/* These numbers must be the same as the values of the ExactSize, */
/* InBetweenSize, and TransformedChar entries in font dictionaries. */
typedef enum {
	fbit_use_outlines = 0,
	fbit_use_bitmaps = 1,
	fbit_transform_bitmaps = 2
} fbit_type;

#endif					/* gxftype_INCLUDED */
