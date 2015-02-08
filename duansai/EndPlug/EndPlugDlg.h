// EndPlugDlg.h : header file
//

#if !defined(AFX_ENDPLUGDLG_H__B1CFF636_4E94_43A5_975A_9FE836378C8B__INCLUDED_)
#define AFX_ENDPLUGDLG_H__B1CFF636_4E94_43A5_975A_9FE836378C8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TestBtn.h"
#include "ViewEndPlug.h"
#include "ManiGroupBox.h"
#include "CameraGroupBox.h"
#include "Cdib.h"
#include "ManiPular1.h"
#include "ManiPular2.h"
#include "Camera1.h"
#include "Camera2.h"
#include "Camera3.h"
#include "TestDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CEndPlugDlg dialog

class CEndPlugDlg : public CDialog
{
// Construction
public:
	CEndPlugDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEndPlugDlg)
	enum { IDD = IDD_ENDPLUG_DIALOG };
	CListCtrl	m_camerapara;
	CListCtrl	m_manipularpara;
	CListCtrl	m_listmanipular;
	CListCtrl	m_listrail;
	CListCtrl	m_motorpara;
	CScrollBar	m_vBar;
	CScrollBar	m_hBar;
	CCamera3	m_camera3;
	CCamera2	m_camera2;
	CCamera1	m_camera1;
	ManiPular2	m_manipular2;
	ManiPular1	m_manipular1;
	CameraGroupBox	m_CameraState;
	ManiGroupBox	m_ManiGroupBox;
	ViewEndPlug	m_viewwindow;
	CTestBtn	m_Start;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEndPlugDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	void ChangeSize(CWnd * pWnd, int cx, int cy,int movenumber);
    void SetControlInfo(WORD CtrlId);
	void SavePhoto();
public:
	void initAlllistControl();
	 CString filename;
	 CDib m_Dib;
	 CRect m_rcPicture;//仅获取绘图区的大小
	 CRect temp_rcPicture;
	 CTestDlg    *pTestDlg;
protected:
	CRect m_rect;
	CDWordArray m_control_info;
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CEndPlugDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStart();
	afx_msg void OnExit();
	afx_msg void OnOpenphoto();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSavephoto();
	afx_msg void OnQualified();
	afx_msg void Onunqualified();
	afx_msg void OnAveragefiltering();
	afx_msg void OnButtonTest();
	afx_msg void OnClose();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDPLUGDLG_H__B1CFF636_4E94_43A5_975A_9FE836378C8B__INCLUDED_)
