// LogicPriorityTable.cpp: implementation of the CLogicPriorityTable class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LogicPriorityTable.h"
#include<map>
#include<string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicPriorityTable::CLogicPriorityTable()
{

}

CLogicPriorityTable::~CLogicPriorityTable()
{

}

CLogicPriorityTable::CLogicPriorityTable(CCalculator& Cal)
{
	CreatePriorityTable(Cal);
	
}


void CLogicPriorityTable::CreatePriorityTable(CCalculator& Cal){

	//һ���ض������ȱ�,û��ʲô�����.
	int i,j;
	m_nTableSize = 9;
	for( i = 0; i < m_nTableSize; i++)
		for( j = 0; j<m_nTableSize; j++)
			Cal.m_PriorityTable[i][j] = 1;                  //���Ĭ�Ϲ�ϵ  ����
		
		
		for(i = 1;i < 7; i++)   //��0��
			Cal.m_PriorityTable[0][i] = -1;
		
		for(i = 2;i < 7; i++)   //��1��
			Cal.m_PriorityTable[1][i] = -1;
		
		for(i = 3;i < 7; i++)   //��2��
			Cal.m_PriorityTable[2][i] = -1;
		
		Cal.m_PriorityTable[3][5] = Cal.m_PriorityTable[3][6] = -1;  //��3��
		
		Cal.m_PriorityTable[4][5] = Cal.m_PriorityTable[4][6] = -1; //��4��
		
		Cal.m_PriorityTable[5][5] = Cal.m_PriorityTable[5][6] = -1; //��5��
		
		for(i = 0;i < 7; i++)             //��6��
			Cal.m_PriorityTable[6][i] = -1;
		
		Cal.m_PriorityTable[6][7] = 0;
		////��7�в���
		
		for(i = 0;i < 7; i++)             //��8��
			Cal.m_PriorityTable[8][i] = -1;
		
		Cal.m_PriorityTable[8][8] = 0;
	



		//���������������ȱ��еĶ�Ӧ�±�
		Cal.m_OperatorIndex['|'] = 0;
		Cal.m_OperatorIndex['&'] = 1;
		Cal.m_OperatorIndex['='] = 2;
		Cal.m_OperatorIndex['<'] = 3;
		Cal.m_OperatorIndex['>'] = 4;
		Cal.m_OperatorIndex['!'] = 5;
		Cal.m_OperatorIndex['('] = 6;
		Cal.m_OperatorIndex[')'] = 7;
		Cal.m_OperatorIndex['#'] = 8;



		Cal.m_bPTCreated = true;
		//return true;
		
}