//==========================================================================================
//
// Module:	LNRTTABL.HPP
//
// Description
//
//  Class Library description for LNTable, LNTableBody, LNTableCell,
//  LNTableCellBody.
//
//==========================================================================================
//
// Copyright (c) 1997-2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTTABL_HPP
#define LNRTTABL_HPP

#include "editdflt.h"


enum LNTABLEBORDERTYPE
{
	LNTABLEBORDERTYPE_NONE   = TABLE_BORDER_NONE,
	LNTABLEBORDERTYPE_SINGLE = TABLE_BORDER_SINGLE,
	LNTABLEBORDERTYPE_DOUBLE = TABLE_BORDER_DOUBLE
};


// The correct definitions for LNTABLEBORDERSTYLE are 
//		LNTABLEBORDERSTYLE_STANDARD,
//		LNTABLEBORDERSTYLE_EMBOSS, and 
//		LNTABLEBORDERSTYLE_EXTRUDE.
// These names are similar to LNFontStyle names.
//
// LNTABLEBORDERSTYLE_EMBOSSED and LNTABLEBORDERSTYLE_EXTRUDED 
// shipped with Evaluation Build 2.0e so we include them here to
// avoid breaking older code.

#define LNTABLEBORDERSTYLE_EMBOSSED LNTABLEBORDERSTYLE_EMBOSS
#define LNTABLEBORDERSTYLE_EXTRUDED LNTABLEBORDERSTYLE_EXTRUDE

enum LNTABLEBORDERSTYLE
{
	LNTABLEBORDERSTYLE_STANDARD = CDTABLE_V4_BORDERS,
	LNTABLEBORDERSTYLE_EMBOSS   = CDTABLE_3D_BORDER_EMBOSS,
	LNTABLEBORDERSTYLE_EXTRUDE  = CDTABLE_3D_BORDER_EXTRUDE
};

enum LNTABLECOLORSTYLE
{
	LNTABLECOLORSTYLE_NONE = 0,
	LNTABLECOLORSTYLE_SOLID,
	LNTABLECOLORSTYLE_ALTERNATING_ROWS,
	LNTABLECOLORSTYLE_ALTERNATING_COLUMNS,
	LNTABLECOLORSTYLE_LEFT_TOP,
	LNTABLECOLORSTYLE_LEFT,
	LNTABLECOLORSTYLE_RIGHT_TOP,
	LNTABLECOLORSTYLE_RIGHT,
	LNTABLECOLORSTYLE_TOP
};

#ifndef TRANS_LEFTTORIGHT_COLUMN
	#define TRANS_LEFTTORIGHT_COLUMN	1
	#define TRANS_ROLLING				2
	#define TRANS_TOPTOBOTTOM_ROW		3
	#define TRANS_WIPE					4
	#define TRANS_BOXES_INCREMENT		5
	#define TRANS_EXPLODE				6
	#define TRANS_DISSOLVE				7
#endif

enum LNTRANSITIONEFFECT
{
	LNTRANSITIONEFFECT_NONE,
	LNTRANSITIONEFFECT_LEFT_TO_RIGHT = TRANS_LEFTTORIGHT_COLUMN,
	LNTRANSITIONEFFECT_ROLLING = TRANS_ROLLING,
	LNTRANSITIONEFFECT_TOP_TO_BOTTOM = TRANS_TOPTOBOTTOM_ROW,
	LNTRANSITIONEFFECT_WIPE = TRANS_WIPE,
	LNTRANSITIONEFFECT_BOX_BY_BOX = TRANS_BOXES_INCREMENT,
	LNTRANSITIONEFFECT_EXPLODE = TRANS_EXPLODE,
	LNTRANSITIONEFFECT_DISSOLVE = TRANS_DISSOLVE
};

enum LNCELLALIGNMENT
{
	LNCELLALIGNMENT_TOP = 0,
	LNCELLALIGNMENT_CENTER,
	LNCELLALIGNMENT_BOTTOM
};

enum LNCELLCOLORSTYLE
{
	LNCELLCOLORSTYLE_NONE = 0,
	LNCELLCOLORSTYLE_HORIZONTAL_GRADIENT,
	LNCELLCOLORSTYLE_VERTICAL_GRADIENT
};

