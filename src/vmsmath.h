/* Copyright (C) 1989 artofcode LLC.  All rights reserved.
  
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

/*$Id: vmsmath.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Substitute for math.h on VAX/VMS systems */

#ifndef vmsmath_INCLUDED
#  define vmsmath_INCLUDED

/* DEC VAX/VMS C comes with a math.h file but GNU VAX/VMS C does not. */
/* This file substitutes for math.h when using GNU C. */
#  ifndef __MATH
#    define __MATH
#    if CC$gfloat
#      define HUGE_VAL 8.988465674311578540726371186585e+307
#    else
#      define HUGE_VAL 1.70141183460469229e+38
#    endif
extern double acos(), asin(), atan(), atan2();
extern double sin(), tan(), cos();
extern double cosh(), sinh(), tanh();
extern double exp(), frexp(), ldexp(), log(), log10(), pow();
extern double modf(), fmod(), sqrt(), ceil(), floor();
extern double fabs(), cabs(), hypot();

#  endif

#endif /* vmsmath_INCLUDED */
