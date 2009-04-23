/* Copyright (C) 2001-2006 Artifex Software, Inc.
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

/* $Id: ttcommon.h,v 1.1 2009/04/23 23:25:52 Arabidopsis Exp $ */

/* Changes after FreeType: cut out the TrueType instruction interpreter. */

/*******************************************************************
 *
 *  ttcommon.h                                                 1.0
 *
 *  Library internal functions renaming.
 *
 *  Copyright 1996-1998 by
 *  David Turner, Robert Wilhelm, and Werner Lemberg
 *
 *  This file is part of the FreeType project, and may only be used
 *  modified and distributed under the terms of the FreeType project
 *  license, LICENSE.TXT.  By continuing to use, modify, or distribute
 *  this file you indicate that you have read the license and
 *  understand and accept it fully.
 *
 *
 *  This file is used to rename automatically all internal engine
 *  functions, when the macro 'TT_PREFIX_ALL_NAMES' is defined.
 *
 *  This is useful to avoid conflicts at link time between functions
 *  from different sources but with the same name.  As a convention,
 *  all FreeType internal functions names are prefixed with the two
 *  letters "FT" by this file.
 *
 *  Note that this file doesn't change the names of FreeType's
 *  external functions, which all begin with "TT_". These are:
 *
 *  - the High-Level API functions (defined in "freetype.h")
 *  - the portable components (memory, file and mutex)
 *
 ******************************************************************/

#ifndef TTCOMMON_H
#define TTCOMMON_H

#ifdef TT_PREFIX_ALL_NAMES

/* -- ttcalc ------------------------------------------------------------- */

#define MulDiv        FTMulDiv
#define MulDiv_Round  FTMulDiv_Round
#define Sqrt32        FTSqrt32
#define Sqrt64        FTSqrt64
#define Add64         FTAdd64
#define Sub64         FTSub64
#define Neg64         FTNeg64
#define MulTo64       FTMulTo64
#define Div64by32     FTDiv64by32
#define Order32       FTOrder32
#define Order64       FTOrder64

/* -- ttlists ------------------------------------------------------------ */

#define Element_New   FTElement_New
#define Element_Done  FTElement_Done
#define List_Add      FTList_Add
#define List_Remove   FTList_Remove
#define List_Find     FTList_Find
#define List_Extract  FTList_Extract

/* -- ttcache ------------------------------------------------------------ */

#define Cache_Create   FTCache_Create
#define Cache_Destroy  FTCache_Destroy
#define Cache_New      FTCache_New
#define Cache_Done     FTCache_Done

/* -- tterror ------------------------------------------------------------ */

#define Message        FTMessage
#define Panic          FTPanic

/* -- ttmutex ------------------------------------------------------------ */

#define Mutex_Create   FTMutex_Create
#define Mutex_Destroy  FTMutex_Destroy
#define Mutex_Lock     FTMutex_Lock
#define Mutex_Release  FTMutex_Release

/* -- ttraster ----------------------------------------------------------- */

#define Render_Glyph        FTRender_Glyph
#define Render_Gray_Glyph   FTRender_Gray_Glyph
#define Set_High_Precision  FTSet_High_Precision
#define Set_Second_Pass     FTSet_Second_Pass

/* -- ttcmap ------------------------------------------------------------- */

#define CharMap_Load   FTCharMap_Load
#define CharMap_Free   FTCharMap_Free
#define CharMap_Index  FTCharMap_Index

/* -- ttobjs ------------------------------------------------------------- */

#define Goto_CodeRange    FTGoto_CodeRange
#define Get_CodeRange     FTGet_CodeRange
#define Set_CodeRange     FTSet_CodeRange
#define Clear_CodeRange   FTClear_CodeRange

#define New_Context       FTNew_Context
#define Done_Context      FTDone_Context
#define Context_Create    FTContext_Create
#define Context_Destroy   FTContext_Destroy
#define Context_Load      FTContext_Load
#define Context_Save      FTContext_Save
#define Context_Run       FTContext_Run

#define New_Instance      FTNew_Instance
#define Done_Instance     FTDone_Instance
#define Instance_Create   FTInstance_Create
#define Instance_Destroy  FTInstance_Destroy
#define Instance_Init     FTInstance_Init
#define Instance_Reset    FTInstance_Reset

#define Face_Create       FTFace_Create
#define Face_Destroy      FTFace_Destroy

#define Glyph_Create      FTGlyph_Create
#define Glyph_Destroy     FTGlyph_Destroy

#define Default_GraphicsState   FTDefault_GraphicsState

/* -- ttload ------------------------------------------------------------- */

#define LookUp_TrueType_Table            FTLookUp_TrueType_Table
#define Load_TrueType_Directory          FTLoad_TrueType_Directory
#define Load_TrueType_MaxProfile         FTLoad_TrueType_MaxProfile
#define Load_TrueType_Gasp               FTLoad_TrueType_Gasp
#define Load_TrueType_Header             FTLoad_TrueType_Header
#define Load_TrueType_Horizontal_Header  FTLoad_TrueType_Horizontal_Header
#define Load_TrueType_Locations          FTLoad_TrueType_Locations
#define Load_TrueType_Names              FTLoad_TrueType_Names
#define Load_TrueType_CVT                FTLoad_TrueType_CVT
#define Load_TrueType_CMap               FTLoad_TrueType_CMap
#define Load_TrueType_HMTX               FTLoad_TrueType_HMTX
#define Load_TrueType_Hdmx               FTLoad_TrueType_Hdmx
#define Load_TrueType_Programs           FTLoad_TrueType_Programs
#define Load_TrueType_OS2                FTLoad_TrueType_OS2
#define Load_TrueType_PostScript         FTLoad_TrueType_PostScript

#define Free_TrueType_Names              FTFree_TrueType_Names
#define Free_TrueType_Hdmx               FTFree_TrueType_Hdmx

/* -- ttgload ------------------------------------------------------------ */

#define Load_TrueType_Glyph    FTLoad_TrueType_Glyph

/* -- ttinterp ----------------------------------------------------------- */

#define RunIns       FTRunIns

/* -- ttdebug ------------------------------------------------------------ */

#define Cur_U_Line   FTCur_U_Line

/* -- ttextend ----------------------------------------------------------- */

#define Extension_Create   FTExtension_Create
#define Extension_Destroy  FTExtension_Destroy
#define Extension_Get      FTExtension_Get
#define Extension_Register FTExtension_Register

/* -- ttkern ------------------------------------------------------------- */

#define Kerning_Create     FTKerning_Create
#define Kerning_Destroy    FTKerning_Destroy

#endif /* TT_PREFIX_ALL_NAMES */

#endif /* TTCOMMON_H */


/* END */