/* Copyright (C) 2003 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
 
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: ttfinp.h,v 1.1 2005/04/18 12:06:01 Arabidopsis Exp $ */
/* A TT font input support. */

#ifndef incl_ttfinp
#define incl_ttfinp

unsigned char  ttfReader__Byte(ttfReader *r);
signed   char  ttfReader__SignedByte(ttfReader *r);
unsigned short ttfReader__UShort(ttfReader *r);
unsigned int   ttfReader__UInt(ttfReader *r);
signed   short ttfReader__Short(ttfReader *r);
signed   int   ttfReader__Int(ttfReader *r);

#endif
