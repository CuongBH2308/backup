#ifndef _ICALCULATER_H_
#define _ICALCULATER_H_

#include<string>
#include<vector>
#include<map>
#include<iostream>
#include <stack>
#include<ctype.h>
#include <math.h>
#include <algorithm>


using namespace std;
const int ERR_NOEXIST = 10000;
const double EPSILON = 0.00001;
typedef pair <string, double> SdPair;

class ICalculater
{
public:
	//ICalculater(void);

	//单参数构造函数,声明为explicit以防止隐式转换
	//explicit ICalculater(string strExp);

	//virtual ~ICalculater(void);
	
public:
	//从外界获取一个字符串作为分析和计算的对象
	virtual void SetExpression(string strExp) = 0;

	//检查表达式是否符合一定的格式,若不符合,返回false,否则将其按要求格式化并返回true
	virtual bool CheckAndFormat(string strExp = "")= 0;

	//核对变量名,若错误返回false,否则代入变量值.若为逻辑表达式,则再进一步求出关系表达式的值
	virtual bool PostFixLize() = 0;

	//算术表达式的值为参数,逻辑表达式的值为返回值
	virtual bool Calculate(double &value) = 0;

	

public:

	//增加一个参数变量名,并赋值
	virtual void AddPara(string strpara,double dbValue = 0.0) = 0;
    
	//删除一个参数变量名
	virtual void DelPara(string strpara) = 0;

	//设置给定参数的值
	virtual void SetParaValue(string strpara,double dbValue) = 0;


};

#endif
