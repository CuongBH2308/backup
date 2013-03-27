// Calculator.h: interface for the CCalculator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULATOR_H__31A4901A_F28F_4A84_A93D_51CD008A9401__INCLUDED_)
#define AFX_CALCULATOR_H__31A4901A_F28F_4A84_A93D_51CD008A9401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "LogicWordAnalyser.h" //�������ͷ�ļ�,�����ඨ�����

//#include "PriorityTable.h"

#include<map>
#include<string>
#include<cmath>
using namespace std;


class CWordAnalyser;
class CSyntaxAnalyser;
class CPriorityTable;

const int MaxWordNum = 100;   //��󵥴���
const int MaxWordLength = 100; //������󳤶�
const int MaxOperatorNum = 20; //������������
const int MaxExpLength = 100;  //����ʽ����
const double EPSILON = 0.00001; //��С����



/////////////////////////////////////////////

//Calculate ��������ֵ
const int SUCCESSED = 0;  //����ɹ�
const int SYNTAX_ERR = 1; //�﷨����
const int WORD_ERR  =  2;//�ʷ�����
const int NO_VALUE = 3;   //����û��ֵ
const int OPERATOR_ERR = 4; //����������


//operate���������ķ���ֵ
const double OPERATE_ERR = -1000000.000f;
class CCalculator  
{

//��Ԫ��
//friend class CWordAnalyser;
friend class CLogicPriorityTable;

friend class CLogicWordAnalyser;

friend class CLogicSyntaxAnalyser;

friend class CArithWordAnalyser;

friend class CArithSyntaxAnalyser;

friend class CArithPriorityTable;

public:
	CCalculator();
	CCalculator(char* Expression);
	CCalculator(CWordAnalyser& CWA,CSyntaxAnalyser& CSA,CPriorityTable& CPT,char* Expression);
	virtual ~CCalculator();

	
	int Calculate(bool& bResult);//�����߼����ʽ

	int Calculate(double& dResult);//�����������ʽ


	void SetExpression(char* Expression);

	//���ôʷ�������,�﷨������,���ȼ���
	void SetAnalyser(CWordAnalyser& CWA,CSyntaxAnalyser& CSA,CPriorityTable& CPT);

    //���ӱ���
	bool AddVariable(char* Var,double dVal = 0.0);

	//���ñ���ֵ
	bool SetVarValue(char* Var,double dVal);

	//ɾ������
	bool DeleteVar(char* Var);
	

protected:
	//��������  for logic
	char Operate(char Operator,char Fir,char Sec);

	char Operate(char Operator,double Fir,double Sec);
    

	//�������㣺�������㣬ע������һ����������˳��ͬ
	double Operate(double Fir,char Operator,double Sec);

	//ͨ���������ȼ����ҵ������ȹ�ϵ
	int ComPare(char Fir,char Sec);


	void Init();//��ʼ�����ݳ�Ա


	bool IsAlpha(char ch);






private:

	//��ʹ�����ñ����ڳ�ʼ���б���г�ʼ��,��̫���
	//������ָ��
	CWordAnalyser*  m_pWordAnalyser;    //�ʷ�������
	CSyntaxAnalyser* m_pSyntaxAnalyser; //�﷨������
	CPriorityTable*  m_pPriorityTable;  //���ȼ���


	//������־�����׶��Ƿ����
	bool m_bWASucceed;
	bool m_bSASucceed;
	bool m_bPTCreated;

private:

	char m_strExp[MaxExpLength];  //���ʽ

	char m_Words[MaxWordNum][MaxWordLength];//���ʱ�
	int  m_WordsAttribute[MaxWordNum];      //�������Ա� 
	int m_nNumWords;                        //���ʸ���
	
	
	int  m_PriorityTable[MaxOperatorNum][MaxOperatorNum]; //������ȼ���
	map<char,int>  m_OperatorIndex;    //������--�±� ��Ӧ��
	


	map<string,double> m_vars; //��������ֵ



	char m_cResult;   //���ս��:t or f



};

#endif // !defined(AFX_CALCULATOR_H__31A4901A_F28F_4A84_A93D_51CD008A9401__INCLUDED_)





















