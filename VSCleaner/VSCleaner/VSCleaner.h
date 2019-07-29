//////////////////////////////////////////////////////////////////////////
//
// File Name   : VSCleaner.h
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : main header file for the VSCLEANER application
//
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_VSCLEANER_H__995A714B_C73A_46F2_99AE_FA94E620DCFF__INCLUDED_)
#define AFX_VSCLEANER_H__995A714B_C73A_46F2_99AE_FA94E620DCFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerApp:
// See VSCleaner.cpp for the implementation of this class
//

class CVSCleanerApp : public CWinApp
{
public:
	CVSCleanerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSCleanerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
    CFileManager* GetFileManager();

	//{{AFX_MSG(CVSCleanerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CFileManager m_fileManager;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSCLEANER_H__995A714B_C73A_46F2_99AE_FA94E620DCFF__INCLUDED_)
