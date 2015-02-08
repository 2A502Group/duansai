// NHegeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "endplug.h"
#include "NHegeDlg.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNHegeDlg dialog


CNHegeDlg::CNHegeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNHegeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNHegeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNHegeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNHegeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNHegeDlg, CDialog)
	//{{AFX_MSG_MAP(CNHegeDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNHegeDlg message handlers

void CNHegeDlg::OnOK() 
{
	DestroyWindow();
}

void CNHegeDlg::OnCancel() 
{
	DestroyWindow();
}

void CNHegeDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    // 画坐标
	
	CPen pen,pen1,*oldpen;
	CBrush brush(RGB(56,32,122));
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	oldpen=dc.SelectObject(&pen);
	for (int i=0; i<4;i++)
	{
		CPoint p1,p2;
		if (i == 0)
		{
            p1.x = 40;
			p1.y = 250;
			p2.x = 320;
			p2.y = 250;
            
		}
		else if(i == 1)
		{
			p1.x = 40;
			p1.y = 250;
			p2.x = 40;
			p2.y = 20;

			dc.TextOut(55,15,"有 孔");
			dc.TextOut(80,260,"划 痕");
			dc.TextOut(160,260,"形 变");
			dc.TextOut(240,260,"堵 塞");

			CRect  rect1(70,250,120,m_nhwithscratch);               //划痕			             
			dc.FillRect(&rect1,&brush);

			CRect  rect2(150,250,200,m_nhwithshapchg);              //形变		 
	        dc.FillRect(&rect2,&brush);	

			CRect  rect3(230,250,280,m_nhwithblock);              //堵塞		 
	        dc.FillRect(&rect3,&brush);	
		}
		else if(i == 2)
		{
			p1.x = 360;
			p1.y = 250;
			p2.x = 640;
			p2.y = 250;

			
	         	
		}
		else 
		{
			p1.x = 360;
			p1.y = 250;
			p2.x = 360;
			p2.y = 20;

			dc.TextOut(375,15,"无 孔");
			dc.TextOut(425,260,"划 痕");
			dc.TextOut(535,260,"形 变");

			//画条形图		
			CRect  rect1(410,250,475,m_nnhwithscratch);               //划痕			             
			dc.FillRect(&rect1,&brush);
			 		 
			CRect  rect2(515,250,585,m_nnhwithshapchg);              //形变		 
	        dc.FillRect(&rect2,&brush);	
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
}

void CNHegeDlg::PostNcDestory()
{
	delete this;
	CDialog::PostNcDestroy();
}

void CNHegeDlg::GetPara(int n3, int n4, int n5, int n6, int n7)
{
    m_nhwithscratch = n3;
	m_nhwithshapchg = n4;
	m_nhwithblock = n5;
	m_nnhwithscratch = n6;
	m_nnhwithshapchg = n7;
}
