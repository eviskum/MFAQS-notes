//===========================================================================
//
// Module:		LNFRMST.HPP
//
// Description:
//
//		Class library definition for the LNFrameset and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNFRMST_HPP
#define LNFRMST_HPP

//
//	Class definition for LNFrameset.
//
class LNIMPEXPCL LNFrameset : public LNNote
{
public:
    LNBOOL GetAllowDesignRefreshToModify () const;
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNFRAMESET;}
	LNString GetComment() const;
	LNBOOL GetHideFromBrowsers() const;
	LNBOOL GetHideFromClients() const;
	LNSTATUS GetHTMLTags(LNHTMLTags *tags) const;

    LNString GetInheritsFromTemplateName () const;
	LNSTATUS GetFrame( const LNString &framename, LNFrame *frame) const;
	LNINT GetFrameCount() const;
    LNBOOL GetPropagateAllowDesignChange () const;
	LNSTATUS GetWindowTitleFormula(LNFormula *formula) const;
	LNFrameset();
	LNFrameset( const LNFrameset &other );
	LNFrameset( const LNNote &other );
	LNSTATUS SetAlias(const LNString &alias);
    void SetAllowDesignRefreshToModify (LNBOOL allow) ;
	LNSTATUS SetComment(const LNString &comment);
    LNSTATUS SetInheritsFromTemplateName (const LNString &name) ;
	void SetHideFromBrowsers(LNBOOL hide);
	void SetHideFromClients(LNBOOL hide);
	LNSTATUS SetHTMLTags( const LNHTMLTags &tags );
    LNSTATUS SetName (const LNString& name) ;
    void SetPropagateAllowDesignChange (LNBOOL propagate) ;
	LNSTATUS SetWindowTitleFormula( const LNFormula &formula );
	LNFrameset& operator=( const LNFrameset &other );
	LNFrameset& operator=( const LNNote &other );
	LNFrame operator[]( LNINT n ) const;
	~LNFrameset();
protected:

private:
	LNFrameset & operator=( LNFramesetBody *note );
	LNFrameset( LNFramesetBody *note );
	LNFramesetBody * GetFramesetBody()
	{ return (LNFramesetBody *)Body;}

	LNFrameset( LNDatabaseBody *db, NOTEID idnote );
	void ValidateNoteType( LNNOTETYPE notetype ) const; 
	void ValidateNoteType( const LNNote &note ) const; 
	void ValidateNoteType( const LNNoteBody *note ) const; 

};
//
//		Class Definition for LNFrameSplitOptions
//
class LNIMPEXPCL LNFrameSplitOptions : public LNNotesClass
{
public:
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNFRAMESPLITOPTIONS;}
	LNString GetFirstFrameName() const { return FirstFrameName;}
	LNString GetSecondFrameName() const { return SecondFrameName;}
	LNBOOL GetVertical() const { return Vertical;}
	LNINT GetFirstFrameSize() const { return FirstFrameSize;}
	LNFrameSplitOptions();
	LNFrameSplitOptions( const LNFrameSplitOptions &other );
	~LNFrameSplitOptions();
	LNFrameSplitOptions& operator=( const LNFrameSplitOptions &other );
	LNSTATUS SetFirstFrameName(const LNString &firstFrameName) 
	{ FirstFrameName = firstFrameName; return LNNOERROR;	}
	LNSTATUS SetSecondFrameName(const LNString &secondFrameName) 
	{ SecondFrameName = secondFrameName; return LNNOERROR; }
	void SetVertical(LNBOOL vertical){  Vertical = vertical;}
	void SetFirstFrameSize( LNINT size ) {FirstFrameSize = size;}
protected:
private:
	void SetFramesetSplitDefaults();
	LNString FirstFrameName;
	LNString SecondFrameName;
	LNINT FirstFrameSize;
	LNBOOL Vertical;
};

/* Signatures for Frameset CD records */
/* if Notes minor point version is less than 1 we need to include this
   these definitions */

