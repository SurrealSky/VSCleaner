//////////////////////////////////////////////////////////////////////////
//
// File Name   : VSCleaner.cpp
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : Defines the class behaviors for the application.
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSCleaner.h"
#include "VSCleanerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerApp

BEGIN_MESSAGE_MAP(CVSCleanerApp, CWinApp)
	//{{AFX_MSG_MAP(CVSCleanerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerApp construction

CVSCleanerApp::CVSCleanerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVSCleanerApp object

CVSCleanerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerApp initialization

BOOL CVSCleanerApp::InitInstance()
{
    HANDLE hMutex = ::CreateMutex( NULL, TRUE, m_pszAppName );
    UNREFERENCED_PARAMETER( hMutex );
    if ( ::GetLastError() == ERROR_ALREADY_EXISTS )
		return FALSE;

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

    if ( ! m_fileManager.Initialize() ) {
        AfxMessageBox( _T( "��ʼ�������ļ�ʧ�� !" ), MB_ICONERROR );
        return FALSE;
    }

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//CResultDialog dlg;
	CVSCleanerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


CFileManager* CVSCleanerApp::GetFileManager()
{

    return ( & m_fileManager );
}

int CVSCleanerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
    m_fileManager.SaveIniFile();
	
	return CWinApp::ExitInstance();
}
