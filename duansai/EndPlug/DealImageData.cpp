// DealImageData.cpp: implementation of the CDealImageData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "endplug.h"
#include "DealImageData.h"
#include "StoreLaterImageInfor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD WINAPI CDealImageData:: DealImagePro(LPVOID pParam)
{
	DWORD					dwWait;
	CDealImageData*			DealImage;
	HANDLE					hWaits;
	DealImage = static_cast<CDealImageData*>(pParam);
	hWaits = DealImage->m_hWaitHandle;
	do 
	{
		dwWait = WaitForSingleObject(hWaits,500);
		DealImage->SendToStoreImage();
	}while (dwWait==WAIT_OBJECT_0||dwWait == WAIT_TIMEOUT);
	return 0;
}

CDealImageData::CDealImageData()
{
	InitializeCriticalSection(&m_cs);
	m_hWaitHandle = CreateEvent(NULL,FALSE,FALSE,NULL);
	DWORD id;
	m_DealImageHandle = ::CreateThread(NULL, 0, DealImagePro, this, 0, &id); 
}

CDealImageData::~CDealImageData()
{
	if(m_DealImageHandle)
	{
		if(::WaitForSingleObject(m_DealImageHandle, 500) != WAIT_OBJECT_0)
			::TerminateThread(m_DealImageHandle, 0);
		CloseHandle(m_DealImageHandle);
	}
	
	ClearQueue();
	CloseHandle(m_hWaitHandle);
}

void CDealImageData::CallAlogrithm(PreImageInfo* imageInfo)
{
// 	PreImageInfo* pPre = new PreImageInfo;
// 	pPre = imageInfo;
	m_DibAlogrithm.CutApart(imageInfo->preimageData,imageInfo->m_iWidth,imageInfo->m_iHeight, pLaterQueue);
}

void CDealImageData::SendToStoreImage()
{
	EnterCriticalSection(&m_cs);
    if (!pLaterQueue.empty())
    {
		CStoreLaterImageInfor::Instance().Store(pLaterQueue.front());
		pLaterQueue.pop();
		SetEvent(m_hWaitHandle);
    }
	LeaveCriticalSection(&m_cs);
}

void CDealImageData::ClearQueue()
{
	while(!pLaterQueue.empty())
	{
		delete pLaterQueue.front();
		pLaterQueue.pop();
	}
}
