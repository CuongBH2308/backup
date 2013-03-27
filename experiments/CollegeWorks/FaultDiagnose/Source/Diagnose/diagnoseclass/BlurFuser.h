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

	//进行所有的计算后对结果进行判断,推出故障结点
	virtual bool FuseDeduce(int& OutNode,int FuseID);

//protected:
	
	//in:融合规则号 //out:此规则用到的 编号-结点号对
	bool GetNodes(int FuseID);
	
	//in:融合规则号 //out:此规则用到的 传感器编号-传感器权重,传感器编号-传感器名字对
	bool GetSensors(int FuseID);
	
	/*
    以下两个函数
	*	关系矩阵中某个位置的征兆数据值,函数类型
	*/
	
	
	//in:结点序号,传感器类型序号(征兆数据类型) out:对应的数据值
	bool GetValueFromDB(int SensorOrder,int NodeOrder,double& x);
	
	
	//从对话框输入数据,并存到数据库中
	bool GetValueFromInput(int SensorOrder,int NodeOrder,double& x);
	
	//通过查Fuse_Node_Func_Table 表得到隶属函数类型
	bool GetFuncType(int FuseID,int NodeOrder,int SensorOrder,int& FuncType);//序号
	
	//计算关系矩阵
	bool CalRelationMatrix(int FuseID);
	
	
	//模糊化:向量X矩阵
	bool FuseLize();
	
	
	//对结果进行单位化
	bool NomorLize();

    //获得结点的总阈值
	bool GetZYZ(int nodeid,double& zongyuezhi);
	
	


protected:

	int m_Nodes[MaxNodes]; //用来放该规则用到的结点号,下标对应其序号,从0开始
	int m_NodeNum; //结点个数
	
	double m_Weight[MaxSensors];//每个传感器的权重,下标对应其序号,从0开始
	int m_SensorNum;//传感器个数

	char m_SensorName[MaxSensors][MaxNameLen]; //每个传感器的名字,如U1,I2

	double m_RMatrix[MaxSensors][MaxNodes];   //关系矩阵

	double m_dResult[MaxNodes];//模糊/DS融合的结果:每个结点的可信度






	




};

#endif // !defined(AFX_BLURFUSER_H__F5A18FE8_87F0_412E_8133_EE8167FABC4A__INCLUDED_)
