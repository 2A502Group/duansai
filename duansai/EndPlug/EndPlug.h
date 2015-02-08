// EndPlug.h : main header file for the ENDPLUG application
//

#if !defined(AFX_ENDPLUG_H__5C021CE7_E997_479B_A120_779D2ED16BA8__INCLUDED_)
#define AFX_ENDPLUG_H__5C021CE7_E997_479B_A120_779D2ED16BA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEndPlugApp:
// See EndPlug.cpp for the implementation of this class
//

class CEndPlugApp : public CWinApp
{
public:
	CEndPlugApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEndPlugApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEndPlugApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDPLUG_H__5C021CE7_E997_479B_A120_779D2ED16BA8__INCLUDED_)