class LNIMPEXPCL LNTableCell : public LNRTContainer
{

public:

	LNTableCell();
	LNTableCell(const LNRTObject &other);
	LNTableCell(const LNTableCell &other);

	~LNTableCell();

	LNTableCell& operator=(const LNRTObject &other);
	LNTableCell& operator=(const LNTableCell &other);

	virtual LNSTATUS Append(const LNString &text, LNBOOL convertNewLines = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, LNRTObject *newObject = 0);

	LNColor	GetBackgroundColor() const;

	LNTABLEBORDERTYPE GetBottomBorderType() const;

	LNINT GetBottomBorderWidth() const;

	LNSTATUS GetCDTableCell(CDTABLECELL *tablecell) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABLECELL; }

	LNCELLCOLORSTYLE GetColorStyle () const;

	LNINT GetColumnIndex() const;

	LNSTATUS GetGradientColor (LNColor * color) const;

	LNTABLEBORDERTYPE GetLeftBorderType() const;
	
	LNINT GetLeftBorderWidth() const;

	LNTABLEBORDERTYPE GetRightBorderType() const;
	
	LNINT GetRightBorderWidth() const;

	LNINT GetRowIndex() const;

 	LNSTATUS GetTable(LNTable *table) const;

	LNTABLEBORDERTYPE GetTopBorderType() const;
	
	LNINT GetTopBorderWidth() const;

	LNTRANSITIONEFFECT GetTransitionEffect ();

	LNCELLALIGNMENT GetVerticalAlignment() const;

	LNBOOL GetTransparent () const;


	LNSTATUS SetBackgroundColor(const LNColor & color);

	LNSTATUS SetBottomBorderType(const LNTABLEBORDERTYPE border);
	
	LNSTATUS SetBottomBorderWidth(LNINT width = 1);

	void SetCDTableCellColumnSpan(BYTE span);

	void SetCDTableCellFlags(BYTE flags);

	void SetCDTableCellRowSpan(BYTE span);

	LNSTATUS SetColorStyle (LNCELLCOLORSTYLE style);

	LNSTATUS SetGradientColor (const LNColor & color);

	LNSTATUS SetLeftBorderType(const LNTABLEBORDERTYPE border);
	
	LNSTATUS SetLeftBorderWidth(LNINT width = 1);

	LNSTATUS SetRightBorderType(const LNTABLEBORDERTYPE border);

	LNSTATUS SetRightBorderWidth(LNINT width = 1);
	
	LNSTATUS SetTopBorderType(const LNTABLEBORDERTYPE border);

	LNSTATUS SetTopBorderWidth(LNINT width = 1);

	LNSTATUS SetTransitionEffect (LNTRANSITIONEFFECT effect);

	LNSTATUS SetTransparent(LNBOOL transparent = TRUE);

	LNSTATUS SetVerticalAlignment (LNCELLALIGNMENT align);

protected:

	LNTableCell(LNTableCellBody *body);

	LNTableCell& operator=(LNTableCellBody *body);

	LNTableCellBody* GetTableCellBody() const; 

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};



class LNIMPEXPCL LNTable : public LNRTContainer
{

public:

	LNTable();	

	~LNTable();
	
	LNTable(const LNRTObject &object);
	LNTable(const LNTable &table);
	LNTable(LNINT rows, LNINT cols);

	LNTable& operator=(const LNRTObject &object);
	LNTable& operator=(const LNTable &table);

	//	Returns the specified table cell object. 
	//	The row and column are zero-based, where (0,0) is the top left table cell.
	LNTableCell operator() (LNINT row, LNINT column);

	virtual LNSTATUS Append(const LNString &text, LNBOOL convert = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, 
		LNRTObject *newObject = 0);

	LNSTATUS AppendColumns(LNINT count);

	//	Appends one or more columns or rows to the table. 
	//	The optional parameter is the number of columns/rows to append.
	LNSTATUS AppendRows(LNINT count);

	LNSTATUS DeleteColumns(LNINT column, LNINT count = 1);
	
