/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: gdevpdfe.c,v 1.3 2006/06/16 12:55:03 Arabidopsis Exp $ */
/* Metadata writer. */
#include "gx.h"
#include "string_.h"
#include "time_.h"
#include "stream.h"
#include "gp.h"
#include "smd5.h"
#include "gscdefs.h"
#include "gdevpdfx.h"
#include "gdevpdfg.h"
#include "gdevpdfo.h"
#include "gdevpdtf.h"

/* Write XML data */
private void
pdf_xml_data_write(stream *s, const byte *data, int data_length)
{
    int l = data_length;
    const byte *p = data;

    for (; l--; p++) {
	switch (*p) {
	    case '<' : stream_puts(s, "&lt;"); break;
	    case '>' : stream_puts(s, "&gt;"); break;
	    case '&' : stream_puts(s, "&amp;"); break;
	    case '\'': stream_puts(s, "&apos;"); break;
	    case '"' : stream_puts(s, "&quot;"); break;
	    default:
		if (*p < 32 || *p > 127)
		    pprintd1(s, "&#%d;", *p);
		else
		    stream_putc(s, *p);
	}
    }
}

/* Write XML string */
private inline void
pdf_xml_string_write(stream *s, const char *data)
{
    pdf_xml_data_write(s, (const byte *)data, strlen(data));
}

/* Begin an opening XML tag */
private inline void
pdf_xml_tag_open_beg(stream *s, const char *data)
{
    stream_putc(s, '<');
    stream_puts(s, data);
}

/* End an XML tag */
private inline void
pdf_xml_tag_end(stream *s)
{
    stream_putc(s, '>');
}

/* End an empty XML tag */
private inline void
pdf_xml_tag_end_empty(stream *s)
{
    stream_puts(s, "/>");
}

/* Write an opening XML tag */
private inline void
pdf_xml_tag_open(stream *s, const char *data)
{
    stream_putc(s, '<');
    stream_puts(s, data);
    stream_putc(s, '>');
}

/* Write a closing XML tag */
private inline void
pdf_xml_tag_close(stream *s, const char *data)
{
    stream_puts(s, "</");
    stream_puts(s, data);
    stream_putc(s, '>');
}

/* Write an attribute name */
private inline void
pdf_xml_attribute_name(stream *s, const char *data)
{
    stream_putc(s, ' ');
    stream_puts(s, data);
    stream_putc(s, '=');
}

/* Write a attribute value */
private inline void
pdf_xml_attribute_value(stream *s, const char *data)
{
    stream_putc(s, '\'');
    pdf_xml_string_write(s, data);
    stream_putc(s, '\'');
}
/* Write a attribute value */
private inline void
pdf_xml_attribute_value_data(stream *s, const byte *data, int data_length)
{
    stream_putc(s, '\'');
    pdf_xml_data_write(s, data, data_length);
    stream_putc(s, '\'');
}

/* Begin an  XML instruction */
private inline void
pdf_xml_ins_beg(stream *s, const char *data)
{
    stream_puts(s, "<?");
    stream_puts(s, data);
}

/* End an XML instruction */
private inline void
pdf_xml_ins_end(stream *s)
{
    stream_puts(s, "?>");
}

/* Write a newline character */
private inline void
pdf_xml_newline(stream *s)
{
    stream_puts(s, "\n");
}

/* Copy to XML output */
private inline void
pdf_xml_copy(stream *s, const char *data)
{
    stream_puts(s, data);
}


/* --------------------------------------------  */

private void
pdf_xmp_time(char *buf, int buf_length)
{
    /* We don't write a day time because we don't have a time zone. */
    struct tm tms;
    time_t t;
    char buf1[4+1+2+1+2+1]; /* yyyy-mm-dd\0 */

    time(&t);
    tms = *localtime(&t);
    sprintf(buf1,
	    "%04d-%02d-%02d",
	    tms.tm_year + 1900, tms.tm_mon + 1, tms.tm_mday);
    strncpy(buf, buf1, buf_length);
}

