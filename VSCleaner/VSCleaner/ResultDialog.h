#if !defined(AFX_RESULTDIALOG_H__0719377D_48F1_450E_8E54_43A2D9168481__INCLUDED_)
#define AFX_RESULTDIALOG_H__0719377D_48F1_450E_8E54_43A2D9168481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultDialog dialog

class CResultDialog : public CDialog,
                      public HookFileManager
{
// Construction
public:
	CResultDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResultDialog)
	enum { IDD = IDD_RESULT_DIALOG };
	CStatic	m_wndInfo;
	CListCtrl m_wndList;
	//}}AFX_DATA

    virtual VOID OnFindFile( CString strFilePath, CString strSize );
    virtual VOID OnFindFileResult( LONG count, DOUBLE total );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResultDialog)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnSize( UINT nType, int cx, int cy );

	afx_msg void OnBtnAll();
	afx_msg void OnBtnNone();
	afx_msg void OnBtnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    BOOL InitListCtrl();

    CResizeCtrl m_resizeCtrl;

public:
	afx_msg void OnBnClickedResultBtnAll2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTDIALOG_H__0719377D_48F1_450E_8E54_43A2D9168481__INCLUDED_)
