// LogicLikeCal.h: interface for the CLogicLikeCal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICLIKECAL_H__A185FF4C_01C2_4128_99F4_7F94992E45CE__INCLUDED_)
#define AFX_LOGICLIKECAL_H__A185FF4C_01C2_4128_99F4_7F94992E45CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ado.h"
#include "ICalculater.h"

//由于	virtual bool PostFixLize(int nodenum);参数不同，不从ICalculater派生

class CLogicLikeCal //: public ICalculater  
{
public:
	CLogicLikeCal();
	explicit CLogicLikeCal(string strExp);
	virtual ~CLogicLikeCal();

public:
	//从外界获取一个字符串作为分析和计算的对象
	virtual void SetExpression(string strExp) ;
	
	//检查表达式是否符合一定的格式,若不符合,返回false,否则将其按要求格式化并返回true
	virtual bool CheckAndFormat(string strExp = "");
	
	//核对变量名,若错误返回false,否则代入变量值.若为逻辑表达式,则再进一步求出关系表达式的值
	virtual bool PostFixLize(int nodenum);
	
	//算术表达式的值为参数,逻辑表达式的值为返回值
	virtual bool Calculate(double &value) ;
	
	
	//增加一个参数变量名,并赋值
	virtual void AddPara(string strpara,double dbValue = 0.0);
	
	//删除一个参数变量名
	virtual void DelPara(string strpara);
	
	//设置给定参数的值
	virtual void SetParaValue(string strpara,double dbValue);

	//设置 all paramenters and its values
	void SetParas(map<string,double> Paras);

private:
	bool IsAccept(char ch);//表达式中的字符是否为合法字符
	bool CheckRegulation();//check the cepression's regulation
	bool IsRpfunction(string::iterator iter);// to see whether the char the iterator 
	                                         //points is represent a function.
	bool IsLogic(char ch);// is ch a logical operator,not include !
	bool IsRelation(char ch); // is ch a Relation operator,<,>,=
	



	bool LogicLize(int nodenum);//calculate the function's value 
	int isp(char c);//in stack priority:栈内优先数
	int icp(char c);//in coming priority:栈外优先数


	bool Get2Operands(char &cLeft,char &cRight);//pop two operand from the stack,used for binary operator
	void AddOperand(char c);
	bool CLogicLikeCal::SingleCalculate(char op);


private:
	string m_strExp;//the calculate expression
	map<string,double> m_Paras;//paramenters and its values
	
	stack<char> m_sOperate;//save operates n alter 中缀 to 后缀,逻辑运算符
	stack<char> m_sOperand;//save operands in calculate the resulti  放1 or 0
	vector<double> m_vecvalue;//used for store the value of the functions
	

};



typedef struct _paras{
	double para1;
    double para2;
	double para3;
    double para4;
	double para5;
    double para6;
} Paras;




bool SetParaTable(map<string,int>& ParaTable);//征兆数据类型ID与符号名的对应

bool GetParasFromDB(int nodenum,int fuctype,int datatype ,Paras& paras);





HRESULT InitlizeCOM();

HRESULT ClearCOM();

bool FunctionValue(int nodenum,int fuctype,int datatype,double x,double& dresult);

#endif // !defined(AFX_LOGICLIKECAL_H__A185FF4C_01C2_4128_99F4_7F94992E45CE__INCLUDED_)





















