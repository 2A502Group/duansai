// ADOConnect.h: interface for the CADOConnect class.
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#include "StdAfx.h"
#include <list>

#ifndef MSADO15DLL
#define MSADO15DLL
#pragma warning(disable:4146)
#import "C:/Program Files/Common Files/System/ADO/msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
//#pragma warning(default:4146)
using namespace ADODB;

#endif //MSADO15DLL


#endif // _MSC_VER > 1000

class CADOConnect
{
public:
    BOOL InitADOConnect(LPCTSTR lpStrFileName, LPCTSTR lpszFilePassword = _T("admin"));
	void ExitConnect();
	static BOOL InitOleCom();
	static BOOL ExitOleCom();
	CADOConnect();
	virtual ~CADOConnect();
	BOOL IsConnectSucceed() const;
	BOOL IsRecordsetEmpty() const;
	BOOL ExecuteSOL(_bstr_t bstrSQL);
protected:
	UINT GetRecordsetCount(const _RecordsetPtr& pRecordset);
	void GetAllTableName(std::list<CString>& nameList);
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);

	_ConnectionPtr& GetConnectionPtr();
	_RecordsetPtr& GetRecordsetPtr();
private:
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;

	BOOL m_IsConnectDataBaseSucceed;
};

