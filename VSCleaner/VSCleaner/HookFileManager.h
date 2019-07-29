//////////////////////////////////////////////////////////////////////////
//
// File Name   : HookFileManager.h 
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : 实现 FileManager 事件处理接口
//
//////////////////////////////////////////////////////////////////////////

#if !defined( __VS_CLEANER_APPLICATION_HOOK_FILE_MANAGER_INCLUDED__ )
#define __VS_CLEANER_APPLICATION_HOOK_FILE_MANAGER_INCLUDED__

//////////////////////////////////////////////////////////////////////////
//

class HookFileManager
{
    // Constructor and Destructor
public:
    HookFileManager();
    virtual ~HookFileManager();

public:
    virtual VOID OnReadFileItem( CString strType, CString strRemark, CString strState );
    virtual VOID OnFindFile( CString strFilePath, CString strSize );
    virtual VOID OnFindFileResult( LONG count, DOUBLE total );

}; // HookFileManager

#endif // __VS_CLEANER_APPLICATION_HOOK_FILE_MANAGER_INCLUDED__