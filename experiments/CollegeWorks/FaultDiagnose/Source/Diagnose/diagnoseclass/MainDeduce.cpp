//#include "..\\stdafx.h"

#include "MainDeduce.h"



CADODatabase GlDataBase;
map<string,int> g_ParaTable;  //��������������ID���������ݷ��ţ���U��I R��


CMalfuncDeduce::CMalfuncDeduce():m_Recordset(&GlDataBase)
{
	//��Ҫ�ڹ��캯���а�����ʧ�ܵĲ���
	/*m_Recordset.SetQuery("select * from data_Table");
	if(!m_Recordset.Open()){
		AfxMessageBox("���ܴ����ݼ�!");
		return;
	}*/

}

CMalfuncDeduce::~CMalfuncDeduce()
{

}

bool CMalfuncDeduce::GetRecordSet(CString str){

	CString strQuery;
	strQuery.Format("select * from data_Table2 where datatime = '%s'",str.GetBuffer(0));
	m_Recordset.SetQuery(strQuery);
	if(!m_Recordset.Open()){
		AfxMessageBox("���ܴ����ݼ�!");
		return false;
	}
	
	else
		
		return true;

}


bool CMalfuncDeduce::SetDataFromDB(int nodeId){
	CString strfind;
	if(m_Recordset.IsEOF() == TRUE){
		return false;
	}
	
	m_datas.clear();
	map<string,int>::iterator iter = g_ParaTable.begin();
	for(;iter!=g_ParaTable.end();iter++){
		
		pair<string,int> p = *iter;
		string strname;
		strname = p.first;
		//strfind.Format("nodesn = %d and dataname = %s ",nodeId,strname.c_str());
		strfind.Format("nodesn = %d ",nodeId);
		m_Recordset.MoveFirst();

		bool bfirst = true;
		while(1)
		{
			CString dataname;
			static CString sdataname;
			
			if(m_Recordset.Find(strfind) == FALSE){
				return false;
			}

			m_Recordset.GetFieldValue("dataname",dataname);
			dataname.TrimRight();
			//����ǵ�һ��ѭ������¼��һ��dataname 
			if(bfirst)
		       sdataname = dataname;
			//������ǵ�һ�Σ����ж��Ƿ����һ����¼����ͬ����ͬ˵����¼�Ѿ�ѭ����û�ҵ���Ӧ��¼�����˳�
			else
				if(sdataname == dataname)
					return false;
			if(strname == dataname.GetBuffer(0))
				break;
			m_Recordset.MoveNext();
			bfirst = false;
		}

		double value;	
		m_Recordset.GetFieldValue("datavalue",value);
		m_datas[strname] = value;
	}
	

	return true;
	 
}



bool CMalfuncDeduce::RegDeduce1Node(int& nodeId,int& ruleid,CString& strrule,int& outnodeid){
	CString strQuery;
	strQuery.Format("select RuleSN ,RContent ,OutNode from Rule_Table  where NodeSN = %d",nodeId );
	CADORecordset RegRuleSet(&GlDataBase);
	RegRuleSet.SetQuery(strQuery);
	if(RegRuleSet.Open() ==FALSE){
		return false;
	}
	
	CString strout;
	strout.Format("������Ͻ�� %d ......\r\n\r\n",nodeId);
	m_strOutput+=strout;
	//g_pTipView->SetEditInfo(m_strOutput);
	
	//�����Ӧ��������ݿ���û������,���û���������
	if(SetDataFromDB(nodeId) == false){
		ruleid = -1; 
		outnodeid = -2;
	//	CString str;
	//	str.Format("��ǰ���%d�����ݿ���û������,�Ƿ���Ҫ�ֹ�����",nodeId);
	//	if(IDNO == AfxMessageBox(str,MB_YESNO)){
		return false;
	//	}
	/*	else{
			if(SetDataFromInput(nodeId) == false)
				return false;
		}
		*/
		
	}
	//��������
	m_RegCal.SetParas(m_datas);
	CString strRegRule;
	//int i = RegRuleSet.GetRecordCount();
	//��δ�Ƴ���һ���֮ǰ,�����˽���ÿ������
	while(RegRuleSet.IsEof() != TRUE){
		
		RegRuleSet.GetFieldValue("RContent",strRegRule);
		
		//���ʽ����
		m_RegCal.SetExpression(strRegRule.GetBuffer(0));
		if(m_RegCal.CheckAndFormat()){
			if(m_RegCal.PostFixLize()){
				double value;
				bool bresult = m_RegCal.Calculate(value);
				if(bresult == true){
					CString strOutNode;

					//���õĹ���ID
					RegRuleSet.GetFieldValue("RuleSN",ruleid);

					//��� �Ľ��
					RegRuleSet.GetFieldValue("OutNode",strOutNode);
					outnodeid = atoi(strOutNode.GetBuffer(0)); //������һ�������
					
					//��������
					RegRuleSet.GetFieldValue("RContent",strrule);


					strout.Format("��� %d ����......\r\n\r\n",nodeId);
					m_strOutput+=strout;
				//	g_pTipView->SetEditInfo(m_strOutput);
					
				//	g_pNtView->SetChildSelNode(nodeId); //�����οؼ���ѡ�е�ǰ����Ľ��
					//���˽�㲻����һ��� ���ӽ��,���޷�ѡ��
					
				//	RegDeduce1Node(nodeId);  //�ݹ鵽��һ���

					
					return true;
				}//if(bresult == true)
				
			}//if(m_RegCal.PostFixLize())
		}//if(m_RegCal.CheckAndFormat())
		
        RegRuleSet.MoveNext();
		
	}//while

	//��ƥ�����
	ruleid = -1; 
	outnodeid = -2;
	strout = "��ƥ�����,�������ʧ��......\r\n\r\n";
	m_strOutput+=strout;
//	g_pTipView->SetEditInfo(m_strOutput);
	
	return false;
}

