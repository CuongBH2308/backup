// BlurFuser.cpp: implementation of the CBlurFuser class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"

#include "BlurFuser.h"
#include "ado.h"
#include "LogicLikeCal.h"
//#include "DataInputDlg.h"
//#include "TroubleDiagnose.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CADODatabase GlDataBase;
extern map<string,int> g_ParaTable;  //��������������ID���������ݷ��ţ���U��I R��
/*extern */map<string,double> datas; //������ŵ�ǰ�������

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlurFuser::CBlurFuser():m_NodeNum(0),m_SensorNum(0)
{
	for(int i = 0;i<MaxNodes;i++)
		m_dResult[i] = 0.0;

}

CBlurFuser::~CBlurFuser()
{

}

bool CBlurFuser::GetNodes(int FuseID)
{
	CADORecordset  recordset(&GlDataBase);
	CString strQuery;
	strQuery.Format("select DISTINCT NodeOrder,NodeSN from Fuse_Node_Func_Table where FR_ID = %d",FuseID);

	recordset.SetQuery(strQuery);
	if(!recordset.Open()) //���޷��򿪼�¼��
		return false;


	int NodeOrder,NodeSN;


	while(!recordset.IsEOF()){
		recordset.GetFieldValue("NodeOrder",NodeOrder);
		recordset.GetFieldValue("NodeSN",NodeSN);
		m_Nodes[NodeOrder] = NodeSN;

		m_NodeNum++;
		recordset.MoveNext();
	}

	return true;
	


}


bool CBlurFuser::GetSensors(int FuseID)
{
	CADORecordset  recordset(&GlDataBase);
	CString strQuery;
	strQuery.Format("select SensorSN,SensorTP,SensorW from Fuse_Sensor_Table where FR_ID = %d",FuseID);
	
	recordset.SetQuery(strQuery);
	if(!recordset.Open()) //���޷��򿪼�¼��
		return false;
	
	
	int SensorSN;
	CString SensorTP;
	double SensorW;
	
	
	while(!recordset.IsEOF()){
		recordset.GetFieldValue("SensorSN",SensorSN);
		recordset.GetFieldValue("SensorTP",SensorTP);
		recordset.GetFieldValue("SensorW",SensorW);

		SensorTP.TrimRight();
		strcpy(m_SensorName[SensorSN],SensorTP.GetBuffer(0));
		m_Weight[SensorSN] = SensorW;

		m_SensorNum++;
		recordset.MoveNext();
	}
	
	return true;
	
}

//��data_Table�л���Ա�������
bool CBlurFuser::GetValueFromDB( int SensorOrder,int NodeOrder,double& x)
{

	CADORecordset  recordset(&GlDataBase);
	CString strQuery;
	strQuery.Format("select datavalue from data_Table2 where dataname = '%s' and NodeSN = %d",
		m_SensorName[SensorOrder],m_Nodes[NodeOrder]);
	
	recordset.SetQuery(strQuery);
	if(!recordset.Open()) //���޷��򿪼�¼��
		return false;
	
	if(recordset.IsEof())
		return false;
	
	recordset.GetFieldValue("datavalue",x);

	return true;

}

bool CBlurFuser::GetValueFromInput(int SensorOrder,int NodeOrder,double& x)
{
	CDataInputDlg didlg;
	int nodeId = m_Nodes[NodeOrder];
	if(1 == didlg.DoModal()){
	
		
		CString strQuery;
	    CADORecordset  recordset(&GlDataBase);
		strQuery.Format("insert into data_Table2 (nodesn) values (%d)",nodeId);
		recordset.SetQuery(strQuery);
		if(recordset.Open() == FALSE)
			return false;

		strQuery.Format("select * from data_Table2 where nodesn = %d",nodeId);  
		recordset.SetQuery(strQuery);
		if(recordset.Open() == FALSE)
			return false;

		/*strQuery.Format("select * from data_Table");  
		recordset.SetQuery(strQuery);
		if(recordset.Open() == FALSE)
			return false;

		strQuery.Format("nodesn = %d",nodeId);  //��λ����ǰ
		if(recordset.Find(strQuery) == FALSE){
			return false;
		}
		*/
		map<string,double>::iterator iter = datas.begin();
		for(;iter!=datas.end();iter++){	
			pair<string,double> p = *iter;

			string strname;
			strname = p.first;

			double value;
			value = p.second;
			
			//recordset.Update();
			recordset.Edit();//  ��SetFieldValueǰ�������һ��
			recordset.SetFieldValue(strname.c_str(),value);
			recordset.Update();
			
			//m_datas[strname] = value;
		}

		x = datas[m_SensorName[SensorOrder]];
		
		
		
		return true;
	}
	else 
		return false;
	
}

