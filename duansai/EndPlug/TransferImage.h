// TransferImage.h: interface for the CTransferImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFERIMAGE_H__4DD8EB92_74F1_4E1B_808D_7640C39F7AB4__INCLUDED_)
#define AFX_TRANSFERIMAGE_H__4DD8EB92_74F1_4E1B_808D_7640C39F7AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ThreadPool.h"
#include "StructData.h"
#include "SingletonObject.h"
#include <queue>
using namespace std;
class CTransferImage :public CSingletonObject<CTransferImage>
{
public:
	void SendImageDataToQueue(BYTE* imageData, int theight, int twidth);
	static DWORD WINAPI TransFerPro(LPVOID pParam);
	CTransferImage();
	virtual ~CTransferImage();
	CRITICAL_SECTION m_cs;
public:
	void ClearQueue();
	void ReleaseNewDataPlace();
	BYTE* GetNewDataPlace();
	void SentDataToProcess();
	queue<PreImageInfo *> PreQueue;//处理前图像队列指针
	PreImageInfo *pPreImgae;
	//-----------------------------------------------------------------------
	//----------------------------------------单实例模型------------------------------
	friend class CSingletonObject<CTransferImage>;
private:
	BYTE*               pNewData;
	HANDLE				m_TransFerHandle;
	HANDLE				m_hWaitHandle;
	HANDLE				m_hNotifyShutdown;
	CThreadPool         m_poolObject;
};

#endif // !defined(AFX_TRANSFERIMAGE_H__4DD8EB92_74F1_4E1B_808D_7640C39F7AB4__INCLUDED_)
