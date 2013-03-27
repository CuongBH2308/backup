// ArithSyntaxAnalyser.cpp: implementation of the CArithSyntaxAnalyser class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ArithSyntaxAnalyser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArithSyntaxAnalyser::CArithSyntaxAnalyser()
{

}

CArithSyntaxAnalyser::~CArithSyntaxAnalyser()
{

}

/*
E->NE_
E->VE_
E->(E)E_

 */

bool CArithSyntaxAnalyser::E(CCalculator& Cal){
	//E->(E)E_
	if(strcmp(Cal.m_Words[m_WordIndex],"(") == 0)  // 相等
	{
		m_WordIndex++;
		if(!E(Cal)) return false;  
		if(strcmp(Cal.m_Words[m_WordIndex],")") == 0)
		{
			m_WordIndex++;
			if(!E_(Cal)) return false;
			return true;
		}
		
		else
		{
			return false;
		}
		
	}
	else{
		//E->   NE_   常量  0
		//E ->  VE_   变量   1
	
		if(Cal.m_WordsAttribute[m_WordIndex]!=2){ //不为操作符
			m_WordIndex++;
			if(!E_(Cal))  return false;
		}

		else
			return false;
		//m_WordIndex++;
		//return true;
	}
}


/*
E_->+EE_
E_->-EE_
E_->*EE_
E_->/EE_
E_->^EE_
E_->NULL  (空串)


 */
bool CArithSyntaxAnalyser::E_(CCalculator& Cal){
	
	
	
	
	if(strcmp(Cal.m_Words[m_WordIndex],  "+") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex], "-") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex], "*") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex], "/") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex], "^") == 0 
		)
		
	{
		m_WordIndex++;
		if(!E(Cal)) return false;
		if(!E_(Cal)) return false;
		return true;
	}
	else if(strcmp(Cal.m_Words[m_WordIndex],")") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex],"#") == 0 ) 
		return true;   //E_-->NULL,是有条件的
	//E_是在一个子表达式之后
	//其后不能为变量或值
	//只能为运算符,表达式结束符'('或'#'
	
	
	else 
		return false;   //E_-->NULL

}


bool CArithSyntaxAnalyser::AnalyseSyntax(CCalculator& Cal){
	if(Cal.m_bWASucceed == false)
		return false;
	
	bool bResult = E(Cal);//不能是E_(pWords),因为一个表达式开头是要符合规定的

	if(bResult == true) 
		Cal.m_bSASucceed = true;
	return bResult;

}