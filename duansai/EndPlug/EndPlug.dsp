# Microsoft Developer Studio Project File - Name="EndPlug" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=EndPlug - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EndPlug.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EndPlug.mak" CFG="EndPlug - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EndPlug - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EndPlug - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EndPlug - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\lib\MVGigE.lib /nologo /subsystem:windows /machine:I386 /out:"../Release/EndPlug.exe"

!ELSEIF  "$(CFG)" == "EndPlug - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\lib\MVGigE.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../Debug/EndPlug.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "EndPlug - Win32 Release"
# Name "EndPlug - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADOConnect.cpp
# End Source File
# Begin Source File

SOURCE=.\Camera1.cpp
# End Source File
# Begin Source File

SOURCE=.\Camera2.cpp
# End Source File
# Begin Source File

SOURCE=.\Camera3.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=.\CDIB.CPP
# End Source File
# Begin Source File

SOURCE=.\CmeraInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DealImageData.cpp
# End Source File
# Begin Source File

SOURCE=.\EndPlug.cpp
# End Source File
# Begin Source File

SOURCE=.\EndPlug.rc
# End Source File
# Begin Source File

SOURCE=.\EndPlugDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOperation.cpp
# End Source File
# Begin Source File

SOURCE=.\HegeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ManiGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ManiPular1.cpp
# End Source File
# Begin Source File

SOURCE=.\ManiPular2.cpp
# End Source File
# Begin Source File

SOURCE=.\NHegeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StopWatch.cpp
# End Source File
# Begin Source File

SOURCE=.\StoreLaterImageInfor.cpp
# End Source File
# Begin Source File

SOURCE=.\TestBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\TestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ThreadPool.cpp
# End Source File
# Begin Source File

SOURCE=.\TransferImage.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewEndPlug.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADOConnect.h
# End Source File
# Begin Source File

SOURCE=.\Camera1.h
# End Source File
# Begin Source File

SOURCE=.\Camera2.h
# End Source File
# Begin Source File

SOURCE=.\Camera3.h
# End Source File
# Begin Source File

SOURCE=.\CameraGroupBox.h
# End Source File
# Begin Source File

SOURCE=.\Cdib.h
# End Source File
# Begin Source File

SOURCE=.\CmeraInterface.h
# End Source File
# Begin Source File

SOURCE=.\DealImageData.h
# End Source File
# Begin Source File

SOURCE=.\EndPlug.h
# End Source File
# Begin Source File

SOURCE=.\EndPlugDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileOperation.h
# End Source File
# Begin Source File

SOURCE=.\HegeDlg.h
# End Source File
# Begin Source File

SOURCE=.\ManiGroupBox.h
# End Source File
# Begin Source File

SOURCE=.\ManiPular1.h
# End Source File
# Begin Source File

SOURCE=.\ManiPular2.h
# End Source File
# Begin Source File

SOURCE=.\NHegeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StopWatch.h
# End Source File
# Begin Source File

SOURCE=.\StoreLaterImageInfor.h
# End Source File
# Begin Source File

SOURCE=.\StructData.h
# End Source File
# Begin Source File

SOURCE=.\TestBtn.h
# End Source File
# Begin Source File

SOURCE=.\TestDlg.h
# End Source File
# Begin Source File

SOURCE=.\ThreadPool.h
# End Source File
# Begin Source File

SOURCE=.\TransferImage.h
# End Source File
# Begin Source File

SOURCE=.\ViewEndPlug.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BkGround.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EndPlug.ico
# End Source File
# Begin Source File

SOURCE=.\res\EndPlug.rc2
# End Source File
# Begin Source File

SOURCE=.\res\gray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo_2.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo_4.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo_5.ico
# End Source File
# Begin Source File

SOURCE=.\res\manipulator.bmp
# End Source File
# Begin Source File

SOURCE=.\res\normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\warning.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\download.png
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
