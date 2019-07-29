//////////////////////////////////////////////////////////////////////////
//
// File Name   : VSCleanerDlg.cpp
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
#include "VSCleanerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CVSCleanerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerDlg dialog

CVSCleanerDlg::CVSCleanerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVSCleanerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSCleanerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    //m_pDirDialog      = NULL;
    m_pFileTypeDialog = NULL;
    m_pResultDialog   = NULL;
}

void CVSCleanerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSCleanerDlg)
	DDX_Control( pDX, IDC_MAIN_TAB_ITEMS, m_wndTab );
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVSCleanerDlg, CDialog)
	//{{AFX_MSG_MAP(CVSCleanerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
	ON_NOTIFY( NM_CLICK, IDC_MAIN_TAB_ITEMS, OnClickTabItems )

    ON_MESSAGE( VS_WM_SCANRESULT, OnBtnScanResult )
    ON_MESSAGE( VS_WM_THREADEXIT, OnThreadExit    )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSCleanerDlg message handlers

BOOL CVSCleanerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    InitTabWnd();
    CreateTabChildWindows();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVSCleanerDlg::OnOK()
{

}

void CVSCleanerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVSCleanerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVSCleanerDlg::OnQueryDragIcon()
{
	return ( HCURSOR ) m_hIcon;
}

void CVSCleanerDlg::OnDestroy()
{
    CDialog::OnDestroy();

    //if ( m_pDirDialog ) {
    //    m_pDirDialog->DestroyWindow();
    //    SAFE_DELETE( m_pDirDialog );
    //}

    if ( m_pFileTypeDialog ) {
        m_pFileTypeDialog->DestroyWindow();
        SAFE_DELETE( m_pFileTypeDialog );
    }

    if ( m_pResultDialog ) {
        m_pResultDialog->DestroyWindow();
        SAFE_DELETE( m_pResultDialog );
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

BOOL CVSCleanerDlg::InitTabWnd()
{
    m_wndTab.GetWindowRect( m_rcTabWnd );
    ScreenToClient( m_rcTabWnd );

    m_rcTabWnd.left   = m_rcTabWnd.left   +  2;
    m_rcTabWnd.right  = m_rcTabWnd.right  -  2;
    m_rcTabWnd.top    = m_rcTabWnd.top    + 25;
    m_rcTabWnd.bottom = m_rcTabWnd.bottom -  5;

    TCITEM tabItem;
    tabItem.mask = TCIF_TEXT;

    tabItem.pszText = _T( "工程目录" );
    m_wndTab.InsertItem( TABITEM_DIRECTORY, & tabItem );

    tabItem.pszText = _T( "文件类型" );
    m_wndTab.InsertItem( TABITEM_FILETYPE, & tabItem );

    return TRUE;
}

// 创建目录选择窗口(模态对话框)
BOOL CVSCleanerDlg::CreateTabChildWindows()
{
	m_pResultDialog = new CResultDialog();
	m_pResultDialog->Create( IDD_RESULT_DIALOG, this );
	m_pResultDialog->MoveWindow( m_rcTabWnd, TRUE );
	m_pResultDialog->ShowWindow( TRUE );

    m_pFileTypeDialog = new CFileTypeDialog();
    m_pFileTypeDialog->Create( IDD_PROPPAGE_FILETYPE, this );
    m_pFileTypeDialog->MoveWindow( m_rcTabWnd, TRUE );
    m_pFileTypeDialog->ShowWindow( FALSE );

    return TRUE;
}

// 销毁模态对话框
BOOL CVSCleanerDlg::DestroyTabChildWindows()
{


    return TRUE;
}

void CVSCleanerDlg::OnClickTabItems( NMHDR* pNMHDR, LRESULT* pResult ) 
{
	// TODO: Add your control notification handler code here
    int nCurSel = m_wndTab.GetCurSel();
    if ( nCurSel == TABITEM_DIRECTORY ) {
		m_pResultDialog->ShowWindow( TRUE );
        m_pFileTypeDialog->ShowWindow( FALSE );
    }
    else if ( nCurSel == TABITEM_FILETYPE ) {
		m_pResultDialog->ShowWindow( FALSE );
        m_pFileTypeDialog->ShowWindow( TRUE );
    }

	*pResult = 0;
}

// 处理目录扫描按钮处理.
LRESULT CVSCleanerDlg::OnBtnScanResult( WPARAM wParam, LPARAM lParam )
{
    // 获取需要扫描的目录
    // 如果没有选择扫描的目录,则不需要弹出扫描结果对话框
  /*  if (m_pResultDialog->GetScanPath() == 0 ) {
        return 0;
    }

    CRect rcWnd;
    GetWindowRect( & rcWnd );

    if ( m_pResultDialog == NULL ) {
        m_pResultDialog = new CResultDialog();
        m_pResultDialog->Create( IDD_RESULT_DIALOG, this );
        m_pResultDialog->ShowWindow( TRUE );
    }
    else {
        m_pResultDialog->ShowWindow( TRUE );
    }

    m_pResultDialog->MoveWindow( rcWnd, TRUE );

    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );
    pFileManager->StartReportFilesDetail( m_pResultDialog );*/

    return 0;
}

LRESULT CVSCleanerDlg::OnThreadExit( WPARAM wParam, LPARAM lParam )
{
    CFileManager* pFileManager = theApp.GetFileManager();
    ASSERT( pFileManager );

    pFileManager->StopReportFilesDetail( m_pResultDialog );

    return 0;
}