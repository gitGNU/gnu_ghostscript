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

/*$Id: gdevdcrd.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Interface for creating a sample device CRD */

#ifndef gdevdcrd_INCLUDED
#define gdevdcrd_INCLUDED

/* Implement get_params for a sample device CRD. */
int sample_device_crd_get_params(P3(gx_device *pdev, gs_param_list *plist,
				    const char *crd_param_name));

#endif	/* gdevdcrd_INCLUDED */
