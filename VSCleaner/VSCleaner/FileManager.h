//////////////////////////////////////////////////////////////////////////
//
// File Name   : FileManager.h 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : 实现对搜索文件目录列表的记录,搜索指定文件类型的操作封装
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

    // 读入文件类型,位于配置文件 vscleaner.init
    BOOL Initialize();
    
    BOOL ReadFileItem( HookFileManager* pHookFileManager );

    // 保存修改文件到 vscleaner.ini 中
    BOOL SaveIniFile();

    // 开始从指定的目录中搜索列出的所有文件类型
    BOOL StartReportFilesDetail( HookFileManager* pHookFileManager );
    BOOL StopReportFilesDetail( HookFileManager* pHookFileManager );

    // 设置类型选择状态
    VOID SetFileTypeCheck( CString strKey, BOOL bChecked );

    BOOL AddFileType( CString strKey, CString strRemark, HookFileManager* pHookFileManager );
    BOOL RemoveFileType( CString strKey );

    // 判断加入文件类型是否重复
    BOOL IsFileTypeExist( CString strKey );

    BOOL IsScanning();

protected:
    // 搜索指定文件类型线程函数
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

    LONG   m_nFileCount;  // 记录搜索文件数目
    DOUBLE m_dbFileSize;  // 记录所有搜索文件总大小

}; // CFileManager

#endif // __VS_CLEANER_APPLICATION_FILE_MANAGER_INCLUDED__