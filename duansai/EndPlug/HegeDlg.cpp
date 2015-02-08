// HegeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "HegeDlg.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHegeDlg dialog


CHegeDlg::CHegeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHegeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHegeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHegeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHegeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHegeDlg, CDialog)
	//{{AFX_MSG_MAP(CHegeDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHegeDlg message handlers

void CHegeDlg::OnOK() 
{
	DestroyWindow();
}

void CHegeDlg::OnCancel() 
{
	DestroyWindow();
}

void CHegeDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// 画坐标
	
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	oldpen=dc.SelectObject(&pen);
	for (int i=0; i<2;i++)
	{
		CPoint p1(40,250),p2;
		if (i == 0)
		{
			p2.x = 370;
			p2.y = 250;
			
		}
		else 
		{
			p2.x = 40;
			p2.y = 20;
		}
		int length = 8;
		double theta =3.1415926*45/180;//转换为弧度
		int  Px,Py,P1x,P1y,P2x,P2y;
		
		//以P2为原点得到向量P2P1 (P)
		Px=p1.x-p2.x;
		Py=p1.y-p2.y;
		//向量P旋转theta角得到向量P1
		
		P1x=(int)(Px*cos(theta)-Py*sin(theta));
		P1y=(int)(Px*sin(theta)+Py*cos(theta));
		//向量P旋转-theta角得到向量P2
		
		P2x=(int)(Px*cos(-theta)-Py*sin(-theta));
		P2y=(int)(Px*sin(-theta)+Py*cos(-theta));
		
		//伸缩向量至制定长度
		double x1,x2;
		x1=sqrt(P1x*P1x+P1y*P1y);
		P1x=(int)(P1x*length/x1);
		P1y=(int)(P1y*length/x1);
		x2=sqrt(P2x*P2x+P2y*P2y);
		P2x=(int)(P2x*length/x2);
		P2y=(int)(P2y*length/x2);
		
		//平移变量到直线的末端
		P1x=P1x+p2.x;
		P1y=P1y+p2.y;
		P2x=P2x+p2.x;
		P2y=P2y+p2.y;
		
		
		dc.MoveTo(p1.x,p1.y);
		dc.LineTo(p2.x,p2.y);
		dc.SelectObject(&pen1);
		dc.MoveTo(p2.x,p2.y);
		dc.LineTo(P1x,P1y);
		dc.MoveTo(p2.x,p2.y);
		dc.LineTo(P2x,P2y);
		
		p2.x = 40;
		p2.y = 20;
		
	}
	dc.SelectObject(oldpen);
	//画条形图
	CBrush brush(RGB(56,32,122));
    CRect  rect1(100,250,180,m_nhole);               //有孔  n1--有孔个数
    CRect  rect2(220,250,300,m_nnhole);              //无孔  n2--无孔个数
	dc.FillRect(&rect1,&brush);
	dc.FillRect(&rect2,&brush);	
	dc.TextOut(120,255,"有 孔");
	dc.TextOut(240,255,"无 孔");
	// Do not call CDialog::OnPaint() for painting messages	
}

void CHegeDlg::PostNcDestory()
{
	delete this;
	CDialog::PostNcDestroy();
}

void CHegeDlg::GetPara(int n1, int n2)
{
    m_nhole = n1;
	m_nnhole = n2;
}
