// ArithPriorityTable.h: interface for the CArithPriorityTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARITHPRIORITYTABLE_H__3158F6D7_6347_448A_9C42_1C2A1822560D__INCLUDED_)
#define AFX_ARITHPRIORITYTABLE_H__3158F6D7_6347_448A_9C42_1C2A1822560D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PriorityTable.h"

class CArithPriorityTable : public CPriorityTable  
{
public:
	CArithPriorityTable();

	CArithPriorityTable(CCalculator& Cal);

	virtual ~CArithPriorityTable();
	
public:
	virtual void CreatePriorityTable(CCalculator& Cal);
};

#endif // !defined(AFX_ARITHPRIORITYTABLE_H__3158F6D7_6347_448A_9C42_1C2A1822560D__INCLUDED_)