bool CMalfuncDeduce::BlurDeduce1Node(int& nodeId,int& ruleid,CString& strrule,int& outnodeid){
	
	CString strQuery;
	strQuery.Format("select brulesn,BRContent,OutNode, Svalue from blur_rule_table  where NodeSN = %d",nodeId );
	CADORecordset RegRuleSet(&GlDataBase);
	RegRuleSet.SetQuery(strQuery);
	if(RegRuleSet.Open() ==FALSE){
		return false;
	}
	

	//�����Ӧ��������ݿ���û������,��ѯ���û��Ƿ���������
	if(SetDataFromDB(nodeId) == false){
		//CString str;
		//str.Format("��ǰ���%d�����ݿ���û������,�Ƿ���Ҫ�ֹ�����",nodeId);
		//if(IDNO == AfxMessageBox(str,MB_YESNO)){
		ruleid = -1; 
		outnodeid = -2;
		return false;
		//}
	/*	else{
			if(SetDataFromInput(nodeId) == false)
				return false;
		}
	*/	
	}
	//��������
	m_BlurCal.SetParas(m_datas);
	CString strRegRule;
	//int i = RegRuleSet.GetRecordCount();
	
	int NextNOdeID = nodeId;  //������¼�ý�㵱ǰ����ֵ�����Ǹ���Ӧ�ӽ��
	double MaxValue = 0.0;   //��������ֵ
	
	double Svalue;            //������¼�ý�㵱ǰ����ֵ���Ĺ����Ӧ��ֵ
	
	
	//��δ�Ƴ���һ���֮ǰ,�����˽���ÿ������
	while(RegRuleSet.IsEof() != TRUE){
		
		RegRuleSet.GetFieldValue("BRContent",strRegRule);
		
		//���ʽ����
		m_BlurCal.SetExpression(strRegRule.GetBuffer(0));
		if(m_BlurCal.CheckAndFormat()){
			if(m_BlurCal.PostFixLize(nodeId)){
				double value;              //��ǰ�����ֵ
				m_BlurCal.Calculate(value);

				/*CString str;
				str.Format("%f",value);
				AfxMessageBox(str);
				*/

				
				if(value>=MaxValue){
					RegRuleSet.GetFieldValue("OutNode",NextNOdeID);
					RegRuleSet.GetFieldValue("Svalue",Svalue);
					RegRuleSet.GetFieldValue("brulesn",ruleid);
					RegRuleSet.GetFieldValue("BRContent",strrule);
					MaxValue = value;
				}
				
				RegRuleSet.MoveNext();
				
				continue;
			}
		}
		
        //�ý���й��������
		break;
		
	}//while
	
	if(NextNOdeID == nodeId){

		ruleid = -1; 
		outnodeid = -2;
		return false;
	}
	
	else if(MaxValue<Svalue){
		ruleid = -1; 
		outnodeid = -2;
		return false;
	}
	
	nodeId = NextNOdeID;
	
	
	//g_pTipView->SetEditInfo(m_strOutput);

	ruleid = ruleid; 
	outnodeid = NextNOdeID;
	
	
//	BlurDeduce1Node(nodeId);
	
	return true;
}

