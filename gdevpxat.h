/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU Ghostscript.
  
  GNU Ghostscript is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
  anyone for the consequences of using it or for whether it serves any
  particular purpose or works at all, unless he says so in writing.  Refer to
  the GNU General Public License for full details.
  
  Everyone is granted permission to copy, modify and redistribute GNU
  Ghostscript, but only under the conditions described in the GNU General
  Public License.  A copy of this license is supposed to have been given to
  you along with GNU Ghostscript so you can know your rights and
  responsibilities.  It should be in a file named COPYING.  Among other
  things, the copyright notice and this notice must be preserved on all
  copies.
  
  Aladdin Enterprises is not affiliated with the Free Software Foundation or
  the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
  does not depend on any other GNU software.
*/

/* gdevpxat.h */
/* Attribute ID definitions for PCL XL */

#ifndef gdevpxat_INCLUDED
#  define gdevpxat_INCLUDED

typedef enum {

  pxaPaletteDepth = 2,
  pxaColorSpace,
  pxaNullBrush,
  pxaNullPen,
  pxaPaletteData,

  pxaPatternSelectID = 8,
  pxaGrayLevel,

  pxaRGBColor = 11,
  pxaPatternOrigin,
  pxaNewDestinationSize,

  pxaDeviceMatrix = 33,
  pxaDitherMatrixDataType,
  pxaDitherOrigin,
  pxaMediaDestination,
  pxaMediaSize,
  pxaMediaSource,
  pxaMediaType,
  pxaOrientation,
  pxaPageAngle,
  pxaPageOrigin,
  pxaPageScale,
  pxaROP3,
  pxaTxMode,

  pxaCustomMediaSize = 47,
  pxaCustomMediaSizeUnits,
  pxaPageCopies,
  pxaDitherMatrixSize,
  pxaDitherMatrixDepth,
  pxaSimplexPageMode,
  pxaDuplexPageMode,
  pxaDuplexPageSide,

  pxaArcDirection = 65,
  pxaBoundingBox,
  pxaDashOffset,
  pxaEllipseDimension,
  pxaEndPoint,
  pxaFillMode,
  pxaLineCapStyle,
  pxaLineJoinStyle,
  pxaMiterLength,
  pxaLineDashStyle,
  pxaPenWidth,
  pxaPoint,
  pxaNumberOfPoints,
  pxaSolidLine,
  pxaStartPoint,
  pxaPointType,
  pxaControlPoint1,
  pxaControlPoint2,
  pxaClipRegion,
  pxaClipMode,

  pxaColorDepth = 98,
  pxaBlockHeight,
  pxaColorMapping,
  pxaCompressMode,
  pxaDestinationBox,
  pxaDestinationSize,
  pxaPatternPersistence,
  pxaPatternDefineID,

  pxaSourceHeight = 107,
  pxaSourceWidth,
  pxaStartLine,

  pxaNumberOfScanLines = 115,

  pxaCommentData = 129,
  pxaDataOrg,

  pxaMeasure = 134,

  pxaSourceType = 136,
  pxaUnitsPerMeasure,

  pxaStreamName = 139,
  pxaStreamDataLength,

  pxaErrorReport = 143,

  pxaCharAngle = 161,
  pxaCharCode,
  pxaCharDataSize,
  pxaCharScale,
  pxaCharShear,
  pxaCharSize,
  pxaFontHeaderLength,
  pxaFontName,
  pxaFontFormat,
  pxaSymbolSet,
  pxaTextData,
  pxaCharSubModeArray,

  pxaXSpacingData = 175,
  pxaYSpacingData,
  pxaCharBoldValue,

  px_attribute_next

} px_attribute_t;

#endif				/* gdevpxat_INCLUDED */
