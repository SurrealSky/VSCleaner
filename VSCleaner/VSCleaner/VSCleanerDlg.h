//////////////////////////////////////////////////////////////////////////
//
// File Name   : VSCleanerDlg.h 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : Header file
//
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSCLEANERDLG_H__ACCD1864_DB39_45C4_8750_8A2CD2267DF3__INCLUDED_)
#define AFX_VSCLEANERDLG_H__ACCD1864_DB39_45C4_8750_8A2CD2267DF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerDlg dialog

class CVSCleanerDlg : public CDialog
{
// Construction
public:
	CVSCleanerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVSCleanerDlg)
	enum { IDD = IDD_VSCLEANER_DIALOG };
	CTabCtrl m_wndTab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSCleanerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVSCleanerDlg)
	virtual BOOL OnInitDialog();
    virtual void OnOK();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDestroy();

	afx_msg void OnClickTabItems( NMHDR* pNMHDR, LRESULT* pResult );

    afx_msg LRESULT OnBtnScanResult( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnThreadExit( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    BOOL InitTabWnd();
    BOOL CreateTabChildWindows();
    BOOL DestroyTabChildWindows();

    // Attributes
    CRect m_rcTabWnd;   // 记录 Tab 窗口的大小

    //CDirDialog*      m_pDirDialog;          // 搜索目录窗口
    CFileTypeDialog* m_pFileTypeDialog;     // 搜索文件类型窗口
    CResultDialog*   m_pResultDialog;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSCLEANERDLG_H__ACCD1864_DB39_45C4_8750_8A2CD2267DF3__INCLUDED_)
