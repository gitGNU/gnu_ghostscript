/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxttf.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Table definitions for TrueType fonts */

#ifndef gxttf_INCLUDED
#  define gxttf_INCLUDED

/* ------ head ------ */

typedef struct ttf_head_s {
    byte
	version[4],		/* version 1.0 */
	fontRevision[4],
	checkSumAdjustment[4],
	magicNumber[4],
	flags[2],
	unitsPerEm[2],
	created[8],
	modified[8],
	xMin[2],
	yMin[2],
	xMax[2],
	yMax[2],
	macStyle[2],
	lowestRecPPM[2],
	fontDirectionHint[2],
	indexToLocFormat[2],
	glyphDataFormat[2];
} ttf_head_t;

/* ------ hhea ------ */

typedef struct ttf_hhea_s {
    byte
	version[4],		/* version 1.0 */
	ascender[2],		/* FWord */
	descender[2],		/* FWord */
	lineGap[2],		/* FWord */
	advanceWidthMax[2],	/* uFWord */
	minLeftSideBearing[2],	/* FWord */
	minRightSideBearing[2],	/* FWord */
	xMaxExtent[2],		/* FWord */
	caretSlopeRise[2],
	caretSlopeRun[2],
	caretOffset[2],
	reserved[8],
	metricDataFormat[2],	/* 0 */
	numHMetrics[2];
} ttf_hhea_t;

/* ------ hmtx ------ */

typedef struct longHorMetric_s {
    byte
	advanceWidth[2],	/* uFWord */
	lsb[2];			/* FWord */
} longHorMetric_t;

/* ------ maxp ------ */

typedef struct ttf_maxp_s {
    byte
	version[2],		/* 1.0 */
	numGlyphs[2],
	maxPoints[2],
	maxContours[2],
	maxCompositePoints[2],
	maxCompositeContours[2],
	maxZones[2],
	maxTwilightPoints[2],
	maxStorage[2],
	maxFunctionDefs[2],
	maxInstructionDefs[2],
	maxStackElements[2],
	maxSizeOfInstructions[2],
	maxComponentElements[2],
	maxComponentDepth[2];
} ttf_maxp_t;

/* ------ OS/2 ------ */

typedef struct ttf_OS_2_s {
    byte
	version[2],		/* version 1 */
	xAvgCharWidth[2],
	usWeightClass[2],
	usWidthClass[2],
	fsType[2],
	ySubscriptXSize[2],
	ySubscriptYSize[2],
	ySubscriptXOffset[2],
	ySubscriptYOffset[2],
	ySuperscriptXSize[2],
	ySuperscriptYSize[2],
	ySuperscriptXOffset[2],
	ySuperscriptYOffset[2],
	yStrikeoutSize[2],
	yStrikeoutPosition[2],
	sFamilyClass[2],
	/*panose:*/
	    bFamilyType, bSerifStyle, bWeight, bProportion, bContrast,
	    bStrokeVariation, bArmStyle, bLetterform, bMidline, bXHeight,
	ulUnicodeRanges[16],
	achVendID[4],
	fsSelection[2],
	usFirstCharIndex[2],
	usLastCharIndex[2],
	sTypoAscender[2],
	sTypoDescender[2],
	sTypoLineGap[2],
	usWinAscent[2],
	usWinDescent[2],
	ulCodePageRanges[8];
} ttf_OS_2_t;

/* ------ vhea ------ */

typedef struct ttf_vhea_s {
    byte
	version[4],		/* version 1.0 */
	ascent[2],		/* FWord */
	descent[2],		/* FWord */
	lineGap[2],		/* FWord */
	advanceHeightMax[2],	/* uFWord */
	minTopSideBearing[2],	/* FWord */
	minBottomSideBearing[2],  /* FWord */
	yMaxExtent[2],		/* FWord */
	caretSlopeRise[2],
	caretSlopeRun[2],
	caretOffset[2],
	reserved[8],
	metricDataFormat[2],	/* 0 */
	numVMetrics[2];
} ttf_vhea_t;

/* ------ vmtx ------ */

typedef struct longVerMetric_s {
    byte
	advanceHeight[2],	/* uFWord */
	topSideBearing[2];	/* FWord */
} longVerMetric_t;

#endif /* gxttf_INCLUDED */
