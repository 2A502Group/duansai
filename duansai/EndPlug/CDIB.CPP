#include "stdafx.h"
#include "cdib.h"
#include "windowsx.h"
#include "math.h"
#include "StructData.h"
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

CDib::CDib()
{
	size=0;
}

CDib::~CDib()
{
    GlobalFreePtr(m_pBitmapInfo);
}

bool CDib::LoadFile(const char* dibFileName)
{
	strcpy(m_fileName,dibFileName);
    CFile dibFile(m_fileName, CFile::modeRead);
    dibFile.Read((void*)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
    if (bitmapFileHeader.bfType == 0x4d42)
    {
        DWORD fileLength = dibFile.GetLength();    
		size = fileLength -sizeof(BITMAPFILEHEADER);
		pDib =(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, size);
        dibFile.Read((void*)pDib, size);
        dibFile.Close();
        m_pBitmapInfo = (BITMAPINFO*) pDib;
        m_pBitmapInfoHeader = (BITMAPINFOHEADER*) pDib;
        m_pRGB = (RGBQUAD*)(pDib + m_pBitmapInfoHeader->biSize);
        int m_numberOfColors = GetNumberOfColors();
        if (m_pBitmapInfoHeader->biClrUsed == 0)
            m_pBitmapInfoHeader->biClrUsed =
			m_numberOfColors;
        DWORD colorTableSize = m_numberOfColors * sizeof(RGBQUAD);
        m_pData = pDib + m_pBitmapInfoHeader->biSize + colorTableSize;
		if (m_pRGB == (RGBQUAD*)m_pData) // No color table
			m_pRGB = NULL;
        m_pBitmapInfoHeader->biSizeImage = GetSize();
		m_valid = TRUE;
		return true;
    }    
    else
    {
        m_valid = FALSE;
        AfxMessageBox("This isn't a bitmap file!");
		return false;
    }
}

BOOL CDib::IsValid()
{
    return m_valid;
}
        
char* CDib::GetFileName()
{
    return m_fileName;
}
        
UINT CDib::GetWidth()
{
    return (UINT) m_pBitmapInfoHeader->biWidth;
}
      
UINT CDib::GetHeight()
{
    return (UINT) m_pBitmapInfoHeader->biHeight;
}
        
DWORD CDib::GetSize()
{
    if (m_pBitmapInfoHeader->biSizeImage != 0)
        return m_pBitmapInfoHeader->biSizeImage;
	else
    {
        DWORD height = (DWORD) GetHeight();
        DWORD width = (DWORD) GetWidth();
        return height * width;
    }
}

UINT CDib::GetNumberOfColors()
{
	int numberOfColors;
	
    if ((m_pBitmapInfoHeader->biClrUsed == 0) &&
		(m_pBitmapInfoHeader->biBitCount < 9))
	{
		switch (m_pBitmapInfoHeader->biBitCount)
		{
		case 1: numberOfColors = 2; break;
		case 4: numberOfColors = 16; break;
		case 8: numberOfColors = 256;
		}
	}
    else
		numberOfColors = (int) m_pBitmapInfoHeader->biClrUsed;
	
    return numberOfColors;
}
    
BYTE* CDib::GetData()
{
    return m_pData;
}

RGBQUAD* CDib::GetRGB()
{
    return m_pRGB;
}

BITMAPINFO* CDib::GetInfo()
{
    return m_pBitmapInfo;
}


BOOL CDib::SaveFile(const CString filename)
{ 
	if (size == NULL)
	{
		AfxMessageBox("图像数据为空");
        return FALSE;
	}
	else
	{
		strcpy(m_fileName,filename);
		CFile dibFile(m_fileName, CFile::modeCreate|CFile::modeWrite);
        dibFile.Write((void*)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
		dibFile.Write((void*)pDib, size);
		dibFile.Close();
		return TRUE;
	}
}
DWORD CDib::GetDibWidthBytes()
{
	byBitCount=m_pBitmapInfoHeader->biBitCount;
	LONG nWidth=m_pBitmapInfoHeader->biWidth;
	dwWidthBytes = (DWORD)m_pBitmapInfoHeader->biWidth;	
	if(byBitCount == 1) dwWidthBytes = (nWidth + 7) / 8;
	else if(byBitCount == 4) dwWidthBytes = (nWidth + 1) / 2;
	else if(byBitCount == 24) dwWidthBytes = 3 * nWidth ;
	while((dwWidthBytes & 3) != 0)dwWidthBytes++;
	return dwWidthBytes;
}

BOOL CDib::MedianFilter(BYTE* imageData, LONG lWidth, LONG lHeight, int iFilterH, int iFilterW, int iFilterMX, int iFilterMY)
{
	unsigned char*	lpSrc;			// 指向源图像的指针	
	unsigned char*	lpDst;			// 指向要复制区域的指针	
	LPSTR			lpNewDIBBits;	// 指向复制图像的指针
	HLOCAL			hNewDIBBits;	
	unsigned char	* aValue;		// 指向滤波器数组的指针
	HLOCAL			hArray;	
	LONG			i,j,k,l;		// 循环变量	
	
	LONG			lLineBytes;		// 图像每行的字节数	
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, imageData, lLineBytes * lHeight);
	
	// 暂时分配内存，以保存滤波器数组
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);
	if (hArray == NULL)
	{
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);
		
		return FALSE;
	}
	
	aValue = (unsigned char * )LocalLock(hArray);
	
	// 开始中值滤波
	// 行(除去边缘几行)
	for(i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		// 列(除去边缘几列)
		for(j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 读取滤波器数组
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)imageData + lLineBytes * (lHeight - 1 
						- i + iFilterMY - k) + j - iFilterMX + l;
					
					// 保存象素值
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}
			
			// 获取中值
			* lpDst = GetMedianNum(aValue, iFilterH * iFilterW);
		}
	}
	
	// 复制变换后的图像
	memcpy(imageData, lpNewDIBBits, lLineBytes * lHeight);
	
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	
	return TRUE;
}