private void
pdf_xmp_write_docinfo_item(gx_device_pdf *pdev, stream *s, const char *key, const char *default_value,
			   void(*write)(stream *s, const byte *data, int data_length))
{
    const cos_value_t *v = cos_dict_find(pdev->Info, (const byte *)key, strlen(key));

    if (v != NULL && (v->value_type == COS_VALUE_SCALAR || 
			v->value_type == COS_VALUE_CONST)) {
	if (v->contents.chars.size > 2 && v->contents.chars.data[0] == '(')
	    write(s, v->contents.chars.data + 1, v->contents.chars.size - 2);
	else
	    write(s, v->contents.chars.data, v->contents.chars.size);
    } else 
	stream_puts(s, default_value);
}

private uint64_t
pdf_uuid_time(gx_device_pdf *pdev)
{   
    long *dt = pdev->uuid_time; /* In seconds since Jan. 1, 1980 and fraction in nanoseconds. */
    uint64_t t;

    /* UUIDs use time in 100ns ticks since Oct 15, 1582. */
    t = (uint64_t)10000000 * dt[0] + dt[0] / 100; /* since Jan. 1, 1980 */
    t += (uint64_t) (1000*1000*10)         /* seconds */
       * (uint64_t) (60 * 60 * 24)         /* days */
       * (uint64_t) (17+30+31+365*397+99); /* # of days */
    return t;
}

private void writehex(char **p, ulong v, int l)
{
    int i = l * 2;
    static const char digit[] = "0123456789abcdef";

    for (; i--;)
	*((*p)++) = digit[v >> (i * 4) & 15];
}

private void
pdf_make_uuid(const byte node[6], uint64_t uuid_time, ulong time_seq, char *buf, int buf_length)
{   
    char b[40], *p = b;
    ulong  uuid_time_lo = (ulong)(uuid_time & 0xFFFFFFFF);       /* MSVC 7.1.3088           */
    ushort uuid_time_md = (ushort)((uuid_time >> 32) & 0xFFFF);  /* cannot compile this     */
    ushort uuid_time_hi = (ushort)((uuid_time >> 48) & 0x0FFF);  /* as function arguments.  */

    writehex(&p, uuid_time_lo, 4); /* time_low */
    *(p++) = '-';
    writehex(&p, uuid_time_md, 2); /* time_mid */
    *(p++) = '-';
    writehex(&p, uuid_time_hi | (ushort)(1 << 12), 2); /* time_hi_and_version */
    *(p++) = '-';
    writehex(&p, (time_seq & 0x3F00) >> 8, 1); /* clock_seq_hi_and_reserved */
    writehex(&p, time_seq & 0xFF, 1); /* clock_seq & 0xFF */
    *(p++) = '-';
    writehex(&p, node[0], 1);
    writehex(&p, node[1], 1);
    writehex(&p, node[2], 1);
    writehex(&p, node[3], 1);
    writehex(&p, node[4], 1);
    writehex(&p, node[5], 1);
    *p = 0;
    strncpy(buf, b, buf_length);
}

private int
pdf_make_instance_uuid(gx_device_pdf *pdev, const byte digest[6], char *buf, int buf_length)
{
    if (pdev->InstanceUUID.size) {
	int l = min(buf_length - 1, pdev->InstanceUUID.size);

	memcpy(buf, pdev->InstanceUUID.data, l);
	buf[l] = 0;
    } else
	pdf_make_uuid(digest, pdf_uuid_time(pdev), pdev->DocumentTimeSeq, buf, buf_length);
    return 0;
}

private int
pdf_make_document_uuid(gx_device_pdf *pdev, const byte digest[6], char *buf, int buf_length)
{
    if (pdev->DocumentUUID.size) {
	int l = min(buf_length - 1, pdev->DocumentUUID.size);

	memcpy(buf, pdev->DocumentUUID.data, l);
	buf[l] = 0;
    } else
	pdf_make_uuid(digest, pdf_uuid_time(pdev), pdev->DocumentTimeSeq, buf, buf_length);
    return 0;
}

private char dd[]={'\'', 0xEF, 0xBB, 0xBF, '\'', 0};

/* --------------------------------------------  */

