//////////////////////////////////////////////////////////////////////////
//
// File Name   : FileManager.cpp 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : ʵ�ֶ������ļ�Ŀ¼�б�ļ�¼,����ָ���ļ����͵Ĳ�����װ
//
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "FileManager.h"

//////////////////////////////////////////////////////////////////////////
// ����ָ���ļ������߳�
//////////////////////////////////////////////////////////////////////////

typedef struct tagThreadParam {
    HWND             hWnd;
    HookFileManager* pHookFileManager;
    CFileManager*    pFileManager;
} ThreadParam;

UINT CFileManager::ThreadProc( LPVOID lParam )
{
    ThreadParam* pThreadParam = reinterpret_cast< ThreadParam* >( lParam );

    CFileManager* pFileManager = pThreadParam->pFileManager;
    CString strPath;

    for ( POSITION pos = pFileManager->m_strList.GetHeadPosition(); pos != NULL; ) {
        strPath = pFileManager->m_strList.GetNext( pos );
        TRACE0( strPath + "\n" );

        pFileManager->FindSubDir( strPath, pThreadParam->pHookFileManager );
    }

    ASSERT( ::IsWindow( pThreadParam->hWnd ) );
    ::PostMessage( pThreadParam->hWnd, VS_WM_THREADEXIT, 0, 0 );
    TRACE0( "Thread Exit !\n" );

    return 0;
}