// For the lowest version of R5 definitions for framesets were not included. We need to 
// include them explicitly because currently we use 5.0.0. If we switch to the later
// version we may just include fsods.h. We kkep this conditional section in case a user
// replaces the toolkit headers with the latest C API headers.

#include "lapiplat.h"

#if !((NOTESAPI_MAJOR_VERSION == 5) && (NOTESAPI_MINOR_VERSION == 0) && (NOTESAPI_MINOR_POINT_VERSION == 0))

#include "fsods.h"

#else

#define SIG_CD_FRAMESETHEADER	(239 | WORDRECORDLENGTH)
#define SIG_CD_FRAMESET			(240 | WORDRECORDLENGTH)
#define SIG_CD_FRAME			(241 | WORDRECORDLENGTH)

/* FRAMESETLENGTH structure used to specify the ROWS or COLS attributes for
   a frameset element. One structure for each row or column */
typedef struct
	{
#define PIXELS_LengthType		1	/* Attribute is expressed as pixels */
#define PERCENTAGE_LengthType	2	/* Attribute is expressed as a percentage */
#define RELATIVE_LengthType		3	/* Attribute is expressed as relative */
	WORD Type;			/* Must be PIXELS_LengthType, PERCENTAGE_LengthType, or RELATIVE_LengthType */
	WORD Value;			/* The value of the ROWS or COLS attribute */
	}	FRAMESETLENGTH;


typedef struct
	{
	WSIG Header;
	WORD Version;
	WORD RecCount;		/* Total number of CDFRAMESET and CDFRAME recs that follow */
	DWORD Reserved[4];	/* Reserved for future use, must be 0 */
	} CDFRAMESETHEADER;


/* On-Disk CDFRAMESET structure used to specify an HTML FRAMESET element */
typedef struct
	{
	WSIG Header;
	DWORD Flags;					/* fFSxxxxxxx as defined below. Unused bits must be set to 0 */
#define fFSBorderEnable			0x00000001	/* Set if BorderEnable is specified */
#define fFSFrameBorderDims 		0x00000004	/* Set if FrameBorderWidth is specified */
#define fFSFrameSpacingDims		0x00000008	/* Set if FrameSpacingWidth is specified */
#define fFSFrameBorderColor		0x00000040	/* Set if FrameBorderColor is specified */
	BYTE  BorderEnable;				/* Specifies the HTML FRAMEBORDER attribute for this frameset element */
	BYTE  byAvail1;					/* Reserved for future use, must be 0 */
	WORD Reserved1;					/* Reserved for future use, must be 0 */
	WORD Reserved2;					/* Reserved for future use, must be 0 */
	WORD FrameBorderWidth;			/* Specifies the HTML BORDER attribute for this frameset element */
	WORD Reserved3;					/* Reserved for future use, must be 0 */
	WORD FrameSpacingWidth;			/* Specifies the HTML FRAMESPACING attribute for this frameset element */
	WORD Reserved4;					/* Reserved for future use, must be 0 */
	COLOR_VALUE ReservedColor1;		/* Reserved for future use, must be 0 */
	COLOR_VALUE ReservedColor2;		/* Reserved for future use, must be 0 */
/* RowQty and ColQty specify the number of FRAMESETLENGTH structures that follow
 * in the variable length data area.  Only one of these values can be non-zero,
 * meaning that a frameset will consist of all rows or all columns but never both. */
	WORD  RowQty; 
	WORD  ColQty;
	WORD  Reserved5;				/* Reserved for future use, must be 0 */
	WORD  Reserved6;				/* Reserved for future use, must be 0 */
	COLOR_VALUE FrameBorderColor;	/* Used to specify the BORDERCOLOR attribute for this frameset element */
	BYTE  Reserved7[2];		   		/* Reserved for future use, must be 0 */
	/* Variable length data follows (strings not null terminated)
	 *	- Row FRAMESETLENGTH structures (count equals RowQty)
	 *	- Col FRAMESETLENGTH structures (count equals ColQty) */
	}	CDFRAMESET;