/* Write Document metadata */
private int
pdf_write_document_metadata(gx_device_pdf *pdev, const byte digest[6])
{
    char instance_uuid[40], document_uuid[40], date_time[40];
    int code;
    stream *s = pdev->strm;

    code = pdf_make_instance_uuid(pdev, digest, instance_uuid, sizeof(instance_uuid));
    if (code < 0)
	return code;
    code = pdf_make_document_uuid(pdev, digest, document_uuid, sizeof(document_uuid));
    if (code < 0)
	return code;
    pdf_xmp_time(date_time, sizeof(date_time));
    pdf_xml_ins_beg(s, "xpacket");
    pdf_xml_attribute_name(s, "begin");
    pdf_xml_copy(s, dd);
    pdf_xml_attribute_name(s, "id");
    pdf_xml_attribute_value(s, "W5M0MpCehiHzreSzNTczkc9d");
    pdf_xml_ins_end(s);
    pdf_xml_newline(s);

    pdf_xml_copy(s, "<?adobe-xap-filters esc=\"CRLF\"?>\n");
    pdf_xml_copy(s, "<x:xmpmeta xmlns:x='adobe:ns:meta/'"
	                      " x:xmptk='XMP toolkit 2.9.1-13, framework 1.6'>\n");
    {
	pdf_xml_copy(s, "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
	                         "xmlns:iX='http://ns.adobe.com/iX/1.0/'>\n");
	{

    	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:pdf");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/pdf/1.3/");
	    pdf_xml_attribute_name(s, "pdf:Producer");
	    pdf_xmp_write_docinfo_item(pdev, s,  "/Producer", "UnknownProduicer",
			pdf_xml_attribute_value_data);
	    pdf_xml_tag_end_empty(s);
	    pdf_xml_newline(s);

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xap");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/");
	    pdf_xml_attribute_name(s, "xap:ModifyDate");
	    pdf_xml_attribute_value(s, date_time);
	    pdf_xml_attribute_name(s, "xap:CreateDate");
	    pdf_xml_attribute_value(s, date_time);
	    pdf_xml_tag_end(s);
	    {
		pdf_xml_tag_open_beg(s, "xap:CreatorTool");
		pdf_xml_tag_end(s);
		{
		    char buf[10];

		    sprintf(buf, "%d.%02d", (int)(gs_revision / 100), (int)(gs_revision % 100));
		    pdf_xml_string_write(s, gs_product);
		    pdf_xml_string_write(s, " ");
		    pdf_xml_string_write(s, buf);
		    pdf_xml_string_write(s, " PDF Writer");
		}
		pdf_xml_tag_close(s, "xap:CreatorTool");
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xapMM");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/mm/");
	    pdf_xml_attribute_name(s, "xapMM:DocumentID");
	    pdf_xml_attribute_value(s, document_uuid);
	    pdf_xml_tag_end_empty(s);
	    pdf_xml_newline(s);

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:dc");
	    pdf_xml_attribute_value(s, "http://purl.org/dc/elements/1.1/");
	    pdf_xml_attribute_name(s, "dc:format");
	    pdf_xml_attribute_value(s,"application/pdf");
	    pdf_xml_tag_end(s);
	    {
		pdf_xml_tag_open(s, "dc:title");
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xmp_write_docinfo_item(pdev, s,  "/Title", "Untitled", 
				    pdf_xml_data_write);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "dc:title");

		if (cos_dict_find(pdev->Info, (const byte *)"/Author", 7)) {
		    pdf_xml_tag_open(s, "dc:creator");
		    {   /* According to the PDF/A specification
			   "it shall be represented by an ordered Text array of
			   length one whose single entry shall consist 
			   of one or more names". */
			pdf_xml_tag_open(s, "rdf:Seq");
			{
			    pdf_xml_tag_open(s, "rdf:li");
			    {
    				pdf_xmp_write_docinfo_item(pdev, s,  "/Author", "Unknown", 
					    pdf_xml_data_write);
			    }
			    pdf_xml_tag_close(s, "rdf:li");
			}
			pdf_xml_tag_close(s, "rdf:Seq");
		    }
		    pdf_xml_tag_close(s, "dc:creator");
		}
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);
	}
	pdf_xml_copy(s, "</rdf:RDF>\n");
    }
    pdf_xml_copy(s, "</x:xmpmeta>\n");

    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "<?xpacket end='w'?>");
    return 0;
}

