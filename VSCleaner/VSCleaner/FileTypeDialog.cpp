//////////////////////////////////////////////////////////////////////////
//
// File Name   : FileTypeDialog.cpp
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : implementation file
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSCleaner.h"
#include "FileTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CVSCleanerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFileTypeDialog dialog


CFileTypeDialog::CFileTypeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTypeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileTypeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFileTypeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTypeDialog)
	DDX_Control( pDX, IDC_FILETYPE_LIST, m_wndList );
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileTypeDialog, CDialog)
	//{{AFX_MSG_MAP(CFileTypeDialog)
		// NOTE: the ClassWizard will add message map macros here
    ON_WM_SIZE()

    ON_BN_CLICKED( IDC_FILETYPE_BTN_ADD, OnBtnAddFileType )
	ON_BN_CLICKED( IDC_FILETYPE_BTN_DEL, OnBtnDelFileType )

	ON_NOTIFY( NM_CLICK, IDC_FILETYPE_LIST, OnClickFileTypeItem )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTypeDialog message handlers

BOOL CFileTypeDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_riseCtrl.Create( this );

    m_riseCtrl.Add( IDC_FILETYPE_LIST,    0, 0, 1, 1 );
    m_riseCtrl.Add( IDC_FILETYPE_BTN_ADD, 1, 1, 1, 1 );
    m_riseCtrl.Add( IDC_FILETYPE_BTN_DEL, 1, 1, 1, 1 );

    InitListCtrol();
    ReadFileTypes();

    return TRUE;
}

void CFileTypeDialog::OnOK()
{

}

void CFileTypeDialog::OnCancel()
{

}

void CFileTypeDialog::OnSize( UINT nType, int cx, int cy )
{
    CDialog::OnSize( nType, cx, cy );

    m_riseCtrl.Size();
}

void CFileTypeDialog::OnBtnAddFileType()
{
    CAddFileTypeDialog dlg;
    
    if ( dlg.DoModal() != IDOK )
		return;

    CString strKey   = dlg.m_strKey;
    CString strValue = dlg.m_strValue;

    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );
    
    if ( pFileManager->IsFileTypeExist( strKey ) ) {
        AfxMessageBox( _T( "文件类型已经存在 !" ), MB_ICONSTOP );
        return;
    }

    if ( pFileManager->AddFileType( strKey, strValue, this ) ) {
        AfxMessageBox( _T( "加入新扫描文件类型\n" ) + strKey + "\n" + strValue, MB_ICONINFORMATION );
    }
    else {
        AfxMessageBox( _T( "加入新扫描文件类型失败 !" ), MB_ICONERROR );
    }
}

void CFileTypeDialog::OnBtnDelFileType()
{
    POSITION pos = m_wndList.GetFirstSelectedItemPosition();
    
    if ( pos != NULL ) {
        int nItem = m_wndList.GetNextSelectedItem( pos );
        
        CString strKey    = m_wndList.GetItemText( nItem, 0 );
        CString strRemark = m_wndList.GetItemText( nItem, 1 );
        
        CString strWarn = _T( "确定删除\n" ) + strKey + "\n" + strRemark;

        INT nRet = AfxMessageBox( strWarn, MB_ICONINFORMATION | MB_YESNO );
        if ( nRet == IDNO )
            return;

        CFileManager* pFileManager = theApp.GetFileManager();
        ASSERT( pFileManager );
        if ( ! pFileManager->RemoveFileType( strKey ) )
            return;
        
        m_wndList.DeleteItem( nItem );
	} 
    else {
        AfxMessageBox( _T( "请选择要删除的文件类型" ), MB_ICONINFORMATION );
    }
}

void CFileTypeDialog::OnClickFileTypeItem( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if (pNMListView)
    {
        CString strKey = m_wndList.GetItemText(pNMListView->iItem, 0);
        BOOL bCheck = m_wndList.GetCheck(pNMListView->iItem);

        if (bCheck)
            bCheck = FALSE;
        else
            bCheck = TRUE;

        m_wndList.SetCheck(pNMListView->iItem, bCheck);

        CFileManager* pFileManager = theApp.GetFileManager();
        ASSERT(pFileManager);
        pFileManager->SetFileTypeCheck(strKey, bCheck);
    }

    /*POSITION pos =  NULL;
    pos = m_wndList.GetFirstSelectedItemPosition();
    
    if ( pos != NULL ) {
        int nItem = m_wndList.GetNextSelectedItem( pos );
        
        CString strKey = m_wndList.GetItemText( nItem, 0 );
        BOOL bCheck = m_wndList.GetCheck( nItem );
        
        if ( bCheck )
            bCheck = FALSE;
        else
            bCheck = TRUE;
        
        m_wndList.SetCheck( nItem, bCheck );
        
        CFileManager* pFileManager = theApp.GetFileManager();
        ASSERT( pFileManager );
        pFileManager->SetFileTypeCheck( strKey, bCheck );
	}*/

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

BOOL CFileTypeDialog::InitListCtrol()
{
    DWORD dwExStyle = m_wndList.GetExtendedStyle();
    
    dwExStyle |= LVS_EX_CHECKBOXES;
    dwExStyle |= LVS_EX_FLATSB;
    dwExStyle |= LVS_EX_FULLROWSELECT;
	dwExStyle |= LVS_EX_GRIDLINES;

    m_wndList.SetExtendedStyle( dwExStyle );
    
    CRect rectClient;
    GetClientRect( & rectClient );
    
    m_wndList.InsertColumn( 0, _T( "类型" ), LVCFMT_LEFT, rectClient.Width() / 6 );
	m_wndList.InsertColumn( 1, _T( "类型说明" ), LVCFMT_LEFT, rectClient.Width() * 2 );

    return TRUE;
}

BOOL CFileTypeDialog::ReadFileTypes()
{
    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );

    pFileManager->ReadFileItem( this );

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
// OnReadFileItem
//  - 读入配置文件信息项
//  - strType   目标类型
//  - strRemark 类型描述信息
//  - strState  选择状态
//
//////////////////////////////////////////////////////////////////////////

VOID CFileTypeDialog::OnReadFileItem( CString strType, CString strRemark, CString strState )
{
	int nIndex = m_wndList.GetItemCount();

    nIndex = m_wndList.InsertItem( m_wndList.GetItemCount(), strType );
    m_wndList.SetItemText( nIndex, 1, strRemark );
    m_wndList.SetCheck( nIndex, ( strState == _T( "TRUE" ) ? TRUE : FALSE ) );
}

