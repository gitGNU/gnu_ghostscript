/* Copyright (C) 1992, 1996, 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: iddict.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Dictionary API with implicit dict_stack argument */

#ifndef iddict_INCLUDED
#  define iddict_INCLUDED

#include "idict.h"
#include "icstate.h"		/* for access to dict_stack */

/* Define the dictionary stack instance for operators. */
#define idict_stack (i_ctx_p->dict_stack)

#define idict_put(pdref, key, pvalue)\
  dict_put(pdref, key, pvalue, &idict_stack)
#define idict_put_string(pdref, kstr, pvalue)\
  dict_put_string(pdref, kstr, pvalue, &idict_stack)
#define idict_undef(pdref, key)\
  dict_undef(pdref, key, &idict_stack)
#define idict_copy(dfrom, dto)\
  dict_copy(dfrom, dto, &idict_stack)
#define idict_copy_new(dfrom, dto)\
  dict_copy_new(dfrom, dto, &idict_stack)
#define idict_resize(pdref, newmax)\
  dict_resize(pdref, newmax, &idict_stack)
#define idict_grow(pdref)\
  dict_grow(pdref, &idict_stack)
#define idict_unpack(pdref)\
  dict_unpack(pdref, &idict_stack)

#endif /* iddict_INCLUDED */