int
pdf_document_metadata(gx_device_pdf *pdev)
{   
    if (pdev->CompatibilityLevel < 1.4)
	return 0;
    if (pdev->ParseDSCCommentsForDocInfo || pdev->PreserveEPSInfo) {
	pdf_resource_t *pres;
	char buf[20];
	byte digest[6];
	int code;
	int options = DATA_STREAM_NOT_BINARY;

	sflush(pdev->strm);
	s_MD5C_get_digest(pdev->strm, digest, sizeof(digest));
	if (pdev->EncryptMetadata)
	    options |= DATA_STREAM_ENCRYPT;
	code = pdf_open_aside(pdev, resourceOther, gs_no_id, &pres, true, options);
	if (code < 0)
	    return code;
	code = pdf_write_document_metadata(pdev, digest);
	if (code < 0)
	    return code;
	code = pdf_close_aside(pdev);
	if (code < 0)
	    return code;
	code = COS_WRITE_OBJECT(pres->object, pdev);
	if (code < 0)
	    return code;
	sprintf(buf, "%ld 0 R", pres->object->id);
	cos_dict_put_c_key_object(pdev->Catalog, "/Metadata", pres->object);
    }
    return 0;
}

/* --------------------------------------------  */

/* Write Font metadata */
private int
pdf_write_font_metadata(gx_device_pdf *pdev, const pdf_base_font_t *pbfont, 
			const byte *digest, int digest_length)
{
    char instance_uuid[40];
    int code;
    stream *s = pdev->strm;
    gs_font_info_t info;
    gs_font_base *pfont = pbfont->complete;

    if (pfont == NULL)
	pfont = pbfont->copied;
    /* Fixme: For True Type fonts need to get Coipyright, Owner from the TT data. */
    pdf_make_uuid(digest, pdf_uuid_time(pdev), pdev->DocumentTimeSeq, instance_uuid, sizeof(instance_uuid));
    code = pfont->procs.font_info((gs_font *)pfont, NULL,
		    (FONT_INFO_COPYRIGHT | FONT_INFO_NOTICE |
			FONT_INFO_FAMILY_NAME | FONT_INFO_FULL_NAME),
					&info);
    if (code < 0)
	return code;
    pdf_xml_ins_beg(s, "xpacket");
    pdf_xml_attribute_name(s, "begin");
    pdf_xml_copy(s, dd);
    pdf_xml_attribute_name(s, "id");
    pdf_xml_attribute_value(s, "W5M0MpCehiHzreSzNTczkc9d");
    pdf_xml_ins_end(s);
    pdf_xml_newline(s);

    pdf_xml_copy(s, "<?adobe-xap-filters esc=\"CRLF\"?>\n");
    pdf_xml_copy(s, "<x:xmpmeta xmlns:x='adobe:ns:meta/'"
	                      " x:xmptk='XMP toolkit 2.9.1-13, framework 1.6'>\n");
    {
	pdf_xml_copy(s, "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
	                         "xmlns:iX='http://ns.adobe.com/iX/1.0/'>\n");
	{

	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xmp");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/");
	    pdf_xml_tag_end(s);
	    {
		pdf_xml_tag_open_beg(s, "xmp:Title");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, pbfont->font_name.data, pbfont->font_name.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmp:Title");
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);


	    pdf_xml_tag_open_beg(s, "rdf:Description");
	    pdf_xml_attribute_name(s, "rdf:about");
	    pdf_xml_attribute_value(s, instance_uuid);
	    pdf_xml_attribute_name(s, "xmlns:xmpRights");
	    pdf_xml_attribute_value(s, "http://ns.adobe.com/xap/1.0/rights/");
	    pdf_xml_tag_end(s);
	    if (info.members & FONT_INFO_COPYRIGHT) {
		pdf_xml_tag_open_beg(s, "xmpRights:Copyright");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, info.Copyright.data, info.Copyright.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmpRights:Copyright");

		/* Don't have an Owner, write Copyright instead. */
		pdf_xml_tag_open_beg(s, "xmpRights:Owner");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, info.Copyright.data, info.Copyright.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmpRights:Owner");
	    }
	    {
		pdf_xml_tag_open_beg(s, "xmpRights:Marked");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_string_write(s, "True");
		}
		pdf_xml_tag_close(s, "xmpRights:Marked");
	    }
	    if (info.members & FONT_INFO_NOTICE) {
		pdf_xml_tag_open_beg(s, "xmpRights:UsageTerms");
		pdf_xml_tag_end(s);
		{
		    pdf_xml_tag_open(s, "rdf:Alt");
		    {
			pdf_xml_tag_open_beg(s, "rdf:li");
			pdf_xml_attribute_name(s, "xml:lang");
			pdf_xml_attribute_value(s, "x-default");
			pdf_xml_tag_end(s);
			{
			   pdf_xml_data_write(s, info.Notice.data, info.Notice.size);
			}
			pdf_xml_tag_close(s, "rdf:li");
		    }
		    pdf_xml_tag_close(s, "rdf:Alt");
		}
		pdf_xml_tag_close(s, "xmpRights:UsageTerms");
	    }
	    pdf_xml_tag_close(s, "rdf:Description");
	    pdf_xml_newline(s);
	}
	pdf_xml_copy(s, "</rdf:RDF>\n");
    }
    pdf_xml_copy(s, "</x:xmpmeta>\n");

    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "                                                                        \n");
    pdf_xml_copy(s, "<?xpacket end='w'?>");
    return 0;
}

