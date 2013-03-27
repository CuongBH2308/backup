// LogicPriorityTable.h: interface for the CLogicPriorityTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICPRIORITYTABLE_H__A99E504E_0ED5_433E_8819_D62C95DF0FFD__INCLUDED_)
#define AFX_LOGICPRIORITYTABLE_H__A99E504E_0ED5_433E_8819_D62C95DF0FFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PriorityTable.h"

class CLogicPriorityTable : public CPriorityTable  
{
public:
	CLogicPriorityTable();
	CLogicPriorityTable(CCalculator& Cal);
	virtual ~CLogicPriorityTable();

public:
	virtual void CreatePriorityTable(CCalculator& Cal);

};

#endif // !defined(AFX_LOGICPRIORITYTABLE_H__A99E504E_0ED5_433E_8819_D62C95DF0FFD__INCLUDED_)
