// EndPlugDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EndPlug.h"
#include "EndPlugDlg.h"
#include "FileOperation.h"
#include "HegeDlg.h"
#include "NHegeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define BAR_WIDTH 16
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEndPlugDlg dialog

CEndPlugDlg::CEndPlugDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEndPlugDlg::IDD, pParent),pTestDlg(NULL)
{
	//{{AFX_DATA_INIT(CEndPlugDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LOGO);
	filename = " ";
	temp_rcPicture.top = 0;
	temp_rcPicture.bottom = 0;
	temp_rcPicture.left = 0;
	temp_rcPicture.right = 0;
	SetControlInfo(IDC_START);
	SetControlInfo(IDC_VIEWWINDOW);
}

void CEndPlugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEndPlugDlg)
	DDX_Control(pDX, IDC_LIST_CAMERA, m_camerapara);
	DDX_Control(pDX, IDC_LISTIDC_LIST_MANIPULAR, m_manipularpara);
	DDX_Control(pDX, IDC_LIST_MANIPULAR_CERRECT, m_listmanipular);
	DDX_Control(pDX, IDC_LIST_LEADRAIL, m_listrail);
	DDX_Control(pDX, IDC_LIST_MOTOR, m_motorpara);
	DDX_Control(pDX, IDC_SCROLLBAR_V, m_vBar);
	DDX_Control(pDX, IDC_SCROLLBAR_H, m_hBar);
	DDX_Control(pDX, IDC_CAMERA3, m_camera3);
	DDX_Control(pDX, IDC_CAMERA2, m_camera2);
	DDX_Control(pDX, IDC_CAMERA1, m_camera1);
	DDX_Control(pDX, IDC_MANIPULAR2, m_manipular2);
	DDX_Control(pDX, IDC_MANIPULAR1, m_manipular1);
	DDX_Control(pDX, IDC_CAMERASTATE, m_CameraState);
	DDX_Control(pDX, IDC_MANISTATE, m_ManiGroupBox);
	DDX_Control(pDX, IDC_VIEWWINDOW, m_viewwindow);
	DDX_Control(pDX, IDC_START, m_Start);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEndPlugDlg, CDialog)
	//{{AFX_MSG_MAP(CEndPlugDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_OPENPHOTO, OnOpenphoto)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_SAVEPHOTO, OnSavephoto)
	ON_COMMAND(ID_Qualified, OnQualified)
	ON_COMMAND(ID_unqualified, Onunqualified)
	ON_COMMAND(ID_Averagefiltering, OnAveragefiltering)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEndPlugDlg message handlers

BOOL CEndPlugDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	initAlllistControl();
 	m_hBar.ShowWindow(SW_HIDE);
 	m_vBar.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEndPlugDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEndPlugDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEndPlugDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEndPlugDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
//	 TODO: Add your message handler code here	
//------------------------------------------------------------	//Ԥ�����������Сλ�õ�������
	//----------------------------------------------------------------------
//	MapWindowPoints��hChildWnd��hParentWnd����LPPOINT��lpRect��2�������ɵõ����ΪhChildWnd�������丸�����ϵ�λ���ˣ��ܷ���ġ�
	//��Ч��GetWindowRect();ScreentoClient();
	//------------------------------------------------------------------------------------------------