bool CBlurFuser::GetFuncType(int FuseID, int NodeOrder,int SensorOrder,int& FuncType)
{
	CADORecordset  recordset(&GlDataBase);
	CString strQuery;
	strQuery.Format("select busfun from Fuse_Node_Func_Table where FR_id = %d and NodeOrder = %d and SensorSN = %d",
		             FuseID, NodeOrder,SensorOrder);

	recordset.SetQuery(strQuery);
	if(!recordset.Open()) //���޷��򿪼�¼��
		return false;
	
	if(recordset.IsEof())
		return false;

	recordset.GetFieldValue("busfun",FuncType);
	
	return true;


}
//FunctionValue(int nodenum,int fuctype,int datatype,double x,double& dresult);

bool CBlurFuser::CalRelationMatrix(int FuseID)
{
	int NodeSN,FuncType,DataType;
	double x;

	int i,j;

	for(i = 0;i<m_SensorNum;i++)  //����һ�������������н���ֵ
		for(j = 0;j<m_NodeNum; j++){
			if(!GetValueFromDB(i,j,x)){
				CString str;
				str.Format("��ǰ���%d�����ݿ���û������,�Ƿ���Ҫ�ֹ�����",m_Nodes[j]);
				if(IDNO == AfxMessageBox(str,MB_YESNO)){
					return false;
				}
				else{
					if(GetValueFromInput(i,j,x) == false)
						return false;
				}
			}

		
			if(!GetFuncType(FuseID,j,i,FuncType))
				return false;
			DataType = g_ParaTable[m_SensorName[i]];
			NodeSN = m_Nodes[j];
			double dresult;
			if(!FunctionValue(NodeSN,FuncType,DataType,x,dresult))
				return false;
			m_RMatrix[i][j] = dresult;
		}
		return true;
}

bool CBlurFuser::FuseLize()
{
	int i,j;
	for(i = 0;i<m_NodeNum;i++){
		for(j = 0;j<m_SensorNum;j++){
            m_dResult[i] +=  m_Weight[j]*m_RMatrix[j][i];
		}
	}
		return true;
}

bool CBlurFuser::NomorLize()
{
	double sum = 0;
	for(int i = 0;i<m_NodeNum;i++)
	{
		sum+=m_dResult[i];

	}

	for(i = 0;i<m_NodeNum;i++)
	{
		m_dResult[i] /=sum;
		
	}

		return true;
}


bool CBlurFuser::GetZYZ(int nodeid,double& zongyuezhi)
{
	CADORecordset  recordset(&GlDataBase);
	CString strQuery;
	strQuery.Format("select zyz from blur_zyz_table where nodesn = %d",nodeid);
	
	recordset.SetQuery(strQuery);
	if(!recordset.Open()) //���޷��򿪼�¼��
		return false;
	
	if(recordset.IsEof())
		return false;
	
	recordset.GetFieldValue("zyz",zongyuezhi);
	
	return true;
}
bool CBlurFuser::FuseDeduce(int& OutNode,int FuseID)
{
	
	
	GetNodes(FuseID); //�õ�m_Nodes[MaxNodes]; //�����Ÿù����õ��Ľ���,�±��Ӧ�����,��0��ʼ

	GetSensors(FuseID); //�õ� m_Weight[MaxSensors];//ÿ����������Ȩ��,�±��Ӧ�����,��0��ʼ
	                    //�õ�m_SensorName[MaxSensors][MaxNameLen]; //ÿ��������������,��U1,I2
	
	CalRelationMatrix(FuseID);//�õ���ϵ����m_RMatrix[MaxSensors][MaxNodes]; 

	FuseLize();//�õ���ʼm_dResult[MaxNodes]

	NomorLize();//��һ��m_dResult[MaxNodes]

	CADORecordset  recordset(&GlDataBase);
	CString strQuery;
	strQuery.Format("select Svalue from Fuse_Rule_Table where FR_id = %d",FuseID);
	
	recordset.SetQuery(strQuery);
	if(!recordset.Open()) //���޷��򿪼�¼��
		return false;
	
	if(recordset.IsEof())
		return false;
	double dyuezhi;
	recordset.GetFieldValue("Svalue",dyuezhi);

	double dmax = 0;
	int OutNodeOrder = -1;

	//�����е����ֵ
	for(int i = 0;i<m_NodeNum; i++)
	{
		if(m_dResult[i]>dmax){
			dmax = m_dResult[i];
			OutNodeOrder = i;
		}
	}

	if(dmax<=dyuezhi)  //���������ֵ
		return false;

	if(OutNodeOrder == -1)
		return false;

	OutNode = m_Nodes[OutNodeOrder];

	//***************************************************************************************

	//���������ֵ���������ֵҲҪ�Ƚ�
	double zyuezhi;
	if(GetZYZ(OutNode,zyuezhi) == true)
	{
		
		if(dmax<=zyuezhi)
			return false;
	}


	
	return true;

	
}