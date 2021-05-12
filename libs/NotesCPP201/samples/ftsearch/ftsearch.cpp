//===========================================================================
//
//		Module:			FTSEARCH.CPP
//
//		Description:
//				Sample C++ API program that	performs a full	text search.
//
//		Syntax:			FTSEARCH [dbname] [options]
//
//				Where dbname = file	path name for the database to search.
//
//				Note: To run the sample you must copy the 'ftsearch' database
//					  to your Notes data directory and use 'ftsearch' as 
//					  the first command line argument. 
//					  
//					  If you do not supply any command line arguments 
//					  you will be prompted for arguments at run time and 
//					  the default arguments will be displayed.
//
//		   		      Supplying options without the dbname argument will
//				      generate an error. If you supply only the first argument,
//				      all the options will be set to their defaults.
//
//					  The sample is hard coded to search for QUERYSTRING which 
//					  is defined as 'documents' in the include file.
//
//				"options" may be one or more of the following in any order:
//														
//				w -	Whole words	only in	the	match. No stemming or partial words.
//					(Default is	to match stemming or partial words.)
//
//				t -	Thesaurus words	are	included in	match (similar word	matches).
//					(Default is	to not match on	thesaurus words.)
//
//				s -	Do not use a search	set	selected from a	particular author.
//					(Default is	to use a search	set. You will be prompted for an author.)
//
//				d -	Maximum	number of documents	to search (default = 100).	
//					There cannot be	a space	between	the	option letter and the 
//					number (i.e., "FTSEARCH	ftsearch.nsf wtsd25").
//
//				o -	Sort option	to use.	This parameter must	be followed	by a 
//					number between 1 and 3,	indicating the sort	option:
//
//					1 =	Sort by	relevance (default)
//					2 =	Sort by	date (newest first)
//					3 =	Sort by	date (oldest first)
//
//					There cannot be	a space	between	the	option letter and the 
//					number (i.e., "FTSEARCH	ftsearch.nsf wtsd25o3").
//
//				v -	Type of	view to	use	in the search. This	parameter must be
//					followed by	a number between 1 and 4, indicating the 
//					view type:
//
//					1 =	By author
//					2 =	Categorize
//					3 =	By main	topics only
//					4 =	By main	view (default)
//
//					There cannot be	a space	between	the	option letter and the 
//					number (i.e., "FTSEARCH	ftsearch.nsf wtsd25o3v2").
//
//===========================================================================
//
// Copyright (c) 1997 Lotus	Development	Corporation. All rights	reserved.
// This	software is	subject	to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable	export regulations.
//
//===========================================================================

#ifndef	FTSEARCH_HPP
#include "ftsearch.hpp"
#endif

// Parameter Strings.

IOParameter				CommandBuf;
IOParameter				PromptString1;
IOParameter				ParamString1;
IOParameter				PromptString2;
IOParameter				ParamString2;
IOParameter				PromptString3;
IOParameter				ParamString3;
IOParameter				PromptString4;
IOParameter				ParamString4;

// Parameter numbers.

IOParameter				PromptNumber1;
LNINT					ParamNumber1;
IOParameter				PromptNumber2;
LNINT					ParamNumber2;
IOParameter				PromptNumber3;
LNINT					ParamNumber3;

