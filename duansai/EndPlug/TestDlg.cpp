// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_Rota = 0;
	m_Fps = 0;
	m_Expouse = 0.0;
	//}}AFX_DATA_INIT
	pCamera = new CCmeraInterface;
}
CTestDlg::~CTestDlg()
{
	if (pCamera!=NULL)
	{
		delete pCamera;
	}
}
void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_EDIT_ROTA, m_Rota);
	DDV_MinMaxInt(pDX, m_Rota, 0, 360);
	DDX_Text(pDX, IDC_EDIT_FPS, m_Fps);
	DDX_Text(pDX, IDC_EDIT_EXPOUSE, m_Expouse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_BN_CLICKED(IDC_BUTTON_OPENDUANKOU, OnButtonOpenduankou)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEDUANKOU, OnButtonCloseduankou)
	ON_BN_CLICKED(IDC_BUTTON_ROTA, OnButtonRota)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, OnButtonContinue)
	ON_EN_KILLFOCUS(IDC_EDIT_EXPOUSE, OnKillfocusEditExpouse)
	ON_EN_KILLFOCUS(IDC_EDIT_FPS, OnKillfocusEditFps)
	ON_MESSAGE(DELTE_PREDARA, OnDeleltePreData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

void CTestDlg::OnButtonOpenduankou() 
{
	// TODO: Add your control notification handler code here
	pCamera->m_Hwnd = (HWND)this->GetSafeHwnd();
	if (pCamera->Open())
	{
		m_Expouse = pCamera->GetExpouseTime();//获取曝光时间
		m_Fps = 10;
		pCamera->Start();
	}
	else
	{
		return;
	}
		UpdateData(FALSE);
}

void CTestDlg::OnButtonCloseduankou() 
{
	// TODO: Add your control notification handler code here
	if (NULL==pCamera->GetCamH())
	{
		this->ShowWindow(SW_HIDE);
	}
	else
	{
		pCamera->Stop();
		this->ShowWindow(SW_HIDE);
	}
	SetDlgItemText(IDC_BUTTON_CONTINUE,"连续采集");
	pCamera->m_bTrigCont = FALSE;
}

void CTestDlg::OnButtonRota() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    pCamera->SetRota(m_Rota);
	pCamera->SetAlgorithmFlag(0);
}

void CTestDlg::OnButtonContinue() 
{
	// TODO: Add your control notification handler code here
	if(!pCamera->m_bTrigCont)
	{
		pCamera->m_bTrigCont = TRUE;	
		pCamera->TrigContinue();
		GetDlgItem(IDC_BUTTON_CONTINUE)->SetWindowText("停止采集");
	}
	else
	{
		pCamera->m_bTrigCont = FALSE;
		pCamera->TerminalTrigContinue();
		GetDlgItem(IDC_BUTTON_CONTINUE)->SetWindowText("连续采集");
	}
}

void CTestDlg::OnKillfocusEditExpouse() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	pCamera->SetExpouseTime(m_Expouse);
}

BOOL CTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestDlg::OnKillfocusEditFps() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pCamera->m_nFPS = m_Fps;
}
void CTestDlg::OnDeleltePreData()
{
	pCamera->m_transfer.ReleaseNewDataPlace();
}