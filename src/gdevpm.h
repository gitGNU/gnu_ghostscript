/* Copyright (C) 1992, 1993 artofcode LLC.  All rights reserved.
  
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

/*$Id: gdevpm.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Defines common to gdevpm.c, gspmdrv.c and PM GSview */

#ifndef gdevpm_INCLUDED
#  define gdevpm_INCLUDED

#define SHARED_NAME "\\SHAREMEM\\%s"
#define SYNC_NAME   "\\SEM32\\SYNC_%s"
#define NEXT_NAME   "\\SEM32\\NEXT_%s"
#define MUTEX_NAME  "\\SEM32\\MUTEX_%s"
#define QUEUE_NAME  "\\QUEUES\\%s"

#define GS_UPDATING	1
#define GS_SYNC		2
#define GS_PAGE		3
#define GS_CLOSE	4
#define GS_ERROR	5
#define GS_PALCHANGE	6
#define GS_BEGIN	7
#define GS_END		8

#endif /* gdevpm_INCLUDED */
