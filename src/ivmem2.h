/* Copyright (C) 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: ivmem2.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* VM control user parameter procedures */

#ifndef ivmem2_INCLUDED
#  define ivmem2_INCLUDED

/* Exported by zvmem2.c for zusparam.c */
int set_vm_reclaim(P2(i_ctx_t *, long));
int set_vm_threshold(P2(i_ctx_t *, long));

#endif /* ivmem2_INCLUDED */