unsigned char CDib::GetMedianNum(unsigned char *bArray, int iFilterLen)
{
	int		i,j;			// 循环变量
	unsigned char bTemp;
	
	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	return bTemp;
}

LPSTR CDib::RotateDIB(BYTE* iamgeData,int width, int height, int iRotateAngle)
{
	LONG	lWidth;				// 源图像的宽度
	LONG	lHeight;			// 源图像的高度	
	LONG	lNewWidth;			// 旋转后图像的宽度
	LONG	lNewHeight;			// 旋转后图像的高度	
	LONG	lLineBytes;			// 图像每行的字节数	
	LONG	lNewLineBytes;		// 旋转后图像的宽度（lNewWidth'，必须是4的倍数）	
	LPSTR	lpSrc;				// 指向源象素的指针	
	HDIB	hDIB;				// 旋转后新DIB句柄	
	LPSTR	lpDst;				// 指向旋转图像对应象素的指针
	LPSTR	lpNewDIB;			// 指向旋转图像的指针
	LPSTR	lpNewDIBBits;	
		
	LONG	i;					// 循环变量（象素在新DIB中的坐标）
	LONG	j;	
	LONG	i0;					// 象素在源DIB中的坐标
	LONG	j0;	
	
	float	fRotateAngle;		// 旋转角度（弧度）	
	float	fSina, fCosa;		// 旋转角度的正弦和余弦	
	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;	
	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	float	f1,f2;
	lWidth = width;			// 获取图像的"宽度"（4的倍数）	
	lLineBytes = WIDTHBYTES(lWidth * 8);// 计算图像每行的字节数	
	lHeight = height;			// 获取图像的高度
	
	// 将旋转角度从度转换到弧度
	fRotateAngle = (float) RADIAN(iRotateAngle);	
	fSina = (float) sin((double)fRotateAngle);	// 计算旋转角度的正弦
	fCosa = (float) cos((double)fRotateAngle);	// 计算旋转角度的余弦
	
	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float) (- (lWidth  - 1) / 2);
	fSrcY1 = (float) (  (lHeight - 1) / 2);
	fSrcX2 = (float) (  (lWidth  - 1) / 2);
	fSrcY2 = (float) (  (lHeight - 1) / 2);
	fSrcX3 = (float) (- (lWidth  - 1) / 2);
	fSrcY3 = (float) (- (lHeight - 1) / 2);
	fSrcX4 = (float) (  (lWidth  - 1) / 2);
	fSrcY4 = (float) (- (lHeight - 1) / 2);
	
	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
	
	// 计算旋转后的图像实际宽度
	lNewWidth  = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);
	
	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);
	
	// 计算旋转后的图像高度
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);
	
	// 两个常数，这样不用以后每次都计算了
	f1 = (float) (-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth  - 1));
	f2 = (float) ( 0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));
	// 分配内存，以保存新DIB
	hDIB = (HDIB) ::LocalAlloc(GHND, lNewLineBytes * lNewHeight);

	if (hDIB == NULL)
	{
		return NULL;
	}
	
	lpNewDIB =  (char * )::LocalLock((HGLOBAL) hDIB);
	
	
	// 找到新DIB象素起始位置
	lpNewDIBBits = lpNewDIB;
	for(i = 0; i < lNewHeight; i++)		// 针对图像每行进行操作
	{		
		for(j = 0; j < lNewWidth; j++)	// 针对图像每列进行操作
		{
			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;
			
			// 计算该象素在源DIB中的坐标
			i0 = (LONG) (-((float) j) * fSina + ((float) i) * fCosa + f2 + 0.5);
			j0 = (LONG) ( ((float) j) * fCosa + ((float) i) * fSina + f1 + 0.5);
			
			// 判断是否在源图范围内
			if( (j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char *)iamgeData + lLineBytes * (lHeight - 1 - i0) + j0;
				
				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				* ((unsigned char*)lpDst) = 255;
			}			
		}		
	}
	memcpy(iamgeData,lpNewDIBBits,lNewHeight*lNewWidth);
	LocalUnlock(lpNewDIB);
	LocalFree(lpNewDIB);
	return lpDst;
}

