// WordAnalyser.h: interface for the CWordAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDANALYSER_H__61377600_B4A5_42CD_A709_3140B48E69DD__INCLUDED_)
#define AFX_WORDANALYSER_H__61377600_B4A5_42CD_A709_3140B48E69DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Calculator.h"
//class CCalculator;  //类声明



class CWordAnalyser  
{
	
public:
	CWordAnalyser();
	//CWordAnalyser(char* Expression,CCalculator& Cal);

	virtual ~CWordAnalyser();


public:
	//子类共用，在基类实现
	bool IsNumber(char ch);//是否数字
	
	bool IsAlpha(char ch);// 是否字母


public:
	//纯虚函数，构成抽象类
	virtual	bool IsOperator(char ch) = 0;  //是否规定的操作符　不同的表达式操作符不同，要在子类里定义

	virtual	bool GenerateWord(CCalculator& Cal) = 0; //产生一个单词　，不同的表达式产生单词方法不同，要在子类里定义

	virtual bool AnalyseWords(char* Expression,CCalculator& Cal) = 0;  //词法分析　　若正确,产生单词序列,并返回true


protected:
	int   m_CurrentWordNum;//当前单词数

	char* m_pCurrentLocation ;//表达式中当前字符

	char* m_pLastLocation;    //上次位置

	char m_strExpression[MaxExpLength];  //表达式

	
};

#endif // !defined(AFX_WORDANALYSER_H__61377600_B4A5_42CD_A709_3140B48E69DD__INCLUDED_)





















