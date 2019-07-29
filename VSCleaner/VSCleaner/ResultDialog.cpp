// ResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VSCleaner.h"
#include "ResultDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CVSCleanerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CResultDialog dialog


CResultDialog::CResultDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CResultDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDialog)
	DDX_Control(pDX, IDC_RESULT_STATIC_INFO, m_wndInfo);
	DDX_Control(pDX, IDC_RESULT_LIST, m_wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultDialog, CDialog)
	//{{AFX_MSG_MAP(CResultDialog)
    ON_WM_SIZE()
	ON_BN_CLICKED( IDC_RESULT_BTN_ALL,  OnBtnAll  )
	ON_BN_CLICKED( IDC_RESULT_BTN_NONE, OnBtnNone )
	ON_BN_CLICKED( IDC_RESULT_BTN_DEL,  OnBtnDel  )
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RESULT_BTN_ALL2, &CResultDialog::OnBnClickedResultBtnAll2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultDialog message handlers

BOOL CResultDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_resizeCtrl.Create( this );
    
    m_resizeCtrl.Add( IDC_RESULT_LIST,        0, 0, 1, 1 );
	m_resizeCtrl.Add(IDC_RESULT_BTN_ALL2,	  0, 1, 0, 1 );
    m_resizeCtrl.Add( IDC_RESULT_BTN_ALL,     0, 1, 0, 1 );
    m_resizeCtrl.Add( IDC_RESULT_BTN_NONE,    0, 1, 0, 1 );
    m_resizeCtrl.Add( IDC_RESULT_BTN_DEL,     0, 1, 0, 1 );
    m_resizeCtrl.Add( IDC_RESULT_STATIC_INFO, 0, 1, 1, 1 );

	InitListCtrl();

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	MoveWindow(rcWnd, TRUE);
	CFileManager* pFileManager = theApp.GetFileManager();
	char path[MAX_PATH] = {0};
	::GetCurrentDirectoryA(MAX_PATH, path);
	pFileManager->AddScanDir(path);
	ASSERT(pFileManager);
	pFileManager->StartReportFilesDetail(this);

    return TRUE;
}

void CResultDialog::OnOK()
{

}

void CResultDialog::OnCancel()
{
    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );
    if ( pFileManager->IsScanning() ) {
        AfxMessageBox( _T( "正在扫描，请稍候 ......\n" ), MB_ICONINFORMATION );
        return;
    }
    else {
        m_wndList.DeleteAllItems();
    }

    CDialog::OnCancel();
}

void CResultDialog::OnSize( UINT nType, int cx, int cy )
{
    CDialog::OnSize( nType, cx, cy );

    m_resizeCtrl.Size();
}

//////////////////////////////////////////////////////////////////////////
//

BOOL CResultDialog::InitListCtrl()
{
    DWORD dwExStyle = m_wndList.GetExtendedStyle();
    
    dwExStyle |= LVS_EX_CHECKBOXES;
    dwExStyle |= LVS_EX_FLATSB;
    dwExStyle |= LVS_EX_FULLROWSELECT;
    dwExStyle |= LVS_EX_GRIDLINES;
    
    m_wndList.SetExtendedStyle( dwExStyle );

    CRect rcMainWnd;
    AfxGetMainWnd()->GetWindowRect( & rcMainWnd );

	m_wndList.DeleteAllItems();
	while (m_wndList.DeleteColumn(0));
    
    m_wndList.InsertColumn( 0, _T( "文件名称" ), LVCFMT_LEFT, rcMainWnd.Width() / 4 * 3 );
    m_wndList.InsertColumn( 1, _T( "文件大小" ), LVCFMT_LEFT, rcMainWnd.Width() / 4     );
	

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

VOID CResultDialog::OnFindFile( CString strFilePath, CString strSize )
{
    TRACE0( strFilePath + "\n" );
    int nIndex = m_wndList.InsertItem( m_wndList.GetItemCount(), strFilePath );
    m_wndList.SetItemText( nIndex, 1, strSize );
	m_wndList.SetCheck(nIndex, TRUE);

    m_wndInfo.SetWindowText( strFilePath );
}


VOID CResultDialog::OnFindFileResult( LONG count, DOUBLE total )
{
	CString strText;
    strText.Format( _T( "搜索文件 %d 大小 %.2f MB" ), count, total / 1024 );

    m_wndInfo.SetWindowText( strText );
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void CResultDialog::OnBtnAll() 
{
	// TODO: Add your control notification handler code here
    int nCount = m_wndList.GetItemCount();
    for ( int nIndex = 0; nIndex < nCount; nIndex++ )
		m_wndList.SetCheck( nIndex, TRUE );
}

void CResultDialog::OnBtnNone() 
{
	// TODO: Add your control notification handler code here
    int nCount = m_wndList.GetItemCount();
    for ( int nIndex = 0; nIndex < nCount; nIndex++ )
		m_wndList.SetCheck( nIndex, FALSE );
}

void CResultDialog::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );
    if ( pFileManager->IsScanning() ) {
        AfxMessageBox( _T( "正在扫描，请稍候 ......\n" ), MB_ICONINFORMATION );
        return;
    }

    CString strPath;
    
    BOOL bDone = TRUE;
    
    int nItemCount = m_wndList.GetItemCount();
    for ( int nIndex = 0; nIndex < nItemCount; nIndex++ ) {
        if ( m_wndList.GetCheck( nIndex ) ) {
            strPath = m_wndList.GetItemText( nIndex, 0 );
            
            // 文件已成功删除
            if ( DeleteFile( strPath ) ) {
                m_wndList.DeleteItem( nIndex );
                
                nItemCount--;
                nIndex--;
            }
            else {
                bDone = FALSE;
            }
        } // Delete the file was selected...
    } // End loop...
    
    if ( ! bDone )
		AfxMessageBox( _T( "某些文件正在使用.不能清理 " ), MB_ICONINFORMATION );
	else
		AfxMessageBox(_T("删除成功!"), MB_ICONINFORMATION);
}

//重新加载
void CResultDialog::OnBnClickedResultBtnAll2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileManager* pFileManager = theApp.GetFileManager();
	char path[MAX_PATH] = { 0 };
	::GetCurrentDirectoryA(MAX_PATH, path);
	pFileManager->ResetScanDir();
	pFileManager->AddScanDir(path);
	ASSERT(pFileManager);
	pFileManager->StartReportFilesDetail(this);

	InitListCtrl();
}
