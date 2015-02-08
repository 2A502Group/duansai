#if !defined(AFX_TESTDLG_H__E6AADA31_1094_4153_B059_B6598A3255F1__INCLUDED_)
#define AFX_TESTDLG_H__E6AADA31_1094_4153_B059_B6598A3255F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//
#include "CmeraInterface.h"
/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog
#define DELTE_PREDARA  WM_USER + 1
class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent =NULL);   // standard constructor
	~CTestDlg();
    CCmeraInterface *pCamera;
// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TESTDLG };
	int		m_Rota;
	int		m_Fps;
	double	m_Expouse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	afx_msg void OnButtonOpenduankou();
	afx_msg void OnButtonCloseduankou();
	afx_msg void OnButtonRota();
	afx_msg void OnButtonContinue();
	afx_msg void OnKillfocusEditExpouse();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEditFps();
	afx_msg void OnDeleltePreData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__E6AADA31_1094_4153_B059_B6598A3255F1__INCLUDED_)
