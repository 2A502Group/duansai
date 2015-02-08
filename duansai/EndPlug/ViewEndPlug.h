#if !defined(AFX_VIEWENDPLUG_H__37055FFD_28F4_4998_8E81_E19E93E1F6EB__INCLUDED_)
#define AFX_VIEWENDPLUG_H__37055FFD_28F4_4998_8E81_E19E93E1F6EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewEndPlug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ViewEndPlug window

class ViewEndPlug : public CStatic
{
// Construction
public:
	ViewEndPlug();

// Attributes
public:
// Operations
public:
   int State;
   CBitmap m_bitmap;
   BITMAP bm;
   int   m_Sourcex, m_Sourcey;//used by Scroll
   CRect *Picture;
   CBitmap *old_bit_map;
   CDC dcImage;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ViewEndPlug)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ViewEndPlug();
	void shuaxin();

	// Generated message map functions
protected:
	//{{AFX_MSG(ViewEndPlug)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWENDPLUG_H__37055FFD_28F4_4998_8E81_E19E93E1F6EB__INCLUDED_)
