#ifndef __CDIB_H
#define __CDIB_H
#include "StoreLaterImageInfor.h"
#include "queue.h"
DECLARE_HANDLE(HDIB);		// DIB??
#define PALVERSION   0x300	// DIB??


#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))

#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)

#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// biWidth'
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)


#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

#define PI 3.1415926535

#define RADIAN(angle) ((angle)*PI/180.0) 
/////////////////////////////////////////////////////////////

// ????????//////////////////////////////////////////
#include <complex>
using namespace std;
/////////////////////////////////////////////////////////////

//  ???????????///////////////////////////////////
typedef struct{
	int Value;
	int Dist;
	int AngleNumber;
}	MaxValue;

typedef struct{
	int Height;
	int Width;
}	Seed;

typedef struct{
	int Height;
	int Width;
}	Point;
/////////////////////////////////////////////////////////////

class CDib: public CObject
{
public:
    RGBQUAD* m_pRGB;
    BYTE* m_pData;
    UINT m_numberOfColors;
	BOOL m_valid;
    BITMAPFILEHEADER bitmapFileHeader;

    BITMAPINFOHEADER* m_pBitmapInfoHeader;
    BITMAPINFO* m_pBitmapInfo;
    BYTE* pDib;
	DWORD size;
	int byBitCount;
	DWORD dwWidthBytes;
public:
    CDib();
    ~CDib();

	char m_fileName[1024];
    char* GetFileName();
    BOOL IsValid();
    DWORD GetSize();
    UINT GetWidth();
    UINT GetHeight();
    UINT GetNumberOfColors();
    RGBQUAD* GetRGB();
    BYTE* GetData();
    BITMAPINFO* GetInfo();
	WORD DIBNumColors(LPBYTE lpDIB);
    BOOL SaveFile(const CString filename);
public:
	void CutApart(BYTE *imageData, int width, int height,queue<LaterImageInfo*>&  LaterQueue);
	LPSTR RotateDIB(BYTE* iamgeData,int width, int height, int iRotateAngle);
	unsigned char GetMedianNum(unsigned char * bArray, int iFilterLen);
	BOOL MedianFilter(BYTE* imageData, LONG lWidth, LONG lHeight, int iFilterH, int iFilterW, int iFilterMX, int iFilterMY);
	DWORD GetDibWidthBytes();
    bool LoadFile(const char* dibFileName);
	// -----------------ÕºœÒ¥¶¿ÌÀ„∑®------------------------------------------------
};

#endif // !defined(AFX_DIBIMAGE_H__254F3D1E_BB20_40DA_AE07_E8E0219DFA8C__INCLUDED_)
