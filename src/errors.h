/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/
/* $Id: errors.h,v 1.7 2007/08/01 14:25:44 jemarch Exp $ */

#ifndef errors_INCLUDED
#  define errors_INCLUDED

/* This file used to contain error codes for the Ghostscript client api.
 * It has been renamed ierrors.h to reduce the risk of namespace collision 
 * and to be consistent with iapi.h.
 */

/* We include that file here to backward compatibility */
#include "ierrors.h"

#endif /* errors_INCLUDED */
