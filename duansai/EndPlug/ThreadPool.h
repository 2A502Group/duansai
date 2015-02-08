// ThreadPool.h: interface for the CThreadPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADPOOL_H__AC42E3B2_CEBA_434D_B369_C1593AB73F0F__INCLUDED_)
#define AFX_THREADPOOL_H__AC42E3B2_CEBA_434D_B369_C1593AB73F0F__INCLUDED_
#pragma warning(disable:4786)//这句话很关键，非常管用
#include <windows.h>
#include <list>
#include <map>
#include <queue>
#include "DealImageData.h"
using namespace std;

#define POOL_SIZE		  10
#define POOL_MAXSIZE	  1000
#define SHUTDOWN_EVT_NAME "PoolEventShutdown"
typedef struct tagThreadData
{
	bool	bFree;
	HANDLE	WaitHandle;
	HANDLE	hThread;
	DWORD	dwThreadId;
} _ThreadData;

typedef map<DWORD, _ThreadData, less<DWORD>, allocator<_ThreadData> > ThreadMap;
enum ThreadPriority
{
	High,
	Low
};
class CThreadPool  
{
private:
	bool CreateThread(bool bSuspend);
	static DWORD WINAPI _ThreadProc(LPVOID);
	ThreadMap m_threads;
	CRITICAL_SECTION m_cs;
	int		m_nPoolSize;		// 初始尺寸
	int		m_nPoolMaxSize;		// 最大尺寸
	HANDLE	m_hNotifyShutdown; // notifies threads that a new function 
	queue<PreImageInfo*> ImageInfo;
	CDealImageData * pDealImageData;
public:
	CThreadPool(int nPoolSize = POOL_SIZE, int nPoolMaxSize = POOL_MAXSIZE, bool bCreateNow = true);
	virtual ~CThreadPool();
	void	FinishNotify(DWORD dwThreadId);
	void	BusyNotify(DWORD dwThreadId);
	
	HANDLE	GetWaitHandle(DWORD dwThreadId);
	HANDLE	GetShutdownHandle();
	
public:
	void    Run(PreImageInfo *pPreimage);
	void    ToDealImageData(DWORD ThreadID);
	void    SetPoolMaxSize(int nMaxSize);
	bool	Create();	// creates the thread pool
	void	Destroy();	// destroy the thread pool
	int		GetPoolSize();
	void	SetPoolSize(int);	
};
#endif // !defined(AFX_THREADPOOL_H__AC42E3B2_CEBA_434D_B369_C1593AB73F0F__INCLUDED_)
