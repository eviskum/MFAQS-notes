//===========================================================================
//
// Module:  LNSECTIO.HPP
//
// Description:
//
//  Class library definition for LNSection and related classes.
//
//===========================================================================
//
// Copyright (c) 1999-2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSECTIO_HPP
#define LNSECTIO_HPP


enum LNSECTIONEXPANDRULE
{
	LNSECTIONEXPANDRULE_DO_NOTHING = 0,
	LNSECTIONEXPANDRULE_EXPAND = 1,
	LNSECTIONEXPANDRULE_COLLAPSE = 2
};

enum LNSECTIONBORDERSTYLE
{
	LNSECTIONBORDERSTYLE_NONE	= BARREC_BORDER_NONE,
	LNSECTIONBORDERSTYLE_SINGLE	= BARREC_BORDER_SINGLE,
	LNSECTIONBORDERSTYLE_DOUBLE	= BARREC_BORDER_DOUBLE,
	LNSECTIONBORDERSTYLE_TRIPLE	= BARREC_BORDER_TRIPLE,
	LNSECTIONBORDERSTYLE_TWOLINE	= BARREC_BORDER_TWOLINE,
	LNSECTIONBORDERSTYLE_SHADOW	= BARREC_BORDER_SHADOW
};



class LNIMPEXPCL LNSection : public LNRTContainer
{

public:
	
	LNSection ();
	LNSection (const LNRTObject &object);
	LNSection (const LNSection &section);
//	LNSection (const LNString &title);
//	LNSection (const LNFormula &titleFormula);
	
	~LNSection();
	
	LNSection& operator= (const LNRTObject &object);
	LNSection& operator= (const LNSection &section);

	LNColor	GetBorderColor () const;

	LNSECTIONBORDERSTYLE	GetBorderStyle () const;

	virtual LNCLASSID GetClassID () const { return LNCLASSID_LNSECTION; }

	LNSECTIONEXPANDRULE GetExpandRuleWhenEditing () const;
	LNSECTIONEXPANDRULE GetExpandRuleWhenPreviewing () const;
	LNSECTIONEXPANDRULE GetExpandRuleWhenPrinting () const;
	LNSECTIONEXPANDRULE GetExpandRuleWhenReading () const;
	
	LNBOOL	GetHideTitleWhenExpanded () const;

	LNBOOL	GetIsExpanded () const;

	LNBOOL	GetShowInPreviewOnly () const;

	LNFontStyle GetTitleFontStyle () const;
	
	LNFormula GetTitleFormula () const;

	LNString GetTitleText () const;

	LNBOOL	IsTitleFormula () const;
	LNBOOL	IsTitleText () const;
	
	LNSTATUS SetBorderColor (const LNColor & color); // Default is NOTES_COLOR_DARK_CYAN

	LNSTATUS SetBorderStyle (LNSECTIONBORDERSTYLE type);

	LNSTATUS SetExpandRuleWhenEditing (LNSECTIONEXPANDRULE autoexpand);
	LNSTATUS SetExpandRuleWhenPreviewing (LNSECTIONEXPANDRULE autoexpand);
	LNSTATUS SetExpandRuleWhenPrinting (LNSECTIONEXPANDRULE autoexpand);
	LNSTATUS SetExpandRuleWhenReading (LNSECTIONEXPANDRULE autoexpand);

	void SetHideTitleWhenExpanded (LNBOOL flag);

	void SetIsExpanded (LNBOOL expand);

	void SetShowInPreviewOnly (LNBOOL flag);
	
	LNSTATUS SetTitleFontStyle (const LNFontStyle &fontstyle);
	
	LNSTATUS SetTitleFormula (const LNFormula &formula);

	LNSTATUS SetTitleText (const LNString &text);


protected:

	LNSection (LNSectionBody *body);

	LNSection& operator= (LNSectionBody *body);

	LNSectionBody* GetSectionBody () const { return (LNSectionBody *) Body; }


	virtual void ValidateRTType (const LNRTObject &other) const;
	virtual void ValidateRTType (const LNRTObjectBody *body) const;
};


#endif

