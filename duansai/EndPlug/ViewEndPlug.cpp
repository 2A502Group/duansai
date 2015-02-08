// ViewEndPlug.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "ViewEndPlug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ViewEndPlug

ViewEndPlug::ViewEndPlug()
{
	State = 0;
 	m_Sourcex = 0;
 	m_Sourcey = 0;
}

ViewEndPlug::~ViewEndPlug()
{
	m_bitmap.DeleteObject();//一定要在析构的时候再将m_bitmap删除，因此在onpaint的时候如果将m_bitmap删除就相当于将内
	                        //存中的图像信息清除了，再从内存中进行图像的显示的时候已近采集不到任何图像信息来刷新绘图区了
	m_Sourcex = 0;
 	m_Sourcey = 0;
}
BEGIN_MESSAGE_MAP(ViewEndPlug, CStatic)
	//{{AFX_MSG_MAP(ViewEndPlug)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ViewEndPlug message handlers
void ViewEndPlug::OnPaint() 
{	
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CRect rc;
	this->GetWindowRect(&rc);
    dc.FillSolidRect(0,0,rc.Width(),rc.Height(),RGB(255,255,255));
	if(State ==1)
	{
		CDC dcImage;
		if(!dcImage.CreateCompatibleDC(&dc))
			return;
	    old_bit_map = dcImage.SelectObject (&m_bitmap);
		dc.BitBlt(0,0,Picture->Width(),Picture->Height(),&dcImage, m_Sourcex, m_Sourcey,SRCCOPY);
		dcImage.SelectObject(old_bit_map);
		dcImage.DeleteDC();
	}
	// Do not call CStatic::OnPaint() for painting messages
}
void ViewEndPlug::shuaxin()
{
	this->Invalidate();
}