//////////////////////////////////////////////////////////////////////////
//
// File Name   : FileManager.h 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : ʵ�ֶ������ļ�Ŀ¼�б�ļ�¼,����ָ���ļ����͵Ĳ�����װ
//
//////////////////////////////////////////////////////////////////////////

#if !defined( __VS_CLEANER_APPLICATION_FILE_MANAGER_INCLUDED__ )
#define __VS_CLEANER_APPLICATION_FILE_MANAGER_INCLUDED__

//////////////////////////////////////////////////////////////////////////
//

typedef struct tagFILE_ITEM {
    CString strRemark;
    CString strSelected;
} FILE_ITEM, * LPFILE_ITEM;

typedef CMap< CString, LPCSTR, LPFILE_ITEM, LPFILE_ITEM& > CMapStringToFileItem;

//////////////////////////////////////////////////////////////////////////
// CFileManager

class CFileManager
{
// Constructor and Destructor
public:
    CFileManager();
    virtual ~CFileManager();

// Operation
public:
    BOOL AddScanDir( CString strDir );
    INT GetDirCount();
    VOID ResetScanDir();

    // �����ļ�����,λ�������ļ� vscleaner.init
    BOOL Initialize();
    
    BOOL ReadFileItem( HookFileManager* pHookFileManager );

    // �����޸��ļ��� vscleaner.ini ��
    BOOL SaveIniFile();

    // ��ʼ��ָ����Ŀ¼�������г��������ļ�����
    BOOL StartReportFilesDetail( HookFileManager* pHookFileManager );
    BOOL StopReportFilesDetail( HookFileManager* pHookFileManager );

    // ��������ѡ��״̬
    VOID SetFileTypeCheck( CString strKey, BOOL bChecked );

    BOOL AddFileType( CString strKey, CString strRemark, HookFileManager* pHookFileManager );
    BOOL RemoveFileType( CString strKey );

    // �жϼ����ļ������Ƿ��ظ�
    BOOL IsFileTypeExist( CString strKey );

    BOOL IsScanning();

protected:
    // ����ָ���ļ������̺߳���
    static UINT ThreadProc( LPVOID lParam );

    BOOL FindSubDir( CString strPath, HookFileManager* pHookFileManager );

// Members
private:
    CStringList m_strList;

    CMapStringToFileItem m_mapType2FileItem;

    const CString M_STR_ININAME;
    const CString M_STR_SECTIONTYPE;
	const CString M_STR_SECTIONSEL;

    CWinThread* m_pWinThread;

    LONG   m_nFileCount;  // ��¼�����ļ���Ŀ
    DOUBLE m_dbFileSize;  // ��¼���������ļ��ܴ�С

}; // CFileManager

#endif // __VS_CLEANER_APPLICATION_FILE_MANAGER_INCLUDED__