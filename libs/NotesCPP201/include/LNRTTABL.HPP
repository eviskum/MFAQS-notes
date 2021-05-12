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
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
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

	LNCOLOR	GetBackgroundColor() const;

	LNTABLEBORDERTYPE GetBottomBorderType() const;

	LNINT GetBottomBorderWidth() const;

	LNSTATUS GetCDTableCell(CDTABLECELL *tablecell) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABLECELL; }

	LNINT GetColumnIndex() const;

	LNTABLEBORDERTYPE GetLeftBorderType() const;
	
	LNINT GetLeftBorderWidth() const;

	LNTABLEBORDERTYPE GetRightBorderType() const;
	
	LNINT GetRightBorderWidth() const;

	LNINT GetRowIndex() const;

 	LNSTATUS GetTable(LNTable *table) const;

	LNTABLEBORDERTYPE GetTopBorderType() const;
	
	LNINT GetTopBorderWidth() const;

	

	LNSTATUS SetBackgroundColor(LNCOLOR color);

	LNSTATUS SetBottomBorderType(const LNTABLEBORDERTYPE border);
	
	LNSTATUS SetBottomBorderWidth(LNINT width = 1);

	void SetCDTableCellColumnSpan(BYTE span);

	void SetCDTableCellFlags(BYTE flags);

	void SetCDTableCellRowSpan(BYTE span);

	LNSTATUS SetLeftBorderType(const LNTABLEBORDERTYPE border);
	
	LNSTATUS SetLeftBorderWidth(LNINT width = 1);

	LNSTATUS SetRightBorderType(const LNTABLEBORDERTYPE border);

	LNSTATUS SetRightBorderWidth(LNINT width = 1);
	
	LNSTATUS SetTopBorderType(const LNTABLEBORDERTYPE border);

	LNSTATUS SetTopBorderWidth(LNINT width = 1);

	LNSTATUS SetTransparent(LNBOOL transparent = TRUE);

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

	//	Returns TRUE if the table width is automatically computed by 
	//	Notes (if the table size is automatically fit to the window size).
	LNBOOL GetAutomaticWidth() const;

	LNTABLEBORDERSTYLE GetBorderStyle() const;	//	4.5 only

	LNSTATUS GetCDTableBegin(CDTABLEBEGIN *tablebegin) const;

	LNSTATUS GetCDTableEnd(CDTABLEEND *tableend) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABLE; }
	
	LNINT GetColumnCount() const;
	
	LNNUMBER GetColumnSpacing(); 
	
 	//	The first parameter is the zero-based column number. The optional second 
	//	parameter specifies the units of measurement. See LNUNITS () for more information.
	LNNUMBER GetColumnWidth(LNINT column);
	
	//	Returns the left margin setting in the specified units.  
	//	See LNUNITS () for more information.
	LNNUMBER GetLeftMargin();
	
	LNINT GetRowCount() const;
	
	LNNUMBER GetRowSpacing();

	LNUNITS	GetUnits() const;

	LNSTATUS InsertColumns(LNINT column, LNINT count = 1);
	
	//	Inserts one or more columns or rows in the table, before the specified column/row. 
	//	The first parameter is the zero-based column/row number. The optional 
	//	second parameter is the number of columns/rows to insert.
	LNSTATUS InsertRows(LNINT row, LNINT count = 1);

	LNSTATUS Outline(LNTABLEBORDERTYPE style);
	LNSTATUS Outline(LNTABLEBORDERSTYLE style = LNTABLEBORDERSTYLE_STANDARD);

	//	Modifies automatic width computation flag.  TRUE fits the table to the window size.
	LNSTATUS SetAutomaticWidth(const LNBOOL flag);
	
	LNSTATUS SetBackgroundColor(LNCOLOR color);

	LNSTATUS SetBorderStyle(LNTABLEBORDERSTYLE newStyle);

	LNSTATUS SetColumnSpacing(const LNNUMBER &spacing);
	
	//	The first parameter is the zero-based column number. The second parameter is the new width. 
	//	If automatic width is set, this function does nothing and returns a warning.
	LNSTATUS SetColumnWidth(LNINT column, const LNNUMBER &width);
	
	//	Modifies the left margin setting. The first parameter is the new margin. 
	//	This function returns an error if the specified margin is out of range.
	LNSTATUS SetLeftMargin(const LNNUMBER &margin);
	
	//	Gets or Sets the spacing between columns in the specified units., 
	//	as defined by LNUITS enum.
	LNSTATUS SetRowSpacing(const LNNUMBER &spacing);
	
	//	Turns off the background color in every table cell in this table. 
	//	This function is only supported for Notes versions 4.5 and later.
	LNSTATUS SetTransparent();

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
	
	//	moved fractionalcolumn stuff in here so its not exposed for next release

	//	Returns the fractional width of the specified column. 
	//	The first parameter is the zero-based column number.  
	//	Fractional column width = column width / table width.  
	//	Fractional width does not have units.
 	LNNUMBER GetFractionalColumnWidth(LNINT column);
	
	//	Modifies the fractional column width of the specified column.  
	//	Fractional width = column width / table width.  Fractional 
	//	width does not have units.   If automatic width is not set, 
	//	this function does nothing and returns a warning. This method 
	//	returns an error if column or fractwidth are out of range.
	LNSTATUS SetFractionalColumnWidth(LNINT column, 
		const LNNUMBER &fractwidth);
};

#endif

