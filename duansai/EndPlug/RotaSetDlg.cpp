// RotaSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "RotaSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotaSetDlg dialog


CRotaSetDlg::CRotaSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotaSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotaSetDlg)
	m_Rota = 0;
	//}}AFX_DATA_INIT
}


void CRotaSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotaSetDlg)
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_Rota);
	DDV_MinMaxInt(pDX, m_Rota, 0, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotaSetDlg, CDialog)
	//{{AFX_MSG_MAP(CRotaSetDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotaSetDlg message handlers
