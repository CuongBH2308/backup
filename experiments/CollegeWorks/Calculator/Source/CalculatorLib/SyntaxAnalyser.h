// SyntaxAnalyser.h: interface for the CSyntaxAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNTAXANALYSER_H__A947414F_B3E3_470F_9ADE_2A52A3BF6409__INCLUDED_)
#define AFX_SYNTAXANALYSER_H__A947414F_B3E3_470F_9ADE_2A52A3BF6409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Calculator.h"
#include<string>

class CSyntaxAnalyser  
{
public:
	CSyntaxAnalyser();
	virtual ~CSyntaxAnalyser();

public:
	virtual bool AnalyseSyntax(CCalculator& Cal) = 0;//语法分析


protected:
	//用来递归进行语法分析，可在子类添加此类辅助函数，但接口不变
	virtual bool E(CCalculator& Cal) = 0;  //一个基类的实例是无意义的,这些函数要在不同的子类定义
	virtual bool E_(CCalculator& Cal) = 0;


protected:

	int m_WordIndex;//当前单词下标

	bool m_bResult;//用做返回值，暂时未用

};

#endif // !defined(AFX_SYNTAXANALYSER_H__A947414F_B3E3_470F_9ADE_2A52A3BF6409__INCLUDED_)
