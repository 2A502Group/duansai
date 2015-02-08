// FileOperation.h: interface for the CFileOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATION_H__A7D49AED_867E_4F52_947C_DAFF41FBC2FB__INCLUDED_)
#define AFX_FILEOPERATION_H__A7D49AED_867E_4F52_947C_DAFF41FBC2FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SingletonObject.h"
#include "ADOConnect.h"

class CFileOperation : public CSingletonObject<CFileOperation>
{
public:
	CFileOperation();
	virtual ~CFileOperation();
public:
	void FileOperationStart();
	CString GetDBFFilePath();
	CString GetFoldePath();
	BOOL DeleteNullFolder();
	void DeleteFolderAndFile();
	BOOL CreateFloderAndDbFile();
	BOOL IsFileExist(const CString &strFileName);
	BOOL LoadResourceFromDll(int resourceId, const CString& strDesFileName);
	BOOL CreateFolderForPlugImage();
	BOOL CreateDirectoryForAll();
	CString GetModuleDir(); 
	CString GetWorkDir();
	CString GetPhotoFilePath();
	CString File_Ext();
	enum EnumMDBNames
	{
		   FileBadPlugInfo	    = 109
	};
	friend class CSingletonObject<CFileOperation>;
public:
	CADOConnect m_Adoconnect;
private:
	CString  m_strPhotoFolderPath;
	CString  name_ext;
	CString  m_strModulePath;
	CString  time_name;
	CString  StrDataBaseFileExtension;
	CString  m_BitMapPath;
	CString  m_BitMapDBInfoPath;
	CString  m_FolderPath;
	CString  m_DataPath;
};

#endif // !defined(AFX_FILEOPERATION_H__A7D49AED_867E_4F52_947C_DAFF41FBC2FB__INCLUDED_)
