// ArithSyntaxAnalyser.h: interface for the CArithSyntaxAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARITHSYNTAXANALYSER_H__3F64FB6C_A458_49A9_BFF8_21AE77374D16__INCLUDED_)
#define AFX_ARITHSYNTAXANALYSER_H__3F64FB6C_A458_49A9_BFF8_21AE77374D16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyntaxAnalyser.h"

class CArithSyntaxAnalyser : public CSyntaxAnalyser  
{
public:
	CArithSyntaxAnalyser();
	virtual ~CArithSyntaxAnalyser();

	
public:
	virtual bool AnalyseSyntax(CCalculator& Cal) ;//·ÖÎö
	
	
protected:
	virtual bool E(CCalculator& Cal);  
	virtual bool E_(CCalculator& Cal) ;

};

#endif // !defined(AFX_ARITHSYNTAXANALYSER_H__3F64FB6C_A458_49A9_BFF8_21AE77374D16__INCLUDED_)
