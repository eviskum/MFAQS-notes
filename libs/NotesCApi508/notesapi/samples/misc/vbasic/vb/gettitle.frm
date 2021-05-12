VERSION 4.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Get Title"
   ClientHeight    =   4020
   ClientLeft      =   1095
   ClientTop       =   1485
   ClientWidth     =   7365
   BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   4425
   Left            =   1035
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   4020
   ScaleWidth      =   7365
   Top             =   1140
   Width           =   7485
   Begin VB.TextBox Result 
      Appearance      =   0  'Flat
      Height          =   735
      Left            =   1560
      TabIndex        =   1
      Top             =   3000
      Width           =   4215
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Get the title..."
      Height          =   1095
      Left            =   2520
      TabIndex        =   0
      Top             =   1440
      Width           =   2175
   End
   Begin VB.TextBox FileName 
      Appearance      =   0  'Flat
      Height          =   495
      Left            =   2640
      TabIndex        =   2
      Top             =   360
      Width           =   3855
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Enter the filename of a Notes database:"
      ForeColor       =   &H80000008&
      Height          =   495
      Left            =   600
      TabIndex        =   3
      Top             =   360
      Width           =   1935
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub Command1_Click()


' Every API wrapper function returns either "success" or "failure"
' with these return codes.

    Const API_SUCCESS = 0
    Const API_FAILURE = 1

' These strings are modified by the API calls, so we must make them
' as long as the API might possibly need.

    Dim database_title As String * 256
    Dim error_msg As String * 256

' The API wrappers return their status into this variable.

    Dim api_error As Integer


' Initialize Notes. (This call is a wrapper for the NotesInit API call.)
'
' Note that on an error, we set the output dialog box to an error message.

    api_error = Start_Notes()
    If (api_error <> API_SUCCESS) Then
        Result.text = "ERROR: Unable to initialize Notes"
        Exit Sub
    End If

' Get the filename of the Notes database from the dialog box. The filename
' must be relative to the Notes data directory, since that is how NSFDbOpen
' works.

    database_filename$ = LTrim$(RTrim$(FileName.text))

' Issue the wrapper call to open the database.
'
' Note that on an error, we issue a wrapper call to get the text of the
' error message. The wrapper DLL always stores the last error code returned
' by the API, for this purpose.

    api_error = Open_Notes_Database(database_filename$)
    If (api_error <> API_SUCCESS) Then
        api_error = Get_Notes_Error_Message(error_msg)
        Result.text = error_msg
        api_error = Stop_Notes()
        Exit Sub
    End If

' Get the title of the database.
'
' Note that we clean up completely before exiting on an error.

    api_error = Get_Notes_Db_Title(database_title)
    If (api_error <> API_SUCCESS) Then
        api_error = Get_Notes_Error_Message(error_msg)
        Result.text = error_msg
        api_error = Close_Notes_Database()
        api_error = Stop_Notes()
        Exit Sub
    End If

' Set the output to the Notes database title that we found.
    
    Result.text = RTrim$(database_title)

' Close the database.

    api_error = Close_Notes_Database()
    If (api_error <> API_SUCCESS) Then
        Result.text = "ERROR: Unable to close the database."
        api_error = Stop_Notes()
        Exit Sub
    End If
    
' Disconnect from Notes (wrapper for NotesTerm).

    api_error = Stop_Notes()
    If (api_error <> API_SUCCESS) Then
        Result.text = "ERROR: Problem while stopping Notes"
        Exit Sub
    End If

' End of Visual Basic procedure.

End Sub

