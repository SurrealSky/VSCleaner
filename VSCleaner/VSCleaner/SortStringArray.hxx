/////////////////////////////////////////////////////////////////////////////
//	filename: 	SortStringArray.hxx
//	author:		L.F.
//  Modifier:   None
//	created:	2007/01/11
//	
//	purpose:	
/////////////////////////////////////////////////////////////////////////////

#if !defined( __C_SORT_STRING_ARRAY_H__ )
#define	__C_SORT_STRING_ARRAY_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSortStringArray : public CStringArray
{
public:
	CSortStringArray();
	virtual ~CSortStringArray();

	// Operation
public:
	VOID Sort();

private:
	BOOL CompareAndSwap( int nPos );
};

#endif	// __C_SORT_STRING_ARRAY_H__