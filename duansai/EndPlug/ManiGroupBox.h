#if !defined(AFX_MANIGROUPBOX_H__116C8A61_BD4B_421D_9E4D_65A555AA1F19__INCLUDED_)
#define AFX_MANIGROUPBOX_H__116C8A61_BD4B_421D_9E4D_65A555AA1F19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManiGroupBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManiGroupBox window

class ManiGroupBox : public CButton
{
// Construction
public:
	ManiGroupBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManiGroupBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ManiGroupBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(ManiGroupBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANIGROUPBOX_H__116C8A61_BD4B_421D_9E4D_65A555AA1F19__INCLUDED_)