int
pdf_font_metadata(gx_device_pdf *pdev, const pdf_base_font_t *pbfont, 
		  const byte *digest, int digest_length, gs_id *metadata_object_id)
{  
    *metadata_object_id = gs_no_id;
    if (pdev->CompatibilityLevel < 1.4)
	return 0;
    /* The PDF/A specification redss about 
	"embedded Type 0, Type 1, or TrueType font programs",
	but we believe that "embedded Type 0 font programs"
	do not exist.
	We create Metadata for Type 1,2,42,9,11.
    */
    if (pdev->PDFA) {
	pdf_resource_t *pres;
	byte digest[6];
	int code;
	int options = DATA_STREAM_NOT_BINARY;

	sflush(pdev->strm);
	s_MD5C_get_digest(pdev->strm, digest, sizeof(digest));
	if (pdev->EncryptMetadata)
	    options |= DATA_STREAM_ENCRYPT;
	code = pdf_open_aside(pdev, resourceOther, gs_no_id, &pres, true, options);
	if (code < 0)
	    return code;
	code = pdf_write_font_metadata(pdev, pbfont, digest, digest_length);
	if (code < 0)
	    return code;
	code = pdf_close_aside(pdev);
	if (code < 0)
	    return code;
	code = COS_WRITE_OBJECT(pres->object, pdev);
	if (code < 0)
	    return code;
	*metadata_object_id = pres->object->id;
    }
    return 0;
}
  
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

/*$Id: gdevpdfe.c,v 1.3 2006/06/16 12:55:03 Arabidopsis Exp $ */
/* Embedded font writing for pdfwrite driver. */
#include "memory_.h"
#include "string_.h"
#include "gx.h"
#include "gserrors.h"
#include "gsmatrix.h"
#include "gxfcid.h"
#include "gxfont.h"
#include "gxfont0.h"
#include "gdevpdfx.h"
#include "gdevpdff.h"
#include "gdevpsf.h"
#include "scommon.h"

/* ---------------- Utilities ---------------- */

/* Begin writing FontFile* data. */
private int
pdf_begin_fontfile(gx_device_pdf *pdev, long FontFile_id,
		   const char *entries, long len1, pdf_data_writer_t *pdw)
{
    stream *s;

    pdf_open_separate(pdev, FontFile_id);
    s = pdev->strm;
    stream_puts(s, "<<");
    if (entries)
	stream_puts(pdev->strm, entries);
    if (len1 >= 0)
	pprintld1(pdev->strm, "/Length1 %ld", len1);
    return pdf_begin_data(pdev, pdw);
}

