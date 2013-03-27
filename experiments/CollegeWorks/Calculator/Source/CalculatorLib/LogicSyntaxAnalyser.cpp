// LogicSyntaxAnalyser.cpp: implementation of the CLogicSyntaxAnalyser class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LogicSyntaxAnalyser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicSyntaxAnalyser::CLogicSyntaxAnalyser()
{

}

CLogicSyntaxAnalyser::~CLogicSyntaxAnalyser()
{

}



//用bool的返回值来表达是否有语法错误,因为递归层层嵌套,当遇到语法
//错误时可能在深层函数中,所以需用对每次函数调用做判断,以便遇到错误时
//可层层返回错误




/*
ER:关系表达式
N:数值　
V：变量
L：逻辑值

ER -> N>V                 
ER -> V>N  
ER -> N<V  
ER -> V<N
ER -> N=V 
ER -> V=N
ER -> L            //t,f
ER -> (ER)

 */

bool CLogicSyntaxAnalyser::ER(CCalculator& Cal){
	if(strcmp(Cal.m_Words[m_WordIndex],"(") == 0)  // 相等
	{
		m_WordIndex++;
		if(!ER(Cal)) return false;  
		if(strcmp(Cal.m_Words[m_WordIndex],")") == 0)
		{
			m_WordIndex++;
			//if(!E_(Cal)) return false;
			return true;
		}
		else
			return false;
	}
	else{
		if((Cal.m_WordsAttribute[m_WordIndex] == 0)||(Cal.m_WordsAttribute[m_WordIndex] == 1))
		{
			
			m_WordIndex++;
			if((strcmp(Cal.m_Words[m_WordIndex],">") == 0)||
				(strcmp(Cal.m_Words[m_WordIndex],"<") == 0)||
				(strcmp(Cal.m_Words[m_WordIndex],"=") == 0)
				)
			{
				
				m_WordIndex++;
				if((Cal.m_WordsAttribute[m_WordIndex] == 0)||(Cal.m_WordsAttribute[m_WordIndex] == 1))
				{
					m_WordIndex++;
					return true;
				}
			}
		}

		if((Cal.m_WordsAttribute[m_WordIndex] == 3)){
            m_WordIndex++;
			return true;
		}

		return false;
		
	}
}





/*
EL:逻辑表达式，函数中用E表示
EL_:扩展（消除左递归后）的逻辑表达式，函数中用E_ 表示


EL-> ER EL_   
EL -> (EL) EL_

 */

bool CLogicSyntaxAnalyser::E(CCalculator& Cal){
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
		//E ->  LE_   逻辑值  3
		if(!ER(Cal)) return false;

		if(!E_(Cal)) return false;



		//m_WordIndex++;
		return true;
	}
}


/*
EL_ -> &EL EL_   
EL_ -> !EL EL_
EL _-> |EL EL_
EL_-> NULL

 */
bool CLogicSyntaxAnalyser::E_(CCalculator& Cal){
	
	
	
	
	if(strcmp(Cal.m_Words[m_WordIndex],"&") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex],"!") == 0 ||
		strcmp(Cal.m_Words[m_WordIndex],"|") == 0 
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
	                   //E_是在一个逻辑或关系表达式之后
	                   //其后不能为关系运算符或变量或值
	                   //只能为逻辑运算符或表达式结束符'('或'#'

	else 
		return false;

}


bool CLogicSyntaxAnalyser::AnalyseSyntax(CCalculator& Cal){
	if(Cal.m_bWASucceed == false)
		return false;
	
	bool bResult = E(Cal);//不能是E_(pWords),因为一个表达式开头是要符合规定的

	if(bResult == true) 
		Cal.m_bSASucceed = true;
	return bResult;

}