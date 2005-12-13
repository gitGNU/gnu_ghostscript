/*
    jbig2dec

    Copyright (c) 2002-2003 artofcode LLC.

    This software is distributed under license and may not
    be copied, modified or distributed except as expressly
    authorized under the terms of the license contained in
    the file LICENSE in this distribution.
                                                                                
    $Id: config_win32.h,v 1.2 2005/12/13 18:01:32 jemarch Exp $
*/

/* configuration header file for compiling under Microsoft Windows */

/* update package version here */
#define PACKAGE "jbig2dec"
#define VERSION "0.3"

#ifdef _MSC_VER /* Microsoft Visual C+*/

  typedef signed char             int8_t;
  typedef short int               int16_t;
  typedef int                     int32_t;
  typedef __int64                 int64_t;
 
  typedef unsigned char             uint8_t;
  typedef unsigned short int        uint16_t;
  typedef unsigned int              uint32_t;
  /* no uint64_t */

#  define vsnprintf _vsnprintf
#  define snprintf _snprintf

#endif /* _MSC_VER */
