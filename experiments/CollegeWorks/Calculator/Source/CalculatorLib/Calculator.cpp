// Calculator.cpp: implementation of the CCalculator class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Calculator.h"
#include "PriorityTable.h"
#include "SyntaxAnalyser.h"
#include "WordAnalyser.h"
#include "stack.h"
//#include "LogicWordAnalyser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCalculator::CCalculator()
{
	Init();
}

CCalculator::CCalculator(char* Expression){

	strcpy(m_strExp,Expression);
	Init();
}


CCalculator::CCalculator(CWordAnalyser& CWA,CSyntaxAnalyser& CSA,CPriorityTable& CPT,char* Expression)
:m_bSASucceed(false),m_bWASucceed(false),m_bPTCreated(false),
m_pWordAnalyser(&CWA),m_pSyntaxAnalyser(&CSA),m_pPriorityTable(&CPT),
m_nNumWords(0)
{
	strcpy(m_strExp,Expression);
	Init();

}

CCalculator::~CCalculator()
{

}

//单词表的初始化
void CCalculator::Init()
{
	int i,j;
	for(i = 0; i<MaxWordNum ; i++) //初始
		
	{
		for(j = 0; j<MaxWordLength ; j++)
			m_Words[i][j] = '\0';
		
		m_WordsAttribute[i] = 0;     //属性表置0,表示数
		
	}

	//m_vars.clear();
	m_OperatorIndex.clear();

}

bool CCalculator::AddVariable(char* Var,double dVal){
	if(m_vars.find(Var)==m_vars.end()){
        char *Var1 = Var;

		while(*Var1!='\0'){  //变量名应该为字母
			if(!IsAlpha(*Var))
				return false;
			Var1++;
		}

		m_vars[Var] = dVal;
		return true;
	}

	else
		return false;  //变量名已经存在
		
}


bool CCalculator::SetVarValue(char* Var,double dVal){
	if(m_vars.find(Var)!=m_vars.end()){
		m_vars[Var] = dVal;
		return true;
	}
	
	else
		return false;  //变量名不存在
	
}

bool CCalculator::DeleteVar(char* Var)
{
	map<string,double>::iterator iter = m_vars.find(Var);
	if(iter!=m_vars.end()){
		m_vars.erase(iter);
		return true;
	}
	
	else
		return false;  //变量名不存在

}

bool CCalculator::IsAlpha(char ch){
	if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z'))
		return true;
	return false;
}

void CCalculator::SetExpression(char* Expression)
{
	strcpy(m_strExp,Expression);
	
}

void CCalculator::SetAnalyser(CWordAnalyser& CWA,CSyntaxAnalyser& CSA,CPriorityTable& CPT){
	Init();
	m_pWordAnalyser = &CWA;
	m_pSyntaxAnalyser = &CSA;
	m_pPriorityTable = &CPT;
}


int CCalculator::ComPare(char Fir,char Sec){
	if(m_OperatorIndex.find(Fir)!=m_OperatorIndex.end()
		&&m_OperatorIndex.find(Sec)!=m_OperatorIndex.end()){
		return m_PriorityTable[m_OperatorIndex[Fir]][m_OperatorIndex[Sec]];
	}
	else
		return -2;
}

////////////////////////////////逻辑运算//////////////////////////////////////////////////////

//逻辑运算中的求关系表达式
char CCalculator::Operate(char Operator,double Fir,double Sec){

	char cResult;
	switch (Operator)
	{
	case '>':
		if(Fir>Sec) cResult = 't';
		else        cResult = 'f';
		break;
		
	case '<':
		if(Fir<Sec) cResult = 't';
		else        cResult = 'f';
		break;
		
	case '=':
		if((Fir-Sec)<EPSILON&&(Fir-Sec)>-EPSILON)   cResult = 't';
		else        cResult = 'f';
		break;
		
	default:cResult = 'w';//错误标志
		break;
		
	}
	return cResult;
}


//逻辑运算中求逻辑运算
char CCalculator::Operate(char Operator,char Fir,char Sec){
	char cResult;
	switch (Operator)
	{
	case '&':
		if((Fir == 't')&&(Sec == 't')) cResult = 't';
		else                       cResult = 'f';
		break;
		
	case '|':
		if((Fir == 't')||(Sec == 't')) cResult = 't';
		else                       cResult = 'f';
		break;
	case '!':
		if(Sec == 'f')  cResult = 't';
		else            cResult = 'f';
		break;
		
	default:cResult = 'w';
		break;
		
	}
	
	return cResult;
}


