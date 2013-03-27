//#include "..\\stdafx.h"

#include "MainDeduce.h"



CADODatabase GlDataBase;
map<string,int> g_ParaTable;  //用来放征兆数据ID和征兆数据符号（如U，I R）


CMalfuncDeduce::CMalfuncDeduce():m_Recordset(&GlDataBase)
{
	//不要在构造函数中包含会失败的操作
	/*m_Recordset.SetQuery("select * from data_Table");
	if(!m_Recordset.Open()){
		AfxMessageBox("不能打开数据集!");
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
		AfxMessageBox("不能打开数据集!");
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
			//如果是第一次循环，记录第一个dataname 
			if(bfirst)
		       sdataname = dataname;
			//如果不是第一次，则判断是否与第一个记录的相同，相同说明记录已经循环，没找到相应记录，则退出
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
	strout.Format("正在诊断结点 %d ......\r\n\r\n",nodeId);
	m_strOutput+=strout;
	//g_pTipView->SetEditInfo(m_strOutput);
	
	//如果对应结点在数据库中没有数据,则用户自行输入
	if(SetDataFromDB(nodeId) == false){
		ruleid = -1; 
		outnodeid = -2;
	//	CString str;
	//	str.Format("当前结点%d在数据库中没有数据,是否需要手工输入",nodeId);
	//	if(IDNO == AfxMessageBox(str,MB_YESNO)){
		return false;
	//	}
	/*	else{
			if(SetDataFromInput(nodeId) == false)
				return false;
		}
		*/
		
	}
	//设置数据
	m_RegCal.SetParas(m_datas);
	CString strRegRule;
	//int i = RegRuleSet.GetRecordCount();
	//在未推出下一结点之前,遍历此结点的每条规则
	while(RegRuleSet.IsEof() != TRUE){
		
		RegRuleSet.GetFieldValue("RContent",strRegRule);
		
		//表达式计算
		m_RegCal.SetExpression(strRegRule.GetBuffer(0));
		if(m_RegCal.CheckAndFormat()){
			if(m_RegCal.PostFixLize()){
				double value;
				bool bresult = m_RegCal.Calculate(value);
				if(bresult == true){
					CString strOutNode;

					//采用的规则ID
					RegRuleSet.GetFieldValue("RuleSN",ruleid);

					//输出 的结点
					RegRuleSet.GetFieldValue("OutNode",strOutNode);
					outnodeid = atoi(strOutNode.GetBuffer(0)); //返回下一个出错点
					
					//规则内容
					RegRuleSet.GetFieldValue("RContent",strrule);


					strout.Format("结点 %d 出错......\r\n\r\n",nodeId);
					m_strOutput+=strout;
				//	g_pTipView->SetEditInfo(m_strOutput);
					
				//	g_pNtView->SetChildSelNode(nodeId); //在树形控件中选中当前推理的结点
					//若此结点不是上一结点 的子结点,则无法选中
					
				//	RegDeduce1Node(nodeId);  //递归到下一结点

					
					return true;
				}//if(bresult == true)
				
			}//if(m_RegCal.PostFixLize())
		}//if(m_RegCal.CheckAndFormat())
		
        RegRuleSet.MoveNext();
		
	}//while

	//无匹配规则
	ruleid = -1; 
	outnodeid = -2;
	strout = "无匹配规则,规则诊断失败......\r\n\r\n";
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
	

	//如果对应结点在数据库中没有数据,则询问用户是否自行输入
	if(SetDataFromDB(nodeId) == false){
		//CString str;
		//str.Format("当前结点%d在数据库中没有数据,是否需要手工输入",nodeId);
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
	//设置数据
	m_BlurCal.SetParas(m_datas);
	CString strRegRule;
	//int i = RegRuleSet.GetRecordCount();
	
	int NextNOdeID = nodeId;  //用来记录该结点当前规则值最大的那个对应子结点
	double MaxValue = 0.0;   //规则的最大值
	
	double Svalue;            //用来记录该结点当前规则值最大的规则对应阈值
	
	
	//在未推出下一结点之前,遍历此结点的每条规则
	while(RegRuleSet.IsEof() != TRUE){
		
		RegRuleSet.GetFieldValue("BRContent",strRegRule);
		
		//表达式计算
		m_BlurCal.SetExpression(strRegRule.GetBuffer(0));
		if(m_BlurCal.CheckAndFormat()){
			if(m_BlurCal.PostFixLize(nodeId)){
				double value;              //当前规则的值
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
		
        //该结点有规则出错了
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