// 	if(nType==1) return; //��С����ʲô������
// 		CRect WndRect;
// 		CWnd *pWnd;
// 		for (int i=0; i < m_control_info.GetSize();i++)
// 		{
// 			pWnd = GetDlgItem(m_control_info[i]);
// 			if (!pWnd)
// 			{
// 				TRACE("Control ID - %d NOT FOUND!!\n",m_control_info[i]);
// 				continue;
// 			}
// 			ChangeSize(pWnd,cx,cy,i);	
// 		}
// 	GetWindowRect(&m_rect); //���仯��ĶԻ�������Ϊ�ɴ�С
// // 	if(nType==1) return; //��С����ʲô������ 
// // 	CWnd *pWnd; 
// // 	pWnd = GetDlgItem(IDC_START); //��ȡ�ؼ����
// // 	ChangeSize(pWnd,cx,cy,0); //����changesize()����
// // 	pWnd =GetDlgItem(IDC_VIEWWINDOW);
// // 	ChangeSize(pWnd,cx,cy,1);
// // 	pWnd = GetDlgItem(IDC_LIST_PARAMETER); 
// // 	ChangeSize(pWnd,cx,cy,2);
// //     GetWindowRect(&m_rect); //���仯��ĶԻ�������Ϊ�ɴ�С
}
void CEndPlugDlg::ChangeSize(CWnd * pWnd, int cx, int cy,int movenumber)//Ԥ������
{
	if (pWnd)
	{
        CRect rect,rectstart;
	    switch (movenumber)
	    {
		case 0://start��ť��Ҫ����λ�ö�����Ҫ������С
			m_Start.GetWindowRect(&rectstart);
			pWnd->GetWindowRect(&rect);
			ScreenToClient(&rect);
 			rect.bottom=cy;
			rect.right=cx; //cx�洢���Ǳ仯��Ŀ�ȣ�cy�洢���Ǳ仯��ĸ߶�
			rect.left = rect.right - rectstart.Width();
			rect.top = rect.bottom - rectstart.Height();			
			pWnd->MoveWindow(rect);
			break;
		case 1://�����ڸı䴰�ڴ�С�Ժ���Ҫ���洰�ڽ�����Ӧ����������
			m_Start.GetWindowRect(&rectstart);
			ScreenToClient(&rectstart);
	       	pWnd->GetWindowRect(&rect); //��ȡ�ؼ��仯ǰ�Ĵ�С
		    ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е��������� 
			rect.left=rect.left*cx/m_rect.Width();//�����ؼ���С ��cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
			rect.right=rectstart.left; //cx�洢���Ǳ仯��Ŀ�ȣ�cy�洢���Ǳ仯��ĸ߶�
			rect.top=rect.top*cy/m_rect.Height(); //m_rect.height()��ʾ���Ǳ仯ǰ������ĸ߶�
			rect.bottom=cy;
			pWnd->MoveWindow(rect);//���ÿؼ���С		
			break;
		case 2://listparameter ��Ҫ����Start��ť�������Լ��Ĵ�С��λ��
			m_Start.GetWindowRect(&rectstart);
			ScreenToClient(&rectstart);
			pWnd->GetWindowRect(&rect);
			ScreenToClient(&rect);
			rect.right=cx; //cx�洢���Ǳ仯��Ŀ�ȣ�cy�洢���Ǳ仯��ĸ߶�
			rect.top = rect.top*cy/m_rect.Height();		
			rect.bottom= rectstart.top;
			rect.left = rectstart.left;			
			pWnd->MoveWindow(rect);
			break;
	    }
	}
}
HBRUSH CEndPlugDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
  
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CEndPlugDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	CString text;
    m_Start.GetWindowText(text);
	if (text == "Start")
	{
		CFileOperation::Instance().FileOperationStart();
	    m_Start.SetWindowText("Close");
	}
	else
	{
		m_Start.SetWindowText("Start");
	}
}
void CEndPlugDlg::SetControlInfo(WORD CtrlId)
{
	m_control_info.Add(CtrlId);
}
void CEndPlugDlg::OnExit() 
{
	// TODO: Add your command handler code here
	if (pTestDlg!=NULL)
	{
		delete pTestDlg;
	}
	if(AfxMessageBox("Sure to Eixt?",MB_YESNO)==IDOK)
	{
		return;
	}
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
void CEndPlugDlg::OnOpenphoto() 
{
	// TODO: Add your command handler code here
	m_viewwindow.m_bitmap.Detach();//����ͼ����Ϣ
	m_viewwindow.m_Sourcex = 0;
	m_viewwindow.m_Sourcey = 0;
	SCROLLINFO horz,vert;//�������Ļ���������Ϣ
	CFileDialog dlg(TRUE,"bmp","*.bmp",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,\
		"BMP�ļ�(*.bmp)|*.bmp||"\
		,NULL);
	if(dlg.DoModal()==IDOK)
	{
	  	filename.Format ("%s",dlg.GetPathName()); 
	}
	else
	{
       return;
	}
	if (!m_Dib.LoadFile(filename))
	{
		return;
	}
	m_viewwindow.State = 1;//����ViewEndPulg���ػ棨State=0����ʾû�ж���ͼƬ��State=1,��ʾ����ͼƬ��ʼ�ػ�ͼƬ��
	if (0 == temp_rcPicture.right)//һ���÷�
	{
		m_viewwindow.GetWindowRect(&m_rcPicture);
		ScreenToClient(&m_rcPicture);
    	temp_rcPicture = m_rcPicture;//�����ػ������򣬣�ע������ָ�������
	}
	else
	{
		m_rcPicture = temp_rcPicture;
	}
	HBITMAP hBitmap=(HBITMAP)LoadImage(NULL,_T(filename),IMAGE_BITMAP,
		0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_viewwindow.m_bitmap.Attach (hBitmap);
	m_viewwindow.m_bitmap.GetBitmap(&m_viewwindow.bm);
	if(m_viewwindow.bm.bmWidth <= m_rcPicture.Width())
	{
		m_viewwindow.Picture = &m_rcPicture;
		m_hBar.ShowWindow(SW_HIDE);
	}
    else
	{
		m_rcPicture.bottom=m_rcPicture.Height() - BAR_WIDTH;
    	m_viewwindow.Picture = &m_rcPicture;
		m_hBar.MoveWindow(m_rcPicture.left,m_rcPicture.bottom,m_rcPicture.Width(),BAR_WIDTH);
		memset(&horz,0,sizeof(SCROLLINFO));
		horz.cbSize = sizeof(SCROLLINFO);
		horz.fMask = SIF_ALL;
	    horz.nMax = m_viewwindow.bm.bmWidth-m_rcPicture.Width();
	    m_hBar.ShowWindow(SW_SHOW);
	    m_hBar.SetScrollInfo(&horz);
	}
	if(m_viewwindow.bm.bmHeight <= m_rcPicture.Height())
	{
		m_viewwindow.Picture = &m_rcPicture;
		m_vBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_rcPicture.right = m_rcPicture.left+m_rcPicture.Width() - BAR_WIDTH;
        m_viewwindow.Picture = &m_rcPicture;
		m_vBar.MoveWindow(m_rcPicture.right,m_rcPicture.top,BAR_WIDTH,m_rcPicture.Height());
		memset(&vert,0,sizeof(SCROLLINFO));
		vert.cbSize = sizeof(SCROLLINFO);
		vert.fMask = SIF_ALL;
    	vert.nMax = m_viewwindow.bm.bmHeight-m_rcPicture.Height();
		m_vBar.ShowWindow(SW_SHOW);
		m_vBar.SetScrollInfo(&vert);
	}
	    m_viewwindow.MoveWindow(&m_rcPicture);
		InvalidateRect(&m_rcPicture);
}

void CEndPlugDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nSBCode)
	{
	case SB_LINELEFT:
	case SB_PAGELEFT:
		if(m_viewwindow.m_Sourcex >=10) m_viewwindow.m_Sourcex -= 10;
		else			   m_viewwindow.m_Sourcex  = 0;
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		if((m_viewwindow.m_Sourcex+m_rcPicture.Width()+10)<m_viewwindow.bm.bmWidth)
			m_viewwindow.m_Sourcex += 10;
		else
			m_viewwindow.m_Sourcex  = m_viewwindow.bm.bmWidth -m_rcPicture.Width();
		break;
	case SB_TOP:
		m_viewwindow.m_Sourcex = 0;
		break;
	case SB_BOTTOM:
		m_viewwindow.m_Sourcex = INT_MAX;
		break;
	case SB_THUMBTRACK:
		m_viewwindow.m_Sourcex= nPos;
		break;
	}	
	//
	m_hBar.SetScrollPos(m_viewwindow.m_Sourcex);
	InvalidateRect(&m_rcPicture,FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEndPlugDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nSBCode)
	{
	case SB_LINEUP:
	case SB_PAGEUP:
		if(m_viewwindow.m_Sourcey >=10) m_viewwindow.m_Sourcey -= 10;
		else			 m_viewwindow.m_Sourcey  = 0;
		break;
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
		if((m_viewwindow.m_Sourcey+m_rcPicture.Height()+10)<m_viewwindow.bm.bmHeight)
			m_viewwindow.m_Sourcey += 10;
		else
			m_viewwindow.m_Sourcey  = m_viewwindow.bm.bmHeight -m_rcPicture.Height();
		break;
	case SB_TOP:
		m_viewwindow.m_Sourcey = 0;
		break;
	case SB_BOTTOM:
		m_viewwindow.m_Sourcey = INT_MAX;
		break;
	case SB_THUMBTRACK:
		m_viewwindow.m_Sourcey = nPos;
		break;
	}
	m_vBar.SetScrollPos(m_viewwindow.m_Sourcey);
	InvalidateRect(&m_rcPicture,FALSE);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CEndPlugDlg::OnSavephoto() 
{
	// TODO: Add your command handler code here
	__try
	{
    	SavePhoto();//�쳣��׽��__try __except()�������release��ʱ�򲻻ᱻ�Ż��������ֱ����try��catch�������release�»ᱻ�Ż���
		            //�Ż�������__try����в������κζ��󣬲����Ǿֲ��Ļ���ȫ�ֵĶ�����
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		AfxMessageBox("Please open a Photo!");
	}
}
void CEndPlugDlg::SavePhoto()
{
	if (!CFileOperation::Instance().CreateDirectoryForAll())
	{
		return;
	}
	else
	{
		filename = CFileOperation::Instance().GetPhotoFilePath() + CFileOperation::Instance().File_Ext();
		if (m_Dib.SaveFile(filename))
		{
			AfxMessageBox("������ɣ�");
		}
		else
		{
			return;
		}
	}
}

void CEndPlugDlg::OnQualified() 
{
	CHegeDlg *phegedlg = new CHegeDlg;
	phegedlg->GetPara(10,20);
	phegedlg->Create(IDD_HEGEDLG,NULL);
    phegedlg->ShowWindow(SW_SHOW);
	
}

void CEndPlugDlg::Onunqualified() 
{
	CNHegeDlg *pnhegedlg = new CNHegeDlg;
	pnhegedlg->GetPara(10,20,30,40,50);
	pnhegedlg->Create(IDD_NHEGEDLG,NULL);
    pnhegedlg->ShowWindow(SW_SHOW);	
}

void CEndPlugDlg::OnAveragefiltering() 
{
	// TODO: Add your command handler code here
}

void CEndPlugDlg::initAlllistControl()
{
	m_listrail.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_listrail.InsertColumn(0,"����ID",LVCFMT_CENTER,140,0);
	m_listrail.InsertColumn(1,"����λ��",LVCFMT_CENTER,140,2);
	m_listrail.InsertColumn(2,"����λ��",LVCFMT_CENTER,140,3);
	m_listrail.InsertItem(0,"");
	m_listrail.SetItemText(0,0,"1");
	m_listrail.SetItemText(0,1,"400");
	m_listrail.SetItemText(0,2,"500");
	m_listrail.InsertItem(1,"");
	m_listrail.SetItemText(1,0,"2");
	m_listrail.SetItemText(1,1,"600");
	m_listrail.SetItemText(1,2,"300");

	m_listmanipular.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_listmanipular.InsertColumn(0,"��е��ID",LVCFMT_CENTER,60,0);
	m_listmanipular.InsertColumn(1,"ץȡ����λ��",LVCFMT_CENTER,90,2);
	m_listmanipular.InsertColumn(2,"ץȡ����λ��",LVCFMT_CENTER,90,3);
	m_listmanipular.InsertColumn(3,"���ú���λ��",LVCFMT_CENTER,90,4);
	m_listmanipular.InsertColumn(4,"��������λ��",LVCFMT_CENTER,90,5);
	m_listmanipular.InsertItem(0,"");
	m_listmanipular.SetItemText(0,0,"1");
	m_listmanipular.SetItemText(0,1,"200");
	m_listmanipular.SetItemText(0,2,"300");
	m_listmanipular.SetItemText(0,3,"100");
    m_listmanipular.SetItemText(0,4,"500");
	m_listmanipular.InsertItem(1,"");
	m_listmanipular.SetItemText(1,0,"2");
	m_listmanipular.SetItemText(1,1,"200");
	m_listmanipular.SetItemText(1,2,"300");
	m_listmanipular.SetItemText(1,3,"100");
    m_listmanipular.SetItemText(1,4,"500");

	m_manipularpara.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_manipularpara.InsertColumn(0,"��е��ID",LVCFMT_CENTER,80,0);
	m_manipularpara.InsertColumn(1,"λ��",LVCFMT_CENTER,80,2);
    m_manipularpara.InsertColumn(2,"��ֵ",LVCFMT_CENTER,50,2);
	m_manipularpara.InsertItem(0,"");
	m_manipularpara.SetItemText(0,0,"��е��1:");
	m_manipularpara.InsertItem(1,"");
	m_manipularpara.SetItemText(1,1,"����λ��");
	m_manipularpara.SetItemText(1,2,"200");
	m_manipularpara.InsertItem(2,"");
	m_manipularpara.SetItemText(2,1,"����λ��");
	m_manipularpara.SetItemText(2,2,"200");
	m_manipularpara.InsertItem(3,"");
	m_manipularpara.SetItemText(3,0,"��е��2:");
	m_manipularpara.InsertItem(4,"");
	m_manipularpara.SetItemText(4,1,"����λ��");
	m_manipularpara.SetItemText(4,2,"400");
	m_manipularpara.InsertItem(5,"");
	m_manipularpara.SetItemText(5,1,"����λ��");
	m_manipularpara.SetItemText(5,2,"500");

	m_camerapara.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_camerapara.InsertColumn(0,"���ID",LVCFMT_CENTER,80,0);
	m_camerapara.InsertColumn(1,"����",LVCFMT_CENTER,80,2);
	m_camerapara.InsertColumn(2,"��ֵ",LVCFMT_CENTER,60,3);

	m_camerapara.InsertItem(0,"");
	m_camerapara.SetItemText(0,0,"���1:");
	m_camerapara.InsertItem(1,"");
	m_camerapara.SetItemText(1,1,"ɨ��Ƶ��");
	m_camerapara.SetItemText(1,2,"200");
	m_camerapara.InsertItem(2,"");
	m_camerapara.SetItemText(2,1,"ͼƬ֡��");
	m_camerapara.SetItemText(2,2,"200");
	m_camerapara.InsertItem(3,"");
	m_camerapara.SetItemText(3,1,"�ع�ʱ��");
	m_camerapara.SetItemText(3,2,"200");
	m_camerapara.InsertItem(4,"");
	m_camerapara.SetItemText(4,1,"ͼƬ��С");
	m_camerapara.SetItemText(4,2,"320*640");

	m_camerapara.InsertItem(5,"");
	m_camerapara.SetItemText(5,0,"���2:");
	m_camerapara.InsertItem(6,"");
	m_camerapara.SetItemText(6,1,"ɨ��Ƶ��");
	m_camerapara.SetItemText(6,2,"200");
	m_camerapara.InsertItem(7,"");
	m_camerapara.SetItemText(7,1,"ͼƬ֡��");
	m_camerapara.SetItemText(7,2,"200");
	m_camerapara.InsertItem(8,"");
	m_camerapara.SetItemText(8,1,"�ع�ʱ��");
	m_camerapara.SetItemText(8,2,"200");
	m_camerapara.InsertItem(9,"");
	m_camerapara.SetItemText(9,1,"ͼƬ��С");
	m_camerapara.SetItemText(9,2,"320*640");

	m_camerapara.InsertItem(10,"");
	m_camerapara.SetItemText(10,0,"���3:");
	m_camerapara.InsertItem(11,"");
	m_camerapara.SetItemText(11,1,"ɨ��Ƶ��");
	m_camerapara.SetItemText(11,2,"200");
	m_camerapara.InsertItem(12,"");
	m_camerapara.SetItemText(12,1,"ͼƬ֡��");
	m_camerapara.SetItemText(12,2,"200");
	m_camerapara.InsertItem(13,"");
	m_camerapara.SetItemText(13,1,"�ع�ʱ��");
	m_camerapara.SetItemText(13,2,"200");
	m_camerapara.InsertItem(14,"");
	m_camerapara.SetItemText(14,1,"ͼƬ��С");
	m_camerapara.SetItemText(14,2,"320*640");

	m_motorpara.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_motorpara.InsertColumn(0,"���ID",LVCFMT_CENTER,80,0);
	m_motorpara.InsertColumn(1,"����",LVCFMT_CENTER,80,2);
	m_motorpara.InsertColumn(2,"��ֵ",LVCFMT_CENTER,50,3);
	m_motorpara.InsertItem(0,"");
	m_motorpara.SetItemText(0,0,"���1:");
	m_motorpara.InsertItem(1,"");
	m_motorpara.SetItemText(1,1,"ת��");
	m_motorpara.SetItemText(1,2,"1000");
	m_motorpara.InsertItem(2,"");
	m_motorpara.SetItemText(2,1,"Ƶ��");
	m_motorpara.SetItemText(2,2,"1000");
	m_motorpara.InsertItem(3,"");
	m_motorpara.SetItemText(3,1,"����");
	m_motorpara.SetItemText(3,2,"1000");
	m_motorpara.InsertItem(4,"");
	m_motorpara.SetItemText(4,0,"���2:");
	m_motorpara.InsertItem(5,"");
	m_motorpara.SetItemText(5,1,"ת��");
	m_motorpara.SetItemText(5,2,"1000");
	m_motorpara.InsertItem(6,"");
	m_motorpara.SetItemText(6,1,"Ƶ��");
	m_motorpara.SetItemText(6,2,"1000");
	m_motorpara.InsertItem(7,"");
	m_motorpara.SetItemText(7,1,"����");
	m_motorpara.SetItemText(7,2,"1000");
}

void CEndPlugDlg::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	if (NULL == pTestDlg)
	{
		pTestDlg = new CTestDlg;
    	pTestDlg->Create(IDD_TESTDLG,this);
	}
	pTestDlg->ShowWindow(SW_SHOW);
}

void CEndPlugDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CFileOperation::Instance().DeleteFolderAndFile();
	CDialog::OnClose();
}

void CEndPlugDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	OnExit();
}