	//	Deletes one or more columns or rows and their data from the table, 
	//	starting with the specified column/row. The first parameter is the 
	//	zero-based column/row number. The second optional parameter is the 
	//	number of columns/rows to delete.
	LNSTATUS DeleteRows(LNINT row, LNINT count = 1);

	LNColor GetAlternateColor () const;

	//	Returns TRUE if the table width is automatically computed by 
	//	Notes (if the table size is automatically fit to the window size).
	LNBOOL GetAutomaticWidth() const;

	LNTABLEBORDERSTYLE GetBorderStyle() const;	//	4.5 only

	LNSTATUS GetCDTableBegin(CDTABLEBEGIN *tablebegin) const;

	LNSTATUS GetCDTableEnd(CDTABLEEND *tableend) const;

	LNColor GetCellBorderColor () const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABLE; }

	LNColor GetColor () const;

	LNTABLECOLORSTYLE GetColorStyle () const;

	LNINT GetColumnCount() const;
	
	LNNUMBER GetColumnSpacing(); 
	
 	//	The first parameter is the zero-based column number. The optional second 
	//	parameter specifies the units of measurement. See LNUNITS () for more information.
	LNNUMBER GetColumnWidth(LNINT column);

	LNBOOL GetIsColumnWidthFixed(const LNINT column) const;

	//	Returns the left margin setting in the specified units.  
	//	See LNUNITS () for more information.
	LNNUMBER GetLeftMargin();
	
	LNINT GetRowCount() const;

	LNNUMBER GetRowSpacing();

	LNString GetRowTabLabel (LNINT row) const;

	LNINT GetRowTimeInterval () const;

	LNUNITS	GetUnits() const;

	LNSTATUS InsertColumns(LNINT column, LNINT count = 1);
	
	//	Inserts one or more columns or rows in the table, before the specified column/row. 
	//	The first parameter is the zero-based column/row number. The optional 
	//	second parameter is the number of columns/rows to insert.
	LNSTATUS InsertRows(LNINT row, LNINT count = 1);

	LNSTATUS Outline(LNTABLEBORDERTYPE style);
	LNSTATUS Outline(LNTABLEBORDERSTYLE style = LNTABLEBORDERSTYLE_STANDARD);

	LNSTATUS SetAlternateColor (const LNColor & color);

	//	Modifies automatic width computation flag.  TRUE fits the table to the window size.
	LNSTATUS SetAutomaticWidth(const LNBOOL flag);
	
	LNSTATUS SetBackgroundColor(const LNColor & color);

	LNSTATUS SetBorderStyle(LNTABLEBORDERSTYLE newStyle);

	LNSTATUS SetCellBorderColor (const LNColor & color);

	LNSTATUS SetColor (const LNColor & color);

	LNSTATUS SetColorStyle (LNTABLECOLORSTYLE style);

	LNSTATUS SetColumnSpacing(const LNNUMBER &spacing);
	
	//	The first parameter is the zero-based column number. The second parameter is the new width. 
	//	If automatic width is set, this function does nothing and returns a warning.
	LNSTATUS SetColumnWidth(LNINT column, const LNNUMBER &width);

	LNSTATUS SetIsColumnWidthFixed(const LNINT column, const LNBOOL newFlag);
	
	//	Modifies the left margin setting. The first parameter is the new margin. 
	//	This function returns an error if the specified margin is out of range.
	LNSTATUS SetLeftMargin(const LNNUMBER &margin);
	
	//	Gets or Sets the spacing between columns in the specified units., 
	//	as defined by LNUITS enum.
	LNSTATUS SetRowSpacing(const LNNUMBER &spacing);

	LNSTATUS SetRowTabLabel (const LNINT row, const LNString &label);

	LNSTATUS SetRowTimeInterval (LNINT interval);
	
	//	Turns off the background color in every table cell in this table. 
	//	This function is only supported for Notes versions 4.5 and later.
	LNSTATUS SetTransparent(const LNBOOL newFlag = TRUE);

	void SetUnits(const LNUNITS units);

protected:

	LNTable(LNTableBody *body);

	LNTable& operator=(LNTableBody *body);

	LNTableBody* GetTableBody() const; 

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNNUMBER Convert(LNINT twips);
	LNINT Convert(const LNNUMBER &number);
};

#endif

