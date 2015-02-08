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
	//画按钮控件的背景颜色   
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
    m_ButRect = lpDrawItemStruct->rcItem;    //获取按钮尺寸
	int nSavedDC = pDC->SaveDC();
	VERIFY( pDC );
	DrawButton( pDC );                //绘制按钮
    pDC->RestoreDC( nSavedDC );
	
	// Get the button's text.
	CString strText;
	GetWindowText(strText);
	
	// Draw the button text using the text color red.
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(125,125,125));/*设置按钮的字体为红色。将返回的原先的颜色暂时保存*/
	::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),&lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
    ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}
void CTestBtn::DrawButton(CDC *pDC)
{
	//绘制按钮背景
	CBrush Brush;
	Brush.CreateSolidBrush( RGB(245,245,245));    //背景刷
	pDC->SelectObject( &Brush );
	pDC->RoundRect(&m_ButRect,CPoint(5,5));   //画圆角矩形
}
