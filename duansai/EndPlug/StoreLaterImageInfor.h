// StoreLaterImageInfor.h: interface for the CStoreLaterImageInfor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORELATERIMAGEINFOR_H__1FC4AAF8_34CD_4937_A573_57AE2870B047__INCLUDED_)
#define AFX_STORELATERIMAGEINFOR_H__1FC4AAF8_34CD_4937_A573_57AE2870B047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StructData.h"
#include <queue>
#include "SingletonObject.h"
#include "ADOConnect.h"
using namespace std;
class CStoreLaterImageInfor : public CSingletonObject<CStoreLaterImageInfor>
{
public:
	CString GetBmpName() const;
	void StoreImage();
	void ClearQueue();
	void Store(LaterImageInfo* platerImage);
	void InitBitmapHeadInfo(void);
	bool SaveBitmap(const char *bmpName, unsigned char *imgBuf, int width, int height);
	static DWORD WINAPI StorePrc(LPVOID pParam);
	CStoreLaterImageInfor();
	virtual ~CStoreLaterImageInfor();
	enum
	{
		BiBitCount = 8,
		ColorTablesize = 1024
	};
public:
	void StoreInDB(BadPlugInfo* pDataToDB);
	RGBQUAD m_Quad[256];
	BITMAPINFOHEADER m_InfoHead;
	BITMAPFILEHEADER m_FileHead;
	CString m_BmpPath;
	HWND m_hWnd;
	CRITICAL_SECTION m_cs;
	friend class CSingletonObject<CStoreLaterImageInfor>;
private:
	queue<LaterImageInfo* > LaterQueue;
	HANDLE				m_hWaitHandle;
	HANDLE				m_hThreadHandle;
};

#endif // !defined(AFX_STORELATERIMAGEINFOR_H__1FC4AAF8_34CD_4937_A573_57AE2870B047__INCLUDED_)
