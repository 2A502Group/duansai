#if !defined(AFX_TESTBTN_H__F9D24EB7_1AFA_4B9B_ACE3_F8D58AAF9B37__INCLUDED_)
#define AFX_TESTBTN_H__F9D24EB7_1AFA_4B9B_ACE3_F8D58AAF9B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestBtn window

class CTestBtn : public CButton
{
// Construction
public:
	CTestBtn();

// Attributes
public:
  void DrawButton(CDC *pDC);
// Operations
public:
  CRect m_ButRect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestBtn)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBTN_H__F9D24EB7_1AFA_4B9B_ACE3_F8D58AAF9B37__INCLUDED_)
