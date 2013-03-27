// LogicWordAnalyser.h: interface for the CLogicWordAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICWORDANALYSER_H__D555EE64_8873_4343_8432_B270D17ADA7B__INCLUDED_)
#define AFX_LOGICWORDANALYSER_H__D555EE64_8873_4343_8432_B270D17ADA7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WordAnalyser.h"

class CLogicWordAnalyser : public CWordAnalyser  
{
public:
	CLogicWordAnalyser();

	virtual ~CLogicWordAnalyser();

public:

	//抽象类里定义的纯虚函数要在子类中重新声明
	virtual	bool IsOperator(char ch);  
	
	virtual	bool GenerateWord(CCalculator& Cal);       

	virtual bool AnalyseWords(char* Expression,CCalculator& Cal);
};

#endif // !defined(AFX_LOGICWORDANALYSER_H__D555EE64_8873_4343_8432_B270D17ADA7B__INCLUDED_)





















