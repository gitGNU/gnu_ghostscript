/* Copyright (C) 1996, 1998 artofcode LLC.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.

*/

/*$Id: gxdevrop.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Extension of gxdevice.h for RasterOp */

#ifndef gxdevrop_INCLUDED
#  define gxdevrop_INCLUDED

/* Define an unaligned implementation of [strip_]copy_rop. */
dev_proc_copy_rop(gx_copy_rop_unaligned);
dev_proc_strip_copy_rop(gx_strip_copy_rop_unaligned);

#endif /* gxdevrop_INCLUDED */
