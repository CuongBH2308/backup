// WordAnalyser.h: interface for the CWordAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDANALYSER_H__61377600_B4A5_42CD_A709_3140B48E69DD__INCLUDED_)
#define AFX_WORDANALYSER_H__61377600_B4A5_42CD_A709_3140B48E69DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Calculator.h"
//class CCalculator;  //������



class CWordAnalyser  
{
	
public:
	CWordAnalyser();
	//CWordAnalyser(char* Expression,CCalculator& Cal);

	virtual ~CWordAnalyser();


public:
	//���๲�ã��ڻ���ʵ��
	bool IsNumber(char ch);//�Ƿ�����
	
	bool IsAlpha(char ch);// �Ƿ���ĸ


public:
	//���麯�������ɳ�����
	virtual	bool IsOperator(char ch) = 0;  //�Ƿ�涨�Ĳ���������ͬ�ı��ʽ��������ͬ��Ҫ�������ﶨ��

	virtual	bool GenerateWord(CCalculator& Cal) = 0; //����һ�����ʡ�����ͬ�ı��ʽ�������ʷ�����ͬ��Ҫ�������ﶨ��

	virtual bool AnalyseWords(char* Expression,CCalculator& Cal) = 0;  //�ʷ�������������ȷ,������������,������true


protected:
	int   m_CurrentWordNum;//��ǰ������

	char* m_pCurrentLocation ;//���ʽ�е�ǰ�ַ�

	char* m_pLastLocation;    //�ϴ�λ��

	char m_strExpression[MaxExpLength];  //���ʽ

	
};

#endif // !defined(AFX_WORDANALYSER_H__61377600_B4A5_42CD_A709_3140B48E69DD__INCLUDED_)





