//---------------------------------------------------------------------------
//
//		MAIN
//
//---------------------------------------------------------------------------
int	main(int argc, char	*argv[])
{
	int				ProgramStatus =	0;
	LNNotesSession	Session; 

#if	defined(MAC)
	// Initialize things for the Macintosh.
	InitGraf(&thePort);		InitFonts();
	InitWindows(); 
	InitDialogs(0);
	SetApplLimit(GetApplLimit()-8192); 
	MaxApplZone();
	MoreMasters(); 
	MoreMasters(); 
	MoreMasters();
#endif

	// Begin TRY block.	
	// Throw all errors	encountered	during command execution.
	LNSetThrowAllErrors	(TRUE);

	try
	{
		LNDatetime		  	LastIndex;
		LNString		  	DatabasePath;
		LNINT			  	MaxDocuments;
		LNINT			  	ViewNumber;
		LNINT			  	SortOption;
		LNBOOL			  	IsStemWords;
		LNBOOL			  	IsThesaurusWords;
		LNBOOL			  	IsSearchSet;
		LNDatabase		  	Db;
		LNFTSearchOptions 	SearchOptions;
		LNDocumentArray		SearchResult;

		// Initialize the Notes	session.
		Session.Init(argc, argv);

		// Parse the argument list.		 
		ProcessArguments ( argc, argv, &DatabasePath, &IsStemWords,	
						   &IsThesaurusWords, &IsSearchSet,	&MaxDocuments,
						   &SortOption,	&ViewNumber		  );

		// Verify that 'ftsearch' is used as the database for the sample
		if ( (DatabasePath != "ftsearch") && (DatabasePath != "ftsearch.nsf") )
		{
			cout << "For this sample you must use the database 'ftsearch'" << endl;
			goto Term;
		}

		// Get the search database.
		Session.GetDatabase(DatabasePath, &Db);

		// Open	the	database.
		Db.Open();

		// Create FT index.
		CreateFTIndex(Db);

		// Get the date/time the database was last indexed.
		Db.GetLastFTIndexed(&LastIndex);
		LNString strLastIndex =	LastIndex;
		cout <<	"The Last Index Time Was: "	<< strLastIndex	<< endl	<< endl;

		// Set the search options.
		SetFTSearchOption(&SearchOptions, MaxDocuments,	SortOption,	IsStemWords, IsThesaurusWords);

		// Search the specified	string in the database.
		if ( IsSearchSet )
		{
			LNNoteArray	SearchSet;

			// Set the search set.
			SetFTSearchSet(Db, &SearchSet);
			Db.FTSearch(QUERYSTRING, &SearchResult,	SearchOptions, SearchSet);
		}
		else
			Db.FTSearch(QUERYSTRING, &SearchResult,	SearchOptions);

		cout <<	"Database search follows:" << endl
			 <<	"This search uses Search Options" << endl
			 <<	"and/or Search Set chosen from above." << endl;

		// Print the note ID and FT	score for each document	
		// in the search result.
		PrintSearchResult(SearchResult);

		// Do an FT	search on a	chosen view	and	print result. 
		ViewFolderFTSearch(Db, ViewNumber);

		// Close the database.
		Db.Close();
	}

	// Display the error message when an error occurs.
	catch (LNSTATUS	lnerror)
	{
		char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf);
		cout <<	"\nError:  " <<	ErrorBuf <<	endl;
		ProgramStatus =	2;
	}

	catch (const char *pErrorMessage)
	{
		cout <<	"\nError: "	<< pErrorMessage <<	endl;
		ProgramStatus =	1;
	}


Term:
	// Terminate the Notes session.
	Session.Term();

	cout <<	"All Done. Hit return to exit: ";
	cin	>> CommandBuf;

	return (ProgramStatus);

} // END main()

//---------------------------------------------------------------------------
//
// Name:
//				CreateFTIndex
//
// Description:
//				Creates	a full text	index of the input parameter database.
//
//---------------------------------------------------------------------------
void CreateFTIndex(LNDatabase &Db)
{
	// Create the full text	index. 
	LNFTIndexStatistics	IndexStat;

	cout <<	endl <<	"Creating a Full Text Index for the database:" << endl << endl;

	Db.CreateFTIndex(LNFTINDEXFLAGS_DEFAULT, "", &IndexStat);

	// Print the indexing status.
	cout <<	"New documents added to the index: " <<	IndexStat.GetNumberOfDocsAdded() <<	endl;
	cout <<	"Revise documents re-indexed:      " <<	IndexStat.GetNumberOfDocsUpdated() << endl;
	cout <<	"Documents deleted from index:     " <<	IndexStat.GetNumberOfDocsDeleted() << endl;
	cout <<	"Total bytes indexed:              " <<	IndexStat.GetNumberOfDocsDeleted() << endl << endl;

} // END CreateFTIndex()

