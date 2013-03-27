// PriorityTable.h: interface for the CPriorityTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIORITYTABLE_H__197C4FDF_F7B7_4CBC_B921_2943CF70F453__INCLUDED_)
#define AFX_PRIORITYTABLE_H__197C4FDF_F7B7_4CBC_B921_2943CF70F453__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CalculatorLib/Calculator.h"

class CPriorityTable  
{
public:
	CPriorityTable();
	virtual ~CPriorityTable();
	
public:
	virtual void CreatePriorityTable(CCalculator& Cal) = 0;	

protected:
	int m_nTableSize;

};

#endif // !defined(AFX_PRIORITYTABLE_H__197C4FDF_F7B7_4CBC_B921_2943CF70F453__INCLUDED_)
