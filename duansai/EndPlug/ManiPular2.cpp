// ManiPular2.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "ManiPular2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManiPular2

ManiPular2::ManiPular2()
{
}

ManiPular2::~ManiPular2()
{
}


BEGIN_MESSAGE_MAP(ManiPular2, CStatic)
	//{{AFX_MSG_MAP(ManiPular2)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManiPular2 message handlers

void ManiPular2::OnPaint() 
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