//---------------------------------------------------------------------------
//
// Name:
//				SetFTSearchOption
//
// Description:
//				Sets up	the	search options.
//---------------------------------------------------------------------------
void SetFTSearchOption(	LNFTSearchOptions	*SearchOptions,	
						LNINT			 	MaxDocuments,
						LNINT			 	SortOption,
						LNBOOL			 	IsStemWords,
						LNBOOL			 	IsThesaurusWords )
{
	// Set the maximum number of documents in result collection.
	SearchOptions->SetMaxDocuments(MaxDocuments);

	// Set the sorting order.
	if (SortOption == 3)
	{
		SearchOptions->SetSortOrder(LNFTSEARCHORDER_OLDEST_FIRST);
		cout <<	"The Search Options: Sort Order is: By Date, oldest first."	<< endl;
	}
	else if	(SortOption	== 2)
	{
		SearchOptions->SetSortOrder(LNFTSEARCHORDER_NEWEST_FIRST);
		cout <<	"The Search Options: Sort Order is: By Date, newest first."	<< endl;
	}
	else
	{
		SearchOptions->SetSortOrder(LNFTSEARCHORDER_BY_RELEVANCE);
		cout <<	"The Search Options: Sort Order is: By Relevance." << endl;
	}

	// Set whether word	stemming (partial-word matching) is	to be used.
	SearchOptions->SetStemWords(IsStemWords);

	// Set whether the thesaurus is	to be used;	default	is FALSE.
	SearchOptions->SetThesaurusWords(IsThesaurusWords);
	
} // END SetFTSearchOption()



//---------------------------------------------------------------------------
//
// Name:
//				SetFTSearchSet
//
// Description:
//				This function gets called if the boolean IsSearchSet is	TRUE. 
//---------------------------------------------------------------------------
void SetFTSearchSet(LNDatabase &Db,	LNNoteArray	*SearchSet )
{
	LNINT AuthorNumber = 6;

	// Set the search set.
	cout <<	endl <<	"You have chosen to search by author." << endl;
	cout <<	"     <1> Lois Baker" << endl;
	cout <<	"     <2> Sandy Bingham" <<	endl;
	cout <<	"     <3> Mark Chin" <<	endl;
	cout <<	"     <4> Maria Gonsalves" << endl;
	cout <<	"     <5> Robin Stephen" <<	endl;
	cout <<	"     <6> Harold Washington (default)" << endl;
	cout <<	"Select one from this list: [6] ";

	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		AuthorNumber = (LNINT)CommandBuf.StringToInteger();

	switch (AuthorNumber)
	{
	case 1:
		Db.Search("SELECT((From=\"Lois Baker\"))", SearchSet);
		break;
	case 2:
		Db.Search("SELECT((From=\"Sandy	Bingham\"))", SearchSet);
		break;
	case 3:
		Db.Search("SELECT((From=\"Mark Chin\"))", SearchSet);
		break;
	case 4:
		Db.Search("SELECT((From=\"Maria	Gonsalves\"))",	SearchSet);
		break;
	case 5:
		Db.Search("SELECT((From=\"Robin	Stephens\"))", SearchSet);
		break;
	default:
		Db.Search("SELECT((From=\"Harold Washington\"))", SearchSet);
		break;
	}

	cout <<	endl;

} // END SetFTSearchSet()


//---------------------------------------------------------------------------
//
// Name:
//				ViewFolderFTSearch
//
// Description:
//---------------------------------------------------------------------------
void ViewFolderFTSearch ( LNDatabase &Db,	LNINT ViewNumber )
{
LNViewFolder	ViewFolder;
LNVFNavigator	ViewSearchResult;

	switch (ViewNumber)
	{
		case 1:
			Db.GetViewFolder("By Author", &ViewFolder);
			break;
		case 2:
			Db.GetViewFolder("Categorized",	&ViewFolder);
			break;
		case 3:
			Db.GetViewFolder("Main Topics Only", &ViewFolder);
			break;
		default:
			Db.GetViewFolder("Main View", &ViewFolder);
			break;
	}

	// Open	the	view/folder.
	ViewFolder.Open();

	// Search the query	string under the specified view.
	ViewFolder.FTSearch(QUERYSTRING, &ViewSearchResult);

	cout <<	"ViewFolder search by chosen View follows:"	<< endl
		 <<	"This search only searches the selected"	<< endl
		 <<	"view for the string: \"" << QUERYSTRING <<	"\"." << endl;

	// Print the result.
	PrintSearchResult(ViewSearchResult);

} // END ViewFolderFTSearch()


