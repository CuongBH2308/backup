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
	//一张特定的优先表,没有什么灵活性.
	int i,j;
	m_nTableSize = 8;
	for( i = 0; i < m_nTableSize; i++)
		for( j = 0; j<m_nTableSize; j++)
			Cal.m_PriorityTable[i][j] = 1;                  //填充默认关系  大于
		
		
		for(i = 2;i < 6; i++)   //第0行
			Cal.m_PriorityTable[0][i] = -1;
		
		for(i = 2;i < 6; i++)   //第1行
			Cal.m_PriorityTable[1][i] = -1;
		
	
		Cal.m_PriorityTable[2][4] = Cal.m_PriorityTable[2][5] = -1;  //第3行
		
		Cal.m_PriorityTable[3][4] = Cal.m_PriorityTable[3][5] = -1; //第4行
		
		Cal.m_PriorityTable[4][4] = Cal.m_PriorityTable[4][5] = -1; //第5行
		
		for(i = 0;i < 6; i++)             //第6行
			Cal.m_PriorityTable[5][i] = -1;
		
		Cal.m_PriorityTable[5][6] = 0;
		////第6行不变
		
		for(i = 0;i < 6; i++)             //第8行
			Cal.m_PriorityTable[7][i] = -1;
		
		Cal.m_PriorityTable[7][7] = 0;
		
		
		
		
		//建立操作符在优先表中的对应下标
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