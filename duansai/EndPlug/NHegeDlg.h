#if !defined(AFX_NHEGEDLG_H__E374B603_CB4C_4E15_ABC8_651C20D9DAC8__INCLUDED_)
#define AFX_NHEGEDLG_H__E374B603_CB4C_4E15_ABC8_651C20D9DAC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NHegeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNHegeDlg dialog

class CNHegeDlg : public CDialog
{
// Construction
public:
	void GetPara(int n3,int n4,int n5,int n6, int n7);
	virtual void PostNcDestory();
	CNHegeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNHegeDlg)
	enum { IDD = IDD_NHEGEDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNHegeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNHegeDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nhwithscratch;         //�п׻���
	int m_nhwithshapchg;         //�п��α�
	int m_nhwithblock;           //�п׶���
	int m_nnhwithscratch;        //�޿׻���
	int m_nnhwithshapchg;        //�޿��α�
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NHEGEDLG_H__E374B603_CB4C_4E15_ABC8_651C20D9DAC8__INCLUDED_)
