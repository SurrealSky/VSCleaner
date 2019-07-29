/////////////////////////////////////////////////////////////////////////////
//	filename: 	SortStringArray.cxx
//	author:		L.F.
//  Modifier:   None
//	created:	2007/01/11
//	
//	purpose:	
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SortStringArray.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// SortStringArray

/////////////////////////////////////////////////////////////////////////////
// SortStringArray constructor and destructor

CSortStringArray::CSortStringArray()
{
}

CSortStringArray::~CSortStringArray()
{
}

/////////////////////////////////////////////////////////////////////////////
// SortStringArray method implementation

VOID CSortStringArray::Sort()
{
	BOOL bDone = FALSE;

	while ( ! bDone )
	{
		bDone = TRUE;
		for ( int pos = 0; pos < GetUpperBound(); pos++ )
			bDone |= CompareAndSwap( pos );
	}
}

BOOL CSortStringArray::CompareAndSwap( int nPos )
{
	CString strTmp;

	int nPosFirst = nPos;
	int nPosNext  = nPos + 1;

	if ( GetAt( nPosFirst ).CompareNoCase( GetAt( nPosNext ) ) > 0 )
	{
		strTmp = GetAt( nPosFirst );
		SetAt( nPosFirst, GetAt( nPosNext ) );
		SetAt( nPosNext, strTmp );

		return TRUE;
	}

	return FALSE;
}