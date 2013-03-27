// BlurFuser.h: interface for the CBlurFuser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLURFUSER_H__F5A18FE8_87F0_412E_8133_EE8167FABC4A__INCLUDED_)
#define AFX_BLURFUSER_H__F5A18FE8_87F0_412E_8133_EE8167FABC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const int MaxNodes = 50;
const int MaxSensors = 50;
const int MaxNameLen = 5;

class CBlurFuser  
{
public:
	CBlurFuser();
	virtual ~CBlurFuser();

	//�������еļ����Խ�������ж�,�Ƴ����Ͻ��
	virtual bool FuseDeduce(int& OutNode,int FuseID);

//protected:
	
	//in:�ںϹ���� //out:�˹����õ��� ���-���Ŷ�
	bool GetNodes(int FuseID);
	
	//in:�ںϹ���� //out:�˹����õ��� ���������-������Ȩ��,���������-���������ֶ�
	bool GetSensors(int FuseID);
	
	/*
    ������������
	*	��ϵ������ĳ��λ�õ���������ֵ,��������
	*/
	
	
	//in:������,�������������(������������) out:��Ӧ������ֵ
	bool GetValueFromDB(int SensorOrder,int NodeOrder,double& x);
	
	
	//�ӶԻ�����������,���浽���ݿ���
	bool GetValueFromInput(int SensorOrder,int NodeOrder,double& x);
	
	//ͨ����Fuse_Node_Func_Table ��õ�������������
	bool GetFuncType(int FuseID,int NodeOrder,int SensorOrder,int& FuncType);//���
	
	//�����ϵ����
	bool CalRelationMatrix(int FuseID);
	
	
	//ģ����:����X����
	bool FuseLize();
	
	
	//�Խ�����е�λ��
	bool NomorLize();

    //��ý�������ֵ
	bool GetZYZ(int nodeid,double& zongyuezhi);
	
	


protected:

	int m_Nodes[MaxNodes]; //�����Ÿù����õ��Ľ���,�±��Ӧ�����,��0��ʼ
	int m_NodeNum; //������
	
	double m_Weight[MaxSensors];//ÿ����������Ȩ��,�±��Ӧ�����,��0��ʼ
	int m_SensorNum;//����������

	char m_SensorName[MaxSensors][MaxNameLen]; //ÿ��������������,��U1,I2

	double m_RMatrix[MaxSensors][MaxNodes];   //��ϵ����

	double m_dResult[MaxNodes];//ģ��/DS�ںϵĽ��:ÿ�����Ŀ��Ŷ�






	




};

#endif // !defined(AFX_BLURFUSER_H__F5A18FE8_87F0_412E_8133_EE8167FABC4A__INCLUDED_)
