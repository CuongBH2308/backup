#ifndef LOGICCAL_H
#define LOGICCAL_H
#include "ICalculater.h"



class CLogicCal :public ICalculater
{
public:
	CLogicCal(void);
	explicit CLogicCal(string strExp);

	virtual ~CLogicCal(void);

public:
	//从外界获取一个字符串作为分析和计算的对象
	virtual void SetExpression(string strExp) ;

	//检查表达式是否符合一定的格式,若不符合,返回false,否则将其按要求格式化并返回true
	virtual bool CheckAndFormat(string strExp = "");

	//核对变量名,若错误返回false,否则代入变量值.若为逻辑表达式,则再进一步求出关系表达式的值
	virtual bool PostFixLize();

	//算术表达式的值为参数,逻辑表达式的值为返回值
	virtual bool Calculate(double &value ) ;


	//增加一个参数变量名,并赋值
	virtual void AddPara(string strpara,double dbValue = 0.0);

	//删除一个参数变量名
	virtual void DelPara(string strpara);

	//设置给定参数的值
	virtual void SetParaValue(string strpara,double dbValue);

	//由一个map<string,double>设置m_Paras
	virtual void SetParas(map<string,double> Paras);



private:
	bool IsAccept(char ch);//to see if ch can be accepted
	bool IsRelation(char ch);//to see if ch is a relation operator
	bool IsLogic(char ch); //to see if ch is  a logic operator
	bool CheckRegulation();//check the cepression's regulation

	bool LogicLize();//calculate the sub relation operators
	char Compare(double left,double right,string op);//compare two doubles ,return '1' if left op right ,otherwise '0'

	int isp(char c);//in stack priority:栈内优先数
	int icp(char c);//in coming priority:栈外优先数

	void AddOperand(char c);//used in calculate,put an operand in the stack
	bool Get1Operand(char &cOperand);//pop an operand from the stack,used for unary operator
	bool Get2Operands(char &cLeft,char &cRight);//pop two operand from the stack,used for binary operator
	bool SingleCalculate(char op);//calculate by one operator



private:
	string m_strExp;//the calculate expression
	map<string,double> m_Paras;//paramenters and its values

	stack<char> m_sOperate;//save operates n alter 中缀 to 后缀,逻辑运算符
	stack<char> m_sOperand;//save operands in calculate the resulti  放1 or 0
};

#endif
	
