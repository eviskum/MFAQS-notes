(c) 1998-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software 
Development Kit Agreement (in the apilicns.txt file in the 
notescpp directory of this toolkit), Restricted Rights for U.S. 
government users, and applicable export regulations.


PROGRAM
-------
button - Notes C++ API sample program that is packaged as an ActiveX 
control. The control is a button that is placed into an HTML page. 
When a user presses this button, the program opens rtxtsamp.nsf database 
and creates a new document there. Inside that document, it places a URL 
link to Lotus web page and also creates an attachment from the HTML file 
of the web page that contains the button.


ENVIRONMENTS
------------

Windows NT (32-bit)
Windows 95 (32-bit)

This program requires the use of Microsoft Visual C++ Version 5.0 and later IDE.


FILES
-----
axbutton.cpp 	- C++ API Specific implementaion of the above actions.

axbutton.hpp 	- C++ API Specific definition of the above actions.

rtxtsamp.nsf    - Sample Notes database (in NOTEDATA directory).

button.html     - Source for the HTML page that contains Button control.

readme.txt	- This file.  Specifies what is needed to use this example.


BUILDING the ActiveX Sample
---------------------------
To recreate the source code for this program you may create the ActiveX sample 
in an existing workspace or a new workspace.  If you decide to create a new
workspace you will need to set up your environment in the Microsoft Visual C++ 
IDE.  Please refer to the "Notes C++ User Guide, Chapter 2, 32 Bit Windows, 
About compiling" first. Then follow these steps:


1.	Open Developer Studio. Click on "New" under the File menu and select the
	Projects tab in the resulting dialog box that appears.

2.	Choose MFC ActiveX ControlWizard as the application type.

3.	Enter, (or navigate to) the location of the ActiveX sample directory.
	i.e. c:\notescpp\samples\activex\

4.	Enter the project name "Button" (without the quotes) which will 
	be appended to location.

5.	Click OK. Please note that Create New Workspace and Win 32 are 
	selected by default.

6.	The dialog "Step 1 of 2" will appear. You can leave the default 
	setting and click next.

7.	Very Important:	The dialog "Step 2 of 2" will appear. Select 
	"BUTTON" from the combo-box labeled "Which window class if any 
	should this control subclass?".

8.	Click Finish to generate the project. Information about the project
	will be displayed when the files have been created in the specified
	directory.   While this is happening, you may or may not get a dialog
	box warning you that the button object already exists.  You can just
	ignore this box if it comes up since you are re-creating the button
	control again and do not care about any previous ones from the sample
	that were registered when you were trying it out for the first time.

9. 	Copy the files AXButton.cpp and AXButton.hpp to your Button project.

10.	Add the files AXButton.cpp and AXButton.hpp to your Button project.

11.	Open the file ButtonCtl.cpp.

12.	Add #include "AXButton.hpp" to ButtonCtl.cpp.

13.	Add a call to the function LaunchSample() to the existing member 
	function CButtonCtrl::OnOcmCommand() as shown below.

	LRESULT CButtonCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
	{
		...
		// TODO: Switch on wNotifyCode here.
		LaunchSample(wNotifyCode);
		return 0;
	}

14.	(Optional) Add a call to the function SetText("Attach!"); to the 
	existing member function CButtonCtrl::OnResetState() as shown below.

	void CButtonCtrl::OnResetState()
	{
		...
		// TODO: Reset any other control state here.
		SetText("Attach!");
	}

15.	Set up the build environment if needed and build the button.ocx.
	This includes setting a 'W32' pre-processor definition (C/C++|General),
	adding 'notescpp\include' to your include path (C/C++|Preprocessor)
	and adding 'notescpp.lib' to your linker libraries.

16.	To test the OCX with the button.html file provided you may need
	change the CLASSID in button.html to match the UUID in button.odl 
	file.
	
	button.odl:
	//  Class information for CButtonCtrl
	[ uuid(0BB958C7-5CA0-11D2-BBE4-00609770B24F),

	button.html:
	<CENTER><OBJECT 
		CLASSID="clsid:0BB958C7-5CA0-11D2-BBE4-00609770B24F"
		ID=hresultcontrol
	></OBJECT></CENTER>


RUNNING ActiveX
----------------
This sample program is designed to work with the sample database RTXTSAMP.NSF 
and the file Button.html. Copy these files to your Notes data directory. 

Note: Make sure that the Notes directory and the C++ API dll directory
      are both in your path.

1.	Register the button control (button.ocx file).
	Syntax: regsvr32 <Full Path> button.ocx.
	(If you build your application in the Developer Studio IDE this step 
	will be done for you.)	

2.	Open button.html in a web browser that supports ActiveX controls. 
	(Note: Some versions of Netscape may NOT support ActiveX controls).

3.	Click on the button that you see on that page.

If you recreate the source code from Microsoft ActiveX Button sample,
you can either try the program in the ActiveX Control Test Container, 
available from the Tools menu in Microsoft Visual C++ IDE, or you can 
replace the clsid in button.html page with the clsid of your newly 
created control, and run the sample from the web page.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if the ActiveX sample worked correctly:

Use Notes to open RTXTSAMP.NSF

Find a new document there. The attachment item should be appended to the 
document.
	   
Find a URL link to www.lotus.com there. Click on it and make sure that Notes 
loads that page in a web browser.

