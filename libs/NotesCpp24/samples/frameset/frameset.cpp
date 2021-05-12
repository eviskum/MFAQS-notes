/****************************************************************************

	Program:    FRAMESET

	File:       FRAMESET.CPP

	Syntax:     frameset 

	Comment:    the sample works with local frameset.nsf database.

	Description:
		This program illustrates how to build frameset programmatically
		from scratch using database resources.

****************************************************************************/

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE 512

char CommandBuf[80];

int main(int argc, char *argv[])
{
	LNNotesSession	Session;

	cout << "Running FRAMESET..." << endl << endl;

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try 
	{
		// Initialize the C++ API.
		Session.Init(argc, argv);

		LNDatabase		Db;
		LNString		DbFilename("frameset.nsf");
		LNString        ViewName("Frameset Classes"); 
		LNString		FramesetName("Home Frameset");
		LNString		BannerPageName("Banner Page");
		LNString		NavigatorName("Navigator");

		// Get the specified database, and open it.
		Session.GetDatabase(DbFilename, &Db);
		Db.Open();

		// Check if frameset exists and remove it
		if(Db.FramesetExists(FramesetName))
			Db.DeleteFrameset(FramesetName);

		// We are going to build a frameset which displays banner in the upper frame,
		// navigator with links in the left frame, and document's content
		// in the bottom frame.

		// Step one. Create primitive frameset with a single horizontal split.

		LNFrameset frameset;
		LNFrameSplitOptions options;
		options.SetVertical(FALSE);

		//It is important to name frames. Name serves as a frame id.
		// We don't care what is the name of the bottom frame here,
		// because we are going to split it further down the road.
		options.SetFirstFrameName("Top Frame");

		// Other (default) split options: 1:4 ratio for 
		// the heights of the frames
		Db.CreateFrameset(FramesetName, options, &frameset);

		LNFrame topFrame, bottomFrame, leftBottomFrame, rightBottomFrame;

		// Get access to the top frame object.
		frameset.GetFrame(options.GetFirstFrameName(), &topFrame);

		// GetAccess to the bottom frame object. We did not specified
		// the name for it, and a default name was assigned on creation.
		// The leftBottomFrame is used here, because that's what it is going
		// to be ultimately, after the second split.
		frameset.GetFrame(options.GetSecondFrameName(), &leftBottomFrame);

		// Step two. 
		// We are going to split bottom frame vertically.
		// After the split the frame that has been splitted represents
		// the first frame of the two newly generated frames 
		// ( first means left - for horisontal, and top - for vertical split).
		// The frame keeps its original properties and content. The other frame
		// is returned as the second argument of the Split call.
		options.SetVertical(TRUE);
		options.SetFirstFrameName("Left Bottom Frame");
		options.SetSecondFrameName("Right Bottom Frame");

		// We also want to change the sizes ratio.
		// For that we specify percentage:
		options.SetFirstFrameSize(25);

		leftBottomFrame.Split(options,&rightBottomFrame);

		// Step 3. Add content to frames.

		// 1. Upper frame will contain a banner page.
		LNPage page;
		Db.GetPage(BannerPageName, &page);

		TIMEDATE td;
		memcpy(&td, Db.GetReplicaID(), sizeof(TIMEDATE));
		topFrame.SetNamedElement(BannerPageName, LNNAMEDELEMENT_PAGE, td);

		// We want it to be fixed size with no scrolling
		topFrame.SetAllowResizing(FALSE);
		topFrame.SetScrollType(LNFRAMESCROLLTYPE_NEVER);

		// 2. Left bottom conains navigator with links.
		leftBottomFrame.SetNamedElement(NavigatorName, LNNAMEDELEMENT_NAVIGATOR, td);

		// We want to be able to move vertical split bar, 
		// but we don't need scrolling in the left bottom frame
		leftBottomFrame.SetAllowResizing(TRUE);
		leftBottomFrame.SetScrollType(LNFRAMESCROLLTYPE_NEVER);

		// We want linked documents to open in the right bottom frame.
		// The following call sets target frame for all links in the left frame.
		leftBottomFrame.SetDefaultTargetName(rightBottomFrame.GetFrameName());

		// 3. Right bottom frame will contain link to the first document 
		// in the "Topics" view.
		LNViewFolder view;
		Db.GetViewFolder(ViewName, &view);
		view.Open();
		LNVFEntry entry;
		view.GotoFirst(&entry);
		LNDocument doc;
		entry.GetDocument(&doc);
		LNDocumentLink link(view, doc);
		rightBottomFrame.SetLink(link);

		// Bottom frame displays documents - turn scrolling on.
		rightBottomFrame.SetAllowResizing(TRUE);
		rightBottomFrame.SetScrollType(LNFRAMESCROLLTYPE_AUTO);

		// In addidition we want current time to appear in the title
		// of the browser window when we open the database.
		LNFormula formula("@Text(@Time(@Now))");
		frameset.SetWindowTitleFormula(formula);

		//Examine what we got
		LNINT count = frameset.GetFrameCount();
		cout << "The number of frames : " << count << endl;
		for(LNINT i = 0; i < count; i++)
		{
			LNFrame frame = frameset[ i ];
			cout << endl <<"Frame name : " << frame.GetFrameName() << endl << " ";

			switch(frame.GetContentType())
			{
			case LNFRAMECONTENTTYPE_URL:
				cout << "URL : " << frame.GetURL() << endl;
				break;
			case LNFRAMECONTENTTYPE_URL_FORMULA:
				{
					LNFormula formula;
					frame.GetURLFormula(&formula);
					cout << "URL formula : " << formula.GetText() << endl;
				}
				break;
			case LNFRAMECONTENTTYPE_VIEW_LINK:
				{
					LNViewLink link;
					frame.GetLink(&link);
					LNViewFolder view;
					link.GetLinkedView(&view);
					cout << "View link. View name : " << view.GetName() << endl;
				}
				break;
			case LNFRAMECONTENTTYPE_DOCUMENT_LINK:
				{
					LNDocumentLink link;
					frame.GetLink(&link);
					LNDocument doc;
					link.GetLinkedDocument(&doc);
					cout << "Document link. Document UNID : " << doc.GetUniversalID() << endl;
				}
				break;
			case LNFRAMECONTENTTYPE_ANCHOR_LINK:
				{
					LNAnchorLink link;
					frame.GetLink(&link);
					LNString anchorText = link.GetAnchorText();
					cout << "Anchor link. Anchor text : " << anchorText << endl;
				}
				break;
			case LNFRAMECONTENTTYPE_NAMED_ELEMENT:
				{
					LNString name;
					LNNAMEDELEMENT type;
					TIMEDATE replicaID;
					frame.GetNamedElement(&name, &type, &replicaID);
					cout << "Named element. Name : " << name << endl;
				}
				break;
			case LNFRAMECONTENTTYPE_NAMED_ELEMENT_SPECIAL:
				cout << "Special named element" << endl;
				break;
			case LNFRAMECONTENTTYPE_NAMED_ELEMENT_FORMULA:
				{
					LNFormula formula;
					LNNAMEDELEMENT type;
					TIMEDATE replicaID;
					frame.GetNamedElementFormula(&formula, &type, &replicaID);
					cout << "Named element formula : " << formula.GetText() << endl; 
				}
				break;
			default:
				break;
			}
		}
		frameset.Save();
		frameset.Close();
		Db.Close();

		// We are done
		Session.Term();
	}
	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	cout << endl;
		
	// All done.
	return(0);
}