void CDib::CutApart(BYTE *imageData, int width, int height,queue<LaterImageInfo*>& LaterQueue)
{
	BYTE* ImageData;
	int Lwidth;
	int Lheight;
	int upScan = 0;
	int downScan = 0;
	int leftScan = 0;
	int rightScan = 0;
	int up = 0;
	int down = 0;
	int left = width;
	int right = 0;
	int newWidth = 0;
	int newHeight = 0;
	ImageData = imageData;
	Lwidth = width;
	Lheight = height;
	int HinByte = WIDTHBYTES(Lheight*8);
    int Linbyte = WIDTHBYTES(Lwidth*8);
	for (int k = 0; k < Lwidth; k++)
	{
		for (int m =0; m <= Lheight/2; m ++)
		{
			upScan = *ImageData+k*HinByte + m;
			if (upScan < 255)
			{
				if (m > up)
				{
					up = m;
				}
			}
            downScan = *ImageData+k*HinByte + Lheight - m -1;
			if (downScan < 255)
			{
				if ((Lheight - m -1) > down)
				{
					down = Lheight - m -1;
				}
			}
		}
	}
	
	// 暂时分配内存，以保存新图
    newWidth = Lwidth;
	newHeight = abs(down - up);
	BYTE* newImageData = new BYTE[newWidth*newHeight*sizeof(BYTE)];
	memcpy(newImageData,ImageData,newWidth*newHeight*sizeof(BYTE));
	delete [] ImageData;//计算完以后将原始图像数据删除
	LaterImageInfo* pLater = new LaterImageInfo;
	pLater->laterimageData = newImageData;
	pLater->m_lHeight = newHeight;
	pLater->m_lWidth = newWidth;
	LaterQueue.push(pLater);
}
