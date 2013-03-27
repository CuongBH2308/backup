#ifndef MAINDEDUCE_H
#define MAINDEDUCE_H


#include<map>
#include<string>
#include "ado.h"
#include "LogicCal.h"
#include "LogicLikeCal.h"

//#include "ModelView.h"

using namespace std;



class CMalfuncDeduce  
{

//constructors and destructors
public:
	CMalfuncDeduce();
	~CMalfuncDeduce();

	


//main functions
public:
	/*1 规则推理  RegularDeduce
		2 模糊推理  BlurDeduce
		3 信息融合  InfoFuseDeduce
		4 神经网络  NNDeduce
		5 推理      Deduce*/
	//bool RegularDeduce(int& StartNode); //规则推理

//	bool BlurDeduce(int &StartNode); //模糊推理

//	bool FuseDeduce(int &StartNode); //融合推理

	



//help functions
public:
	bool GetRecordSet(CString str);//获取数据集

//	bool SetDataFromInput(int nodeId);//用户输入数据,并存入数据库
	bool SetDataFromDB(int nodeId);   //从数据库得到数据

	bool RegDeduce1Node(int& nodeId,int& ruleid,CString& strrule,int& outnodeid);   //推理一个结点:它可能有多条规则,in:检测点 out:下一个错误点

	bool BlurDeduce1Node(int& nodeId,int& ruleid,CString& strrule,int& outnodeid);   //推理一个结点:它可能有多条规则,in:检测点 out:下一个错误点

//	bool FuseDeduce1Node(int& nodeId);    //融合,推理一个结点:它可能有多条规则(模糊融合,DS融合),in:检测点 out:下一个错误点
//	bool GetFuseID(int& FuseID,int nodeId,int type);//type:1 bf,2 ds,3 bp.取得对应结点,融合类型的FuseID
	

	
	

//data members
private:
	map<string,double> m_datas;  //当前结点数据(用于规则推理,模糊推理)

	CADORecordset m_Recordset;   //数据集

	CLogicLikeCal m_BlurCal;       //calculate the blur expression 模糊推理
	

	CLogicCal     m_RegCal;        //calculate the regular expression 规则推理



	CString       m_strOutput;      //输出提示信息

	

	


};

bool SetParaTable(map<string,int>& ParaTable);//征兆数据类型ID与符号名的对应

#endif