/* On-Disk CDFRAME structure used to specify an HTML FRAME element */
typedef struct
	{
	WSIG Header;
	DWORD Flags;	/* fsFRxxxxx as defined below, unused bits must be set to 0 */
#define fFRBorderEnable				0x00000001	/* Set if BorderEnable is specified */
#define fFRMarginWidth				0x00000002	/* Set if MarginWidth is specified */
#define fFRMarginHeight				0x00000004	/* Set if MarginHeight is specified */
#define fFRFrameBorderColor			0x00000008	/* Set if FrameBorderColor is specified */
#define fFRScrolling				0x00000010	/* Set if ScrollBarStyle is specified */
	WORD  wAvail1;					/* Reserved for future use, must be 0 */
	BYTE  BorderEnable;				/* Specifies the FRAMEBORDER attribute for this Frame element */
	BYTE  NoResize;					/* Specifies the NORESIZE attribute for this Frame element */
// #define ALWAYS_ScrollStyle		1	/* SCROLLING = ALWAYS */
// #define NEVER_ScrollStyle		2	/* SCROLLING = NEVER */
// #define AUTO_ScrollStyle 		3	/* SCROLLING = AUTO */
	WORD  ScrollBarStyle;		/* Specifies the SCROLLING attribute for this
	                             * frame element.  Must be ALWAYS_ScrollStyle,
								 * NEVER_ScrollStyle or AUTO_ScrollStyle */
	WORD  MarginWidth;			/* Specifies the MARGINWIDTH attribute for this frame element */
	WORD  MarginHeight;			/* Specifies the MARGINHEIGHT attribute for this frame element */
	DWORD dwReserved;			/* Reserved for future use, must be 0 */
	WORD  FrameNameLength;		/* Length of FrameName string that follows. 
	                             * Set to 0 if not specified. */
	WORD Reserved1;
	WORD  FrameTargetLength;    	/* Length of default target frame name. Set to 0 if not specified */
	COLOR_VALUE FrameBorderColor;	/* Specifies the BORDERCOLOR attribute for this frame element */
	WORD wReserved;					/* Reserved for future use, must be 0 */
	/* Variable length data follows (strings not null terminated)
	 *  - Frame Name string (Specifies the NAME attribute for this frame element */
	/*  - Frame Target string */
	} CDFRAME;

#if defined(GCC) && defined(SUN)
#define odsmacro(name, num, size) enum{_/*##*/name = num};
#else
#define odsmacro(name, num, size) enum{_##name = num};
#endif

odsmacro(FRAMESETLENGTH, 625, sizeof(FRAMESETLENGTH))
odsmacro(CDFRAMESETHEADER, 626, sizeof(CDFRAMESETHEADER))
odsmacro(CDFRAMESET, 627, sizeof(CDFRAMESET))
odsmacro(CDFRAME, 628, sizeof(CDFRAME))
#endif //version of the C API headers

#ifndef ALWAYS_ScrollStyle
	#define ALWAYS_ScrollStyle		1	/* SCROLLING = ALWAYS */
#endif
#ifndef NEVER_ScrollStyle
	#define NEVER_ScrollStyle		2	/* SCROLLING = NEVER */
#endif
#ifndef AUTO_ScrollStyle
	#define AUTO_ScrollStyle 		3	/* SCROLLING = AUTO */
#endif

enum LNFRAMESCROLLTYPE
{
	LNFRAMESCROLLTYPE_NEVER = NEVER_ScrollStyle,
	LNFRAMESCROLLTYPE_ALWAYS = ALWAYS_ScrollStyle,
	LNFRAMESCROLLTYPE_AUTO = AUTO_ScrollStyle,
	LNFRAMESCROLLTYPE_DEFAULT = AUTO_ScrollStyle
};

