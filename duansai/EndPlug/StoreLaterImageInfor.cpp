// StoreLaterImageInfor.cpp: implementation of the CStoreLaterImageInfor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "endplug.h"
#include "StoreLaterImageInfor.h"
#include "FileOperation.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD WINAPI CStoreLaterImageInfor::  StorePrc(LPVOID pParam)
{
	DWORD					dwWait;
	CStoreLaterImageInfor*	StoreLImage;
	HANDLE					hWaits;
	
	StoreLImage = static_cast<CStoreLaterImageInfor*>(pParam);
	hWaits = StoreLImage->m_hWaitHandle;
	do 
	{
		dwWait = WaitForSingleObject(hWaits,500);
		StoreLImage->StoreImage();
	} while (dwWait == WAIT_OBJECT_0||dwWait == WAIT_TIMEOUT);
	return 0;
}
CStoreLaterImageInfor::CStoreLaterImageInfor()
{
	InitializeCriticalSection(&m_cs);
	m_BmpPath = CFileOperation::Instance().GetFoldePath()+"\\";
	m_hWaitHandle = CreateEvent(NULL,FALSE,FALSE,NULL);
	InitBitmapHeadInfo();
	
	DWORD id;
	m_hThreadHandle = ::CreateThread(NULL, 0, StorePrc, this, 0, &id); 
}

CStoreLaterImageInfor::~CStoreLaterImageInfor()
{	
	if(m_hThreadHandle)
	{
		if(::WaitForSingleObject(m_hThreadHandle, 500) != WAIT_OBJECT_0)
			::TerminateThread(m_hThreadHandle, 0);
		CloseHandle(m_hThreadHandle);
	}
	
	ClearQueue();
	CloseHandle(m_hWaitHandle);
}

void CStoreLaterImageInfor::Store(LaterImageInfo* platerImage)
{
// 	LaterImageInfo* pLaterImageinfo = new LaterImageInfo;
// 	pLaterImageinfo = platerImage;
	LaterQueue.push(platerImage);
}
bool CStoreLaterImageInfor::SaveBitmap(const char *bmpName, unsigned char *imgBuf, int width, int height)
{
	if(NULL == imgBuf)
	{
		return false;
	}
	int lineByte=(width *BiBitCount/8+3)/4*4;
	FILE *fp=fopen(bmpName,"wb");
	if (NULL == fp)
	{
		return 0;
	}
	
	//申请位图文件头结构变量，填写文件头信息
	m_FileHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ColorTablesize+lineByte*height;
	//写文件头进文件
	fwrite(&m_FileHead,sizeof(BITMAPFILEHEADER),1,fp);
	
	//申请位图信息头结构变量，填写信息头信息
	m_InfoHead.biHeight=height;
	m_InfoHead.biWidth=width;
	m_InfoHead.biSizeImage=lineByte*height;
	
	//写位图信息进内存
	fwrite(&m_InfoHead,sizeof(BITMAPINFOHEADER),1,fp);
	
	//设定调色板数据
	fwrite(m_Quad,sizeof(RGBQUAD),256,fp);
	
	//写进图数据进文件
	fwrite(imgBuf,height*lineByte,1,fp);
	fclose(fp);
	return true;
}

void CStoreLaterImageInfor::InitBitmapHeadInfo()
{
	m_FileHead.bfType=0x4D42;	//bmp
	//	fileHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ColorTablesize+lineByte*height;
	m_FileHead.bfReserved1=0;
	m_FileHead.bfReserved2=0;
	m_FileHead.bfOffBits=54+ColorTablesize;
	
	//申请位图信息头结构变量，填写信息头信息
	m_InfoHead.biBitCount=BiBitCount;
	m_InfoHead.biClrImportant=0;
	m_InfoHead.biClrUsed=0;
	m_InfoHead.biCompression=0;
	//	m_InfoHead.biHeight=height;
	m_InfoHead.biPlanes=1;
	m_InfoHead.biSize=40;
	//	head.biSizeImage=lineByte*height;
	//	head.biWidth=width;
	m_InfoHead.biXPelsPerMeter=0;
	m_InfoHead.biYPelsPerMeter=0;
	
	//设定调色板数据
	for(int   n=0;   n<256;   n++)   
	{   
		m_Quad[n].rgbBlue		=   n;   
		m_Quad[n].rgbGreen		=   n;   
		m_Quad[n].rgbRed		=   n;   
		m_Quad[n].rgbReserved	=   0;   
	}
}
void CStoreLaterImageInfor:: ClearQueue()
{
	while (!LaterQueue.empty())
	{
		delete LaterQueue.front();
		LaterQueue.pop();
	}	
}
void CStoreLaterImageInfor:: StoreImage()
{
	EnterCriticalSection(&m_cs);
	LaterImageInfo * pDataStruct;
	if (!LaterQueue.empty())
	{
		pDataStruct = LaterQueue.front();
		if (NULL != pDataStruct)
		{
			this->SaveBitmap(GetBmpName(), pDataStruct->laterimageData, 
				pDataStruct->m_lWidth, pDataStruct->m_lHeight);		//存图像到data目录下指定文件夹中（年-月-日格式）	
			delete pDataStruct;
		}
		LaterQueue.pop();
		SetEvent(m_hWaitHandle);
	}
	LeaveCriticalSection(&m_cs);
}
CString CStoreLaterImageInfor:: GetBmpName() const
{
	CString strTemp;
	strTemp.Format(_T("%s%s")
		, m_BmpPath
		, CTime::GetCurrentTime().Format("%H-%M-%S"));
	return strTemp;
}

void CStoreLaterImageInfor::StoreInDB(BadPlugInfo* pDataToDB)
{
	if (!CFileOperation::Instance().m_Adoconnect.IsConnectSucceed())
	{
		return;
	}
	CString  sql; 
	sql.Format("insert into t_BadPlugInfo(m_tWidth,m_tHeight,m_tType,m_tName)\
		values('%d','%d','%d','%d')"
		,(unsigned long)pDataToDB->m_tWidth
		,(unsigned long)pDataToDB->m_tHeight
		,pDataToDB->m_tType
		,CTime::GetCurrentTime().Format("%H%M%S"));
	if(!CFileOperation::Instance().m_Adoconnect.ExecuteSOL((_bstr_t)sql))
	{
		return;
	}
}
