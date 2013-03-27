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
	/*1 ��������  RegularDeduce
		2 ģ������  BlurDeduce
		3 ��Ϣ�ں�  InfoFuseDeduce
		4 ������  NNDeduce
		5 ����      Deduce*/
	//bool RegularDeduce(int& StartNode); //��������

//	bool BlurDeduce(int &StartNode); //ģ������

//	bool FuseDeduce(int &StartNode); //�ں�����

	



//help functions
public:
	bool GetRecordSet(CString str);//��ȡ���ݼ�

//	bool SetDataFromInput(int nodeId);//�û���������,���������ݿ�
	bool SetDataFromDB(int nodeId);   //�����ݿ�õ�����

	bool RegDeduce1Node(int& nodeId,int& ruleid,CString& strrule,int& outnodeid);   //����һ�����:�������ж�������,in:���� out:��һ�������

	bool BlurDeduce1Node(int& nodeId,int& ruleid,CString& strrule,int& outnodeid);   //����һ�����:�������ж�������,in:���� out:��һ�������

//	bool FuseDeduce1Node(int& nodeId);    //�ں�,����һ�����:�������ж�������(ģ���ں�,DS�ں�),in:���� out:��һ�������
//	bool GetFuseID(int& FuseID,int nodeId,int type);//type:1 bf,2 ds,3 bp.ȡ�ö�Ӧ���,�ں����͵�FuseID
	

	
	

//data members
private:
	map<string,double> m_datas;  //��ǰ�������(���ڹ�������,ģ������)

	CADORecordset m_Recordset;   //���ݼ�

	CLogicLikeCal m_BlurCal;       //calculate the blur expression ģ������
	

	CLogicCal     m_RegCal;        //calculate the regular expression ��������



	CString       m_strOutput;      //�����ʾ��Ϣ

	

	


};

bool SetParaTable(map<string,int>& ParaTable);//������������ID��������Ķ�Ӧ

#endif