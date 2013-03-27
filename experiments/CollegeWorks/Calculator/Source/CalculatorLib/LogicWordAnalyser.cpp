// LogicWordAnalyser.cpp: implementation of the CLogicWordAnalyser class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LogicWordAnalyser.h"
#include<string>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLogicWordAnalyser::CLogicWordAnalyser(){
	
}


CLogicWordAnalyser::~CLogicWordAnalyser()
{

}


//***************纯虚函数在子类中的实现*********************************************************//

bool CLogicWordAnalyser::IsOperator(char ch){
	if(ch == '&' || ch == '!'||ch == '|' || ch == '<'
		||ch == '>' || ch == '='||ch == '(' || ch == ')'|| ch == '#')
		return true;
	return false;
}

bool CLogicWordAnalyser::GenerateWord(CCalculator& Cal){
	
	if(*m_pCurrentLocation == ' '){ //跳过空格
		do
		{
			m_pCurrentLocation++;
		}
		while(*m_pCurrentLocation == ' ');
	}
	
	
	
	//如果是操作符
	if(IsOperator(*m_pCurrentLocation)){
		
		//如果是单目的,转化成双目的
		if(*m_pCurrentLocation == '!'){
			
			Cal.m_Words[m_CurrentWordNum][0] = 't';   //
			Cal.m_WordsAttribute[m_CurrentWordNum] = 3;  //t,属性为 3
			Cal.m_nNumWords++;
			m_CurrentWordNum++;
			
		}
		
		
		Cal.m_Words[m_CurrentWordNum][0] = *m_pCurrentLocation;//加入单词表
		
		Cal.m_WordsAttribute[m_CurrentWordNum] = 2; //操作符,属性为 2
		
		m_CurrentWordNum++;
		
		m_pLastLocation = m_pCurrentLocation; //向后移进
		
		m_pCurrentLocation++;
		
		return true;
		
	}
	
	
	
	
	else if(IsNumber(*m_pCurrentLocation)){
		int i ;
		i = 0;
		do
		{
			Cal.m_Words[m_CurrentWordNum][i++] = *m_pCurrentLocation;
			m_pLastLocation = m_pCurrentLocation;
			m_pCurrentLocation++; 
		}while(IsNumber(*m_pCurrentLocation));  //Cal.m_WordsAttribute[m_CurrentWordNum]不变为0,为整数
		
		
		
		if(*m_pCurrentLocation == '.') //小数点
		{
			
			Cal.m_Words[m_CurrentWordNum][i++] = *m_pCurrentLocation;
			m_pCurrentLocation++;
			if(!IsNumber(*m_pCurrentLocation)) //小数点后应该为数字
				return false;
			while(IsNumber(*m_pCurrentLocation))
			{
				Cal.m_Words[m_CurrentWordNum][i++] = *m_pCurrentLocation;
				m_pLastLocation = m_pCurrentLocation;
				m_pCurrentLocation++;
			}
			//数的属性为 0,不变  //Cal.m_WordsAttribute[m_CurrentWordNum]不变为0,为整数
			//Cal.m_WordsAttribute[m_CurrentWordNum] = 1; //小数 属性为 1
			m_CurrentWordNum ++;
			return true;
		}
		else
		{
			m_CurrentWordNum ++;
			return true;
		}
		
	}
	
	
	else if(IsAlpha(*m_pCurrentLocation)){
		int i ;
		i = 0;
		do
		{
			Cal.m_Words[m_CurrentWordNum][i++] = *m_pCurrentLocation;
			m_pLastLocation = m_pCurrentLocation;
			m_pCurrentLocation++; 
		}while(IsAlpha(*m_pCurrentLocation)); 
		
		Cal.m_WordsAttribute[m_CurrentWordNum] = 1;//变量
		m_CurrentWordNum++;
	}
	else //若每个单词不以以上形式开始,则词法错误
		
		return false;
}

bool CLogicWordAnalyser::AnalyseWords(char* Expression,CCalculator& Cal){

	
	m_CurrentWordNum = 0;
	
	m_pCurrentLocation = NULL;
	
	strcpy(m_strExpression,"("); //以"("开头
	
	strcat(m_strExpression,Expression);
	
	strcat(m_strExpression,"#");  //加上结束单词
	
	m_pCurrentLocation = m_strExpression+1;  //当前位置为原表达式第一个
	
	m_pLastLocation = m_strExpression;       //指向 (
	
	
	while(*m_pCurrentLocation != '\0'){  //直到表达式最后
		if(!GenerateWord(Cal)){
			
			return false;
		}
		Cal.m_nNumWords++;
	}
		
		Cal.m_bWASucceed = true;
		return true;
}