//===========================================================================
//
// Module:  LNRTELEM.HPP
//
// Description:
//
//  Class library definition for LNRTElement and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTELEM_HPP
#define LNRTELEM_HPP



class LNIMPEXPCL LNRTElement : public LNRTObject
{


public:
	
	LNRTElement();
	LNRTElement(const LNRTObject &object);
	LNRTElement(const LNRTElement &element);

	~LNRTElement();
	
	LNRTElement& operator=(const LNRTObject &object);
	LNRTElement& operator=(const LNRTElement &element);
	
	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTELEMENT; }

	LNSTATUS GetCursor(LNRTCursor *cursor) const;					 
	
protected:

	LNRTElement(LNRTElementBody *body);
	
	LNRTElement& operator=(LNRTElementBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};





// Default class for CDRecords we don't understand or haven't implemented yet.
class LNIMPEXPCL LNCompositeData : public LNRTElement
{
public:
	
	LNCompositeData();
	LNCompositeData( const LNRTObject &object );
	LNCompositeData( const LNCompositeData &compositeData );
	
	~LNCompositeData();
	
	LNCompositeData& operator=( const LNRTObject &object );
	LNCompositeData& operator=( const LNCompositeData &compositeData );

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNCOMPOSITEDATA; }

	WORD GetCDSignature() const;
	
 	virtual LNINT GetSize() const;

	LNSTATUS Read( LNINT bufsize, void *buf, LNINT offset = 0 ) const;

	LNSTATUS ReadODS( WORD odstype, void *buf, LNINT offset = 0 ) const;

	LNSTATUS Write( LNINT bufsize, void *buf, LNINT offset = 0 );

	LNSTATUS WriteODS( WORD odstype, void *buf, LNINT offset = 0 );	

protected:

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

