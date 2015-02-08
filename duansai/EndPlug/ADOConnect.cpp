// ADOConnect.cpp: implementation of the CADOConnect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConnect.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CADOConnect::CADOConnect()
	:m_IsConnectDataBaseSucceed(FALSE)
{
}

CADOConnect::~CADOConnect()
{
	ExitConnect();
}

BOOL CADOConnect::InitOleCom()
{
	if (S_OK == ::CoInitialize(NULL))
	{
		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("初始化OLE/COM库环境错误"));
		return FALSE;
	}
}

BOOL CADOConnect::ExitOleCom()
{
	//释放环境
	::CoUninitialize();
	return TRUE;
}


inline BOOL CADOConnect::IsRecordsetEmpty() const
{
	if(  m_pRecordset->adoEOF || m_pRecordset->adoEOF)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CADOConnect::IsConnectSucceed() const
{
	return m_IsConnectDataBaseSucceed;
}

inline _RecordsetPtr& CADOConnect::GetRecordsetPtr()
{
	return m_pRecordset;
}

inline _ConnectionPtr& CADOConnect::GetConnectionPtr()
{
	return m_pConnection;
}


BOOL CADOConnect::InitADOConnect(LPCTSTR lpStrFileName, LPCTSTR lpszFilePassword)
{
	//初始化OLE/COM库环境
		
	try
	{
		ExitConnect();
		//创建connection对象
		m_pConnection.CreateInstance("ADODB.Connection");
		if (NULL == m_pConnection)
		{
			return FALSE;
		}
		//设置连接字符串
		CString strConnect;
// 		strConnect.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Persist Security Info=False;\
// 			Jet OLEDB:DataBase Password=%s"), lpStrFileName, lpszFilePassword);
		
		strConnect.Format(_T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=%s;Persist Security Info=False;\
 			Jet OLEDB:DataBase Password=%s"), lpStrFileName, lpszFilePassword);
		m_pConnection->Open((_bstr_t)strConnect,"","",0);//SERVER和UID,PWD的设置根据实际情况来设置
		m_IsConnectDataBaseSucceed = TRUE;
		return TRUE;
		
	}
	//捕捉异常
	catch(_com_error& e)
	{
		//显示错误信息
		AfxMessageBox(e.Description());
		return FALSE;
	}
	
}

void CADOConnect::ExitConnect()
{
	try
	{
		if (m_IsConnectDataBaseSucceed)
		{
			//关闭记录集和连接
			if(NULL != m_pRecordset)
			{
				m_pRecordset->Close();
				m_pRecordset=NULL;
			}
			
			if (NULL != m_pConnection)
			{
				m_pConnection->Close();
				m_pConnection=NULL;
			}

			m_IsConnectDataBaseSucceed = FALSE;
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());	
	}
	
}

BOOL CADOConnect::ExecuteSOL(_bstr_t bstrSQL)
{
	try
	{
		//是否已连接数据库
        if(m_pConnection==NULL)
			return FALSE;
		_variant_t affect;
		m_pConnection->Execute(bstrSQL,&affect,adCmdText);
		if(affect.lVal)
		{
			return true;
		}	
 		else
		{
			return FALSE;
		}	
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}
}

_RecordsetPtr& CADOConnect::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if (m_pRecordset != NULL)
		{
			m_pRecordset->Close();
		}

		m_pRecordset.CreateInstance(__uuidof(Recordset));
        m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);//adOpenDynamic
	}
    catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;

}

void CADOConnect::GetAllTableName(std::list<CString>& nameList) //获取数据库的所有表的名称
{	
	_RecordsetPtr prs(__uuidof(Recordset));
    CString cs;
	prs=m_pConnection->OpenSchema(adSchemaTables); 
		while (!prs->adoEOF)
		{
			if (!strcmp((_bstr_t)prs->Fields->GetItem("TABLE_TYPE")->Value,"TABLE"))
			{
				cs=(char *)((_bstr_t)prs->Fields->GetItem("TABLE_NAME")->Value);
				nameList.push_back(cs);
				prs->MoveNext();
			}
			else
				prs->MoveNext();
		}
		
		prs->Close();

}


UINT CADOConnect::GetRecordsetCount(const _RecordsetPtr& pRecordset)
{
	int nCount = 0;
	
	if (m_pRecordset->GetState() == adStateClosed/*ADOCG::adStateClosed*/)
	{
        return 0;
	}
	
	if(pRecordset->adoEOF)
	{
		return 0;
	}

	try
	{
		pRecordset->MoveFirst();
		while(!pRecordset->adoEOF)
		{
			pRecordset->MoveNext();
			nCount = nCount + 1;
		}
		pRecordset->MoveFirst();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return 0;
	}
	return nCount;

}
