//===========================================================================
//
// Module:  LNGRPHIC.HPP
//
// Description:
//
//		Class library definition for the LNRTGraphic and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNGRPHIC_HPP
#define LNGRPHIC_HPP


//	class definition for LNRTGraphic

enum LNGRAPHICFORMAT
{
	LNGRAPHICFORMAT_VERSION1 = CDGRAPHIC_VERSION1,
	LNGRAPHICFORMAT_VERSION2 = CDGRAPHIC_VERSION2,
	LNGRAPHICFORMAT_VERSION3 = CDGRAPHIC_VERSION3
};


class LNIMPEXPCL LNGraphic : public LNRTElement
{
	friend class LNRTOLEObjectBody;
	friend class LNRTAttachmentBody;
	friend class LNRTInputParser;

public:

	LNGraphic();
	LNGraphic(const LNRTObject &other);
	LNGraphic(const LNGraphic &graphic);

	~LNGraphic();

	LNGraphic&			operator=(const LNRTObject &object);
	LNGraphic&			operator=(const LNGraphic &graphic);

	LNSTATUS			GetBitmap(LNBitmap *bitmap) const;

	virtual LNCLASSID	GetClassID() const { return LNCLASSID_LNGRAPHIC; };
	
	LNINT				GetDestinationHeight(LNBOOL *pixelunits) const;
	
	LNINT				GetDestinationWidth(LNBOOL *pixelunits) const;

	LNGRAPHICFORMAT		GetGraphicFormat() const;

	LNSTATUS			GetMetafile(LNMetafile *metaFile) const;

	LNBOOL				IsResized() const;

protected:
	LNGraphic (LNGraphicBody * pBody);

	LNGraphic &			operator=(LNGraphicBody * pBody);

	virtual void		ValidateRTType(const LNRTObject &other) const;
	virtual void		ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNGraphicBody		*GetGraphicBody() const;
};


#endif

