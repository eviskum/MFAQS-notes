//===========================================================================
//
// Module:		LNCDREC.HPP
//
// Description:
//
//		Class library definition for the classes which handle
//      miscellaneos CD records used in many places.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNCDREC_HPP
#define LNCDREC_HPP

#ifndef RSRCODS_DEFS
#include <rsrcods.h>
#endif

//
//  Class definition of LNHTMLTags
//
class LNIMPEXPCL LNHTMLTags : public LNNotesClass
{
public:
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNHTMLTAGS;}

	void Clear();
	LNBOOL IsNull() const;
	LNString GetIdTag() const { return Id; }
	LNString GetClassTag() const { return Id; }
	LNINT GetSize() const;
	LNString GetStyleTag() const { return Style; }
	LNString GetTitleTag() const { return Title; }
	LNString GetHTMLCode() const { return Extra; }
	LNString GetName() const { return Name; }
	LNHTMLTags() {}
	LNHTMLTags( const LNHTMLTags &other )
	{
		this->operator=(other);
	}
	LNHTMLTags& operator=( const LNHTMLTags &other )
	{
		Id = other.Id;
		Class = other.Class;
		Style = other.Style;
		Title = other.Title;
		Extra = other.Extra;
		return (*this);
	}

	~LNHTMLTags(){}

	void SetIdTag( const LNString &tag ) { Id = tag; }
	void SetClassTag( const LNString &tag ) { Class = tag; }
	void SetStyleTag( const LNString &tag ) { Style = tag; }
	void SetTitleTag( const LNString &tag ) { Title = tag; }
	void SetHTMLCode( const LNString &code ) { Extra = code; }
	void SetName( const LNString &name ) { Name = name; }
protected:

private:
	LNSTATUS Load (char **ppData);
	LNSTATUS Load (LNItemBody *itemBody, LNINT offset, LNINT *newOffset);
	LNSTATUS Load (const LNRTObject &object);
	void LoadVariableData(CDIDNAME cdidname, char *ptr);
	void UpdateRecordData(CDIDNAME *cdidname) const;
	void UpdateVariableData(CDIDNAME cdidname, char **pPtr) const;
	LNSTATUS Update(char **ppData) const;
	LNSTATUS Update(LNItemBody *itemBody, LNINT offset, LNINT *newOffset) const;
	LNSTATUS Update(LNRTObject *object) const;
	LNString Id;
	LNString Class;
	LNString Style;
	LNString Title;
	LNString Extra;
	LNString Name;
};
#endif // LNCDREC_HPP