//---------------------------------------------------------------------------
//
// Name:
//				PrintSearchResult
//
// Description:
//---------------------------------------------------------------------------
void PrintSearchResult(LNDocumentArray &SearchResult)
{
	// Check the SearchResult if returned from full	text searching.
	if (SearchResult.IsFTSearch() == TRUE)
	{
		// Get the number of documents in the result document array.
		LNINT DocCount = SearchResult.GetCount();
		cout <<	DocCount <<	" document(s) found on query: \""	<< QUERYSTRING << "\"" << endl;

		cout <<	"Document   FTScore  " << endl;
		for	(LNINT i=0;	i<DocCount;	i++)
		{
			LNDocument Doc(SearchResult[i]);

			// Print the document ID.
			cout <<	hex	<< Doc.GetNoteID() << "	   ";
			// Print the FT	Score of the document.
			cout <<	dec	<< Doc.GetFTSearchScore() << endl;
		}		
		
		cout <<	endl;
	}
	else
		cout <<	"The result set isn't from FTSearch" <<	endl;

} // END PrintSearchResult()

//---------------------------------------------------------------------------
//
// Name:
//				PrintSearchResult
//
// Description:
//---------------------------------------------------------------------------
void PrintSearchResult(LNVFNavigator &SearchResult)
{
	// Check the SearchResult if returned from full	text searching.
	if (SearchResult.IsFTSearch())
	{
		// Get the number of documents in the result document array.
		LNINT DocCount = SearchResult.GetEntryCount();
		cout <<	DocCount <<	" document(s) found on query: \""	<< QUERYSTRING << "\"" << endl;

		cout <<	"Document   FTScore  " << endl;
		for	(LNINT i=0;	i<DocCount;	i++)
		{
			LNVFEntry Doc(SearchResult[i]);

			// Print the document ID.
			cout <<	hex	<< Doc.GetNoteID() << "	   ";
			// Print the FT	Score of the document.
			cout <<	dec	<< Doc.GetFTSearchScore() << endl;
		}		
		
		cout <<	endl;
	}
	else
		cout <<	"The result set isn't from FTSearch" <<	endl;

} // END PrintSearchResult()



//---------------------------------------------------------------------------
//
// Name:
//				ProcessArguments
//
// Description:
//		Scan the input command line	and	sort out the input strings.
//		If no arguments	were supplied, prompt for them.
//
//		Throws exceptions:
//				char *			Argument error description
//---------------------------------------------------------------------------
void ProcessArguments (	int				argc,
						char			*argv[],
						LNString		*DatabasePath,
						LNBOOL			*IsStemWords,		// Use stemming	(partial-word matching)? TRUE or FALSE.
						LNBOOL			*IsThesaurusWords,	// Use thesaurus in	search?	TRUE or	FALSE.
						LNBOOL			*IsSearchSet,	  	// Whether to select docs from a particular	author.
						LNINT			*MaxDocuments,	  	// Maximum number of documents in result collection.
						LNINT			*SortOption,	  	// The sorting order.
						LNINT			*ViewNumber )	 	// The type	of view	to use in the search.

