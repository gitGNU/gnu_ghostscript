/* $Id: ps2pdf12.cmd,v 1.4 2010/07/10 22:02:35 Arabidopsis Exp $ */
/*
 * This file is maintained by a user: if you have any questions about it,
 * please contact Mark Hale (mark.hale@physics.org).
 */

/* Convert PostScript to PDF 1.2 (Acrobat 3-and-later compatible). */

parse arg params

call 'ps2pdf' '-dCompatibilityLevel=1.2' params
