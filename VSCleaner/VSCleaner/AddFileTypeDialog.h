#if !defined(AFX_ADDFILETYPEDIALOG_H__EDE90B31_6A38_455D_BB68_E19B28A91583__INCLUDED_)
#define AFX_ADDFILETYPEDIALOG_H__EDE90B31_6A38_455D_BB68_E19B28A91583__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddFileTypeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddFileTypeDialog dialog

class CAddFileTypeDialog : public CDialog
{
// Construction
public:
	CAddFileTypeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddFileTypeDialog)
	enum { IDD = IDD_ADDFILETYPE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

    CString m_strKey;
    CString m_strValue;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddFileTypeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddFileTypeDialog)
		// NOTE: the ClassWizard will add member functions here
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFILETYPEDIALOG_H__EDE90B31_6A38_455D_BB68_E19B28A91583__INCLUDED_)
