//===========================================================================
//
// Module:  LNACTION.HPP
//
// Description:
//
//		Class library definition for LNActions, LNAction, and related classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNACTION_HPP
#define LNACTION_HPP


//===========================================================================
//
//		Data types and constants
//
//===========================================================================

// Command codes for system actions
enum LNACTIONCOMMAND
{
	LNACTIONCOMMAND_UNKNOWN = 0,
	LNACTIONCOMMAND_CATEGORIZE = 1,
	LNACTIONCOMMAND_EDIT_DOCUMENT = 2,
	LNACTIONCOMMAND_SEND_DOCUMENT = 3,
	LNACTIONCOMMAND_FORWARD = 4,
	LNACTIONCOMMAND_MOVE_TO_FOLDER = 5,
	LNACTIONCOMMAND_REMOVE_FROM_FOLDER = 6
};

	// Action bar line styles
enum LNACTIONBARLINESTYLE
{
	LNACTIONBARLINESTYLE_UNKNOWN = 0,
	LNACTIONBARLINESTYLE_NARROW,
	LNACTIONBARLINESTYLE_MEDIUM,
	LNACTIONBARLINESTYLE_WIDE,
	LNACTIONBARLINESTYLE_DOUBLE
};

	// Action bar line types
enum LNACTIONBARLINETYPE
{
	LNACTIONBARLINETYPE_NONE,
	LNACTIONBARLINETYPE_FIT_TO_WINDOW,
	LNACTIONBARLINETYPE_UNDER_BUTTONS,
	LNACTIONBARLINETYPE_FIXED_LENGTH
};

enum LNACTIONIMAGETYPE
{
	LNACTIONIMAGETYPE_NONE,
	LNACTIONIMAGETYPE_NOTES,
	LNACTIONIMAGETYPE_CUSTOM,
	LNACTIONIMAGETYPE_FORMULA
};

//===========================================================================
//
//		Class definition for LNAction
//
//===========================================================================

class LNIMPEXPCL LNAction : public LNSmartPtr
{
	public:
		LNAction (void);
		LNAction (const LNAction & other);

		LNAction (const LNString &title, const LNLotusScript &script);
		LNAction (const LNString &title, const LNSimpleAction & action);
		LNAction (const LNString &title, const LNSimpleActions & actions);
		LNAction (const LNString &title, const LNFormula &formula);
		LNAction (const LNString &title, const LNJavaScript &javascript);

		~LNAction (void);

		LNAction &		operator= (const LNAction & other);

		LNACTIONTYPE	GetActionType (void) const;
		LNACTIONIMAGETYPE GetActionImageType (void) const;

		LNCLASSID		GetClassID (void) const
							{ return (LNCLASSID_LNACTION); }

		LNBOOL			GetCloseOLEObject (void) const;

		LNACTIONCOMMAND	GetCommand (void) const;
		LNSTATUS		GetFormula (LNFormula * pFormula) const;
		LNSTATUS		GetJavaScript (LNJavaScript * pJavaScript) const;
		
		LNBOOL			GetHideFromNotes (void) const;
		LNBOOL			GetHideFromWeb (void) const;
		
		LNSTATUS		GetHideIfFormula( LNFormula *formula ) const;
		
		LNFormula		GetImageFormula (void) const;
		LNString		GetImageName (void) const;
		LNINT			GetIconIndex (void) const;

		LNSTATUS		GetLotusScript (LNLotusScript * pScript) const;
		
		LNBOOL			GetOLEWindowToFront (void) const;
		LNBOOL			GetPublishWithOLE (void) const;
		LNBOOL			GetRightAlignButton (void) const;
		LNBOOL			GetRightAlignImage (void) const; 
		LNBOOL			GetShowInButtonBar (void) const;
		LNBOOL			GetShowInMenu (void) const;
		LNBOOL			GetShowWhenEditing (void) const;
		LNBOOL			GetShowWhenEditingPreview (void) const;
		LNBOOL			GetShowWhenPreviewing (void) const;
		LNBOOL			GetShowWhenReading (void) const;
		
		LNSTATUS		GetSimpleActions (LNSimpleActions * pActions) const;

		LNINT			GetSize () const;

		LNString		GetTargetName (void) const;
		LNString		GetTitle (void) const;

