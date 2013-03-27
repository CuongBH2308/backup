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

	//���������캯��,����Ϊexplicit�Է�ֹ��ʽת��
	//explicit ICalculater(string strExp);

	//virtual ~ICalculater(void);
	
public:
	//������ȡһ���ַ�����Ϊ�����ͼ���Ķ���
	virtual void SetExpression(string strExp) = 0;

	//�����ʽ�Ƿ����һ���ĸ�ʽ,��������,����false,�����䰴Ҫ���ʽ��������true
	virtual bool CheckAndFormat(string strExp = "")= 0;

	//�˶Ա�����,�����󷵻�false,����������ֵ.��Ϊ�߼����ʽ,���ٽ�һ�������ϵ���ʽ��ֵ
	virtual bool PostFixLize() = 0;

	//�������ʽ��ֵΪ����,�߼����ʽ��ֵΪ����ֵ
	virtual bool Calculate(double &value) = 0;

	

public:

	//����һ������������,����ֵ
	virtual void AddPara(string strpara,double dbValue = 0.0) = 0;
    
	//ɾ��һ������������
	virtual void DelPara(string strpara) = 0;

	//���ø���������ֵ
	virtual void SetParaValue(string strpara,double dbValue) = 0;


};

#endif
