
/*	Miscellaneous Package Global Definitions */

#ifndef MISC_DEFS
#define MISC_DEFS

#ifdef __cplusplus
extern "C" {
#endif


/*	Some useful constants */

#define	MAXALPHANUMBER		40
#define	MAXALPHATIMEDATE	80
#define	MAXALPHATIMEDATEPAIR (80 * 2 + 3)
#define MAXSPRINTF			256
#define MAXSOUNDEX			(4+1)		/* 4 chars plus null terminator */

/*	Flags for IntlTextCompare */

#define INTL_ACCENT_SENSITIVE	0x0001
#define INTL_CASE_SENSITIVE		0x0002


/* time structure - NOTE: These fields MUST BE int's, NOT UNSIGNEDS! */

typedef struct {
	int year;					/* 1-32767 */
	int month;					/* 1-12 */
	int day;					/* 1-31 */
	int weekday;				/* 1-7, Sunday is 1 */
	int hour;					/* 0-23 */
	int minute;					/* 0-59 */
	int second;					/* 0-59 */
	int hundredth;				/* 0-99 */
	int dst;					/* FALSE or TRUE */
	int zone;					/* -11 to +11 */
	TIMEDATE GM;
} TIME;

/*	Special encodings for TIMEDATE fields.  Note that these are all in
	HOST-SPECIFIC format, and must be used with TimeConstruct or
	TimeExtractJulianDate or TimeExtractTicks! */

#define ALLDAY 0xffffffffL		/* put this in the TIME field */
#define ANYDAY 0xffffffffL		/* put this in the DATE field */
#define TICKS_IN_DAY 8640000L	/* 10msec ticks in a day */
#define TICKS_IN_HOUR 360000L	/* 10msec ticks in an hour */
#define TICKS_IN_MINUTE 6000L	/* 10msec ticks in a minute */
#define TICKS_IN_SECOND 100L	/* 10msec ticks in a second */
#define SECS_IN_DAY 86400L		/* seconds in a day */


/* DTFlags values (do not change - these values are also stored on disk!) */

#define DT_VALID		0x8000		/* Validity bit: If 1, use new DTFMT; if 0, use old TFMT */
#define	DT_4DIGITYEAR	0x0001		/* Require 4 digit year on INPUT (not output) */
#define DT_ALPHAMONTH	0x0002		/* Require months be INPUT as letters, not digits (e.g. "jan", not 01) */
#define DT_SHOWTIME		0x0004		/* Display time element on output */
#define DT_SHOWDATE		0x0008		/* Display date element on output */
#define DT_24HOUR		0x0040		/* Display time on output using 24 hour clock format */
#define DT_STYLE_YMD	1			/* Date element order:  Year, Month, Day, Day-of-week */
#define DT_STYLE_MDY	2			/* Date element order: Day-of-week, Month, Day, Year */
#define DT_STYLE_DMY	3			/* Date element order: Day-of-week, Day, Month, Year */
#define DT_STYLE_MSK	0x000f0000	/* This is where we store the style value in DTFlags */
#define DT_GET_STYLE(dwflag)		((dwflag & DT_STYLE_MSK) >> 0x10)			/* Macro to retrieve the style value from DTFlags */
#define DT_SET_STYLE(dwflag, style)	(dwflag = ((dwflag & 0xfff0ffff) | (style << 0x10)))	/* Macro to store the style value in DTFlags */

/* DTFlags2 values (do not change - these values are also stored on disk!) */

#define DT_USE_TFMT					0x0001		/* Use the 4.X format structure instead of this 5.X format structure */


/* DTYearFmt values (do not change - these values are also stored on disk!) */

#define DT_YFMT_YY		1				/* 2 digit year */
#define	DT_YFMT_YYYY	2			/* 4 digit year */
/* The following DTYearFmt values are valid only for Imperial calendars */
#define DT_YFMT_GE		3				/* Single letter (first letter ) of epoch name and 1 or 2 digit (no leading zeros) year */
#define DT_YFMT_GEE		4				/* Single letter (first letter ) of epoch name and 2 digit (with leading zeros, if necessary) year */
#define DT_YFMT_GGE		5
#define DT_YFMT_GGEE	6			/* Abbreviated spelling and 2 digit (with leading zeros, if necessary) year */
#define DT_YFMT_GGGE	7
#define DT_YFMT_GGGEE	8		/* fully spelled out epoch name and 2 digit (with leading zeros, if necessary) year */

/* DTDOWFmt values (Day-Of-Week) (do not change - these values are also stored on disk!) */

#define DT_WFMT_WWW		1
#define DT_WFMT_WWWW	2
#define DT_WFMT_WWWP	3			/* 3 letter abbreviation inside parenthesis */
#define DT_WFMT_WWWWP	4		/* Spelled out fully inside parenthesis */

/* DTMonthFmt values (do not change - these values are also stored on disk!) */

#define DT_MFMT_M		1
#define DT_MFMT_MM		2
#define DT_MFMT_MMM		3
#define DT_MFMT_MMMM	4

/* DTDayFmt values (do not change - these values are also stored on disk!) */

#define DT_DFMT_D		1
#define DT_DFMT_DD		2

/* DTDShow values (controls what is shown on OUTPUT for date) */
/* (do not change - these values are also stored on disk!) */

#define DT_DSHOW_ALL	1
#define DT_DSHOW_YM		2
#define DT_DSHOW_WMD	3
#define DT_DSHOW_W		4
#define DT_DSHOW_M		5
#define DT_DSHOW_MD		6
#define DT_DSHOW_MDY	7
#define DT_DSHOW_D		8
#define DT_DSHOW_Y		9

/* DTDSpecial bit values:  Special handling of date OUTPUT */
/* (do not change - these values are also stored on disk!) */

#define DT_DSPEC_NONE	0				/* No special handling */
#define DT_DSPEC_TODAY	0x0001			/* Use 'Today', 'Yesterday', 'Tomorrow', when possible */
#define DT_DSPEC_Y4		0x0002			/* Always display year on OUTPUT as 4 digit year */
#define DT_DSPEC_21Y4	0x0004			/* Output 2 digit year for this century; use 4 digit year for other century */
#define DT_DSPEC_CURYR	0x0008			/* Display year when not the current year */

/* DTTShow values (controls what to shown on OUTPUT for time) */
/* (do not change - these values are also stored on disk!) */

#define DT_TSHOW_H		1
#define DT_TSHOW_HM		2
#define DT_TSHOW_HMS	3
#define DT_TSHOW_ALL	4

/* Values for FTFMT "Preferences" field (do not change - these values are also stored on disk!) */

#define	NPREF_CLIENT	0		/* Get preferences from the client */
#define	NPREF_FIELD		1		/* Get preferences fromt the form or view */


/*	Number Format */

#define	NFMT_GENERAL		0		/* Number Formats */
#define	NFMT_FIXED			1
#define	NFMT_SCIENTIFIC		2
#define	NFMT_CURRENCY		3

#define	NATTR_PUNCTUATED	0x0001	/* Number Attributes */
#define	NATTR_PARENS		0x0002
#define	NATTR_PERCENT		0x0004
#define NATTR_VARYING		0x0008

typedef struct {
	BYTE Digits;					/* Number of decimal digits */
	BYTE Format;					/* Display Format */
	BYTE Attributes;				/* Display Attributes */
	BYTE Unused;
} NFMT;

/*	Time Format */

#define	TDFMT_FULL			0		/* year, month, and day */
#define	TDFMT_CPARTIAL		1		/* month and day, year if not this year */
#define	TDFMT_PARTIAL		2		/* month and day */
#define	TDFMT_DPARTIAL		3		/* year and month */
#define TDFMT_FULL4			4		/* year(4digit), month, and day */
#define TDFMT_CPARTIAL4		5		/* month and day, year(4digit) if not this year */
#define TDFMT_DPARTIAL4		6		/* year(4digit) and month */
#define	TTFMT_FULL			0		/* hour, minute, and second */
#define	TTFMT_PARTIAL		1		/* hour and minute */
#define	TTFMT_HOUR			2		/* hour */
#define	TZFMT_NEVER			0		/* all times converted to THIS zone */
#define	TZFMT_SOMETIMES		1		/* show only when outside this zone */
#define	TZFMT_ALWAYS		2		/* show on all times, regardless */
#define	TSFMT_DATE			0		/* DATE */
#define	TSFMT_TIME			1		/* TIME */
#define	TSFMT_DATETIME		2		/* DATE TIME */
#define	TSFMT_CDATETIME		3		/* DATE TIME or TIME Today or TIME Yesterday */

typedef struct {
	BYTE Date;						/* Date Display Format */
	BYTE Time;						/* Time Display Format */
	BYTE Zone;						/* Time Zone Display Format */
	BYTE Structure;					/* Overall Date/Time Structure */
} TFMT;


/* function templates */

BOOL LNPUBLIC		TimeLocalToGM (TIME far *Time);
BOOL LNPUBLIC		TimeGMToLocal (TIME far *Time);
BOOL LNPUBLIC		TimeGMToLocalZone (TIME far *Time);
int LNPUBLIC		TimeDateCompare (TIMEDATE far *t1, TIMEDATE far *t2);
int LNPUBLIC		TimeDateCollate (TIMEDATE far *t1, TIMEDATE far *t2);
DWORD LNPUBLIC		TimeExtractJulianDate (TIMEDATE far *);
DWORD LNPUBLIC		TimeExtractDate (TIMEDATE far *);
DWORD LNPUBLIC		TimeExtractTicks (TIMEDATE far *);
void LNPUBLIC		TimeExtractLocal (TIMEDATE far *Time, BOOL fTime, TIMEDATE far *retTime);
void LNPUBLIC		TimeConstruct (DWORD Date, DWORD Time, TIMEDATE far *result);


#define	TIMEDATE_MINIMUM	0
#define	TIMEDATE_MAXIMUM	1
#define	TIMEDATE_WILDCARD	2
void LNPUBLIC		TimeConstant(WORD, TIMEDATE far *);

#define TimeDateEqual(a,b) ((BOOL)TimeDateCollate(a,b)==0)
#define TimeDateClear(a) (TimeConstant(TIMEDATE_MINIMUM, a))
STATUS LNPUBLIC		TimeDateIncrement (TIMEDATE far *Time, LONG Interval);
LONG LNPUBLIC		TimeDateDifference (TIMEDATE far *t1, TIMEDATE far *t2);
void LNPUBLIC		TimeDateDifferenceFloat (TIMEDATE far *t1,
						TIMEDATE far *t2, NUMBER far *difference);
BOOL LNPUBLIC		TimeDateAdjust (TIMEDATE far *Time, int seconds, int minutes, int hours, int days, int months, int years);
int LNPUBLIC		IntlTextCompare(void far *Str1, WORD Str1Len,
									void far *Str2, WORD Str2Len, DWORD Flags);
STATUS LNPUBLIC		ConvertTextToTIMEDATE (void far *IntlFormat,
										TFMT far *TextFormat,
										char far * far *Text,
										WORD MaxLength,
										TIMEDATE far *retTIMEDATE);
STATUS LNPUBLIC		ConvertTextToTIMEDATEPAIR (void far *IntlFormat,
										TFMT far *TextFormat,
										char far * far *Text,
										WORD MaxLength,
										TIMEDATE_PAIR far *retTIMEDATE);
STATUS LNPUBLIC		ConvertTIMEDATEToText (void far *IntlFormat,
										TFMT far *TextFormat,
										TIMEDATE far *InputTime,
										char far *retTextBuffer,
										WORD TextBufferLength,
										WORD far *retTextLength);
STATUS LNPUBLIC		ConvertTIMEDATEPAIRToText (void far *IntlFormat,
										TFMT far *TextFormat,
										TIMEDATE_PAIR far *InputTime,
										char far *retTextBuffer,
										WORD TextBufferLength,
										WORD far *retTextLength);
STATUS LNPUBLIC		ConvertTextToFLOAT (void far *IntlFormat,
										NFMT far *NumberFormat,
										char far * far *ppInputText,
										WORD InputTextMaxLength,
										NUMBER far *retNumber);
STATUS LNPUBLIC		ConvertFLOATToText (void far *IntlFormat,
										NFMT far *NumberFormat,
										NUMBER far *Number,
										char far *retTextBuffer,
										WORD TextBufferLength,
										WORD far *retTextLength);
void LNPUBLIC Soundex (char far *String, WORD StringLength, char far *retSoundexString);

/* Abstract */

/* chunk separator parameters */
#define ABS_CHUNKBEGIN "ChunkBegin="
#define ABS_CHUNKSEP "ChunkSep="
#define ABS_CHUNKEND "ChunkEnd="

/* abstraction commands */
#define ABS_TEXTONLY		"textonly "
#define ABS_COUNTWORDS		"countwords "
#define ABS_SAVE			"save "
#define ABS_RESTORE			"restore "
#define ABS_TRYFIT			"tryfit "
#define ABS_ABBREV			"abbrev "
#define ABS_SORTCHUNKS		"sortchunks "
#define ABS_NOSTOPLIST		"nostoplist "
#define ABS_NOSIGLIST		"nosiglist "
#define ABS_USEDICT			"ab-usedict "
#define ABS_NODICT			"ab-usedict=0 "
#define ABS_DROPVOWELS		"ab-dropvowels "
#define ABS_KEEPVOWELS		"ab-dropvowels=0 "
#define ABS_TRIMWHITE		"ab-trimwhite "
#define ABS_NOTRIMWHITE		"ab-trimwhite=0 "
#define ABS_TRIMPUNCT		"ab-trimpunct "
#define ABS_NOTRIMPUNCT		"ab-trimpunct=0 "
#define ABS_DROPFIRSTVOWEL	"ab-dropfirstvowels "
#define ABS_KEEPFIRSTVOWEL	"ab-dropfirstvowels=0 "


STATUS LNPUBLIC Abstract(char far *szKeywords,
						char far *szText, 
						DWORD maxAbstract,
						char far *szAbstract,
						DWORD far *retSize);


#ifdef __cplusplus
}
#endif

#endif /* MISC_DEFS */

