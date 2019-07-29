// AddFileTypeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VSCleaner.h"
#include "AddFileTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddFileTypeDialog dialog


CAddFileTypeDialog::CAddFileTypeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFileTypeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddFileTypeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddFileTypeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddFileTypeDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddFileTypeDialog, CDialog)
	//{{AFX_MSG_MAP(CAddFileTypeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddFileTypeDialog message handlers

BOOL CAddFileTypeDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;
}

void CAddFileTypeDialog::OnOK()
{
    GetDlgItem( IDC_ADDFILETYPE_EDT_FILE   )->GetWindowText( m_strKey   );
    GetDlgItem( IDC_ADDFILETYPE_EDT_REMARK )->GetWindowText( m_strValue );

    m_strKey.TrimLeft();
    m_strValue.TrimLeft();

    if ( m_strKey.IsEmpty() || m_strValue.IsEmpty() ) {
        AfxMessageBox( _T( "类型或描述不可以为空" ), MB_ICONINFORMATION );
        return;
    }

    CDialog::OnOK();
}

void CAddFileTypeDialog::OnCancel()
{

    CDialog::OnCancel();
}