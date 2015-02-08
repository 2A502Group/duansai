; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEndPlugDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "endplug.h"
LastPage=0

ClassCount=19
Class1=CEndPlugApp
Class2=CAboutDlg
Class3=CEndPlugDlg
Class4=ViewEndPlug

ResourceCount=6
Resource1=IDD_NHEGEDLG
Resource2=IDD_ABOUTBOX
Class5=CTestBtn
Class6=EndPlug1
Class7=ManiPular1
Class8=ManiPular2
Class9=ManiGroupBox
Class10=CameraGroupBox
Class11=Camera1
Class12=Cmera2
Class13=Cmera3
Class14=Camera2
Class15=Camera3
Resource3=IDD_ENDPLUG_DIALOG
Class16=CHegeDlg
Resource4=IDD_HEGEDLG
Class17=CNHegeDlg
Resource5=IDD_TESTDLG
Class18=CTestDlg
Class19=CRotaSetDlg
Resource6=IDR_MENU1

[CLS:CEndPlugApp]
Type=0
BaseClass=CWinApp
HeaderFile=EndPlug.h
ImplementationFile=EndPlug.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=EndPlugDlg.cpp
ImplementationFile=EndPlugDlg.cpp

[CLS:CEndPlugDlg]
Type=0
BaseClass=CDialog
HeaderFile=EndPlugDlg.h
ImplementationFile=EndPlugDlg.cpp
LastObject=ID_EXIT
Filter=D
VirtualFilter=dWC

[CLS:ViewEndPlug]
Type=0
BaseClass=CStatic
HeaderFile=ViewEndPlug.h
ImplementationFile=ViewEndPlug.cpp
Filter=W
VirtualFilter=WC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ENDPLUG_DIALOG]
Type=1
Class=CEndPlugDlg
ControlCount=44
Control1=IDC_START,button,1342242827
Control2=IDC_MANISTATE,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CAMERASTATE,button,1342177287
Control6=IDC_MANIPULAR1,static,1342308352
Control7=IDC_MANIPULAR2,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CAMERA2,static,1342308352
Control12=IDC_CAMERA3,static,1342308352
Control13=IDC_CAMERA1,static,1342308352
Control14=IDC_SCROLLBAR_H,scrollbar,1342177280
Control15=IDC_SCROLLBAR_V,scrollbar,1342177281
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_LIST_LEADRAIL,SysListView32,1350631425
Control19=IDC_BTN_LEFT,button,1342242816
Control20=IDC_BTN_O,button,1342242816
Control21=IDC_BTN_RIGHT,button,1342242816
Control22=IDC_BTN_FORWARD,button,1342242816
Control23=IDC_BTN_BACK,button,1342242816
Control24=IDC_LIST_MANIPULAR_CERRECT,SysListView32,1350631425
Control25=IDC_BTN_MANIPULAR1_DOWN,button,1342242816
Control26=IDC_BTN_ORIGIN,button,1342242816
Control27=IDC_BTN_MANIPULAR2_DOWN,button,1342242816
Control28=IDC_BTN_MANIPULAR1_UP,button,1342242816
Control29=IDC_BTN_MANIPULAR2_GET,button,1342242816
Control30=IDC_STATIC,button,1342177287
Control31=IDC_LISTIDC_LIST_MANIPULAR,SysListView32,1350631425
Control32=IDC_LIST_CAMERA,SysListView32,1350631425
Control33=IDC_LIST_MOTOR,SysListView32,1350631425
Control34=IDC_STATIC,button,1342177287
Control35=IDC_VIEWWINDOW,static,1342308352
Control36=IDC_STATIC,button,1342177287
Control37=IDC_BUTTON_TEST,button,1342242816
Control38=IDC_BUTTON_SETTING,button,1342242816
Control39=IDC_BUTTON_EXIT,button,1342242816
Control40=IDC_BUTTON_PRINTREPORT,button,1342242816
Control41=IDC_BUTTON_ALGORITHM,button,1342242816
Control42=IDC_BUTTON_CORRECT,button,1342242816
Control43=IDC_BUTTON_GOODQUERY,button,1342242816
Control44=IDC_BUTTON_DEFECTQUERY,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CEndPlugDlg
Command1=ID_OPENPHOTO
Command2=ID_SAVEPHOTO
Command3=ID_SAVESETUP
Command4=ID_LOADSETUP
Command5=ID_PRINT
Command6=ID_PRINTSETUP
Command7=ID_PRINTPREVIEW
Command8=ID_EXIT
Command9=ID_PARAMETERSETUP
Command10=ID_AUTHORITYSETUP
Command11=ID_ROBORTCALIBRATION
Command12=ID_CAMERACALIBOTATION
Command13=ID_Averagefiltering
Command14=ID_Medianfiltering
Command15=ID_Edgedetection
Command16=ID_Thresholdsegmentation
Command17=ID_Houghtransform
Command18=ID_Classificationidentification
Command19=ID_Originalimage
Command20=ID_SystermStart
Command21=ID_Systemclose
Command22=ID_Qualified
Command23=ID_unqualified
Command24=ID_Bytime
Command25=ID_ByClass
Command26=ID_About
Command27=ID_Content
CommandCount=27

