//////////////////////////////////////////////////////////////////////////
//
// File Name   : DirTreeCtrl.cpp
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
#include "DirTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl

CDirTreeCtrl::CDirTreeCtrl()
{
    m_bFiles = FALSE;
}

CDirTreeCtrl::~CDirTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CDirTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CDirTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_NOTIFY_REFLECT( TVN_ITEMEXPANDED, OnItemexpanded )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl message handlers


//////////////////////////////////////////////////////////////////////////
// 实现
//////////////////////////////////////////////////////////////////////////

BOOL CDirTreeCtrl::DisplayTree( LPCTSTR strRoot, BOOL bFiles /* = FALSE */ )
{
    DWORD dwStyle = GetStyle();
    if ( dwStyle & TVS_EDITLABELS ) {
        // 禁止用户编辑树形控件子项
        ModifyStyle( TVS_EDITLABELS , 0 );
	}

    DeleteAllItems();

    if ( ! GetSystemImageList() )
        return FALSE;

    // TRUE. Show directory and files...
	m_bFiles = bFiles;

    if ( strRoot == NULL || strRoot[ 0 ] == _T( '\\0' ) ) {
        if ( ! DisplayDrives() )
            return FALSE;
        
        m_strRoot = _T( "" );
    }
    else {
        m_strRoot = strRoot;
        if ( m_strRoot.Right( 1 ) != _T( '\\' ) )
            m_strRoot += _T( '\\' );
        
        HTREEITEM hParent = AddItem( TVI_ROOT, m_strRoot );
        DisplayPath( hParent, m_strRoot );
	}

    return TRUE;
}

