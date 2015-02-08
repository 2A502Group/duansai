// ThreadPool.cpp: implementation of the CThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "endplug.h"
#include "ThreadPool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD WINAPI CThreadPool::_ThreadProc(LPVOID pParam)
{
	DWORD					dwWait;
	CThreadPool*			pool;
  	HANDLE					hThread = GetCurrentThread();
	DWORD					dwThreadId = GetCurrentThreadId();
	HANDLE					hWaits[2];

//	ASSERT(pParam != NULL);
	if(NULL == pParam)
	{
		return -1;
	}

	pool = static_cast<CThreadPool*>(pParam);
	hWaits[0] = pool->GetWaitHandle(dwThreadId);
	hWaits[1] = pool->GetShutdownHandle();
    
	do 
	{
		dwWait = WaitForMultipleObjects(2, hWaits, FALSE, 500);
		pool->BusyNotify(dwThreadId);	
		pool->ToDealImageData(dwThreadId);
		pool->FinishNotify(dwThreadId); // tell the pool, i am now free
	} while(dwWait==WAIT_OBJECT_0||dwWait == WAIT_TIMEOUT);
	return 0;
}

CThreadPool::CThreadPool(int nPoolSize, int nPoolMaxSize, bool bCreateNow)
{
	pDealImageData = new CDealImageData;
	m_nPoolSize = nPoolSize;
	m_nPoolMaxSize = nPoolMaxSize;

	if(bCreateNow)
	{
		if(!Create())
		{
			throw 1;
		}
	}
}

bool CThreadPool::Create()
{

	InitializeCriticalSection(&m_cs); // this is used to protect the shared 
									  // data like the list and map
	
	m_hNotifyShutdown = CreateEvent(NULL, TRUE, FALSE, SHUTDOWN_EVT_NAME);
	if(!m_hNotifyShutdown)
	{
		return false;
	}

	// create the threads
	for(int nIndex = 0; nIndex < m_nPoolSize; nIndex++)
	{
		if(!CreateThread(true))
			break;
	}
	return true;
}
//------------------------------------------------------------------------------

CThreadPool::~CThreadPool()
{
	Destroy();
}

void CThreadPool::Destroy()
{
	// tell all threads to shutdown.
	SetEvent(m_hNotifyShutdown);

	// lets give the thread one second atleast to terminate
	Sleep(1000);
	
	ThreadMap::iterator iter;
	_ThreadData ThreadData;
	
	// walk through the events and threads and close them all
	for(iter = m_threads.begin(); iter != m_threads.end(); iter++)
	{
		ThreadData = (*iter).second;		
		CloseHandle(ThreadData.WaitHandle);
		CloseHandle(ThreadData.hThread);
	}

	// close the shutdown event
	CloseHandle(m_hNotifyShutdown);

	// delete the critical section
	DeleteCriticalSection(&m_cs);

	// empty all collections
	for (int i = 0; i< ImageInfo.size();i++)
	{
		if (!ImageInfo.empty())
		{
			ImageInfo.pop();
		}
	}
	m_threads.clear();
}
//------------------------------------------------------------------------------

int CThreadPool::GetPoolSize()
{
	return m_nPoolSize;
}

void CThreadPool::SetPoolSize(int nSize)
{
//	ASSERT(nSize > 0);
	if(nSize <= 0)
	{
		return;
	}

	m_nPoolSize = nSize;
}

//------------------------------------------------------------------------------
HANDLE CThreadPool::GetShutdownHandle()
{
	return m_hNotifyShutdown;
}

void CThreadPool::FinishNotify(DWORD dwThreadId)
{
	ThreadMap::iterator iter;
	
	EnterCriticalSection(&m_cs);
	iter = m_threads.find(dwThreadId);

	if(iter == m_threads.end())	// if search found no elements
	{			
		LeaveCriticalSection(&m_cs);
		return;
	}
	else
	{	
		m_threads[dwThreadId].bFree = true;
	
		if(!ImageInfo.empty())
		{
	
			LeaveCriticalSection(&m_cs);
			return;
		}		
		else
		{
			LeaveCriticalSection(&m_cs);
			ResetEvent(m_threads[dwThreadId].WaitHandle);
		}
	}	
}
//------------------------------------------------------------------------------

