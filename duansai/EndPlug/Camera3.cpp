// amera3.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "Camera3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Camera3

CCamera3::CCamera3()
{
}

CCamera3::~CCamera3()
{
}


BEGIN_MESSAGE_MAP(CCamera3, CStatic)
	//{{AFX_MSG_MAP(CCamera3)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Camera3 message handlers

void CCamera3::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);
	
	CBitmap m_bitmap;
	//draw background bitmap
	m_bitmap.LoadBitmap(IDB_WARNNING);
	BITMAP bm;
	m_bitmap.GetBitmap (&bm);
	
	dcMemory.SelectObject(&m_bitmap);	
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcMemory, 0, 0, SRCCOPY);
	CBitmap *old_bit_map = dcMemory.SelectObject (&m_bitmap);
    m_bitmap.DeleteObject();
	dcMemory.DeleteDC();
	// Do not call CStatic::OnPaint() for painting messages
}
