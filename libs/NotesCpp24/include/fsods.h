#ifdef __cplusplus
extern "C" {
#endif


/* This file contains all definitions and data structures relavent to 
   On-Disk storage of $FRAMESET items.
*/

#ifndef FSODS_DEFS
#define FSODS_DEFS

#ifndef ODS_DEFS
#include "ods.h"
#endif

#ifndef COLORODS_DEFS
#include "colorods.h"
#endif


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
#define ALWAYS_ScrollStyle		1	/* SCROLLING = ALWAYS */
#define NEVER_ScrollStyle		2	/* SCROLLING = NEVER */
#define AUTO_ScrollStyle 		3	/* SCROLLING = AUTO */
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
#endif	/* FSODS_DEFS */

#ifdef __cplusplus
}
#endif
