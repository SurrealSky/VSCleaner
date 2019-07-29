//////////////////////////////////////////////////////////////////////////
//
// File Name   : ResizeCtrl.cpp
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : main implementation file for the VSCLEANER application
//
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ResizeCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//

ResizeItem::ResizeItem( HWND hWnd, CRect rcWnd, FLOAT left, FLOAT top, FLOAT right, FLOAT bottom )
{
    m_hWnd   = hWnd;
    m_rcWnd  = rcWnd;
    m_left   = left;
    m_top    = top;
    m_right  = right;
    m_bottom = bottom;
}

ResizeItem::~ResizeItem()
{

}

//////////////////////////////////////////////////////////////////////////
//

CResizeCtrl::CResizeCtrl()
{
    m_pWndParent = NULL;
}

CResizeCtrl::~CResizeCtrl()
{
    POSITION    pos         = NULL;
    ResizeItem* pResizeItem = NULL;

    for ( int i = 0; i < m_arrayResizeItem.GetSize(); i++ ) {
         pResizeItem = m_arrayResizeItem.GetAt( i );
         SAFE_DELETE( pResizeItem );
    }
}

//////////////////////////////////////////////////////////////////////////
//

BOOL CResizeCtrl::Create( CWnd* pWndParent )
{
    pWndParent->GetWindowRect( m_rcOrg );
    m_pWndParent = pWndParent;

    return TRUE;
}

BOOL CResizeCtrl::Add( int nCtrlID, FLOAT left, FLOAT top, FLOAT right, FLOAT bottom )
{
    ASSERT( IsWindow( m_pWndParent->GetSafeHwnd() ) );
    if ( ! IsWindow( m_pWndParent->GetSafeHwnd() ) )
        return FALSE;

    HWND hChild = GetDlgItem( m_pWndParent->GetSafeHwnd(), nCtrlID );
    ASSERT( IsWindow( hChild ) );
    if ( ! IsWindow( hChild ) )
        return FALSE;

    CRect rcWindow;
    ::GetWindowRect( hChild, rcWindow );
	m_pWndParent->ScreenToClient( rcWindow );

    ResizeItem* pResizeItem = new ResizeItem( hChild, rcWindow, left, top, right, bottom );
    m_arrayResizeItem.Add( pResizeItem );

    return TRUE;
}

VOID CResizeCtrl::Size()
{
    if ( m_arrayResizeItem.GetSize() == 0 )
        return;

    CRect rcWindow;
    m_pWndParent->GetWindowRect( rcWindow );

    int dx = rcWindow.Width()  - m_rcOrg.Width();
    int dy = rcWindow.Height() - m_rcOrg.Height();

    BOOL bDefered = FALSE;
    HDWP hDWP = ::BeginDeferWindowPos( m_arrayResizeItem.GetSize() );

    for ( int i = 0; i < m_arrayResizeItem.GetSize(); i++ ) {
        if ( Defer( hDWP, m_arrayResizeItem.GetAt( i ), dx, dy ) )
            bDefered = TRUE;
    }

    if ( bDefered )
        ::EndDeferWindowPos( hDWP );

    m_rcOrg = rcWindow;
}

BOOL CResizeCtrl::Defer( HDWP& hDWP, ResizeItem* pResizeItem, int dx, int dy )
{
    HWND hWnd = pResizeItem->m_hWnd;
    if ( ::IsWindow( hWnd ) ) {
        CRect rcItem = pResizeItem->m_rcWnd;

        rcItem.left   += INT( dx * pResizeItem->m_left   );
        rcItem.top    += INT( dy * pResizeItem->m_top    );
        rcItem.right  += INT( dx * pResizeItem->m_right  );
        rcItem.bottom += INT( dy * pResizeItem->m_bottom );

        UINT uFlags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER;

        CRect rOld;
        CRect rNew = rcItem;

        ::GetWindowRect( hWnd, & rOld );
        m_pWndParent->ScreenToClient( & rOld );

        // if the x-y coordinates have not changed, there is no reason
        // to move the dialog item.
        if ( rNew.TopLeft() == rOld.TopLeft() )
            uFlags |= SWP_NOMOVE;

        // if the cx-cy size has not changed, there is no reason to
        // size the dialog item.  If size has changed, don't
        // copy bits of the client area (i.e. have them invalidated/redrawn)
        if ( rNew.Size() == rOld.Size() )
            uFlags |= SWP_NOSIZE;
        else
		    uFlags |= SWP_NOCOPYBITS;

        hDWP = ::DeferWindowPos( hDWP, hWnd, 0, rcItem.left, rcItem.top, rcItem.Width(), rcItem.Height(), uFlags );
        if ( hDWP ==  NULL) {
            TRACE(_T("DeferWindowPos failed for ID %i\n"), GetDlgCtrlID( hWnd ) );
            return FALSE;
	    }
    }

    return TRUE;
}