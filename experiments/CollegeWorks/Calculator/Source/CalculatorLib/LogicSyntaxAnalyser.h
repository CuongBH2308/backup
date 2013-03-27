// LogicSyntaxAnalyser.h: interface for the CLogicSyntaxAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICSYNTAXANALYSER_H__0AA49417_A657_48C9_8A18_B740DCDABED0__INCLUDED_)
#define AFX_LOGICSYNTAXANALYSER_H__0AA49417_A657_48C9_8A18_B740DCDABED0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyntaxAnalyser.h"

class CLogicSyntaxAnalyser : public CSyntaxAnalyser  
{
public:
	CLogicSyntaxAnalyser();
	virtual ~CLogicSyntaxAnalyser();

public:
	virtual bool AnalyseSyntax(CCalculator& Cal) ;//分析
	

protected:
	virtual bool E(CCalculator& Cal);  
	virtual bool E_(CCalculator& Cal) ;
	
	virtual bool ER(CCalculator& Cal) ;  //关系表达式



};

#endif // !defined(AFX_LOGICSYNTAXANALYSER_H__0AA49417_A657_48C9_8A18_B740DCDABED0__INCLUDED_)
