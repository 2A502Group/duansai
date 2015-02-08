// CmeraInterface.h: interface for the CCmeraInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMERAINTERFACE_H__EBCFD1FC_942A_4362_9FF9_A938A4AC941B__INCLUDED_)
#define AFX_CMERAINTERFACE_H__EBCFD1FC_942A_4362_9FF9_A938A4AC941B__INCLUDED_
#include "Cdib.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\include\MVGigE.h"
#include "..\include\MVImage.h"
#include "StopWatch.h"
#include "TransferImage.h"
class CCmeraInterface  
{
public:
	CCmeraInterface();
	virtual ~CCmeraInterface();
private:
	HANDLE m_hCam;
	MVImage m_image;
	MV_PixelFormatEnums m_PixelFormat;
	int		m_nZoom;
	CDib Dib;
	int m_flag;
	int m_RotaAngle;
	BOOL                TerminalContinue;
public:
	HWND m_Hwnd;//标识传过来的句柄
	UINT m_nFPS;		//! 帧率
	BOOL m_bTrigCont;	//! 连续触发模式
	int m_nTimeCostMax;	//! 从发出触发指令到得到图像所花费时间的最大值
	double m_fExpo;		//! 曝光时间
	HANDLE ContinueThread;
	CTransferImage m_transfer;
public:
	void SetExpouseTime(double ExTime);
	double GetExpouseTime();
	void TerminalTrigContinue();
	void TrigContinue();
	void SetRota(int Rota);
	void SetAlgorithmFlag(int flag);
	HANDLE GetCamH();
	void Stop();
	BOOL Open();
	void Destroy();
	void Start();
	int  StreamCB(MV_IMAGE_INFO *pInfo);
	void Save();
};

#endif // !defined(AFX_CMERAINTERFACE_H__EBCFD1FC_942A_4362_9FF9_A938A4AC941B__INCLUDED_)
