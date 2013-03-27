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



//��bool�ķ���ֵ������Ƿ����﷨����,��Ϊ�ݹ���Ƕ��,�������﷨
//����ʱ��������㺯����,�������ö�ÿ�κ����������ж�,�Ա���������ʱ
//�ɲ�㷵�ش���




/*
ER:��ϵ���ʽ
N:��ֵ��
V������
L���߼�ֵ

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
	if(strcmp(Cal.m_Words[m_WordIndex],"(") == 0)  // ���
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
EL:�߼����ʽ����������E��ʾ
EL_:��չ��������ݹ�󣩵��߼����ʽ����������E_ ��ʾ


EL-> ER EL_   
EL -> (EL) EL_

 */

bool CLogicSyntaxAnalyser::E(CCalculator& Cal){
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
		//E ->  LE_   �߼�ֵ  3
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
		return true;   //E_-->NULL,����������
	                   //E_����һ���߼����ϵ���ʽ֮��
	                   //�����Ϊ��ϵ������������ֵ
	                   //ֻ��Ϊ�߼����������ʽ������'('��'#'

	else 
		return false;

}


bool CLogicSyntaxAnalyser::AnalyseSyntax(CCalculator& Cal){
	if(Cal.m_bWASucceed == false)
		return false;
	
	bool bResult = E(Cal);//������E_(pWords),��Ϊһ�����ʽ��ͷ��Ҫ���Ϲ涨��

	if(bResult == true) 
		Cal.m_bSASucceed = true;
	return bResult;

}