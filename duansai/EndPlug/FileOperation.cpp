// FileOperation.cpp: implementation of the CFileOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "endplug.h"
#include "FileOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib") 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperation::CFileOperation()
{
	m_strModulePath = GetModuleDir();//�����ռ��ַ
	m_DataPath = m_strModulePath + "\\data";//data�ļ��е�·��
	StrDataBaseFileExtension = ".dbf";//���ݿ⸴�ƺ��ļ�����չ��
	m_strPhotoFolderPath = "";
	name_ext = "";//.bmp��չ��;
	time_name = "";//ʱ��Ҳ���ļ�����Ҳ�����ݿ��ļ�����
	m_BitMapPath = "";//BMP�ļ���ַ������ͼ���ļ���ַ��
	m_BitMapDBInfoPath = "";//DBF�ļ����ݿ��ַ
	m_FolderPath = "";//�����洢�ļ��е�ַ
}

CFileOperation::~CFileOperation()
{
}
BOOL CFileOperation::CreateDirectoryForAll()
{
	BOOL ret;//��ʶ�ļ����Ƿ񴴽��ɹ�
	m_strPhotoFolderPath =GetModuleDir(); 
	if(m_strPhotoFolderPath ==" ")
	{
		AfxMessageBox("Get the path fail,Please try again!");
		ret =  FALSE;
	}
		m_strPhotoFolderPath +="\\Photo";
	if   (!PathIsDirectory(m_strPhotoFolderPath))   	// �ж�·���Ƿ����   
	{   
		CString  strMsg;   
		strMsg.Format   ("ָ��·��\"%s\"�����ڣ��Ƿ񴴽�?",m_strPhotoFolderPath);   
		if   (AfxMessageBox(strMsg,   MB_YESNO)   ==   IDYES)   
		{   
			if   (!CreateDirectory(m_strPhotoFolderPath,   NULL))//begain to create;
			{   
				strMsg.Format   ("����·��\"%s\"ʧ�ܣ��Ƿ����?",   m_strPhotoFolderPath);   
				if   (AfxMessageBox(strMsg,   MB_YESNO)   ==   IDYES)   
					ret = FALSE;   
			}   
			else
			{
				AfxMessageBox("�����ɹ�!");
				ret =  TRUE;
			}
		}   
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		ret = TRUE;
	}
	return ret;
}
CString CFileOperation:: GetModuleDir() 
{ 
	HMODULE module = GetModuleHandle(0); 
	char pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 
	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		return CString(""); 
	else 
	{
		return csFullPath.Left( nPos); 
	}
}
CString CFileOperation::GetWorkDir() 
{  
	char pFileName[MAX_PATH]; 
	int nPos = GetCurrentDirectory( MAX_PATH, pFileName); 
	CString csFullPath(pFileName);  
	if( nPos < 0 ) 
		return CString(""); 
	else 
		return csFullPath; 
}
CString CFileOperation::GetPhotoFilePath()
{
	return m_strPhotoFolderPath;
}
CString CFileOperation::File_Ext()
{
	CTime curTime = CTime::GetCurrentTime();
    name_ext = curTime.Format(_T("\\%Y-%H-%M-%S"));
	return name_ext;
}

BOOL CFileOperation::CreateFolderForPlugImage()
{
	CTime curTime =CTime::GetCurrentTime();
	CString FolderName;
	FolderName.Format(_T("\\%d-%d-%d"),curTime.GetYear(),curTime.GetMonth(),curTime.GetDay());
	time_name = FolderName;
	if (!PathIsDirectory(m_DataPath))
	{
		if(!CreateDirectory(m_DataPath,NULL))//����data�ļ���
			return FALSE;
	}
	CString PathFolder = m_DataPath +FolderName;
	m_FolderPath = PathFolder;
	if (PathFolder==" ")
	{
		return FALSE;
	}
	else
	{
		if (!PathIsDirectory(PathFolder))
		{
			if(!CreateDirectory(PathFolder,NULL))
				return FALSE;
			else
                return TRUE;
		}
		else
		{
			return TRUE;
		}
	}
}

BOOL CFileOperation::LoadResourceFromDll(int resourceId, const CString &strDesFileName)
{
	
	if(IsFileExist(strDesFileName))
	{
		return TRUE;
	}
	HMODULE hModule = ::LoadLibrary(_T("SourceDB.dll"));
	if (NULL == hModule)
	{
		return FALSE;
	}
	
	BOOL ret = FALSE;
	HRSRC	res = ::FindResource(hModule, MAKEINTRESOURCE(resourceId), _T("accdb"));
	if (NULL != res)
	{
		HGLOBAL	gl	= ::LoadResource(hModule, res);
		LPVOID	lp	= ::LockResource(gl);
		HANDLE	fp	= ::CreateFile(strDesFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
		DWORD writtenLen;
		if (::WriteFile(fp, lp, ::SizeofResource(hModule, res), &writtenLen, NULL))
		{
			ret = TRUE;
		}
		
		::CloseHandle(fp);
		::FreeResource(res);
	}
	else
	{
		TCHAR szBuffer[MAX_PATH] = {0};
		int iLen = _stprintf(szBuffer, _T("Error code %d:"), GetLastError());
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			szBuffer + iLen,
			MAX_PATH - iLen - 3,
			NULL
			);
		AfxMessageBox(szBuffer);
	}
	
	::FreeLibrary(hModule);
	return ret;
}

BOOL CFileOperation::IsFileExist(const CString &strFileName)
{
	CFileFind fFind;
	return fFind.FindFile(strFileName);
}

BOOL CFileOperation::CreateFloderAndDbFile()
{
	CreateFolderForPlugImage();
	CString FileDataBasePath = m_DataPath + time_name \
		    + StrDataBaseFileExtension;//time_name��һ��ʱ��ֵ������-��-��
	m_BitMapDBInfoPath = FileDataBasePath;
	if (!LoadResourceFromDll(CFileOperation::FileBadPlugInfo, FileDataBasePath))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void CFileOperation::DeleteFolderAndFile()
{
	if (DeleteNullFolder())//ɾ�����ļ��гɹ������ɾ��DBF��ʽ���ļ���Ҳ�����ݿ��ļ���
	{
		if (m_Adoconnect.IsConnectSucceed())
		{
	    	m_Adoconnect.ExitConnect();
		}
		Sleep(100);
		DeleteFile(GetDBFFilePath());
	}
}

BOOL CFileOperation::DeleteNullFolder()
{
	CFileFind finder;
	int FileCount = 0;
	BOOL Finde = finder.FindFile(GetFoldePath()+"\\*.*");
	while (Finde)
	{  
		FileCount++;
		Finde = finder.FindNextFile();   
	}
	finder.Close();
	if (FileCount <=2)
	{
		Finde = FALSE;	
		FileCount = 0;
		if (::RemoveDirectory(GetFoldePath()))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}	
	}
	else
	{
		return FALSE;
	}
}

CString CFileOperation::GetFoldePath()
{
	return m_FolderPath;
}

CString CFileOperation::GetDBFFilePath()
{
	return m_BitMapDBInfoPath;
}

void CFileOperation::FileOperationStart()
{
	if (CreateFloderAndDbFile())
	{
		CString strFileName;
		strFileName = GetDBFFilePath();
		m_Adoconnect.InitADOConnect(strFileName);
	}
}
