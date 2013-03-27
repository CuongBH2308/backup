// ArithWordAnalyser.h: interface for the CArithWordAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARITHWORDANALYSER_H__2F15BEE8_6A10_4B48_9D65_D7A30DECBF2D__INCLUDED_)
#define AFX_ARITHWORDANALYSER_H__2F15BEE8_6A10_4B48_9D65_D7A30DECBF2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WordAnalyser.h"

class CArithWordAnalyser : public CWordAnalyser  
{
public:
	CArithWordAnalyser();
	virtual ~CArithWordAnalyser();

public:
	//抽象类里定义的纯虚函数要在子类中重新声明
	virtual	bool IsOperator(char ch);  
	
	virtual	bool GenerateWord(CCalculator& Cal);       
	
	virtual bool AnalyseWords(char* Expression,CCalculator& Cal);

};

#endif // !defined(AFX_ARITHWORDANALYSER_H__2F15BEE8_6A10_4B48_9D65_D7A30DECBF2D__INCLUDED_)
