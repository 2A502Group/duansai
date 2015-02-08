#if !defined(AFX_ROTASETDLG_H__DC358F95_CDD2_433B_B71D_2B0594BBC0AB__INCLUDED_)
#define AFX_ROTASETDLG_H__DC358F95_CDD2_433B_B71D_2B0594BBC0AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotaSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotaSetDlg dialog

class CRotaSetDlg : public CDialog
{
// Construction
public:
	CRotaSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRotaSetDlg)
	enum { IDD = IDD_DIALOG_ANGLE };
	int		m_Rota;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotaSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotaSetDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTASETDLG_H__DC358F95_CDD2_433B_B71D_2B0594BBC0AB__INCLUDED_)