/* Finish writing FontFile* data. */
private int
pdf_end_fontfile(gx_device_pdf *pdev, pdf_data_writer_t *pdw)
{
    return pdf_end_data(pdw);
}

/* ---------------- Individual font types ---------------- */

/* ------ Type 1 family ------ */

/*
 * Acrobat Reader apparently doesn't accept CFF fonts with Type 1
 * CharStrings, so we need to convert them.  Also remove lenIV,
 * so Type 2 fonts will compress better.
 */
#define TYPE2_OPTIONS (WRITE_TYPE2_NO_LENIV | WRITE_TYPE2_CHARSTRINGS)

/* Write the FontFile[3] data for an embedded Type 1, Type 2, or */
/* CIDFontType 0 font. */
private int
pdf_embed_font_as_type1(gx_device_pdf *pdev, gs_font_type1 *font,
			long FontFile_id, gs_glyph subset_glyphs[256],
			uint subset_size, const gs_const_string *pfname)
{
    stream poss;
    int lengths[3];
    int code;
    pdf_data_writer_t writer;
#define MAX_INT_CHARS ((sizeof(int) * 8 + 2) / 3)
    char lengths_str[9 + MAX_INT_CHARS + 11];  /* /Length2 %d/Length3 0\0 */
#undef MAX_INT_CHARS

    swrite_position_only(&poss);
    /*
     * We omit the 512 zeros and the cleartomark, and set Length3 to 0.
     * Note that the interpreter adds them implicitly (per documentation),
     * so we must set MARK so that the encrypted portion pushes a mark on
     * the stack.
     *
     * NOTE: the options were set to 0 in the first checked-in version of
     * this file.  We can't explain this: Acrobat Reader requires eexec
     * encryption, so the code can't possibly have worked.
     *
     * Acrobat Reader 3 allows lenIV = -1 in Type 1 fonts, but Acrobat
     * Reader 4 doesn't.  Therefore, we can't allow it.
     */
#define TYPE1_OPTIONS (WRITE_TYPE1_EEXEC | WRITE_TYPE1_EEXEC_MARK |\
		       WRITE_TYPE1_WITH_LENIV)
    code = psf_write_type1_font(&poss, font, TYPE1_OPTIONS,
				 subset_glyphs, subset_size, pfname, lengths);
    if (code < 0)
	return code;
    sprintf(lengths_str, "/Length2 %d/Length3 0", lengths[1]);
    code = pdf_begin_fontfile(pdev, FontFile_id, lengths_str, lengths[0],
			      &writer);
    if (code < 0)
	return code;
    code = psf_write_type1_font(writer.binary.strm, font, TYPE1_OPTIONS,
				subset_glyphs, subset_size, pfname,
				lengths /*ignored*/);
#undef TYPE1_OPTIONS
    pdf_end_fontfile(pdev, &writer);
    return code;
}

/* Embed a font as Type 2. */
private int
pdf_embed_font_as_type2(gx_device_pdf *pdev, gs_font_type1 *font,
			long FontFile_id, gs_glyph subset_glyphs[256],
			uint subset_size, const gs_const_string *pfname,
			gs_int_rect *FontBBox)
{
    int code;
    pdf_data_writer_t writer;
    int options = TYPE2_OPTIONS |
	(pdev->CompatibilityLevel < 1.3 ? WRITE_TYPE2_AR3 : 0);

    code = pdf_begin_fontfile(pdev, FontFile_id, "/Subtype/Type1C", -1L,
			      &writer);
    if (code < 0)
	return code;
    code = psf_write_type2_font(writer.binary.strm, font, options,
				subset_glyphs, subset_size, pfname,
				FontBBox);
    pdf_end_fontfile(pdev, &writer);
    return code;
}

/* Embed a Type 1 or Type 2 font. */
private int
pdf_embed_font_type1(gx_device_pdf *pdev, gs_font_type1 *font,
		     long FontFile_id, gs_glyph subset_glyphs[256],
		     uint subset_size, const gs_const_string *pfname,
		     gs_int_rect *FontBBox)
{
    switch (((const gs_font *)font)->FontType) {
    case ft_encrypted:
	if (pdev->CompatibilityLevel < 1.2)
	    return pdf_embed_font_as_type1(pdev, font, FontFile_id,
					   subset_glyphs, subset_size, pfname);
	/* For PDF 1.2 and later, write Type 1 fonts as Type1C. */
    case ft_encrypted2:
	return pdf_embed_font_as_type2(pdev, font, FontFile_id,
			       subset_glyphs, subset_size, pfname, FontBBox);
    default:
	return_error(gs_error_rangecheck);
    }
}

