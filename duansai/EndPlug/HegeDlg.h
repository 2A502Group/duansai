#if !defined(AFX_HEGEDLG_H__01571E5D_EDF4_43D3_8D64_B92C48EF47A4__INCLUDED_)
#define AFX_HEGEDLG_H__01571E5D_EDF4_43D3_8D64_B92C48EF47A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HegeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHegeDlg dialog

class CHegeDlg : public CDialog
{
// Construction
public:
	void GetPara(int n1,int n2);
	virtual void PostNcDestory();
	CHegeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHegeDlg)
	enum { IDD = IDD_HEGEDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHegeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHegeDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nnhole;     //нч©в
	int m_nhole;      //сп©в
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEGEDLG_H__01571E5D_EDF4_43D3_8D64_B92C48EF47A4__INCLUDED_)
