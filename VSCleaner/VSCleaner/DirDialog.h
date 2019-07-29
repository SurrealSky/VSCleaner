//////////////////////////////////////////////////////////////////////////
//
// File Name   : DirDialog.h 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : Header file
//
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRDIALOG_H__D83EF66D_CD47_4121_A636_7FD9BCE5BD03__INCLUDED_)
#define AFX_DIRDIALOG_H__D83EF66D_CD47_4121_A636_7FD9BCE5BD03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirDialog dialog

class CDirDialog : public CDialog
{
// Construction
public:
	CDirDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirDialog)
	enum { IDD = IDD_PROPPAGE_DIRECTORY };
	CDirTreeCtrl m_wndDir;
	//}}AFX_DATA
    
    // 获取扫描的目录,并返回被扫描的目录文件数目
    INT GetScanPath();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirDialog)
		// NOTE: the ClassWizard will add member functions here
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();

    afx_msg void OnSize( UINT nType, int cx, int cy );
    afx_msg void OnBtnScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    BOOL InitTreeWnd();
    VOID TravelTreeChildItem( HTREEITEM htItem );

// Members
    CResizeCtrl m_riseCtrl;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRDIALOG_H__D83EF66D_CD47_4121_A636_7FD9BCE5BD03__INCLUDED_)
