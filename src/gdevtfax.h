/* Copyright (C) 1999, 2000 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2, or (at your option) any later version.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: gdevtfax.h,v 1.4 2005/12/13 16:57:20 jemarch Exp $ */
/* Entry points to the TIFF/fax writing driver */

#ifndef gdevtfax_INCLUDED
#  define gdevtfax_INCLUDED

int gdev_fax_print_page_stripped(gx_device_printer *pdev, FILE *prn_stream,
				 stream_CFE_state *ss, long rows_per_strip);

#endif /* gdevtfax_INCLUDED */
