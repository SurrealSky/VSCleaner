//////////////////////////////////////////////////////////////////////////
//
// File Name   : ResizeCtrl.h
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : main header file for the VSCLEANER application
//
//////////////////////////////////////////////////////////////////////////

#if !defined( __VS_CLEANER_APPLICATION_RESIZE_CTRL_INCLUDED__ )
#define __VS_CLEANER_APPLICATION_RESIZE_CTRL_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
//

class ResizeItem
{
public:
    ResizeItem( HWND hWnd, CRect rcWnd, FLOAT left, FLOAT top, FLOAT right, FLOAT bottom );
    virtual ~ResizeItem();

// Members
public:
    HWND  m_hWnd;
    CRect m_rcWnd;
    FLOAT m_left;
    FLOAT m_top;
    FLOAT m_right;
    FLOAT m_bottom;
}; // ResizeItem

//////////////////////////////////////////////////////////////////////////
// CResizeCtrl

class CResizeCtrl
{
// Constructor and Destructor
public:
    CResizeCtrl();
    virtual ~CResizeCtrl();

// Operation
public:
    BOOL Create( CWnd* pWndParent );
    BOOL Add( int nCtrlID, FLOAT left, FLOAT top, FLOAT right, FLOAT bottom );
    VOID Size();

// Implementation
private:

    // 计算调整控件位置的公式
    //
    // newValue = oldValue + ( ( deltaValueParent * partValue ) / maxPart );
    //
    // newValue          - new left or top position or new width or height
    // oldValue          - old left or top position or old width or height 
    // deltaValueParent  - changes in parent width or height
    // partValue         - left, top, width or height value specified in the Add Method
    // maxPart           - value specified by the maxPart parameter of the constructor
    //                     or the Create method
    BOOL Defer( HDWP& hDWP, ResizeItem* pResizeItem, int dx, int dy );

private:
    typedef CArray< ResizeItem*, ResizeItem*& > ResizeItemArray;

    CWnd* m_pWndParent;     // 父窗口句柄
    CRect m_rcOrg;          // 记录父窗口对话框的大小

    ResizeItemArray m_arrayResizeItem;

}; // CResizeCtrl

#endif // __VS_CLEANER_APPLICATION_RESIZE_CTRL_INCLUDED__