BOOL CFileManager::FindSubDir( CString strPath, HookFileManager* pHookFileManager )
{
    strPath = "D:\\����\\VSCleaner\\VSCleaner\\Bin\\Debug";
    if ( strPath.IsEmpty() )
		return FALSE;

    CFileFind fileFind;
    
	BOOL bFind = FALSE;
    
    if ( strPath.Right( 1 ) == _T( '\\' ) )
        strPath += _T( "*.*" );
    else
		strPath += _T( "\\*.*" );

	bFind = fileFind.FindFile( strPath );

    // ʹ�õݹ����������ļ�
    CString strFileType = "";
    CString strSize     = "";
	int     nIndex      = 0;
    FLOAT   fileSize    = 0;

     while ( bFind ) {
 		bFind = fileFind.FindNextFile();

        if ( fileFind.IsDirectory() && ( ! fileFind.IsDots() ) ) {
             strFileType = fileFind.GetFilePath();
             FindSubDir( strFileType, pHookFileManager );
 		}
        else {
            strFileType = fileFind.GetFileName();
			if (strFileType.Find("VC.db")!=-1&&strFileType.GetLength()-strFileType.Find("VC.db") == 5)
			{
				strFileType = "VC.db";
			}
			else
			{
				nIndex = strFileType.ReverseFind('.');
				strFileType.Delete(0, nIndex + 1);
			}

            // �ж��������ļ��Ƿ���Ҫ����
            LPFILE_ITEM pFileItem = NULL;
            strFileType.MakeLower();

            if ( m_mapType2FileItem.Lookup( strFileType, pFileItem ) ) {
                if ( pFileItem->strSelected == _T( "TRUE" ) ) {
                    fileSize = FLOAT( fileFind.GetLength() ) / 1024;

                    // �����ļ���С(KB)
		            strSize.Format( "%.2f KB", fileSize );

                    pHookFileManager->OnFindFile( fileFind.GetFilePath(), strSize );

                    ::InterlockedIncrement ( & m_nFileCount );
                    m_dbFileSize += fileSize;
                }
            }
        }
     } // while

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

CFileManager::CFileManager() :	
    M_STR_ININAME    ( _T( "vscleaner.ini" ) ),
    M_STR_SECTIONTYPE( _T( "FileType"      ) ),
	M_STR_SECTIONSEL ( _T( "FileSelect"    ) )
{
    m_pWinThread = NULL;
    m_nFileCount = 0;
    m_dbFileSize = 0;
}

CFileManager::~CFileManager()
{
    POSITION pos = NULL;

    CString     strKey;
    LPFILE_ITEM pFileItem = NULL;
    
    for ( pos = m_mapType2FileItem.GetStartPosition(); pos != NULL; ) {
        m_mapType2FileItem.GetNextAssoc( pos, strKey, pFileItem );
        SAFE_DELETE( pFileItem );
    }
}

//////////////////////////////////////////////////////////////////////////
// ʵ��
//////////////////////////////////////////////////////////////////////////

BOOL CFileManager::AddScanDir( CString strDir )
{
    m_strList.AddTail( strDir );

    return TRUE;
}

INT CFileManager::GetDirCount()
{
    return m_strList.GetCount();
}

VOID CFileManager::ResetScanDir()
{
    m_strList.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////
// �����ļ�����,λ�������ļ� vscleaner.init
//////////////////////////////////////////////////////////////////////////

BOOL CFileManager::Initialize()
{
    CString strPath;
    GetModuleFileName( NULL, strPath.GetBuffer( MAX_PATH ), MAX_PATH );
    strPath.ReleaseBuffer();
    
    int nIndex = strPath.ReverseFind( '\\' );
    strPath.Delete( nIndex, strPath.GetLength() - nIndex );
    if ( strPath.Right( 1 ) != _T( "\\" ) )
		strPath += _T( "\\" );

    strPath += M_STR_ININAME;
    
    // ���������ļ�������,�����Դ��ȡĬ�������ļ�
    if ( ! PathFileExists( strPath ) ) {
        HRSRC hRsrc = FindResource( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDR_INI_FILE ), _T( "RT_RCDATA" ) );
        ASSERT( hRsrc );
        if ( hRsrc == NULL )
            return FALSE;
        
        HGLOBAL hGlobal = LoadResource( AfxGetInstanceHandle(), hRsrc );
        ASSERT( hGlobal );
        if ( hGlobal == NULL )
            return FALSE;
        
        DWORD dwSize = SizeofResource( AfxGetInstanceHandle(), hRsrc );
        ASSERT( dwSize > 0 );
        
        LPVOID pData = LockResource( hGlobal );
        
        CFile file;
        file.Open( strPath, CFile::modeCreate | CFile::modeReadWrite );
        file.Write( pData, dwSize );
        file.Close();
	}

    int nSize = 8192;   // 1024 * 8
    
    TCHAR szKeyNames[ 8192 ] = { '\0' };
    int nLength = GetPrivateProfileString( M_STR_SECTIONTYPE, NULL, NULL, szKeyNames, nSize, strPath );
    ASSERT( nLength < nSize );
    if ( nLength > nSize )
		return FALSE;

    CString strKey;
	FILE_ITEM fileItem;

    for ( int i = 0; i < nLength; i++ ) {
        // ע��
        // -- ÿ�� Key �ķָ��������� '\0' �ָ���,�� Key \0\0 Key
        if ( szKeyNames[ i ] == '\0' ) {

            GetPrivateProfileString( M_STR_SECTIONTYPE, strKey, NULL, fileItem.strRemark.GetBuffer( MAX_PATH * 2 ), MAX_PATH * 2, strPath );
            fileItem.strRemark.ReleaseBuffer();

            GetPrivateProfileString( M_STR_SECTIONSEL, strKey, NULL, fileItem.strSelected.GetBuffer( 10 ), 10, strPath );
            fileItem.strSelected.ReleaseBuffer();

            strKey.MakeLower();

            // �����Ƿ��Ѿ����� ?
            LPFILE_ITEM pFileItem = NULL;
            if ( m_mapType2FileItem.Lookup( strKey, pFileItem ) )
                continue;

            // �������ͺ�ѡ��״̬
            pFileItem = new FILE_ITEM;
            *pFileItem = fileItem;
            m_mapType2FileItem[ strKey ] = pFileItem;

            strKey.Empty();
        
            fileItem.strRemark.Empty();
            fileItem.strSelected.Empty();
        }
        else {
            // ������һ�� Key
            strKey += szKeyNames[ i ];
        }
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// ��ȡ�����ļ���������Ϣ
//////////////////////////////////////////////////////////////////////////

BOOL CFileManager::ReadFileItem( HookFileManager* pHookFileManager )
{
    if ( pHookFileManager == NULL )
        return FALSE;

    POSITION pos = NULL;

    CString     strKey;
    LPFILE_ITEM pFileItem = NULL;

    for ( pos = m_mapType2FileItem.GetStartPosition(); pos != NULL; ) {
        m_mapType2FileItem.GetNextAssoc( pos, strKey, pFileItem );
        pHookFileManager->OnReadFileItem( strKey, pFileItem->strRemark, pFileItem->strSelected );
    }


    return TRUE;
}

BOOL CFileManager::SaveIniFile()
{
    CString strPath;
    GetModuleFileName( NULL, strPath.GetBuffer( MAX_PATH ), MAX_PATH );
    strPath.ReleaseBuffer();
    
    int nIndex = strPath.ReverseFind( '\\' );
    strPath.Delete( nIndex, strPath.GetLength() - nIndex );
    if ( strPath.Right( 1 ) != _T( "\\" ) )
        strPath += _T( "\\" );
    
    strPath += M_STR_ININAME;
    if ( PathFileExists( strPath ) )
        DeleteFile( strPath );
    
    POSITION pos = NULL;
    
    CString strKey;
    
    LPFILE_ITEM pFileItem = NULL;
    
    for ( pos = m_mapType2FileItem.GetStartPosition(); pos != NULL; ) {
        m_mapType2FileItem.GetNextAssoc( pos, strKey, pFileItem );
        ASSERT( pFileItem );
        
        WritePrivateProfileString( M_STR_SECTIONTYPE, strKey, pFileItem->strRemark,   strPath );
        WritePrivateProfileString( M_STR_SECTIONSEL,  strKey, pFileItem->strSelected, strPath );
	}

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// ��ָ����Ŀ¼�������г��������ļ�����
//////////////////////////////////////////////////////////////////////////

BOOL CFileManager::StartReportFilesDetail( HookFileManager* pHookFileManager )
{
    ASSERT( pHookFileManager );
    if ( pHookFileManager == NULL )
        return FALSE;

    if ( m_pWinThread != NULL ) {
        return TRUE;
    }

    m_nFileCount = 0;
    m_dbFileSize = 0;

    // ע�⣬���Ҫʹ�þֲ���̬��������Ϊ�������� PostMessage ��ʽ�����
    // ��֤�˸ú����˳�ʱ�̲߳���ֵ��Ȼ��Ч���������ַǷ����ʵ�ַ����
    static ThreadParam tp;

    tp.hWnd             = AfxGetMainWnd()->GetSafeHwnd();
    tp.pFileManager     = this;
    tp.pHookFileManager = pHookFileManager;

    m_pWinThread = AfxBeginThread( CFileManager::ThreadProc, & tp, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED );
    m_pWinThread->m_bAutoDelete = FALSE;
    m_pWinThread->ResumeThread();

    return TRUE;
}

BOOL CFileManager::StopReportFilesDetail( HookFileManager* pHookFileManager )
{
    if ( m_pWinThread == NULL )
        return TRUE;

    WaitForSingleObject( m_pWinThread->m_hThread, INFINITE );
    SAFE_DELETE( m_pWinThread );
    TRACE0( "Delete Thread !\n" );

    pHookFileManager->OnFindFileResult( m_nFileCount, m_dbFileSize );

    m_nFileCount = 0;
    m_dbFileSize = 0;

    return TRUE;
}

VOID CFileManager::SetFileTypeCheck( CString strKey, BOOL bChecked )
{
    LPFILE_ITEM pFileItem = NULL;
    
    if ( ! m_mapType2FileItem.Lookup( strKey, pFileItem ) )
        return;
    
    if ( bChecked )
        pFileItem->strSelected = _T( "TRUE" );
    else
		pFileItem->strSelected = _T( "FALSE" );    
}

BOOL CFileManager::AddFileType( CString strKey, CString strRemark, HookFileManager* pHookFileManager )
{
    strKey.MakeLower();
    
    LPFILE_ITEM pFileItem = NULL;
    
    if ( m_mapType2FileItem.Lookup( strKey, pFileItem ) )
        return FALSE;
    
    pFileItem = new FILE_ITEM;
    ASSERT( pFileItem != NULL );
    
    pFileItem->strRemark   = strRemark;
    pFileItem->strSelected = _T( "FALSE" );
    
    m_mapType2FileItem[ strKey ] = pFileItem;

    pHookFileManager->OnReadFileItem( strKey, strRemark, _T( "FALSE" ) );

	return TRUE;
}

BOOL CFileManager::RemoveFileType( CString strKey )
{
    LPFILE_ITEM pFileItem = NULL;
    
    if ( ! m_mapType2FileItem.Lookup( strKey, pFileItem ) )
        return FALSE;
    
    delete pFileItem;
    
	m_mapType2FileItem.RemoveKey( strKey );
   
    return TRUE;
}

BOOL CFileManager::IsFileTypeExist( CString strKey )
{
    LPFILE_ITEM pFileItem = NULL;
    
    strKey.MakeLower();
    
    if ( m_mapType2FileItem.Lookup( strKey, pFileItem ) )
        return TRUE;
    
	return FALSE;    
}

BOOL CFileManager::IsScanning()
{
    if ( m_pWinThread )
        return TRUE;

    return FALSE;
}

