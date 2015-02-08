#if !defined(AFX_AMERA1_H__B810AFC4_D5A4_4493_A956_C5DC8DC1BEA1__INCLUDED_)
#define AFX_AMERA1_H__B810AFC4_D5A4_4493_A956_C5DC8DC1BEA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// amera1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Camera1 window

class CCamera1 : public CStatic
{
// Construction
public:
	CCamera1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamera1)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCamera1();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCamera1)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMERA1_H__B810AFC4_D5A4_4493_A956_C5DC8DC1BEA1__INCLUDED_)
