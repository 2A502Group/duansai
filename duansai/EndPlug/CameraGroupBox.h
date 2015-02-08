#if !defined(AFX_AMERAGROUPBOX_H__C905BD98_A001_41B9_A326_99A45CC0B1CD__INCLUDED_)
#define AFX_AMERAGROUPBOX_H__C905BD98_A001_41B9_A326_99A45CC0B1CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ameraGroupBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CameraGroupBox window

class CameraGroupBox : public CButton
{
// Construction
public:
	CameraGroupBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraGroupBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CameraGroupBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCameraGroupBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMERAGROUPBOX_H__C905BD98_A001_41B9_A326_99A45CC0B1CD__INCLUDED_)
