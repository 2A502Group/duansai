// TestBtn.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "TestBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestBtn

CTestBtn::CTestBtn()
{
}

CTestBtn::~CTestBtn()
{
}


BEGIN_MESSAGE_MAP(CTestBtn, CButton)
	//{{AFX_MSG_MAP(CTestBtn)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBtn message handlers

void CTestBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	UINT uStyle = DFCS_BUTTONPUSH;
	
	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);
	
	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;
	
	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem,DFC_BUTTON, uStyle);
	//����ť�ؼ��ı�����ɫ   
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
    m_ButRect = lpDrawItemStruct->rcItem;    //��ȡ��ť�ߴ�
	int nSavedDC = pDC->SaveDC();
	VERIFY( pDC );
	DrawButton( pDC );                //���ư�ť
    pDC->RestoreDC( nSavedDC );
	
	// Get the button's text.
	CString strText;
	GetWindowText(strText);
	
	// Draw the button text using the text color red.
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(125,125,125));/*���ð�ť������Ϊ��ɫ�������ص�ԭ�ȵ���ɫ��ʱ����*/
	::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),&lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
    ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}
void CTestBtn::DrawButton(CDC *pDC)
{
	//���ư�ť����
	CBrush Brush;
	Brush.CreateSolidBrush( RGB(245,245,245));    //����ˢ
	pDC->SelectObject( &Brush );
	pDC->RoundRect(&m_ButRect,CPoint(5,5));   //��Բ�Ǿ���
}