//计算逻辑表达式
int CCalculator::Calculate(bool& bResult){

	bResult = false;//初始设置为 false

	if(!m_pWordAnalyser->AnalyseWords(m_strExp,*this))   //词法分析,构造单词表
		return WORD_ERR;         //语法错误

	if(!m_pSyntaxAnalyser->AnalyseSyntax(*this))         //语法分析
		return SYNTAX_ERR;


	m_pPriorityTable->CreatePriorityTable(*this);         //构造优先级表
	

	
	
	CStack<char> CharStack;            //操作符栈
	
	CStack<double>  rValueStack;       //关系运算操作数栈
	
	CStack<char>  lValueStack;         //逻辑运算操作数栈，t or f
	
	CharStack.Push('#');
	
	int WordIndex = 0;
	
	char top;
	CharStack.GetTop(top);


	while(!(strcmp(m_Words[WordIndex],"#") == 0 && top == '#')) //是否读完单词且操作符栈为空
	{

		/*1  实数进实数栈*/

		if(m_WordsAttribute[WordIndex] == 0)//数值
		{
			double Value = atof(m_Words[WordIndex]);
			rValueStack.Push(Value);
			WordIndex ++;
			
		}
		
		else if(m_WordsAttribute[WordIndex] == 1)  //变量
		{
			if(m_vars.find(m_Words[WordIndex])!=m_vars.end()){//若变量存在，取其值　
				
				double Value = m_vars[m_Words[WordIndex]];
				rValueStack.Push(Value);
				WordIndex ++;
			}
			
			else{
				return NO_VALUE;  //变量未赋值
				
			}
			
		}
		
		/*2  逻辑值进逻辑栈*/

		else if(m_WordsAttribute[WordIndex] == 3)//逻辑值
		{
			char Value =(m_Words[WordIndex][0]);
			lValueStack.Push(Value);
			WordIndex ++;
			
		}

		/*3  操作符按情况进行归约或移进*/

		else          //操作符
		{
			switch (ComPare(top,(m_Words[WordIndex][0])))
			{
			case -1://移进
				CharStack.Push(m_Words[WordIndex][0]);
				WordIndex ++;
				break;

			case 0: //() 消去括号对 ## 对
				CharStack.Pop(top);
				WordIndex ++;
				break;
				
			case 1:   //归约(计算)　　这里没有WordIndex ++，当前单词在下一轮中还要用
				{
					double dFirNum ,dSecNum;
					char cFirOp,cSecOp,cResult;
					char Operator;
					
					CharStack.Pop(Operator);//前面用的CharStack.GetTop
					
					if(Operator == '>'||Operator == '<' || Operator == '='){
						
						rValueStack.Pop(dSecNum);
						rValueStack.Pop(dFirNum);
						
						cResult = Operate(Operator,dFirNum,dSecNum); //关系运算
					//	if(cResult = 'w')  return false;
						lValueStack.Push(cResult);
					}
					
					else if(Operator == '&'||Operator == '|' || Operator == '!'){
						
						lValueStack.Pop(cSecOp);
						lValueStack.Pop(cFirOp);
						
						cResult = Operate(Operator,cFirOp,cSecOp);  //逻辑运算
						lValueStack.Push(cResult);
					}

					else 
						return OPERATOR_ERR;

					break;
				}//case 1
				
				
			default	:
				break;
			}//switch
		}//else
		
		
		CharStack.GetTop(top);  //取下一个操作符

	}//while
	
	lValueStack.GetTop(m_cResult );//很明显,逻辑栈中最后的值为最后结果
	

	if(m_cResult == 't')  bResult = true;
	else bResult = false;

	return SUCCESSED;
}




////////////////////////////////算术运算////////////////////////////////////////////////////////////

//算术运算中单步运算
double CCalculator::Operate(double Fir,char Operator,double Sec)
{
	double dResult;
	switch (Operator)
	{
	case '+':
		dResult = Fir+Sec;
		break;
		
	case '-':
		dResult = Fir-Sec;
		break;
	case '*':
		dResult = Fir*Sec;
		break;
	case '/':
		dResult = Fir/Sec;
		break;
	case '^':
		dResult = pow(Fir,(int)Sec);
		break;
	default:dResult = OPERATE_ERR;
		break;
		
	}
	
	return dResult;
}


int CCalculator::Calculate(double& dResult)
{	
	if(!m_pWordAnalyser->AnalyseWords(m_strExp,*this))   //词法分析,构造单词表
		return WORD_ERR;         //语法错误
	
	if(!m_pSyntaxAnalyser->AnalyseSyntax(*this))         //语法分析
		return SYNTAX_ERR;
	
	
	m_pPriorityTable->CreatePriorityTable(*this);         //构造优先级表
	
	
	
	
	CStack<char> CharStack;           //操作符栈
	CStack<double>  ValueStack;       //操作数栈
	
	CharStack.Push('#');
	
	int WordIndex = 0;
	
	char top;
	CharStack.GetTop(top);
	while(!(strcmp(m_Words[WordIndex],"#") == 0 && top == '#'))
	{
		if(m_WordsAttribute[WordIndex] == 0)//操作数
		{
			double Value = atof(m_Words[WordIndex]);
			ValueStack.Push(Value);
			WordIndex ++;
			
		}

		else if(m_WordsAttribute[WordIndex] == 1)  //变量
		{
			if(m_vars.find(m_Words[WordIndex])!=m_vars.end()){//若变量存在，取其值　
				
				double Value = m_vars[m_Words[WordIndex]];
				ValueStack.Push(Value);
				WordIndex ++;
			}
			
			else{
				return NO_VALUE;  //变量未赋值
				
			}
			
		}
		
		
		else          //操作符
		{
			switch (ComPare(top,(m_Words[WordIndex][0])))
			{
			case -1://移进
				CharStack.Push(m_Words[WordIndex][0]);
				WordIndex ++;
				break;
				
			case 0: //() 消去括号对 ## 对
				CharStack.Pop(top);
				WordIndex ++;
				break;
				
			case 1:   //归约(计算)　　这里没有WordIndex ++，当前单词在下一轮中还要用
				{
					double nFirNum ,nSecNum, nResult;
					char Operator;
					ValueStack.Pop(nSecNum);
					ValueStack.Pop(nFirNum);
					CharStack.Pop(Operator);
					nResult = Operate(nFirNum,Operator,nSecNum);
					ValueStack.Push(nResult);
					break;
				}
			default	:
				break;
			}//end switch
		}
		
		
		CharStack.GetTop(top);
	}
	
	ValueStack.GetTop(dResult );

	return SUCCESSED;
}