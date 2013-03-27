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

//����	virtual bool PostFixLize(int nodenum);������ͬ������ICalculater����

class CLogicLikeCal //: public ICalculater  
{
public:
	CLogicLikeCal();
	explicit CLogicLikeCal(string strExp);
	virtual ~CLogicLikeCal();

public:
	//������ȡһ���ַ�����Ϊ�����ͼ���Ķ���
	virtual void SetExpression(string strExp) ;
	
	//�����ʽ�Ƿ����һ���ĸ�ʽ,��������,����false,�����䰴Ҫ���ʽ��������true
	virtual bool CheckAndFormat(string strExp = "");
	
	//�˶Ա�����,�����󷵻�false,����������ֵ.��Ϊ�߼����ʽ,���ٽ�һ�������ϵ���ʽ��ֵ
	virtual bool PostFixLize(int nodenum);
	
	//�������ʽ��ֵΪ����,�߼����ʽ��ֵΪ����ֵ
	virtual bool Calculate(double &value) ;
	
	
	//����һ������������,����ֵ
	virtual void AddPara(string strpara,double dbValue = 0.0);
	
	//ɾ��һ������������
	virtual void DelPara(string strpara);
	
	//���ø���������ֵ
	virtual void SetParaValue(string strpara,double dbValue);

	//���� all paramenters and its values
	void SetParas(map<string,double> Paras);

private:
	bool IsAccept(char ch);//���ʽ�е��ַ��Ƿ�Ϊ�Ϸ��ַ�
	bool CheckRegulation();//check the cepression's regulation
	bool IsRpfunction(string::iterator iter);// to see whether the char the iterator 
	                                         //points is represent a function.
	bool IsLogic(char ch);// is ch a logical operator,not include !
	bool IsRelation(char ch); // is ch a Relation operator,<,>,=
	



	bool LogicLize(int nodenum);//calculate the function's value 
	int isp(char c);//in stack priority:ջ��������
	int icp(char c);//in coming priority:ջ��������


	bool Get2Operands(char &cLeft,char &cRight);//pop two operand from the stack,used for binary operator
	void AddOperand(char c);
	bool CLogicLikeCal::SingleCalculate(char op);


private:
	string m_strExp;//the calculate expression
	map<string,double> m_Paras;//paramenters and its values
	
	stack<char> m_sOperate;//save operates n alter ��׺ to ��׺,�߼������
	stack<char> m_sOperand;//save operands in calculate the resulti  ��1 or 0
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




bool SetParaTable(map<string,int>& ParaTable);//������������ID��������Ķ�Ӧ

bool GetParasFromDB(int nodenum,int fuctype,int datatype ,Paras& paras);





HRESULT InitlizeCOM();

HRESULT ClearCOM();

bool FunctionValue(int nodenum,int fuctype,int datatype,double x,double& dresult);

#endif // !defined(AFX_LOGICLIKECAL_H__A185FF4C_01C2_4128_99F4_7F94992E45CE__INCLUDED_)





















