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

	//一张特定的优先表,没有什么灵活性.
	int i,j;
	m_nTableSize = 9;
	for( i = 0; i < m_nTableSize; i++)
		for( j = 0; j<m_nTableSize; j++)
			Cal.m_PriorityTable[i][j] = 1;                  //填充默认关系  大于
		
		
		for(i = 1;i < 7; i++)   //第0行
			Cal.m_PriorityTable[0][i] = -1;
		
		for(i = 2;i < 7; i++)   //第1行
			Cal.m_PriorityTable[1][i] = -1;
		
		for(i = 3;i < 7; i++)   //第2行
			Cal.m_PriorityTable[2][i] = -1;
		
		Cal.m_PriorityTable[3][5] = Cal.m_PriorityTable[3][6] = -1;  //第3行
		
		Cal.m_PriorityTable[4][5] = Cal.m_PriorityTable[4][6] = -1; //第4行
		
		Cal.m_PriorityTable[5][5] = Cal.m_PriorityTable[5][6] = -1; //第5行
		
		for(i = 0;i < 7; i++)             //第6行
			Cal.m_PriorityTable[6][i] = -1;
		
		Cal.m_PriorityTable[6][7] = 0;
		////第7行不变
		
		for(i = 0;i < 7; i++)             //第8行
			Cal.m_PriorityTable[8][i] = -1;
		
		Cal.m_PriorityTable[8][8] = 0;
	



		//建立操作符在优先表中的对应下标
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