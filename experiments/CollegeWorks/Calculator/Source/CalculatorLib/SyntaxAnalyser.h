// SyntaxAnalyser.h: interface for the CSyntaxAnalyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNTAXANALYSER_H__A947414F_B3E3_470F_9ADE_2A52A3BF6409__INCLUDED_)
#define AFX_SYNTAXANALYSER_H__A947414F_B3E3_470F_9ADE_2A52A3BF6409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Calculator.h"
#include<string>

class CSyntaxAnalyser  
{
public:
	CSyntaxAnalyser();
	virtual ~CSyntaxAnalyser();

public:
	virtual bool AnalyseSyntax(CCalculator& Cal) = 0;//�﷨����


protected:
	//�����ݹ�����﷨����������������Ӵ��ศ�����������ӿڲ���
	virtual bool E(CCalculator& Cal) = 0;  //һ�������ʵ�����������,��Щ����Ҫ�ڲ�ͬ�����ඨ��
	virtual bool E_(CCalculator& Cal) = 0;


protected:

	int m_WordIndex;//��ǰ�����±�

	bool m_bResult;//��������ֵ����ʱδ��

};

#endif // !defined(AFX_SYNTAXANALYSER_H__A947414F_B3E3_470F_9ADE_2A52A3BF6409__INCLUDED_)
