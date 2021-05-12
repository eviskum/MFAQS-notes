'
' Declare the DLL entry points for all the external functions.
'
Declare Function Start_Notes Lib "api_wrap.dll" () As Integer
Declare Function Stop_Notes Lib "api_wrap.dll" () As Integer
Declare Function Open_Notes_Database Lib "api_wrap.dll" (ByVal FileName As String) As Integer
Declare Function Close_Notes_Database Lib "api_wrap.dll" () As Integer
Declare Function Get_Notes_Db_Title Lib "api_wrap.dll" (ByVal Title As String) As Integer
Declare Function Get_Notes_Error_Message Lib "api_wrap.dll" (ByVal Message As String) As Integer