[CLS:CTestBtn]
Type=0
HeaderFile=TestBtn.h
ImplementationFile=TestBtn.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

[CLS:EndPlug1]
Type=0
HeaderFile=EndPlug1.h
ImplementationFile=EndPlug1.cpp
BaseClass=CStatic
Filter=W

[CLS:ManiPular1]
Type=0
HeaderFile=ManiPular1.h
ImplementationFile=ManiPular1.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[CLS:ManiPular2]
Type=0
HeaderFile=ManiPular2.h
ImplementationFile=ManiPular2.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[CLS:ManiGroupBox]
Type=0
HeaderFile=ManiGroupBox.h
ImplementationFile=ManiGroupBox.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

[CLS:CameraGroupBox]
Type=0
HeaderFile=ameraGroupBox.h
ImplementationFile=ameraGroupBox.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

[CLS:Camera1]
Type=0
HeaderFile=amera1.h
ImplementationFile=amera1.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[CLS:Cmera2]
Type=0
HeaderFile=mera2.h
ImplementationFile=mera2.cpp
BaseClass=CStatic
Filter=W

[CLS:Cmera3]
Type=0
HeaderFile=mera3.h
ImplementationFile=mera3.cpp
BaseClass=CStatic
Filter=W

[CLS:Camera2]
Type=0
HeaderFile=amera2.h
ImplementationFile=amera2.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[CLS:Camera3]
Type=0
HeaderFile=amera3.h
ImplementationFile=amera3.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[DLG:IDD_HEGEDLG]
Type=1
Class=CHegeDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CHegeDlg]
Type=0
HeaderFile=HegeDlg.h
ImplementationFile=HegeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHegeDlg
VirtualFilter=dWC

[DLG:IDD_NHEGEDLG]
Type=1
Class=CNHegeDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CNHegeDlg]
Type=0
HeaderFile=NHegeDlg.h
ImplementationFile=NHegeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CNHegeDlg
VirtualFilter=dWC

[CLS:CTestDlg]
Type=0
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_EXPOUSE
VirtualFilter=dWC

[DLG:IDD_TESTDLG]
Type=1
Class=CTestDlg
ControlCount=10
Control1=IDC_BUTTON_OPENDUANKOU,button,1342242816
Control2=IDC_BUTTON_CLOSEDUANKOU,button,1342242816
Control3=IDC_BUTTON_ROTA,button,1342242816
Control4=IDC_EDIT_ROTA,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_FPS,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUTTON_CONTINUE,button,1342242816
Control9=IDC_EDIT_EXPOUSE,edit,1350631552
Control10=IDC_STATIC,static,1342308352

[CLS:CRotaSetDlg]
Type=0
HeaderFile=RotaSetDlg.h
ImplementationFile=RotaSetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_ANGLE
VirtualFilter=dWC

