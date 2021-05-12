//===========================================================================
//
//	Module:	LNRTTYPE.HPP
//
//	Description
//
//		Class library declaration for class LNRichTextType and its types
//
//===========================================================================
//
// Copyright (c) 1997-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNRTTYPE_HPP
#define LNRTTYPE_HPP


enum LNRTTYPE
{
	LNRTTYPE_UNDEFINED	= 0,
	LNRTTYPE_OBJECT,	
	LNRTTYPE_ELEMENT,
	LNRTTYPE_COMPOSITE_DATA,
	LNRTTYPE_COMPOSITE_CONTAINER,
	LNRTTYPE_CHAR,
	LNRTTYPE_CONTAINER,
	LNRTTYPE_STYLIZED_TEXT,
	LNRTTYPE_GRAPHIC,
	LNRTTYPE_METAFILE,
	LNRTTYPE_PM_METAFILE,
	LNRTTYPE_PM_METAFILE_SEGMENT,
	LNRTTYPE_WIN_METAFILE,
	LNRTTYPE_WIN_METAFILE_SEGMENT,
	LNRTTYPE_MAC_METAFILE,
	LNRTTYPE_MAC_METAFILE_SEGMENT,
	LNRTTYPE_CGM_METAFILE,
	LNRTTYPE_BITMAP,
	LNRTTYPE_BITMAP_SEGMENT,
	LNRTTYPE_BITMAP_COLOR_TABLE,
	LNRTTYPE_BITMAP_PATTERN_TABLE,
	LNRTTYPE_BITMAP_TRANSPARENCY_TABLE,
	LNRTTYPE_EMBEDDED_OBJECT,
	LNRTTYPE_ATTACHMENT,
	LNRTTYPE_HOTSPOT,
	LNRTTYPE_RESOURCE_LINK,
	LNRTTYPE_LINK_HOTSPOT,
    LNRTTYPE_URL_LINK,
	LNRTTYPE_TEXT_POPUP,
	LNRTTYPE_FORMULA_POPUP,
	LNRTTYPE_ACTION_HOTSPOT,
	LNRTTYPE_BUTTON,
	LNRTTYPE_SECTION,
	LNRTTYPE_NEW_PARAGRAPH,
	LNRTTYPE_ITEM,
	LNRTTYPE_TABLE,
	LNRTTYPE_TABLE_CELL,
	LNRTTYPE_LINK,
	LNRTTYPE_DATABASE_LINK,
	LNRTTYPE_VIEW_LINK,
	LNRTTYPE_DOCUMENT_LINK,
	LNRTTYPE_ANCHOR_LINK,
	LNRTTYPE_ANCHOR_LOCATION,
	LNRTTYPE_FORM_FIELD,
	LNRTTYPE_TEXT_FIELD,
	LNRTTYPE_TIME_FIELD,
	LNRTTYPE_NUMBER_FIELD,
	LNRTTYPE_KEYWORDS_FIELD,
	LNRTTYPE_RICH_TEXT_FIELD,
	LNRTTYPE_FORMULA_FIELD,
	LNRTTYPE_PASSWORD_FIELD,
	LNRTTYPE_NAMES_FIELD,
	LNRTTYPE_AUTHORS_FIELD,
	LNRTTYPE_READERS_FIELD,
	LNRTTYPE_SUBFORM,
	LNRTTYPE_COMPUTED_SUBFORM,
	LNRTTYPE_OLE_OBJECT,
	LNRTTYPE_ACTIVE_OBJECT,
	LNRTTYPE_JAVA_APPLET,
	LNRTTYPE_NO_MORE
};


#endif