{
	LNBOOL prompt =	FALSE;

// Macintosh cannot	process	(argc, argv).
#if	defined(MAC)
	prompt = TRUE;
#else
	if (argc < 2)
		prompt = TRUE;	
#endif

	// Set up the default parameters first.
	InitDefaultParams();

	*DatabasePath			= ParamString1;
	*IsStemWords			= TRUE;
	*IsThesaurusWords		= FALSE;
	*IsSearchSet			= TRUE;
	*MaxDocuments			= ParamNumber1;
	*SortOption				= ParamNumber2;
	*ViewNumber				= ParamNumber3;

	// Check the command line.
	if (prompt)
	{
		// Get user	input data by prompting.
		GetArguments();
		*DatabasePath =	ParamString1;

		if(	(ParamString2[0] ==	'n') ||	(ParamString2[0] ==	'N') )
			*IsStemWords = FALSE;

		if(	(ParamString3[0] ==	'y') ||	(ParamString3[0] ==	'Y') )
			*IsThesaurusWords =	TRUE;

		if(	(ParamString4[0] ==	'n') ||	(ParamString4[0] ==	'N') )
			*IsSearchSet = FALSE;

		*MaxDocuments =	ParamNumber1;
		*SortOption	= ParamNumber2;
		*ViewNumber	= ParamNumber3;
	}
	else
	{
	int	i, j, number;

		// Parse the command line.
		*DatabasePath =	argv[1];
			
		for(i=2; i<argc; i++)
		{
		char *argstring	= argv[i];
		int	count =	strlen(argstring);

			for	(j=0; j<count; j++)
			{
				switch (argstring[j])
				{
				case 'W':
				case 'w':
					*IsStemWords = FALSE;
					break;
				
				case 'T':
				case 't':
					*IsThesaurusWords =	TRUE;
					break;

				case 'S':
				case 's':
					*IsSearchSet = FALSE;
					break;

				case 'D':
				case 'd':
					if ( (number = atoi( &argstring[(j+1)] ) ) ) 
						*MaxDocuments =	number;
					break;

				case 'O':
				case 'o':
					if ( (number = atoi( &argstring[(j+1)] ) ) ) 
						*SortOption	= number;
					break;

				case 'V':
				case 'v':
					if ( (number = atoi( &argstring[(j+1)] ) ) ) 
						*ViewNumber	= number;
					break;
				}

			} // END for (j=0; j<count;	j++)

		} // END for(i=2; i<argc; i++)

	} // END if	(argc <	2) ELSE

} // END ProcessArguments()


