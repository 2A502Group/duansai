#if !defined(AFX_AMERA3_H__9E8A7FFC_A95F_4EDC_B73A_792BB428BFA9__INCLUDED_)
#define AFX_AMERA3_H__9E8A7FFC_A95F_4EDC_B73A_792BB428BFA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// amera3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Camera3 window

class CCamera3 : public CStatic
{
// Construction
public:
	CCamera3();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamera3)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCamera3();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCamera3)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMERA3_H__9E8A7FFC_A95F_4EDC_B73A_792BB428BFA9__INCLUDED_)
