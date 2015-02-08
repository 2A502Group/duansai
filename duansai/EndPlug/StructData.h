#pragma once

#ifdef _DATATYPE_H
#else
#define _DATATYPE_H
typedef struct BadPlugInfo
{
	int m_tWidth;
	int m_tHeight;
	CString m_tType;
	CString m_tName;
}*pBadPlugInfo;

typedef struct PreImageInfo
{
	BYTE* preimageData;
	int m_iWidth;
	int m_iHeight;
}*pPreImageInfo;

typedef struct LaterImageInfo
{
	BYTE* laterimageData;
	int m_lWidth;
	int m_lHeight;
}*pLaterImageInfo;
#endif