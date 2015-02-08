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
	m_bitmap.DeleteObject();//һ��Ҫ��������ʱ���ٽ�m_bitmapɾ���������onpaint��ʱ�������m_bitmapɾ�����൱�ڽ���
	                        //���е�ͼ����Ϣ����ˣ��ٴ��ڴ��н���ͼ�����ʾ��ʱ���ѽ��ɼ������κ�ͼ����Ϣ��ˢ�»�ͼ����
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