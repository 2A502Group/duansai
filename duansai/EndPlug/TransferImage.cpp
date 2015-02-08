// TransferImage.cpp: implementation of the CTransferImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "endplug.h"
#include "TransferImage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransferImage::CTransferImage()
{
	DWORD id;
    InitializeCriticalSection(&m_cs);
	m_hWaitHandle = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_TransFerHandle = ::CreateThread(NULL, 0, TransFerPro, this, 0, &id); 
	pNewData = NULL;
}

CTransferImage::~CTransferImage()
{
	if (pNewData!=NULL)
	{
		delete [] pNewData;
	}
	if (pPreImgae!=NULL)
	{
		delete [] pPreImgae;
	}
	if(m_TransFerHandle)
	{
		if(::WaitForSingleObject(m_TransFerHandle, 500) != WAIT_OBJECT_0)
			::TerminateThread(m_TransFerHandle, 0);
		CloseHandle(m_TransFerHandle);
	}
	
	ClearQueue();
	CloseHandle(m_hWaitHandle);
	ClearQueue();
}

void CTransferImage::SendImageDataToQueue(BYTE *imageData, int theight, int twidth)
{
	EnterCriticalSection(&m_cs);
	BYTE lLineByte = WIDTHBYTES(twidth*8);
	pNewData = new BYTE[theight*lLineByte];
	memcpy(pNewData,imageData,theight*lLineByte);
	pPreImgae = new PreImageInfo;//处理前图像指针
    pPreImgae->preimageData = pNewData;
	pPreImgae->m_iHeight = theight;
	pPreImgae->m_iWidth = twidth;
	PreQueue.push(pPreImgae);
	LeaveCriticalSection(&m_cs);
} 
DWORD WINAPI CTransferImage:: TransFerPro(LPVOID pParam)
{
	DWORD					dwWait;
	CTransferImage*			TransferImage;
	HANDLE					hWaits;
	TransferImage = static_cast<CTransferImage*>(pParam);
	hWaits = TransferImage->m_hWaitHandle;
	do 
	{
		dwWait = WaitForSingleObject(hWaits,500);
		TransferImage->SentDataToProcess();
	}while (dwWait==WAIT_OBJECT_0||dwWait == WAIT_TIMEOUT);
	return 0;
}

void CTransferImage::SentDataToProcess()
{
	EnterCriticalSection(&m_cs);
	if (!PreQueue.empty())
	{
		m_poolObject.Run(PreQueue.front());
		PreQueue.pop();	
		SetEvent(m_hWaitHandle);
	}
	LeaveCriticalSection(&m_cs);
}

BYTE* CTransferImage::GetNewDataPlace()
{
	return pNewData;
}

void CTransferImage::ReleaseNewDataPlace()
{
	delete []pNewData;
}

void CTransferImage::ClearQueue()
{
	while (!PreQueue.empty())
	{
		delete PreQueue.front();
		PreQueue.pop();
	}
}
