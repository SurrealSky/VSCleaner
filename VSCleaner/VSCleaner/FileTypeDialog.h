//////////////////////////////////////////////////////////////////////////
//
// File Name   : FileTypeDialog.h 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : Header file
//
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_FILETYPEDIALOG_H__BF382FD3_38A4_4E08_B92F_295450C8221C__INCLUDED_)
#define AFX_FILETYPEDIALOG_H__BF382FD3_38A4_4E08_B92F_295450C8221C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTypeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileTypeDialog dialog

class CFileTypeDialog : public CDialog,
                        public HookFileManager
{
// Construction
public:
	CFileTypeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileTypeDialog)
	enum { IDD = IDD_PROPPAGE_FILETYPE };
	CListCtrl m_wndList;
	//}}AFX_DATA

    virtual VOID OnReadFileItem( CString strType, CString strRemark, CString strState );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTypeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileTypeDialog)
		// NOTE: the ClassWizard will add member functions here
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();

    afx_msg void OnSize( UINT nType, int cx, int cy );

    afx_msg void OnBtnAddFileType();
	afx_msg void OnBtnDelFileType();

	afx_msg void OnClickFileTypeItem( NMHDR* pNMHDR, LRESULT* pResult );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    BOOL InitListCtrol();
    BOOL ReadFileTypes();

    // Members
    CResizeCtrl m_riseCtrl;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETYPEDIALOG_H__BF382FD3_38A4_4E08_B92F_295450C8221C__INCLUDED_)