enum LNFRAMECONTENTTYPE
{
	LNFRAMECONTENTTYPE_URL,
	LNFRAMECONTENTTYPE_URL_FORMULA,
	LNFRAMECONTENTTYPE_VIEW_LINK,
	LNFRAMECONTENTTYPE_DOCUMENT_LINK,
	LNFRAMECONTENTTYPE_ANCHOR_LINK,
	LNFRAMECONTENTTYPE_NAMED_ELEMENT,
	LNFRAMECONTENTTYPE_NAMED_ELEMENT_SPECIAL,
	LNFRAMECONTENTTYPE_NAMED_ELEMENT_FORMULA
};

enum LNNAMEDELEMENT
{
	LNNAMEDELEMENT_PAGE,
	LNNAMEDELEMENT_FORM,
	LNNAMEDELEMENT_FRAMESET,
	LNNAMEDELEMENT_VIEW,
	LNNAMEDELEMENT_SIMPLE_VIEW,
	LNNAMEDELEMENT_FOLDER,
	LNNAMEDELEMENT_SIMPLE_FOLDER,
	LNNAMEDELEMENT_NAVIGATOR
};

enum LNSPECIALLINK
{
	LNSPECIALLINK_CURRENT_DATABASE,
	LNSPECIALLINK_USER_MAIL_FILE,
	LNSPECIALLINK_USER_ADDRESS_BOOK,
	LNSPECIALLINK_USER_SUBSCRIPTIONS,
	LNSPECIALLINK_USER_BOOKMARKS
};
//
//	Class definition for LNFrame
//
class LNIMPEXPCL LNFrame : public LNSmartPtr
{
public:
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNFRAME;}
	LNBOOL GetAllowResizing() const;
	LNBOOL GetBorderEnabled() const;
	LNFRAMECONTENTTYPE GetContentType() const;
	LNString GetDefaultTargetName() const;
	LNString GetFrameName() const;
	LNSTATUS GetNamedElement( LNString *name, LNNAMEDELEMENT *type, TIMEDATE *replicaID ) const;
	LNSTATUS GetNamedElementFormula(LNFormula *formula, LNNAMEDELEMENT *type) const;
	LNSTATUS GetNamedElementSpecial( LNString *name, 
		LNNAMEDELEMENT *type, LNSPECIALLINK *specialLinkType ) const;
	LNSTATUS GetLink(LNViewLink *link) const;
	LNFRAMESCROLLTYPE GetScrollType() const;
	LNString GetURL() const;
	LNSTATUS GetURLFormula(LNFormula *formula) const;
	LNFrame();
	LNFrame( const LNFrame &other );
	LNFrame& operator=( const LNFrame &other );
	~LNFrame();
	void SetAllowResizing(LNBOOL flag);
	void SetBorderEnabled(LNBOOL flag);
	LNSTATUS SetDefaultTargetName(const LNString &name);
	LNSTATUS SetFrameName( const LNString &name );
	LNSTATUS SetLink( const LNViewLink &link);
	LNSTATUS SetNamedElement( const LNString &name, 
		LNNAMEDELEMENT type, TIMEDATE replicaId );
	LNSTATUS SetNamedElementFormula( const LNFormula &formula, LNNAMEDELEMENT type );
	LNSTATUS SetNamedElementSpecial( const LNFormula &formula, 
		LNNAMEDELEMENT type, LNSPECIALLINK specialLink );
	LNSTATUS SetScrollType(LNFRAMESCROLLTYPE type);
	LNSTATUS SetURL( const LNString &url );
	LNSTATUS SetURLFormula( const LNFormula &urlFormula );
	LNSTATUS Split(const LNFrameSplitOptions &options, LNFrame *newFrame);
protected:
private:
	LNFramesetTreeBody *ParentFrameset;
	LNFrame(LNFrameBody *frameBody);
};

#endif // LNFRMST_HPP