// 获取系统盘，目录图标列表
BOOL CDirTreeCtrl::GetSystemImageList()
{
    SHFILEINFO shFileInfo;

    HIMAGELIST hImageList = NULL;

    if ( GetImageList( TVSIL_NORMAL ) )
        m_imgList.Detach();

    hImageList = ( HIMAGELIST ) SHGetFileInfo( _T( "C:\\" ), 0, & shFileInfo, sizeof( SHFILEINFO ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
    if ( hImageList == NULL ) {
        TRACE0( "Can't get the the handle of the System image list...\n" );
        return FALSE;
	}

    m_imgList.m_hImageList = hImageList;
    
	SetImageList( & m_imgList, TVSIL_NORMAL );

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

BOOL CDirTreeCtrl::DisplayDrives()
{
    //
    // Displaying the Available Drives on this PC
    // This are the First Items in the TreeCtrl
    //
    DeleteAllItems();
    
    TCHAR szDrives[ MAX_PATH ] = { '\0' };
    LPCH  pDrive               = NULL;
    
    if ( ! GetLogicalDriveStrings( sizeof( szDrives ), szDrives ) ) {
        TRACE0( "Failed Getting Logical Settting !\n" );
        return FALSE;
    }
    
    pDrive = szDrives;
    while ( *pDrive ) {
        HTREEITEM hParent = AddItem( TVI_ROOT, pDrive );
        if ( FindSubDir( pDrive ) )
            InsertItem( "", 0, 0, hParent );
        
        pDrive += strlen( pDrive ) + 1;
    }
    
    return TRUE;
}

VOID CDirTreeCtrl::DisplayPath( HTREEITEM hParent, LPCTSTR szPath )
{
    //
    // Displaying the Path in the TreeCtrl
    //
    
    CFileFind fileFind;
    
    BOOL    bFind        = FALSE;
    CString strPathFiles = szPath;
    
    CSortStringArray strDirArray;
    CSortStringArray strFileArray;
    
    if ( strPathFiles.Right( 1 ) != '\\' )
        strPathFiles += '\\';
    strPathFiles += _T( "\\*.*" );
    
    bFind = fileFind.FindFile( strPathFiles );
    
    while ( bFind ) {
        bFind = fileFind.FindNextFile();
        if ( fileFind.IsDirectory() && ! fileFind.IsDots() ) {
            strDirArray.Add( fileFind.GetFilePath() );
        }
        else if ( ! fileFind.IsDirectory() && m_bFiles ) {
            strFileArray.Add( fileFind.GetFilePath() );
        }
    } // End
    
    strDirArray.Sort();
    SetRedraw( FALSE );
    CWaitCursor waitCursor;
    
    for ( int i = 0; i < strDirArray.GetSize(); i++ ) {
        HTREEITEM hItem = AddItem( hParent, strDirArray.GetAt( i ) );
        if ( FindSubDir( strDirArray.GetAt( i ) ) )
            InsertItem( "", 0, 0, hItem );
    }
    
    if ( m_bFiles ) {
        strFileArray.Sort();
        for (int i = 0; i < strFileArray.GetSize(); i++ )
            AddItem( hParent, strFileArray.GetAt( i ) );
    }
    
    SetRedraw( TRUE );
}

LPCTSTR CDirTreeCtrl::GetSubPath( LPCTSTR szPath )
{
    static CString strPath;
    
    int nPos = 0;
    
    strPath = szPath;
    if ( strPath.Right( 1 ) == '\\' )
        strPath.SetAt( strPath.GetLength() - 1, '\0' );
    
    nPos = strPath.ReverseFind( '\\' );
    if ( nPos != -1 )
        strPath = strPath.Mid( nPos + 1 );
    
    return ( LPCTSTR ) strPath;
}

BOOL CDirTreeCtrl::FindSubDir( LPCTSTR szPath )
{
    // 判断是否还有子目录
    CFileFind fileFind;
    
    CString strPath = szPath;
    BOOL    bFind   = FALSE;
    
    if ( strPath.Right( 1 ) == _T( '\\' ) )
        strPath += _T( "*.*" );
    else
        strPath += _T( "\\*.*" );
    
    bFind = fileFind.FindFile( strPath );
    
    while ( bFind ) {
        bFind = fileFind.FindNextFile();
        if ( fileFind.IsDirectory() && ! fileFind.IsDots() )
            return TRUE;
        
        if ( ! fileFind.IsDirectory() && m_bFiles && ! fileFind.IsHidden() )
            return TRUE;
    }
    
    return FALSE;
}

CString CDirTreeCtrl::GetFullPath( HTREEITEM hItem )
{
    ASSERT( hItem );
    if ( hItem == NULL )
        return _T( "" );
    
    HTREEITEM hParent = hItem;
    
    CString strFullPath;
    CString strTmp;
    
    while ( hParent )
    {
        strTmp       =  GetItemText( hParent );
        strTmp      += _T( "\\" );
        strFullPath  = strTmp + strFullPath;
        hParent      = GetParentItem( hParent );
    }
    
    strFullPath.TrimRight( '\\' );
    
    return strFullPath;
}

HTREEITEM CDirTreeCtrl::AddItem( HTREEITEM hParent, LPCTSTR szPath )
{
    // Adding the Item to the TreeCtrl with the current Icons
    SHFILEINFO shFileInfo;
    
    int nIcon    = 0;
    int nIconSel = 0;
    
    CString strPath = szPath;
    if ( strPath.Right( 1 ) != '\\'  )
        strPath += '\\';
    
    if ( ! SHGetFileInfo( strPath, 0, & shFileInfo, sizeof( SHFILEINFO ), SHGFI_ICON | SHGFI_SMALLICON ) )
    {
        TRACE0( "Failed Getting File Icon Info !\n" );
        return NULL;
    }
    
    nIcon = shFileInfo.iIcon;
    
    // we only need the index from the system image list
    DestroyIcon( shFileInfo.hIcon );
    
    if ( ! SHGetFileInfo( strPath, 0, & shFileInfo, sizeof( SHFILEINFO ), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_OPENICON ) ) {
        TRACE0( "Failed Getting File Icon Info !\n" );
        return NULL;
    }
    
    nIconSel = shFileInfo.iIcon;
    
    // we only need the index from the system image list
    DestroyIcon( shFileInfo.hIcon );
    
    if ( hParent == TVI_ROOT )
        return InsertItem( strPath, nIcon, nIconSel, hParent );
    
    return InsertItem( GetSubPath( strPath ), nIcon, nIconSel, hParent );
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void CDirTreeCtrl::OnItemexpanded( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_TREEVIEW* pNMTreeView = ( NM_TREEVIEW* ) pNMHDR;
    
    if ( pNMTreeView->itemNew.state & TVIS_EXPANDED )
    {
        ExpandItem( pNMTreeView->itemNew.hItem, TVE_EXPAND );
    }
    else
    {
        //
        // Delete the Items, but leave one there, for 
        // expanding the item next time
        //
        HTREEITEM hChild = GetChildItem( pNMTreeView->itemNew.hItem );
        while ( hChild )
        {
            DeleteItem( hChild );
            hChild = GetChildItem( pNMTreeView->itemNew.hItem );
        }
        
        InsertItem( "", pNMTreeView->itemNew.hItem );
    }
    
    *pResult = 0;
}

VOID CDirTreeCtrl::ExpandItem( HTREEITEM hItem, UINT nCode )
{
    CString strPath;
    
    if ( nCode == TVE_EXPAND )
    {
        HTREEITEM hChild = GetChildItem( hItem );
        while ( hChild )
        {
            DeleteItem( hChild );
            hChild = GetChildItem( hChild );
        }
        
        strPath = GetFullPath( hItem );
        DisplayPath( hItem, strPath );
    } // End
}
