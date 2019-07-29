//////////////////////////////////////////////////////////////////////////
//
// File Name   : DirDialog.cpp
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
#include "DirDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CVSCleanerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDirDialog dialog


CDirDialog::CDirDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDirDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDirDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirDialog)
	DDX_Control( pDX, IDC_DIR_TREE, m_wndDir );
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CDirDialog, CDialog )
	//{{AFX_MSG_MAP(CDirDialog)
		// NOTE: the ClassWizard will add message map macros here
    ON_WM_SIZE()

    ON_BN_CLICKED( IDC_DIR_BTN_SCAN, OnBtnScan )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirDialog message handlers

BOOL CDirDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_riseCtrl.Create( this );

    m_riseCtrl.Add( IDC_DIR_TREE,     0, 0, 1, 1 );     // 左上角不变
    m_riseCtrl.Add( IDC_DIR_BTN_SCAN, 1, 1, 1, 1 );     // 位置平移

    InitTreeWnd();

    return TRUE;
}

void CDirDialog::OnOK()
{

}

void CDirDialog::OnCancel()
{

}

void CDirDialog::OnSize( UINT nType, int cx, int cy )
{
    CDialog::OnSize( nType, cx, cy );
    
    m_riseCtrl.Size();
}

void CDirDialog::OnBtnScan()
{
    // 注意，这儿不可以使用 PostMessage
    // 如果打算使用 PostMessage
    // 则需要使用临界区保护 CFileManager::m_strList 的搜索目录存储时保存
    AfxGetMainWnd()->SendMessage( VS_WM_SCANRESULT );
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

BOOL CDirDialog::InitTreeWnd()
{
	DWORD dwStyle = m_wndDir.GetExStyle();

    dwStyle |= TVS_LINESATROOT | TVS_HASBUTTONS | TVS_HASLINES;
    
    m_wndDir.ModifyStyleEx( 0, dwStyle );
    m_wndDir.DisplayTree( NULL, FALSE );

    return TRUE;
}

VOID CDirDialog::TravelTreeChildItem( HTREEITEM htItem )
{
    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );

	HTREEITEM htItemChild = m_wndDir.GetChildItem( htItem );
    CString strPath;

    while ( htItemChild ) {
        // 如果当前目录被选择，则它的子目录无须再扫描保存
        if ( m_wndDir.GetCheck( htItemChild ) ) {
            strPath = m_wndDir.GetFullPath( htItemChild );
            pFileManager->AddScanDir( strPath );

            htItemChild = m_wndDir.GetNextSiblingItem( htItemChild );
            continue;
        }

        // 当前目录没有被选择，则扫描它的子目录
        TravelTreeChildItem( htItemChild );
        htItemChild = m_wndDir.GetNextSiblingItem( htItemChild );
    }
}

INT CDirDialog::GetScanPath()
{
    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );

    // 清理上次记录的搜索目录
    pFileManager->ResetScanDir();

    HTREEITEM hRoot = m_wndDir.GetRootItem();
    CString strPath;
    
    while ( hRoot ) {
        // 如果当前目录被选择，则它的子目录无须再扫描保存
        if ( m_wndDir.GetCheck( hRoot ) ) {
            strPath = m_wndDir.GetItemText( hRoot );
            pFileManager->AddScanDir( strPath );

            hRoot = m_wndDir.GetNextSiblingItem( hRoot );
            continue;
        }

        // 当前目录没有被选择，则扫描它的子目录
        TravelTreeChildItem( hRoot );
        hRoot = m_wndDir.GetNextSiblingItem( hRoot );
    }

    return pFileManager->GetDirCount();
}