/* Copyright (C) 2003 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: ttload.c,v 1.5 2006/06/16 12:55:04 Arabidopsis Exp $ */

/* Changes after FreeType: cut out the TrueType instruction interpreter. */

/*******************************************************************
 *
 *  ttload.c                                                    1.0
 *
 *    TrueType Tables Loader.                          
 *
 *  Copyright 1996-1998 by
 *  David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 *  This file is part of the FreeType project, and may only be used
 *  modified and distributed under the terms of the FreeType project
 *  license, LICENSE.TXT.  By continuing to use, modify, or distribute
 *  this file you indicate that you have read the license and
 *  understand and accept it fully.
 *
 ******************************************************************/

#include "ttmisc.h"

#include "ttfoutl.h"
#include "tttypes.h"
#include "ttcalc.h"
#include "ttobjs.h"
#include "ttload.h"
#include "ttfinp.h"

#ifdef DEBUG
#  define DebugTrace( font, fmt )  (void)(!font->DebugPrint ? 0 : font->DebugPrint(font, fmt))
#  define DebugTrace1( font, fmt, x)  (void)(!font->DebugPrint ? 0 : font->DebugPrint(font, fmt, x))
#else
#  define DebugTrace( font, fmt )
#  define DebugTrace1( font, fmt, x)
#endif

/*******************************************************************
 *
 *  Function    :  Load_TrueType_MaxProfile
 *
 *  Description :  Loads the maxp table into face table.
 *
 *  Input  :  face     face table to look for
 *
 *  Output :  Error code.
 *
 ******************************************************************/

  TT_Error  Load_TrueType_MaxProfile( PFace  face )
  {
    ttfReader *r = face->r;
    ttfFont *font = face->font;
    PMaxProfile  maxProfile = &face->maxProfile;

    r->Seek(r, font->t_maxp.nPos);

    DebugTrace(font, "MaxProfile " );

    /* read frame data into face table */
    maxProfile->version               = GET_ULong();

    maxProfile->numGlyphs             = GET_UShort();

    maxProfile->maxPoints             = GET_UShort();
    maxProfile->maxContours           = GET_UShort();
    maxProfile->maxCompositePoints    = GET_UShort();
    maxProfile->maxCompositeContours  = GET_UShort();

    maxProfile->maxZones              = GET_UShort();
    maxProfile->maxTwilightPoints     = GET_UShort();

    maxProfile->maxStorage            = GET_UShort();
    maxProfile->maxFunctionDefs       = GET_UShort();
    maxProfile->maxInstructionDefs    = GET_UShort();
    maxProfile->maxStackElements      = GET_UShort();
    maxProfile->maxSizeOfInstructions = GET_UShort();
    maxProfile->maxComponentElements  = GET_UShort();
    maxProfile->maxComponentDepth     = GET_UShort();

    face->numGlyphs     = maxProfile->numGlyphs;

    face->maxPoints     = MAX( maxProfile->maxCompositePoints, 
                               maxProfile->maxPoints );
    face->maxContours   = MAX( maxProfile->maxCompositeContours,
                               maxProfile->maxContours );
    face->maxComponents = maxProfile->maxComponentElements +
                          maxProfile->maxComponentDepth;

    DebugTrace(font, "loaded\n");
  
    return TT_Err_Ok;
  }

/*******************************************************************
 *
 *  Function    :  Load_TrueType_CVT
 *
 *  Description :  Loads cvt table into resident table.
 *
 *  Input  :  face     face table to look for
 *
 *  Output :  Error code.
 *
 ******************************************************************/

  TT_Error  Load_TrueType_CVT( PFace  face )
  {
    long  n;
    Int  limit;

    ttfReader *r = face->r;
    ttfFont *font = face->font;
    ttfMemory *mem = font->tti->ttf_memory;
    r->Seek(r, font->t_cvt_.nPos);


    face->cvt=NULL;

    DebugTrace(font, "CVT ");

    face->cvtSize = font->t_cvt_.nLen / 2;

#   if 0
    if(face->cvtSize < 300)
      face->cvtSize = 300; /* Work around DynaLab bug in DingBat1. */
#   endif

    if(face->cvtSize > 0) {  /* allow fonts with a CVT table */
	face->cvt = mem->alloc_bytes(mem, face->cvtSize * sizeof(Short), "Load_TrueType_CVT");
	if (!face->cvt)
	    return TT_Err_Out_Of_Memory;
    }


    limit = face->cvtSize;

    for ( n = 0; n < limit && !r->Eof(r); n++ )
      face->cvt[n] = GET_Short();

    DebugTrace(font, "loaded\n");

    return TT_Err_Ok;
  }


/*******************************************************************
 *
 *  Function    :  Load_TrueType_Programs
 *
 *  Description :  Loads the font (fpgm) and cvt programs into the
 *                 face table.
 *
 *  Input  :  face
 *
 *  Output :  Error code.
 *
 ******************************************************************/

  TT_Error  Load_TrueType_Programs( PFace  face )
  {
    ttfReader *r = face->r;
    ttfFont *font = face->font;
    ttfMemory *mem = font->tti->ttf_memory;

    face->fontProgram = NULL;
    face->cvtProgram = NULL;


    DebugTrace(font, "Font program ");

    /* The font program is optional */
    if(!font->t_fpgm.nPos)
    {
      face->fontProgram = (Byte*)NULL;
      face->fontPgmSize = 0;

      DebugTrace(font, "is absent.\n");
    }
    else
    {
      face->fontPgmSize = font->t_fpgm.nLen;
      r->Seek(r, font->t_fpgm.nPos);
      face->fontProgram = mem->alloc_bytes(mem, face->fontPgmSize, "Load_TrueType_Programs");

      if (!face->fontProgram)
        return TT_Err_Out_Of_Memory;
      r->Read(r, face->fontProgram,face->fontPgmSize );
      DebugTrace1(font, "loaded, %12d bytes\n", face->fontPgmSize);
    }

    DebugTrace(font, "Prep program ");

    if (!font->t_prep.nPos)
    {
      face->cvtProgram = (Byte*)NULL;
      face->cvtPgmSize = 0;

      DebugTrace(font, "is missing!\n");
    }
    else
    { face->cvtPgmSize=font->t_prep.nLen;
      r->Seek(r, font->t_prep.nPos);
      face->cvtProgram = mem->alloc_bytes(mem, face->cvtPgmSize, "Load_TrueType_Programs");
      if (!face->cvtProgram)
        return TT_Err_Out_Of_Memory;
      r->Read(r, face->cvtProgram,face->cvtPgmSize );
      DebugTrace1(font, "loaded, %12d bytes\n", face->cvtPgmSize );
    }

    return TT_Err_Ok;
  }