//---------------------------------------------------------------------------
//
// Name:
//				InitDefaultParams
//
// Description:
//				Set	up all the default parameter strings and numbers for user
//				input.	Called by ProcessArguments() if	no user	input params
//				were provided.
//
//				NOTE:
//						You	only need to edit this function	and	ProcessArguments() 
//						when creating a	new	sample.	 The rest of the user interface	
//						functions below	are	called by ProcessArguments() and are 
//						generic, which means that they can stay	the	same unless
//						you	increase or	decrease the number	of parameters to use.
//						Then you only need to cut or paste in one more or one less
//						block of the switch	statements in the functions	below.
//---------------------------------------------------------------------------
void InitDefaultParams()
{
	// Initialize default parameter	strings.

	PromptString1 =	 "File path name for the database to search     : [";
	ParamString1 = "ftsearch.nsf";

	PromptString2 =	 "Use Stemming Words? (partial word matches)    : [";
	ParamString2 = "Y";

	PromptString3 =	 "Use Thesaurus Words? (similar word matches)   : [";
	ParamString3 = "N";

	PromptString4 =	 "Select documents from particular author?      : [";
	ParamString4 = "Y";

	// Initialize default parameter	numbers.

	PromptNumber1 =	 "Max number of docs for the result collection  : [";
	ParamNumber1 = 100;

	PromptNumber2 << "\nThe sorting order for the result collection \n"
				  << "     <1> By Relevance	\n"
				  << "     <2> By Date (newest first) \n"
				  << "     <3> By Date (oldest first)               : [";
	ParamNumber2 = 1;

	PromptNumber3 << "\nThe kind of view to search under \n"
				  << "     <1> By Author \n"
				  << "     <2> Categorize \n"
				  << "     <3> By Main Topics only \n"
				  << "     <4> By Main View (default)               : [";
	ParamNumber3 = 4;

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//				GetArguments
//
// Description:
//				Allows the user	to change any or all of	the	input parameter	
//				IOParameter.  The inputs can also be left as they are if desired.
//---------------------------------------------------------------------------
void GetArguments()
{
	BOOL isCorrectData = FALSE;

	QueryArguments();

	while (!isCorrectData)
	{
		PrintArguments();

		cout <<		 "Are these current data settings correct?      : [Y] ";
		cin	>> CommandBuf;

		switch(	CommandBuf[0] )
		{
		case 'Y':
		case 'y':

			isCorrectData =	TRUE;							// All done, get out now!
			break;

		default:

			// Prompt again	for	anything other than	a "Y" or carriage return.
			if(	(CommandBuf) !=	(const char	*)"" )
				QueryArguments();
			else
				isCorrectData =	TRUE;					// All done, get out now!

		} // END switch

	} // END while

} // END GetArguments()


//---------------------------------------------------------------------------
//
// Name:
//				PrintArguments
//
// Description:
//				Prints out all of the current input	parameters to use.
//---------------------------------------------------------------------------
void PrintArguments()
{
	cout <<	endl;
	cout <<	"The Current Default Data Settings are:	" << endl;
	cout <<	endl;

	// Print out current parameter strings.
	cout <<	PromptString1 << ParamString1 << "]" <<	endl;
	cout <<	PromptString2 << ParamString2 << "]" <<	endl;
	cout <<	PromptString3 << ParamString3 << "]" <<	endl;
	cout <<	PromptString4 << ParamString4 << "]" <<	endl;

	// Print out current parameter numbers.
	cout <<	PromptNumber1 << ParamNumber1 << "]" <<	endl;
	cout <<	PromptNumber2 << ParamNumber2 << "]" <<	endl;
	cout <<	PromptNumber3 << ParamNumber3 << "]" <<	endl;
	cout <<	endl;

} // END PrintArguments()


//---------------------------------------------------------------------------
//
// Name:
//				QueryArguments
//
// Description:
//				Queries	the	user to	change any of the input	parameters.
//				A carriage return on any of	the	prompts	leaves it alone.
//---------------------------------------------------------------------------
void QueryArguments()
{
	cout <<	endl;
	cout <<	"Enter the following parameters (or hit Enter to accept default):" << endl;
	cout <<	endl;

	// Prompt for Strings....
	cout <<	PromptString1 << ParamString1 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamString1 = CommandBuf;

	cout <<	PromptString2 << ParamString2 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamString2 = CommandBuf;

	cout <<	PromptString3 << ParamString3 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamString3 = CommandBuf;

	cout <<	PromptString4 << ParamString4 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamString4 = CommandBuf;


	// Prompt for numbers.
	cout <<	PromptNumber1 << ParamNumber1 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamNumber1 = (LNINT)CommandBuf.StringToInteger();

	cout <<	PromptNumber2 << ParamNumber2 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamNumber2 = (LNINT)CommandBuf.StringToInteger();

	cout <<	PromptNumber3 << ParamNumber3 << "]> ";
	cin	>> CommandBuf;
	if(	(CommandBuf) !=	(const char	*)"" )
		ParamNumber3 = (LNINT)CommandBuf.StringToInteger();

} // END QueryArguments()



//===========================================================================
//
// IOPARAMETER Class Implementation
//
// Description:	
//				Implementation for a simple	generic	string buffer class
//				to hold	user input and output prompts.
//===========================================================================

//===========================================================================
// Constructors
//===========================================================================
IOParameter::IOParameter() // Default constructor.
{
	size =1; //	Null Terminator.
	
	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	pBuf[0]	= '\0';
}

//===========================================================================
IOParameter::IOParameter( const	char *Str )	// Init	with const string.
{
	size = strlen(Str) + 1;									// Size	of string +	null term.

	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, Str);
}


