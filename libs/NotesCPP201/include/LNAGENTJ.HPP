//===========================================================================
//
// Module:		LNAGENTJ.HPP
//
// Description:
//
//		Class library definition for the LNAgentJava... classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNAGENTJ_HPP
#define LNAGENTJ_HPP


//
// LNAgentJava class declaration
//
class LNIMPEXPCL LNAgentJava : public  LNSmartPtr
{
	friend class LNAgent;
public:

	LNAgentJava ();

	LNAgentJava (const LNAgentJava & other);

	~LNAgentJava ();

	LNAgentJava & operator= (const LNAgentJava &other);

	LNSTATUS ExportFile( const LNString &name, const LNString &path = "" ) const;

	LNSTATUS ExportAllFiles(const LNString &path = "") const; 

	LNString GetBaseClassName () const;

	LNCLASSID GetClassID () const { return LNCLASSID_LNAGENTJAVA;}

	LNString GetCodePath() const;

	LNText GetFilenames() const;

	LNSTATUS ImportFile( const LNString &filename, const LNString &path = "");

	LNSTATUS ImportFiles(const LNText &filenames, const LNString &path = "");

	LNSTATUS ReimportAllFiles( const LNString &path = "" );

	LNSTATUS ReimportFile (const LNString &filename, const LNString &path = "");

	LNSTATUS RemoveAllFiles();

	LNSTATUS RemoveFile(const LNString &filename);

	LNSTATUS ReorderFilename( const LNString &filename, LNINT newPosition );

	LNSTATUS SetBaseClassName (const LNString &name);

	LNSTATUS SetCodePath ( const LNString &path );

protected:

	LNAgent GetAgent() const;

	LNSTATUS LoadJavaCodeInfo();

	LNSTATUS SaveJavaCodeInfo();

	LNAgentJavaBody *GetAgentJavaBody() const { return (LNAgentJavaBody *)Body; };

	LNAgentJava ( const LNString &classname, 
						  const LNString &path, 
						  const LNText &filenames,
						  LNAgentBody *agentBody);

	LNAgentJava (LNAgentBody *agentBody);
};

#endif
