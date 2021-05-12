//===========================================================================
//
// Module:  LNHOTLNK.HPP
//
// Description:
//
//  Class library definition for LNLinkHotspot and related classes.
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNHOTLNK_HPP
#define LNHOTLNK_HPP



class LNIMPEXPCL LNLinkHotspot : public LNHotspot
{

public:
	
	LNLinkHotspot();

	LNLinkHotspot(const LNRTObject &other);
	LNLinkHotspot(const LNLinkHotspot &other);
	
	LNLinkHotspot(const LNDatabaseLink &link, const LNString &text);
	LNLinkHotspot(const LNDatabaseLink &link, const LNGraphic &graphic);

	~LNLinkHotspot();
	
	LNLinkHotspot& operator=(const LNRTObject &other);
	LNLinkHotspot& operator=(const LNLinkHotspot &other);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLINKHOTSPOT; }

	LNSTATUS GetLink(LNDatabaseLink *link) const;

	LNSTATUS SetLink(const LNDatabaseLink &link);

protected:

	LNLinkHotspot(const LNDatabaseLink &link);

	LNLinkHotspot(LNLinkHotspotBody *body);

	LNLinkHotspot& operator=(LNLinkHotspotBody *body);

	LNLinkHotspotBody* GetLinkHotspotBody() const { return (LNLinkHotspotBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