void CThreadPool::BusyNotify(DWORD dwThreadId)
{
	ThreadMap::iterator iter;
	
	EnterCriticalSection(&m_cs);

	iter = m_threads.find(dwThreadId);

	if(iter == m_threads.end())	
	{
		LeaveCriticalSection(&m_cs);
	}
	else
	{		
		m_threads[dwThreadId].bFree = false;		
		LeaveCriticalSection(&m_cs);
	}	
}
void CThreadPool::Run(PreImageInfo *pPreimage)
{
//	ASSERT(runObject != NULL);
	// add it to the list
//     PreImageInfo *pImageinfo = new PreImageInfo;
// 	pImageinfo = pPreimage;
//     ImageInfo.push(pImageinfo);
	ImageInfo.push(pPreimage);

	// See if any threads are free
	EnterCriticalSection(&m_cs);
	ThreadMap::iterator iter;
	_ThreadData ThreadData;

	bool bStarted = false;
	for(iter = m_threads.begin(); iter != m_threads.end(); iter++)
	{
		ThreadData = (*iter).second;
		
		if(ThreadData.bFree)
		{
			m_threads[ThreadData.dwThreadId].bFree = false;			
			SetEvent(ThreadData.WaitHandle); 
			bStarted = true;
			break;
		}
	}

	// 线程不足，添加线程
	if(!bStarted)//这一块儿没有添加
		CreateThread(false);	
	LeaveCriticalSection(&m_cs);
}

HANDLE CThreadPool::GetWaitHandle(DWORD dwThreadId)
{
	HANDLE hWait;
	ThreadMap::iterator iter;
	
	EnterCriticalSection(&m_cs);
	iter = m_threads.find(dwThreadId);
	
	if(iter == m_threads.end())	// if search found no elements
	{
		LeaveCriticalSection(&m_cs);
		return NULL;
	}
	else
	{		
		hWait = m_threads[dwThreadId].WaitHandle;
		LeaveCriticalSection(&m_cs);
	}	

	return hWait;
}
//------------------------------------------------------------------------------

void CThreadPool::SetPoolMaxSize(int nMaxSize)
{
	m_nPoolMaxSize = nMaxSize;
}

// 创建线程，调用时需用临界区保护
// bSuspend:是否暂时挂起

bool CThreadPool::CreateThread(bool bSuspend)
{
	HANDLE		hThread;
	DWORD		dwThreadId;
	_ThreadData ThreadData;
	TCHAR		szEvtName[20];

	if(m_threads.size() >= m_nPoolMaxSize)
		return false;

	hThread = ::CreateThread(NULL, 0, CThreadPool::_ThreadProc, 
			this, CREATE_SUSPENDED, &dwThreadId);
//	ASSERT(NULL != hThread);
	
	if(hThread)
	{
		// add the entry to the map of threads
		ThreadData.bFree		= bSuspend;
		ThreadData.WaitHandle	= CreateEvent(NULL, TRUE, !bSuspend, szEvtName);
		ThreadData.hThread		= hThread;
		ThreadData.dwThreadId	= dwThreadId;
		
		m_threads.insert(ThreadMap::value_type(dwThreadId, ThreadData));//每增加一个线程就在MAP中插入一个		
		
		ResumeThread(hThread); //创建并挂起
	}
	else
	{
		return false;
	}
	return true;
}

void CThreadPool::ToDealImageData(DWORD ThreadID)
{
	EnterCriticalSection(&m_cs);
	if (!ImageInfo.empty())
	{
		pDealImageData->CallAlogrithm(ImageInfo.front());
		ImageInfo.pop();
		SetEvent(m_threads[ThreadID].WaitHandle);
	}
	LeaveCriticalSection(&m_cs);
}