		void			SetCloseOLEObject (LNBOOL newFlag);

		LNSTATUS		SetCommand (LNACTIONCOMMAND newCommand);

		LNSTATUS		SetFormula (const LNFormula & newFormula);
		LNSTATUS		SetJavaScript (const LNJavaScript & newJavaScript);

		void			SetHideFromNotes (LNBOOL newFlag);
		void			SetHideFromWeb (LNBOOL newFlag);

		LNSTATUS		SetHideIfFormula( const LNFormula &formula );
		LNSTATUS        SetImageFormula (const LNFormula &imageFormula);
		LNSTATUS        SetImageName (const LNString &imageName);
		LNSTATUS		SetIconIndex (LNINT newIcon);

		LNSTATUS		SetLotusScript (const LNLotusScript & newScript);

		void			SetOLEWindowToFront (LNBOOL newFlag);
		void			SetPublishWithOLE (LNBOOL newFlag);
		void			SetRightAlignButton (LNBOOL newFlag);
		void			SetRightAlignImage (LNBOOL newFlag);
		void			SetShowInButtonBar (LNBOOL newFlag);
		void			SetShowInMenu (LNBOOL newFlag);
		void			SetShowWhenEditing (LNBOOL newFlag);
		void			SetShowWhenEditingPreview (LNBOOL newFlag);
		void			SetShowWhenPreviewing (LNBOOL newFlag);
		void			SetShowWhenReading (LNBOOL newFlag);

		LNSTATUS		SetSimpleAction (const LNSimpleAction & newAction);
		LNSTATUS		SetSimpleActions (const LNSimpleActions & newActions);

		LNSTATUS		SetTargetName(const LNString &newName);
		LNSTATUS		SetTitle (const LNString &newTitle);

	protected:
		LNAction (LNActionBody * pBody);

	private:
		LNActionBody *	GetActionBody (void) const;
		LNSTATUS		PrepareToModify (LNBOOL createBody);
};


//===========================================================================
//
//		Class definition for LNActions
//
//===========================================================================

class LNIMPEXPCL LNActions : public LNItem
{

	public:
		LNActions (void);
		LNActions (const LNItem & other);
		LNActions (const LNActions & other);
		LNActions (const LNNote & note);

		~LNActions (void);

		LNActions &			operator= (const LNItem & other);
		LNActions &			operator= (const LNActions & other);

		LNAction &			operator[] (LNINT n);

		LNSTATUS			Append (const LNAction & newAction);
		LNSTATUS			Delete (LNINT index, LNINT count = 1);

		LNColor				GetActionBarBackgroundColor (void) const;
		LNColor				GetActionBarLineColor (void) const;
		LNINT				GetActionBarLineLength (void) const;
		LNACTIONBARLINESTYLE	GetActionBarLineStyle (void) const;
		LNACTIONBARLINETYPE	GetActionBarLineType (void) const;
		LNBOOL				GetActionBarUseSystemColor (void) const;

		virtual LNCLASSID	GetClassID (void) const
								{ return (LNCLASSID_LNACTIONS); }
		LNINT				GetCount (void) const;

		LNSTATUS			Insert (LNINT position, const LNAction & newAction);

		LNSTATUS			SetActionBarBackgroundColor (const LNColor &newColor);
		LNSTATUS			SetActionBarLineColor (const LNColor &newColor);
		LNSTATUS			SetActionBarLineLength (LNINT newLength);
		LNSTATUS			SetActionBarLineStyle (LNACTIONBARLINESTYLE newStyle);
		LNSTATUS			SetActionBarLineType (LNACTIONBARLINETYPE newType);
		LNSTATUS			SetActionBarUseSystemColor (LNBOOL newFlag);

private:
		LNActions (LNNoteBody * noteb, LNActionsBody * itemb) :
			LNItem(noteb, (LNItemBody *) itemb) {}
		LNActionsBody * GetActionsBody (void) const;


		LNINT			GetSize () const;
		LNSTATUS		Load (LNNoteBody * pNote, LNBOOL createDefaults);
		LNSTATUS		PrepareToModify (LNBOOL createBody);
		LNSTATUS		SetNewActions (LNNoteBody * pNoteBody) const;
};

#endif
