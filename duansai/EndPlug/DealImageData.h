// DealImageData.h: interface for the CDealImageData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEALIMAGEDATA_H__07E1AA63_56B6_4022_BE94_568C4562977F__INCLUDED_)
#define AFX_DEALIMAGEDATA_H__07E1AA63_56B6_4022_BE94_568C4562977F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StructData.h"
#include "Cdib.h"
#include "queue.h"
class CDealImageData  
{
public:
	static DWORD WINAPI DealImagePro(LPVOID pParam);
	void SendToStoreImage();
	void CallAlogrithm(PreImageInfo* imageInfo);
    
	CDealImageData();
	virtual ~CDealImageData();
public:
	void ClearQueue();
	CRITICAL_SECTION m_cs;
private:
	CDib m_DibAlogrithm;
	queue<LaterImageInfo*> pLaterQueue;
	HANDLE				m_DealImageHandle;
	HANDLE				m_hWaitHandle;
};

#endif // !defined(AFX_DEALIMAGEDATA_H__07E1AA63_56B6_4022_BE94_568C4562977F__INCLUDED_)
