// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3E8D98C9_7AB6_4909_A055_CC0D2A0CBCB4__INCLUDED_)
#define AFX_STDAFX_H__3E8D98C9_7AB6_4909_A055_CC0D2A0CBCB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxmt.h>
#include <afxtempl.h>
#include <shlwapi.h>

#pragma comment( lib, "shlwapi.lib" )

//////////////////////////////////////////////////////////////////////////
// 自定义宏

#ifndef SAFE_DELETE
#undef SAFE_DELETE
#define SAFE_DELETE( ptr ) if ( ptr ) { delete ptr; ptr = NULL; }
#endif  // SAFE_DELETE

#define TABITEM_DIRECTORY   0
#define TABITEM_FILETYPE    1
#define TABITEM_FINDRESULT  2

#define VS_WM_SCANRESULT    ( WM_APP + 0x0001 )
#define VS_WM_THREADEXIT    ( WM_APP + 0x0005 )

//////////////////////////////////////////////////////////////////////////
// 工程头文件

#include "resource.h"
#include "SortStringArray.hxx"
#include "ResizeCtrl.h"
#include "DirTreeCtrl.h"
#include "HookFileManager.h"
#include "FileManager.h"
#include "DirDialog.h"
#include "FileTypeDialog.h"
#include "ResultDialog.h"
#include "AddFileTypeDialog.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3E8D98C9_7AB6_4909_A055_CC0D2A0CBCB4__INCLUDED_)