//===========================================================================
// Constructs a	decimal	radix string representation	of an integer.
IOParameter::IOParameter( const	int	Number )
{
	char	buf[16];												// Temporary buffer	for	characters.

	sprintf(buf, "%d", Number);

	size = strlen(buf) + 1;							// Size	of string +	null term.

	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, buf);
}


//===========================================================================
IOParameter::IOParameter( const	IOParameter	&Other ) //	Copy constructor.
{
	size = Other.size;

	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, Other.pBuf);
}

//===========================================================================
// Constructor using 2 IOParameter objects as input.
IOParameter::IOParameter( const	IOParameter& Prefix, const IOParameter&	Postfix)
{
	size = Prefix.size + Postfix.size -	1;

	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, Prefix.pBuf);
	strcat(pBuf, Postfix.pBuf);
}

//===========================================================================
// Subscript, etc.
//===========================================================================
char IOParameter::operator [] (int Index)
{
	char c;

	if (Index >	size)
		c =	'\0';
	else
		c =	pBuf[Index];

	return c;
}

//===========================================================================
// Assignment.
//===========================================================================
IOParameter	IOParameter::operator =	( const	IOParameter	&Other )
{
	if(pBuf)
		delete [] pBuf;

	size = Other.size;
	
	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, Other.pBuf);

	return *this;
}

//===========================================================================
IOParameter	IOParameter::operator =	( const	char *Str )
{
	size = strlen(Str) +1;

	if (pBuf)
		delete [] pBuf;
	
	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, Str);
	return *this;
}

//===========================================================================
// I/O operators.
//===========================================================================
ostream	&operator << ( ostream &Stream,	const IOParameter &Other )
{
	Stream << Other.pBuf;
	return Stream;
}

//===========================================================================
istream	&operator >> ( istream &Stream,	IOParameter	&Other )
{
	const int buflen = 255;									// Arbitrary size, change if needed.
	char t[buflen];																							// temp	string... 
	int	len;

	for	(len=0;	len<buflen;	len++)
	{
		Stream.get(t[len]);
		if (t[len] == '\n')	 //	Newline	character
			break;
		if (t[len] == '\b')	 //	Backspace character
		{
			if(len)
			{
				len--;
				// cout	<< "'\b'";	// For debug only.
			}
		}
	}

	t[len] = '\0';
	len++;

	if(Other.pBuf)
		delete [] Other.pBuf;

	if (! (Other.pBuf =	new	char[len]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	Other.size = len;

	strcpy(Other.pBuf, t);
	return Stream;

} // END istream &operator >>

//===========================================================================
// Concatenate.
//===========================================================================
IOParameter	IOParameter::operator +	( const	IOParameter	&Other ) //	Cat	2 IOParameter objects.
{
	return IOParameter(	*this, Other );
}

//===========================================================================
IOParameter	IOParameter::operator +	( const	char *Str )	// Cat IOParameter and string.
{
	return IOParameter(	*this, IOParameter(Str)	);
}

//===========================================================================
IOParameter	operator + ( char *Str,	const IOParameter &Other ) // Cat string with IOParameter.
{
	return IOParameter(	IOParameter(Str), Other	);
}

//===========================================================================
IOParameter& IOParameter::operator << (	const IOParameter &Other ) // Cat 2	IOParameter	objects.
{
	IOParameter	TempString(*this);

	size = TempString.size + Other.size	- 1;

	if (pBuf)
		delete [] pBuf;

	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, TempString.pBuf);
	strcat(pBuf, Other.pBuf);

	return *this;
}

//===========================================================================
IOParameter& IOParameter::operator << (	const char *Str	) // Cat IOParameter and string.
{
	IOParameter	TempString(*this);
	IOParameter	Other(Str);

	size = TempString.size + Other.size	- 1;

	if (pBuf)
		delete [] pBuf;

	if(! (pBuf = new char[size]) )
	{
		cout <<	"IOParameter:  Allocation Error!!!"	<< endl;
		exit(1);
	}

	strcpy(pBuf, TempString.pBuf);
	strcat(pBuf, Other.pBuf);

	return *this;	
}


