// CmeraInterface.cpp: implementation of the CCmeraInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmeraInterface.h"
#include "afxmt.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CStopWatch g_StopWatch;
CEvent g_EventStop;
double g_fTriggerFps;
DWORD WINAPI ThreadTrigger(LPVOID pParam)//控制采集图像的线程，每触发一次可采集一幅图像
{
	DWORD dWait = 0;
	do 
	{
		DWORD dwMilliseconds = (DWORD)(10000/g_fTriggerFps);
		g_StopWatch.Start();
		MVTriggerSoftware((HANDLE)pParam);
		dWait = WaitForSingleObject(g_EventStop.m_hObject,dwMilliseconds);
	} while (dWait != WAIT_OBJECT_0);
	return 0;
}

CCmeraInterface::CCmeraInterface()
{
	m_nZoom =1;
	m_hCam = NULL;
	m_RotaAngle = 0;
	m_nFPS = 10;
	m_fExpo = 0;
	m_bTrigCont = FALSE;
	m_nTimeCostMax = 0;
	ContinueThread = NULL;
	TerminalContinue = FALSE;
    MVInitLib();
}

CCmeraInterface::~CCmeraInterface()
{
	if(ContinueThread)
	{
		if(::WaitForSingleObject(ContinueThread, 500) != WAIT_OBJECT_0)
			::TerminateThread(ContinueThread, 0);
		CloseHandle(ContinueThread);
	}
}

BOOL CCmeraInterface::Open()
{
	BOOL ret;
	CWaitCursor cursor;

	int nCams = 0;
	MVGetNumOfCameras(&nCams);
	if( nCams == 0 )
	{
		MessageBox(m_Hwnd,"没有找到相机,请确认连接和相机IP设置","提示",MB_ICONWARNING);
		ret = false;
		return ret;
	}

	MVSTATUS_CODES r = MVOpenCamByIndex(0,&m_hCam);
	if( m_hCam == NULL )
	{
		if( r == MVST_ACCESS_DENIED )
		{
			MessageBox(m_Hwnd,"无法打开相机，可能正被别的软件控制","提示",MB_ICONWARNING);
			ret = false;
			return ret;
		}
	}
	MVSetTriggerMode(m_hCam, TriggerMode_On);
	MVSetTriggerSource(m_hCam, TriggerSource_Software);
	MVSetStrobeSource(m_hCam,LineSource_ExposureActive);
	MVSetStrobeInvert(m_hCam,TRUE);
	int w,h;			
	MVGetWidth(m_hCam,&w);
	MVGetHeight(m_hCam,&h);
	MVGetPixelFormat(m_hCam,&m_PixelFormat);

	if( m_PixelFormat == PixelFormat_Mono8 )
	{
		m_image.Create(w,h,8);
        ret = true;
		return ret;
	}
	else
	{
		m_image.Create(w,h,24);
		ret = true;
		return ret;
	}
}

void CCmeraInterface::Destroy()
{
	// TODO: Add your message handler code here
	if( m_hCam != NULL )
	{
		MVCloseCam(m_hCam);
	}

	MVTerminateLib();
	if (m_hCam!=NULL)
	{
		m_hCam = NULL;
	}
}


int Stream_CB(MV_IMAGE_INFO *pInfo,long nUserVal)
{
	CCmeraInterface *pDlg = (CCmeraInterface *)nUserVal;
	return ( pDlg->StreamCB(pInfo) );
}

void CCmeraInterface::Start()
{
	//开始采集
	MVStartGrab(m_hCam,Stream_CB,(long)this);
}

int CCmeraInterface::StreamCB(MV_IMAGE_INFO *pInfo)
{
		int w = m_image.GetWidth();
		int h = m_image.GetHeight();
		
		if( m_PixelFormat == PixelFormat_Mono8 )
		{
			ASSERT( m_image.GetPitch() == m_image.GetWidth() );
			memcpy(m_image.GetBits(),pInfo->pImageBuffer,w*h);
            m_transfer.SendImageDataToQueue((BYTE*)m_image.GetBits(),h,w);
			switch(m_flag)
			{
			case 0:
				Dib.RotateDIB((BYTE*)m_image.GetBits(),w,h,m_RotaAngle);//算法调用
				break;
			case 1:
				break;
			default :
				break;
			}
		}
		else
		{
			MVBayerToBGR(m_hCam,pInfo->pImageBuffer,m_image.GetBits(),m_image.GetPitch(),w,h,m_PixelFormat);
		}
		
		const int xDest = 0;
		const int yDest = 40;
		
		HDC hdc = GetDC(m_Hwnd);
		CDC *pDC = new CDC;
		pDC->Attach(hdc);
		//1:1 显示全图
		if( m_nZoom == 0 )
		{
			m_image.Draw(pDC->GetSafeHdc(),xDest,yDest);
		}
		else if( m_nZoom == 1)
		{
			pDC->SetStretchBltMode(COLORONCOLOR);
			m_image.Draw(pDC->GetSafeHdc(),xDest,yDest,w,h);
		}
		
		//1:1 显示中间部分图
		//m_image.Draw(pDC->GetSafeHdc(),xDest,yDest,w/2,h/2,w/4,h/4,w/2,h/2);
		pDC->Detach();
	    ReleaseDC(m_Hwnd,(HDC)pDC);
	return 0;
}

void CCmeraInterface::Save()
{
	CFileDialog Dlg(FALSE,"BMP","Untitled",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Bitmap (*.bmp)|*.bmp|Jpeg (*.jpg)|*.jpg|TIFF (*.tif)|*.tif|");

	if( Dlg.DoModal() == IDOK )
	{
		m_image.Save(Dlg.GetFileName().LockBuffer());
	}
}

void CCmeraInterface::Stop()
{
	if (!TerminalContinue)
	{
	    g_EventStop.SetEvent();
		Sleep(500);
	}
	if (MVST_SUCCESS == MVStopGrab(m_hCam))
	{
		TerminalContinue = TRUE;
		Destroy();
	}
}

HANDLE CCmeraInterface::GetCamH()
{
	return m_hCam;
}

void CCmeraInterface::SetAlgorithmFlag(int flag)
{
	m_flag = flag;
}

void CCmeraInterface::SetRota(int Rota)
{
	m_RotaAngle =Rota;
}

void CCmeraInterface::TrigContinue()
{	
	if (ContinueThread!=NULL)
	{
		CloseHandle(ContinueThread);
	}
	if (m_nFPS > 0)
	{
		m_nTimeCostMax = 0;
		g_StopWatch.Reset();
		g_EventStop.ResetEvent();
	    ContinueThread = CreateThread(NULL,0,ThreadTrigger,m_hCam,0,NULL);
		g_fTriggerFps = m_nFPS;
	}	
	TerminalContinue =FALSE;
}

void CCmeraInterface::TerminalTrigContinue()
{
	TerminalContinue = TRUE;
	g_EventStop.SetEvent();
	if(ContinueThread)
	{
		if(::WaitForSingleObject(ContinueThread, 500) != WAIT_OBJECT_0)
			::TerminateThread(ContinueThread, 0);
		CloseHandle(ContinueThread);
	}
}

double CCmeraInterface::GetExpouseTime()
{
	MVGetExposureTime(m_hCam,&m_fExpo);
	return m_fExpo;
}

void CCmeraInterface::SetExpouseTime(double ExTime)
{
	MVSetExposureTime(m_hCam,ExTime);
}