/* Embed a CIDFontType0 font. */
private int
pdf_embed_font_cid0(gx_device_pdf *pdev, gs_font_cid0 *font,
		    long FontFile_id, const byte *subset_cids,
		    uint subset_size, const gs_const_string *pfname)
{
    int code;
    pdf_data_writer_t writer;

    if (pdev->CompatibilityLevel < 1.2)
	return_error(gs_error_rangecheck);
    code = pdf_begin_fontfile(pdev, FontFile_id, "/Subtype/CIDFontType0C", -1L,
			      &writer);
    if (code < 0)
	return code;
    code = psf_write_cid0_font(writer.binary.strm, font, TYPE2_OPTIONS,
			       subset_cids, subset_size, pfname);
    pdf_end_fontfile(pdev, &writer);
    return code;
}

/* ------ TrueType family ------ */

/* Embed a TrueType font. */
private int
pdf_embed_font_type42(gx_device_pdf *pdev, gs_font_type42 *font,
		      long FontFile_id, gs_glyph subset_glyphs[256],
		      uint subset_size, const gs_const_string *pfname)
{
    /* Acrobat Reader 3 doesn't handle cmap format 6 correctly. */
    const int options = WRITE_TRUETYPE_CMAP | WRITE_TRUETYPE_NAME |
	(pdev->CompatibilityLevel <= 1.2 ?
	 WRITE_TRUETYPE_NO_TRIMMED_TABLE : 0);
    stream poss;
    int code;
    pdf_data_writer_t writer;

    swrite_position_only(&poss);
    code = psf_write_truetype_font(&poss, font, options,
				   subset_glyphs, subset_size, pfname);
    if (code < 0)
	return code;
    code = pdf_begin_fontfile(pdev, FontFile_id, NULL, stell(&poss), &writer);
    if (code < 0)
	return code;
    psf_write_truetype_font(writer.binary.strm, font, options,
			    subset_glyphs, subset_size, pfname);
    pdf_end_fontfile(pdev, &writer);
    return 0;
}

/* Embed a CIDFontType2 font. */
private int
pdf_embed_font_cid2(gx_device_pdf *pdev, gs_font_cid2 *font,
		    long FontFile_id, const byte *subset_bits,
		    uint subset_size, const gs_const_string *pfname)
{
    /* CIDFontType 2 fonts don't use cmap, name, OS/2, or post. */
#define OPTIONS 0
    int code;
    pdf_data_writer_t writer;

    code = pdf_begin_fontfile(pdev, FontFile_id, NULL, -1L, &writer);
    if (code < 0)
	return code;
    psf_write_cid2_font(writer.binary.strm, font, OPTIONS,
			subset_bits, subset_size, pfname);
#undef OPTIONS
    pdf_end_fontfile(pdev, &writer);
    return 0;
}

/* ---------------- Entry point ---------------- */

/*
 * Write the FontDescriptor and FontFile* data for an embedded font.
 * Return a rangecheck error if the font can't be embedded.
 */
