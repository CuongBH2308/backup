// Calculator.h: interface for the CCalculator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCULATOR_H__31A4901A_F28F_4A84_A93D_51CD008A9401__INCLUDED_)
#define AFX_CALCULATOR_H__31A4901A_F28F_4A84_A93D_51CD008A9401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "LogicWordAnalyser.h" //若加入此头文件,出现类定义错误

//#include "PriorityTable.h"

#include<map>
#include<string>
#include<cmath>
using namespace std;


class CWordAnalyser;
class CSyntaxAnalyser;
class CPriorityTable;

const int MaxWordNum = 100;   //最大单词数
const int MaxWordLength = 100; //单词最大长度
const int MaxOperatorNum = 20; //最大运算符个数
const int MaxExpLength = 100;  //最长表达式长度
const double EPSILON = 0.00001; //极小正数



/////////////////////////////////////////////

//Calculate 函数返回值
const int SUCCESSED = 0;  //计算成功
const int SYNTAX_ERR = 1; //语法错误
const int WORD_ERR  =  2;//词法错误
const int NO_VALUE = 3;   //变量没有值
const int OPERATOR_ERR = 4; //操作符错误


//operate函数表错误的返回值
const double OPERATE_ERR = -1000000.000f;
class CCalculator  
{

//友元类
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

	
	int Calculate(bool& bResult);//计算逻辑表达式

	int Calculate(double& dResult);//计算算术表达式


	void SetExpression(char* Expression);

	//设置词法分析器,语法分析器,优先级表
	void SetAnalyser(CWordAnalyser& CWA,CSyntaxAnalyser& CSA,CPriorityTable& CPT);

    //增加变量
	bool AddVariable(char* Var,double dVal = 0.0);

	//设置变量值
	bool SetVarValue(char* Var,double dVal);

	//删除变量
	bool DeleteVar(char* Var);
	

protected:
	//单步计算  for logic
	char Operate(char Operator,char Fir,char Sec);

	char Operate(char Operator,double Fir,double Sec);
    

	//单步计算：算术运算，注意与上一个函数参数顺序不同
	double Operate(double Fir,char Operator,double Sec);

	//通过查找优先级表找到其优先关系
	int ComPare(char Fir,char Sec);


	void Init();//初始化数据成员


	bool IsAlpha(char ch);






private:

	//若使用引用必须在初始化列表进行初始化,不太灵活
	//这里用指针
	CWordAnalyser*  m_pWordAnalyser;    //词法分析器
	CSyntaxAnalyser* m_pSyntaxAnalyser; //语法分析器
	CPriorityTable*  m_pPriorityTable;  //优先级表


	//用来标志各个阶段是否完成
	bool m_bWASucceed;
	bool m_bSASucceed;
	bool m_bPTCreated;

private:

	char m_strExp[MaxExpLength];  //表达式

	char m_Words[MaxWordNum][MaxWordLength];//单词表
	int  m_WordsAttribute[MaxWordNum];      //单词属性表 
	int m_nNumWords;                        //单词个数
	
	
	int  m_PriorityTable[MaxOperatorNum][MaxOperatorNum]; //算符优先级表
	map<char,int>  m_OperatorIndex;    //操作符--下标 对应表
	


	map<string,double> m_vars; //变量名与值



	char m_cResult;   //最终结果:t or f



};

#endif // !defined(AFX_CALCULATOR_H__31A4901A_F28F_4A84_A93D_51CD008A9401__INCLUDED_)





















