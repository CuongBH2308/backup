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


//***************���麯���������е�ʵ��*********************************************************//

bool CLogicWordAnalyser::IsOperator(char ch){
	if(ch == '&' || ch == '!'||ch == '|' || ch == '<'
		||ch == '>' || ch == '='||ch == '(' || ch == ')'|| ch == '#')
		return true;
	return false;
}

bool CLogicWordAnalyser::GenerateWord(CCalculator& Cal){
	
	if(*m_pCurrentLocation == ' '){ //�����ո�
		do
		{
			m_pCurrentLocation++;
		}
		while(*m_pCurrentLocation == ' ');
	}
	
	
	
	//����ǲ�����
	if(IsOperator(*m_pCurrentLocation)){
		
		//����ǵ�Ŀ��,ת����˫Ŀ��
		if(*m_pCurrentLocation == '!'){
			
			Cal.m_Words[m_CurrentWordNum][0] = 't';   //
			Cal.m_WordsAttribute[m_CurrentWordNum] = 3;  //t,����Ϊ 3
			Cal.m_nNumWords++;
			m_CurrentWordNum++;
			
		}
		
		
		Cal.m_Words[m_CurrentWordNum][0] = *m_pCurrentLocation;//���뵥�ʱ�
		
		Cal.m_WordsAttribute[m_CurrentWordNum] = 2; //������,����Ϊ 2
		
		m_CurrentWordNum++;
		
		m_pLastLocation = m_pCurrentLocation; //����ƽ�
		
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
		}while(IsNumber(*m_pCurrentLocation));  //Cal.m_WordsAttribute[m_CurrentWordNum]����Ϊ0,Ϊ����
		
		
		
		if(*m_pCurrentLocation == '.') //С����
		{
			
			Cal.m_Words[m_CurrentWordNum][i++] = *m_pCurrentLocation;
			m_pCurrentLocation++;
			if(!IsNumber(*m_pCurrentLocation)) //С�����Ӧ��Ϊ����
				return false;
			while(IsNumber(*m_pCurrentLocation))
			{
				Cal.m_Words[m_CurrentWordNum][i++] = *m_pCurrentLocation;
				m_pLastLocation = m_pCurrentLocation;
				m_pCurrentLocation++;
			}
			//��������Ϊ 0,����  //Cal.m_WordsAttribute[m_CurrentWordNum]����Ϊ0,Ϊ����
			//Cal.m_WordsAttribute[m_CurrentWordNum] = 1; //С�� ����Ϊ 1
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
		
		Cal.m_WordsAttribute[m_CurrentWordNum] = 1;//����
		m_CurrentWordNum++;
	}
	else //��ÿ�����ʲ���������ʽ��ʼ,��ʷ�����
		
		return false;
}

bool CLogicWordAnalyser::AnalyseWords(char* Expression,CCalculator& Cal){

	
	m_CurrentWordNum = 0;
	
	m_pCurrentLocation = NULL;
	
	strcpy(m_strExpression,"("); //��"("��ͷ
	
	strcat(m_strExpression,Expression);
	
	strcat(m_strExpression,"#");  //���Ͻ�������
	
	m_pCurrentLocation = m_strExpression+1;  //��ǰλ��Ϊԭ���ʽ��һ��
	
	m_pLastLocation = m_strExpression;       //ָ�� (
	
	
	while(*m_pCurrentLocation != '\0'){  //ֱ�����ʽ���
		if(!GenerateWord(Cal)){
			
			return false;
		}
		Cal.m_nNumWords++;
	}
		
		Cal.m_bWASucceed = true;
		return true;
}