int
pdf_write_embedded_font(gx_device_pdf *pdev, pdf_font_descriptor_t *pfd)
{
    gs_font *font = pfd->base_font;
    gs_const_string font_name;
    byte *fnchars = pfd->FontName.chars;
    uint fnsize = pfd->FontName.size;
    bool do_subset;
    long FontFile_id = pfd->FontFile_id;
    gs_glyph subset_glyphs[256];
    gs_glyph *subset_list = 0;	/* for non-CID fonts */
    byte *subset_bits = 0;	/* for CID fonts */
    uint subset_size = 0;
    gs_matrix save_mat;
    int code;

    /* Determine whether to subset the font. */
    switch (pfd->do_subset) {
    case FONT_SUBSET_OK:
	do_subset = pdev->params.SubsetFonts && pdev->params.MaxSubsetPct > 0;
	break;
    case FONT_SUBSET_YES:
	do_subset = true;
	break;
    case FONT_SUBSET_NO:
	do_subset = false;
	break;
    }
    if (do_subset) {
	int max_pct = pdev->params.MaxSubsetPct;
	int used, i;

	for (i = 0, used = 0; i < pfd->chars_used.size; ++i)
	    used += byte_count_bits[pfd->chars_used.data[i]];
	/*
	 * We want to subset iff used / total <= MaxSubsetPct / 100, i.e.,
	 * iff total >= used * 100 / MaxSubsetPct.  This observation
	 * allows us to stop the enumeration loop early.
	 */
	if (max_pct < 100) {
	    do_subset = false;
	    if (max_pct > 0) {
		int max_total = used * 100 / max_pct;
		int index, total;
		gs_glyph ignore_glyph;

		for (index = 0, total = 0;
		     (font->procs.enumerate_glyph(font, &index,
						  GLYPH_SPACE_INDEX,
						  &ignore_glyph), index != 0);
		     )
		    if (++total >= max_total) {
			do_subset = true;
			break;
		    }
	    }
	}
    }

    /* Generate an appropriate font name. */
    if (pdf_has_subset_prefix(fnchars, fnsize)) {
	/* Strip off any existing subset prefix. */
	fnsize -= SUBSET_PREFIX_SIZE;
	memmove(fnchars, fnchars + SUBSET_PREFIX_SIZE, fnsize);
    }
    if (do_subset) {
	memmove(fnchars + SUBSET_PREFIX_SIZE, fnchars, fnsize);
	pdf_make_subset_prefix(pdev, fnchars, FontFile_id);
	fnsize += SUBSET_PREFIX_SIZE;
    }
    font_name.data = fnchars;
    font_name.size = pfd->FontName.size = fnsize;
    code = pdf_write_FontDescriptor(pdev, pfd);
    if (code >= 0) {
	pfd->written = true;

	/*
	 * Finally, write the font (or subset), using the original
	 * (unscaled) FontMatrix.
	 */
	save_mat = font->FontMatrix;
	font->FontMatrix = pfd->orig_matrix;
	switch (font->FontType) {
	case ft_composite:
	    /* Nothing to embed -- the descendant fonts do it all. */
	    break;
	case ft_encrypted:
	case ft_encrypted2:
	    if (do_subset) {
		subset_size = psf_subset_glyphs(subset_glyphs, font,
						pfd->chars_used.data);
		subset_list = subset_glyphs;
	    }
	    code = pdf_embed_font_type1(pdev, (gs_font_type1 *)font,
					FontFile_id, subset_list,
					subset_size, &font_name, 
					&pfd->values.FontBBox);
	    break;
	case ft_TrueType:
	    if (do_subset) {
		subset_size = psf_subset_glyphs(subset_glyphs, font,
						pfd->chars_used.data);
		subset_list = subset_glyphs;
	    }
	    code = pdf_embed_font_type42(pdev, (gs_font_type42 *)font,
					 FontFile_id, subset_list,
					 subset_size, &font_name);
	    break;
	case ft_CID_encrypted:
	    if (do_subset) {
		subset_size = pfd->chars_used.size << 3;
		subset_bits = pfd->chars_used.data;
	    }
	    code = pdf_embed_font_cid0(pdev, (gs_font_cid0 *)font,
				       FontFile_id, subset_bits,
				       subset_size, &font_name);
	    break;
	case ft_CID_TrueType:
	    if (do_subset) {
		/*
		 * Note that the subset mask for CIDFontType 2 fonts is
		 * indexed by the TrueType glyph number, not the CID.
		 */
		subset_size = pfd->glyphs_used.size << 3;
		subset_bits = pfd->glyphs_used.data;
	    }
	    code = pdf_embed_font_cid2(pdev, (gs_font_cid2 *)font,
				       FontFile_id, subset_bits,
				       subset_size, &font_name);
	    break;
	default:
	    code = gs_note_error(gs_error_rangecheck);
	}
	font->FontMatrix = save_mat;
    }
    return code;
}
