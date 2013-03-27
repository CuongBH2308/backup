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
	if(strcmp(Cal.m_Words[m_WordIndex],"(") == 0)  // ���
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
		//E->   NE_   ����  0
		//E ->  VE_   ����   1
	
		if(Cal.m_WordsAttribute[m_WordIndex]!=2){ //��Ϊ������
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
E_->NULL  (�մ�)


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
		return true;   //E_-->NULL,����������
	//E_����һ���ӱ��ʽ֮��
	//�����Ϊ������ֵ
	//ֻ��Ϊ�����,���ʽ������'('��'#'
	
	
	else 
		return false;   //E_-->NULL

}


bool CArithSyntaxAnalyser::AnalyseSyntax(CCalculator& Cal){
	if(Cal.m_bWASucceed == false)
		return false;
	
	bool bResult = E(Cal);//������E_(pWords),��Ϊһ�����ʽ��ͷ��Ҫ���Ϲ涨��

	if(bResult == true) 
		Cal.m_bSASucceed = true;
	return bResult;

}