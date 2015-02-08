// ManiGroupBox.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "ManiGroupBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManiGroupBox

ManiGroupBox::ManiGroupBox()
{

}

ManiGroupBox::~ManiGroupBox()
{
}


BEGIN_MESSAGE_MAP(ManiGroupBox, CButton)
	//{{AFX_MSG_MAP(ManiGroupBox)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManiGroupBox message handlers

HBRUSH ManiGroupBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CRect rc;
	this->GetClientRect(&rc);
	pDC->FillSolidRect(rc,RGB(245,245,245));
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}
