#ifdef __cplusplus
extern "C" {
#endif


/*	Notes On-Disk Structure Definitions - for the actions facility
	Currently contains only a single CD record that completely
	describes a customizable menu action.
*/
#ifndef ACT_ODS_DEFS
#define ACT_ODS_DEFS

#ifndef ODS_DEFS
#include "ods.h"
#endif

#ifndef COLORODS_DEFS
#include "colorods.h"					/* COLOR_VALUE */
#endif


/*	CDACTION -  Action Record, used in forms ($ACTION) to 
	define a customizable menu action.
*/

typedef struct {
	LSIG	Header;				/* Signature and Length */
	WORD	Type;				/* Type of action (formula, script, etc.)*/
	WORD	IconIndex;			/* Index into array of icons.	*/
	DWORD 	Flags;				/* Action flags		*/
	WORD 	TitleLen;			/* Length (in bytes) of action's title*/
	WORD	FormulaLen;
	DWORD	ShareId;			
								/*	Variable portion of the record -
								  	TitleLen bytes of action's title
								  	followed by Size - Titlelen bytes
									of formula, script, etc. depending
									on the action type.
								*/
} CDACTION;

/* bitwise flags for the Flags field */

#define		ACTION_SHOW_IN_MENU				0x00000001L
#define		ACTION_SHOW_IN_BAR				0x00000002L
#define		ACTION_SHOW_WHEN_PREVIEWING		0x00000004L
#define		ACTION_SHOW_WHEN_READING		0x00000008L

#define		ACTION_SHOW_WHEN_EDITING		0x00000010L
#define		ACTION_SHOW_ON_OLE_LAUNCH		0x00000020L
#define		ACTION_OLE_CLOSE_WHEN_CHOSEN	0x00000040L
#define		ACTION_NO_FORMULA				0x00000080L
#define		ACTION_SHOW_WHEN_PREVEDITING	0x00000100L

#define		ACTION_OLE_DOC_WINDOW_TO_FRONT 	0x00001000L
#define		ACTION_HIDE_FROM_NOTES			0x00002000L
#define		ACTION_HIDE_FROM_WEB			0x00004000L
#define		ACTION_READING_ORDER_RTL		0x00008000L
#define		ACTION_SHARED					0x00010000L	/* action is shared*/
#define 	ACTION_MODIFIED					0x00020000L	/* action has been modified (not saved on disk) */
#define		ACTION_ALWAYS_SHARED			0x00040000L	/* flag not saved on disk */
#define		ACTION_ALIGN_ICON_RIGHT			0x00080000L
#define		ACTION_IMAGE_RESOURCE_ICON		0x00100000L
#define		ACTION_FRAME_TARGET				0x00400000L 
#define		ACTION_TEXT_ONLY_IN_MENU		0x00800000L
#define		ACTION_BUTTON_TO_RIGHT			0x01000000L /* Show button on opposite side from action bar direction */

#define		ACTION_ODS_FLAG_MASK			0x01F9F1FF



typedef struct {
	BSIG	Header;				/*	Signature and Length		*/
	WORD	BackColor;			/*	Background color index.	*/
	WORD	LineColor;			/*	Line color index.		*/
	WORD	LineStyle;			/*	Style of line.			*/
	WORD	BorderStyle;		/*	Border style.			*/
	WORD	BorderWidth;		/*	Border width (twips)	*/
	
	DWORD	dwFlags;
	DWORD	ShareID;
	FONTID	FontID;
	WORD	BtnHeight;
	WORD	HeightSpc;

}	CDACTIONBAR;

/* bitwise flags for the dwFlags field */

#define ACTION_BAR_FLAG_NO_SYS_COLOR	0x00000001
#define ACTION_BAR_FLAG_ALIGN_RIGHT		0x00000002		/* Right justify buttons */
#define ACTION_BAR_FLAG_TRANS_BUTTONS	0x00000004		/* Buttons are transparent */
#define ACTION_BAR_FLAG_SYS_BUTTONS		0x00000008		/* Buttons use system color */
#define ACTION_BAR_FLAG_BTNBCK_IMGRSRC	0x00000010		/* Image resource used for button background */
#define ACTION_BAR_FLAG_BARBCK_IMGRSRC	0x00000020		/* Image resource used for bar background */
#define ACTION_BAR_FLAG_SET_PADDING		0x00000040		/* Use the Padding setting instead of default 2 pixels */
#define ACTION_BAR_FLAG_USE_APPLET		0x00000080		/* Use applet in browser */
#define ACTION_BAR_FLAG_SET_HEIGHT			0x00000100	/* Use Height setting instead of default ICON_DEFAULT_HEIGHT */
#define ACTION_BAR_FLAG_ABSOLUTE_HEIGHT		0x00000200	/* if ACTION_BAR_FLAG_SET_HEIGHT, use absolute height spec'd by user */
#define ACTION_BAR_FLAG_BACKGROUND_HEIGHT	0x00000400	/* if ACTION_BAR_FLAG_SET_HEIGHT, use background image's height */
#define ACTION_BAR_FLAG_SET_WIDTH			0x00000800	/* Use Width setting instead of default width */
#define ACTION_BAR_FLAG_BACKGROUND_WIDTH	0x00001000	/* if ACTION_BAR_FLAG_SET_WIDTH, use background image's width */

typedef struct {
	WSIG		Header;
	COLOR_VALUE	BackColor;
	COLOR_VALUE	LineColor;
	COLOR_VALUE	FontColor;
	COLOR_VALUE	ButtonColor;
	WORD		BtnBorderDisplay;
	WORD		wAppletHeight;				/* This is always recalculated on save */
	DWORD		Spare[19];
	/* Leaving many spares for future mouse down/ mouse over colors and whatever else we want */
}	CDACTIONBAREXT;
	
/*	End of Action Package On Disk Structure Definitions */

#endif

#ifdef __cplusplus

}
#endif


