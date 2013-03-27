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

//���ʱ�ĳ�ʼ��
void CCalculator::Init()
{
	int i,j;
	for(i = 0; i<MaxWordNum ; i++) //��ʼ
		
	{
		for(j = 0; j<MaxWordLength ; j++)
			m_Words[i][j] = '\0';
		
		m_WordsAttribute[i] = 0;     //���Ա���0,��ʾ��
		
	}

	//m_vars.clear();
	m_OperatorIndex.clear();

}

bool CCalculator::AddVariable(char* Var,double dVal){
	if(m_vars.find(Var)==m_vars.end()){
        char *Var1 = Var;

		while(*Var1!='\0'){  //������Ӧ��Ϊ��ĸ
			if(!IsAlpha(*Var))
				return false;
			Var1++;
		}

		m_vars[Var] = dVal;
		return true;
	}

	else
		return false;  //�������Ѿ�����
		
}


bool CCalculator::SetVarValue(char* Var,double dVal){
	if(m_vars.find(Var)!=m_vars.end()){
		m_vars[Var] = dVal;
		return true;
	}
	
	else
		return false;  //������������
	
}

bool CCalculator::DeleteVar(char* Var)
{
	map<string,double>::iterator iter = m_vars.find(Var);
	if(iter!=m_vars.end()){
		m_vars.erase(iter);
		return true;
	}
	
	else
		return false;  //������������

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

////////////////////////////////�߼�����//////////////////////////////////////////////////////

//�߼������е����ϵ���ʽ
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
		
	default:cResult = 'w';//�����־
		break;
		
	}
	return cResult;
}


//�߼����������߼�����
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


//�����߼����ʽ
int CCalculator::Calculate(bool& bResult){

	bResult = false;//��ʼ����Ϊ false

	if(!m_pWordAnalyser->AnalyseWords(m_strExp,*this))   //�ʷ�����,���쵥�ʱ�
		return WORD_ERR;         //�﷨����

	if(!m_pSyntaxAnalyser->AnalyseSyntax(*this))         //�﷨����
		return SYNTAX_ERR;


	m_pPriorityTable->CreatePriorityTable(*this);         //�������ȼ���
	

	
	
	CStack<char> CharStack;            //������ջ
	
	CStack<double>  rValueStack;       //��ϵ���������ջ
	
	CStack<char>  lValueStack;         //�߼����������ջ��t or f
	
	CharStack.Push('#');
	
	int WordIndex = 0;
	
	char top;
	CharStack.GetTop(top);


	while(!(strcmp(m_Words[WordIndex],"#") == 0 && top == '#')) //�Ƿ���굥���Ҳ�����ջΪ��
	{

		/*1  ʵ����ʵ��ջ*/

		if(m_WordsAttribute[WordIndex] == 0)//��ֵ
		{
			double Value = atof(m_Words[WordIndex]);
			rValueStack.Push(Value);
			WordIndex ++;
			
		}
		
		else if(m_WordsAttribute[WordIndex] == 1)  //����
		{
			if(m_vars.find(m_Words[WordIndex])!=m_vars.end()){//���������ڣ�ȡ��ֵ��
				
				double Value = m_vars[m_Words[WordIndex]];
				rValueStack.Push(Value);
				WordIndex ++;
			}
			
			else{
				return NO_VALUE;  //����δ��ֵ
				
			}
			
		}
		
		/*2  �߼�ֵ���߼�ջ*/

		else if(m_WordsAttribute[WordIndex] == 3)//�߼�ֵ
		{
			char Value =(m_Words[WordIndex][0]);
			lValueStack.Push(Value);
			WordIndex ++;
			
		}

		/*3  ��������������й�Լ���ƽ�*/

		else          //������
		{
			switch (ComPare(top,(m_Words[WordIndex][0])))
			{
			case -1://�ƽ�
				CharStack.Push(m_Words[WordIndex][0]);
				WordIndex ++;
				break;

			case 0: //() ��ȥ���Ŷ� ## ��
				CharStack.Pop(top);
				WordIndex ++;
				break;
				
			case 1:   //��Լ(����)��������û��WordIndex ++����ǰ��������һ���л�Ҫ��
				{
					double dFirNum ,dSecNum;
					char cFirOp,cSecOp,cResult;
					char Operator;
					
					CharStack.Pop(Operator);//ǰ���õ�CharStack.GetTop
					
					if(Operator == '>'||Operator == '<' || Operator == '='){
						
						rValueStack.Pop(dSecNum);
						rValueStack.Pop(dFirNum);
						
						cResult = Operate(Operator,dFirNum,dSecNum); //��ϵ����
					//	if(cResult = 'w')  return false;
						lValueStack.Push(cResult);
					}
					
					else if(Operator == '&'||Operator == '|' || Operator == '!'){
						
						lValueStack.Pop(cSecOp);
						lValueStack.Pop(cFirOp);
						
						cResult = Operate(Operator,cFirOp,cSecOp);  //�߼�����
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
		
		
		CharStack.GetTop(top);  //ȡ��һ��������

	}//while
	
	lValueStack.GetTop(m_cResult );//������,�߼�ջ������ֵΪ�����
	

	if(m_cResult == 't')  bResult = true;
	else bResult = false;

	return SUCCESSED;
}




////////////////////////////////��������////////////////////////////////////////////////////////////

//���������е�������
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
	if(!m_pWordAnalyser->AnalyseWords(m_strExp,*this))   //�ʷ�����,���쵥�ʱ�
		return WORD_ERR;         //�﷨����
	
	if(!m_pSyntaxAnalyser->AnalyseSyntax(*this))         //�﷨����
		return SYNTAX_ERR;
	
	
	m_pPriorityTable->CreatePriorityTable(*this);         //�������ȼ���
	
	
	
	
	CStack<char> CharStack;           //������ջ
	CStack<double>  ValueStack;       //������ջ
	
	CharStack.Push('#');
	
	int WordIndex = 0;
	
	char top;
	CharStack.GetTop(top);
	while(!(strcmp(m_Words[WordIndex],"#") == 0 && top == '#'))
	{
		if(m_WordsAttribute[WordIndex] == 0)//������
		{
			double Value = atof(m_Words[WordIndex]);
			ValueStack.Push(Value);
			WordIndex ++;
			
		}

		else if(m_WordsAttribute[WordIndex] == 1)  //����
		{
			if(m_vars.find(m_Words[WordIndex])!=m_vars.end()){//���������ڣ�ȡ��ֵ��
				
				double Value = m_vars[m_Words[WordIndex]];
				ValueStack.Push(Value);
				WordIndex ++;
			}
			
			else{
				return NO_VALUE;  //����δ��ֵ
				
			}
			
		}
		
		
		else          //������
		{
			switch (ComPare(top,(m_Words[WordIndex][0])))
			{
			case -1://�ƽ�
				CharStack.Push(m_Words[WordIndex][0]);
				WordIndex ++;
				break;
				
			case 0: //() ��ȥ���Ŷ� ## ��
				CharStack.Pop(top);
				WordIndex ++;
				break;
				
			case 1:   //��Լ(����)��������û��WordIndex ++����ǰ��������һ���л�Ҫ��
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