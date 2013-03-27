// ArithPriorityTable.cpp: implementation of the CArithPriorityTable class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ArithPriorityTable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArithPriorityTable::CArithPriorityTable()
{

}

CArithPriorityTable::~CArithPriorityTable()
{

}

CArithPriorityTable::CArithPriorityTable(CCalculator& Cal){
	
	CreatePriorityTable(Cal);

}

void CArithPriorityTable::CreatePriorityTable(CCalculator& Cal){
	//һ���ض������ȱ�,û��ʲô�����.
	int i,j;
	m_nTableSize = 8;
	for( i = 0; i < m_nTableSize; i++)
		for( j = 0; j<m_nTableSize; j++)
			Cal.m_PriorityTable[i][j] = 1;                  //���Ĭ�Ϲ�ϵ  ����
		
		
		for(i = 2;i < 6; i++)   //��0��
			Cal.m_PriorityTable[0][i] = -1;
		
		for(i = 2;i < 6; i++)   //��1��
			Cal.m_PriorityTable[1][i] = -1;
		
	
		Cal.m_PriorityTable[2][4] = Cal.m_PriorityTable[2][5] = -1;  //��3��
		
		Cal.m_PriorityTable[3][4] = Cal.m_PriorityTable[3][5] = -1; //��4��
		
		Cal.m_PriorityTable[4][4] = Cal.m_PriorityTable[4][5] = -1; //��5��
		
		for(i = 0;i < 6; i++)             //��6��
			Cal.m_PriorityTable[5][i] = -1;
		
		Cal.m_PriorityTable[5][6] = 0;
		////��6�в���
		
		for(i = 0;i < 6; i++)             //��8��
			Cal.m_PriorityTable[7][i] = -1;
		
		Cal.m_PriorityTable[7][7] = 0;
		
		
		
		
		//���������������ȱ��еĶ�Ӧ�±�
		Cal.m_OperatorIndex['+'] = 0;
		Cal.m_OperatorIndex['-'] = 1;
		Cal.m_OperatorIndex['*'] = 2;
		Cal.m_OperatorIndex['/'] = 3;
		Cal.m_OperatorIndex['^'] = 4;
		Cal.m_OperatorIndex['('] = 5;
		Cal.m_OperatorIndex[')'] = 6;
		Cal.m_OperatorIndex['#'] = 7;
	
		
		
		
		Cal.m_bPTCreated = true;
		//return true;
}