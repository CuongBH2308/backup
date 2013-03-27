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
	//������ȡһ���ַ�����Ϊ�����ͼ���Ķ���
	virtual void SetExpression(string strExp) ;

	//�����ʽ�Ƿ����һ���ĸ�ʽ,��������,����false,�����䰴Ҫ���ʽ��������true
	virtual bool CheckAndFormat(string strExp = "");

	//�˶Ա�����,�����󷵻�false,����������ֵ.��Ϊ�߼����ʽ,���ٽ�һ�������ϵ���ʽ��ֵ
	virtual bool PostFixLize();

	//�������ʽ��ֵΪ����,�߼����ʽ��ֵΪ����ֵ
	virtual bool Calculate(double &value ) ;


	//����һ������������,����ֵ
	virtual void AddPara(string strpara,double dbValue = 0.0);

	//ɾ��һ������������
	virtual void DelPara(string strpara);

	//���ø���������ֵ
	virtual void SetParaValue(string strpara,double dbValue);

	//��һ��map<string,double>����m_Paras
	virtual void SetParas(map<string,double> Paras);



private:
	bool IsAccept(char ch);//to see if ch can be accepted
	bool IsRelation(char ch);//to see if ch is a relation operator
	bool IsLogic(char ch); //to see if ch is  a logic operator
	bool CheckRegulation();//check the cepression's regulation

	bool LogicLize();//calculate the sub relation operators
	char Compare(double left,double right,string op);//compare two doubles ,return '1' if left op right ,otherwise '0'

	int isp(char c);//in stack priority:ջ��������
	int icp(char c);//in coming priority:ջ��������

	void AddOperand(char c);//used in calculate,put an operand in the stack
	bool Get1Operand(char &cOperand);//pop an operand from the stack,used for unary operator
	bool Get2Operands(char &cLeft,char &cRight);//pop two operand from the stack,used for binary operator
	bool SingleCalculate(char op);//calculate by one operator



private:
	string m_strExp;//the calculate expression
	map<string,double> m_Paras;//paramenters and its values

	stack<char> m_sOperate;//save operates n alter ��׺ to ��׺,�߼������
	stack<char> m_sOperand;//save operands in calculate the resulti  ��1 or 0
};

#endif
	
