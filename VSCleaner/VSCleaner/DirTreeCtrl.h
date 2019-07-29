//////////////////////////////////////////////////////////////////////////
//
// File Name   : DirTreeCtrl.h
// File Date   : 2010-01-20
// Author      : DannyLai(L.F.)
// Blog        : http://blog.csdn.net/laiboy
//               http://laiboy.cublog.cn
// E-mail      : laiboy80@21cn.com
// Description : Header file
//
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRTREECTRL_H__29F83081_1567_468F_AC76_5853E77CC7D2__INCLUDED_)
#define AFX_DIRTREECTRL_H__29F83081_1567_468F_AC76_5853E77CC7D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl window

class CDirTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CDirTreeCtrl();

// Attributes
public:

// Operations
public:
    BOOL DisplayTree( LPCTSTR strRoot, BOOL bFiles = FALSE );

    // ��ȡ��ǰ���ؼ������������·��
	CString GetFullPath( HTREEITEM hItem );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDirTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDirTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnItemexpanded( NMHDR* pNMHDR, LRESULT* pResult );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
    // ��ȡϵͳ�̣�Ŀ¼ͼ���б�
    BOOL GetSystemImageList();

    BOOL DisplayDrives();
	VOID DisplayPath( HTREEITEM hParent, LPCTSTR szPath );

	VOID ExpandItem( HTREEITEM hItem, UINT nCode );

	HTREEITEM AddItem( HTREEITEM hParent, LPCTSTR szPath );

	LPCTSTR GetSubPath( LPCTSTR szPath );
	BOOL FindSubDir( LPCTSTR szPath );

    // Attributes
    CImageList m_imgList;

    BOOL m_bFiles;		// TRUE  -- ֻʾĿ¼,����ʾ�ļ�
						// FALSE -- ��ʾ�����ļ�,����Ŀ¼

    CString m_strError;
	CString m_strRoot;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRTREECTRL_H__29F83081_1567_468F_AC76_5853E77CC7D2__INCLUDED_)
