/* $Id: ps2pdf14.cmd,v 1.2 2004/02/14 22:20:04 atai Exp $ */
/*
 * This file is maintained by a user: if you have any questions about it,
 * please contact Mark Hale (mark.hale@physics.org).
 */

/* Convert PostScript to PDF 1.4 (Acrobat 5-and-later compatible). */

parse arg params

call 'ps2pdf' '-dCompatibilityLevel=1.4' params
