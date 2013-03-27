// LogicLikeCal.cpp: implementation of the CLogicLikeCal class.
//
//////////////////////////////////////////////////////////////////////
#include "..\\stdafx.h"
#include "LogicLikeCal.h"
#include "AlgorithmCOM.h"
//#include "AlgorithmCOM_i.c"
#include <atlbase.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CADODatabase GlDataBase;
extern map<string,int> g_ParaTable;  //��������������ID���������ݷ��ţ���U��I R��

IBlurAlgo * pBlurAlgo;
IDispatch * pDispatch;
IClassFactory * pClassFactory;	// �೧�ӿ�ָ��


//�������������ж���ֵ�Ƿ����
template <class F,class S>
class value_equals
{
	public:
		value_equals(const S& s):second(s)
		{ }
		
		bool operator() (pair<const F,S> elem)
		{
			return elem.second == second;
		}


	private:
		S second;
};


HRESULT InitlizeCOM(){
	//HRESULT hr;
	//��ʼ��COM��
	//HRESULT hr=::CoInitialize(0);

	//if(hr!=S_OK) return hr;
	//	��ȡ������೧�ӿ�ָ��
	HRESULT hr=::CoGetClassObject(CLSID_AlgorithmCOM,
		CLSCTX_INPROC,
		NULL,
		IID_IClassFactory,
		(void**)&pClassFactory);

//	if(hr!=S_OK) return hr;
	
	// ������������
	hr = pClassFactory->CreateInstance(NULL,IID_IBlurAlgo,(void**)&pBlurAlgo);
	// �˷����ĺô����ڿ���һ�δ����������, ����Ҫ
////	if(hr!=S_OK) return hr;
	
	
	//��ѯ����ʵ�ֵĽӿ�pDispatch
	hr=pBlurAlgo->QueryInterface(IID_IDispatch, (void **)&pDispatch);
	
//	if(hr!=S_OK) return hr;

	return S_OK;

//	S_FALSE
}

HRESULT ClearCOM(){
	
	pClassFactory->Release();
	pBlurAlgo->Release();
	pDispatch->Release();
	
//	::CoUninitialize();
	return S_OK;
}

double f(){
	return 1.09;
}



bool SetParaTable(map<string,int>& ParaTable){
	if(GlDataBase.IsOpen() == TRUE){
		CADORecordset recordset(&GlDataBase);

		int id;
		CString str;
		//str.Format("select MAX(���) from ���� where ����=%d",j );
		recordset.SetQuery("select * from ��������");
		recordset.Open();
		ParaTable.clear();
		while(recordset.IsEof()!=TRUE){
		   recordset.GetFieldValue(_T("������������ID"),id);
		   recordset.GetFieldValue(_T("�����������ͷ���"),str);
		   str.TrimRight();
		   ParaTable[str.GetBuffer(0)] = id;
		   recordset.MoveNext();
		}
		//cout<<ParaTable.size();
		return true;
	}
	return false;

}

//��ö�Ӧ���������ĸ�������
bool GetParasFromDB(int nodenum,int fuctype,int datatype ,Paras& paras){
	if(GlDataBase.IsOpen() == TRUE){
		CADORecordset recordset(&GlDataBase);
		map<string,int>::iterator itor;
		itor = find_if(g_ParaTable.begin(),g_ParaTable.end(),value_equals<string,int>(datatype));
		if(itor == g_ParaTable.end())
			return false;
		string str = itor->first;
		//int id;
		//CString str;
		//str.Format("select MAX(���) from ���� where ����=%d",j );
		CString strQuery;
		strQuery.Format("select * from rule_unit_sub_table where nodesn = %d and dataname = '%s' and busfun = %d ",
			nodenum,str.c_str(),fuctype);
		recordset.SetQuery(strQuery);
		recordset.Open();
		if(recordset.GetRecordCount()==0){
			//AfxMessageBox("û�ж�Ӧ����������������");
			return false;
		}
		else if(recordset.GetRecordCount()>1){
			//AfxMessageBox("����һ�������������������޸ĸù��򣡣���");
			return false;

		}

		else if(recordset.GetRecordCount() == 1){
			recordset.GetFieldValue(_T("Para1"),paras.para1);
			recordset.GetFieldValue(_T("Para2"),paras.para2);
			recordset.GetFieldValue(_T("Para3"),paras.para3);
			recordset.GetFieldValue(_T("Para4"),paras.para4);
			recordset.GetFieldValue(_T("Para5"),paras.para5);
			recordset.GetFieldValue(_T("Para6"),paras.para6);

			
			//cout<<endl<<paras.para1;
			return true;
		}
			

		

	}

	return false;
  
}


bool FunctionValue(int nodenum,int fuctype,int datatype,double x,double& dresult){
	Paras paras;
	if(GetParasFromDB(nodenum,fuctype,datatype,paras) == false) 
		return false;
	CComVariant  varResult;
	CComVariant *pvars=new CComVariant[6];
	DISPPARAMS disp;

	//DISPPARAMS disp = { pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
	//hr=pDispatch->Invoke(0x1, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
	
	
	varResult.Clear();
	HRESULT hr;
	
	switch(fuctype) {
	case 1://��̬�ֲ�
		pvars[0] = paras.para2;//k
		pvars[1] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 2;
		disp.cNamedArgs = 0;	
			
		hr=pDispatch->Invoke(0x1, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

		pvars[0] = x;
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 1;
		disp.cNamedArgs = 0;
		hr=pDispatch->Invoke(0x2, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		//cout<<"the result is "<<varResult.dblVal;

		break;
	case 2://���Ƿֲ�
		pvars[0] = paras.para2;//b
		pvars[1] = paras.para3;//c
		pvars[2] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 3;
		disp.cNamedArgs = 0;	
		
		hr=pDispatch->Invoke(0x3, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		if(hr != S_OK)  return 0.0;
		pvars[0] = x;
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 1;
		disp.cNamedArgs = 0;
		hr=pDispatch->Invoke(0x4, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		if(hr != S_OK)  return 0.0;
		//cout<<"the result is "<<varResult.dblVal;
		

		break;
	case 3: //���ηֲ�
		pvars[0] = paras.para2;//b
		pvars[1] = paras.para3;//c
		pvars[2] = paras.para4;//d
		pvars[3] = paras.para5;//e
		pvars[4] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 5;
		disp.cNamedArgs = 0;	
		
		hr=pDispatch->Invoke(0x5, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		
		pvars[0] = x;
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 1;
		disp.cNamedArgs = 0;
		hr=pDispatch->Invoke(0x6, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		//cout<<"the result is "<<varResult.dblVal;
		break;
		
	case 4: //����̬�ֲ�
		pvars[0] = paras.para2;//k
		pvars[1] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 2;
		disp.cNamedArgs = 0;	
		
		hr=pDispatch->Invoke(0x7, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		
		pvars[0] = x;
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 1;
		disp.cNamedArgs = 0;
		hr=pDispatch->Invoke(0x8, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		//cout<<"the result is "<<varResult.dblVal;

		break;
	case 5:  //����̬�ֲ�
		pvars[0] = paras.para2;//k
		pvars[1] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 2;
		disp.cNamedArgs = 0;	
		
		hr=pDispatch->Invoke(0x9, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		
		pvars[0] = x;
		
		disp.rgvarg = pvars;
		disp.rgdispidNamedArgs = NULL;
		disp.cArgs = 1;
		disp.cNamedArgs = 0;
		hr=pDispatch->Invoke(0xA, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
	//	cout<<"the result is "<<varResult.dblVal;
		
		break;
	default: //cout<<"wrong"<<endl;
		return false;
	}

	dresult = varResult.dblVal;
	return true;
}

CLogicLikeCal::CLogicLikeCal()
{
	/*GlDataBase.SetConnectionString("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=TDESdb");
	if(GlDataBase.Open()!=TRUE){
		cout<<"�������ݿ�ʧ��!"<<endl;
	}
	else
		cout<<"connect to database!"<<endl;
		*/

	
	//SetParaTable(g_ParaTable);

	//InitlizeCOM();
	//FunctionValue(1,1,1);

	InitlizeCOM();

}

CLogicLikeCal::~CLogicLikeCal()
{
	//ClearCOM();
	ClearCOM();

}

CLogicLikeCal::CLogicLikeCal(string strExp){
	m_strExp = strExp;
}

//***************************************************************************

void CLogicLikeCal::SetExpression(string strExp){
	m_strExp = strExp;
	//cout<<m_strExp<<endl;
}



bool CLogicLikeCal::CheckAndFormat(string strExp /* = "" */){
	//if(strExp.empty()!=0) ����string����,""������empty
	if(strExp!="") 
		m_strExp = strExp;
	if(m_strExp.empty() == true) return false;
	
	string::iterator iter, begin,end;
	begin = m_strExp.begin();
	end = m_strExp.end();
	
	//check if every element in the string is fit the expression
	for(iter = begin;iter!=end;iter++){
		if(!IsAccept(*iter)) return false;
	}

	////////////////////////
	//cout<<endl<<strtmp;
	//////////////////////////
	
	
	if(CheckRegulation()==false){
		//cout<<endl<<"wrong regulation!";
		return false;
	}
	
	return true;
}


bool CLogicLikeCal::IsAccept(char ch){
	if(!isdigit(ch)) {
		if(!isalpha(ch)) {
			if(ch!='.'){
				if(ch!='&'&&ch!='!'&&ch!='|'&&ch!='('&&ch!=')'){
					if(ch!='<'&&ch!='>'&&ch!='=')
						if(ch!='+'&&ch!='-')
							
							return false;
				}
			}
		}
	}
	return true;
}

bool CLogicLikeCal::IsRelation(char ch)
{
	if(ch == '<'||ch == '>'||ch == '=')
	{
		return true;
	}
	else 
		return false;
}

bool CLogicLikeCal::CheckRegulation(){

	string::iterator iter, begin,end;
	char ch1,ch2,ch3;
	begin = m_strExp.begin();
	end = m_strExp.end();
	ch1 = *begin;
		//��λΪ (, �ַ�f
	if(ch1!='('&&ch1!='f'){
		//cout<<endl<<"the first char is wrong!";
		return false;
	}

	
	for(iter = begin;iter!=end;iter++){
		ch1 = *iter;
		ch2 = *(iter+1);
		if(iter+1 == end) ch2 = '#';
		char ch3 = *(iter+2);
		
		//(->��ĸ,  (
		if(ch1 == '('){
			if(ch2!='('&&!isalpha(ch2)){
				//cout<<endl<<"(---> wrong";
				return false;
			}
			
		}
		
		//��ĸ--->��ĸ, ) ,���� //�˴���ĸ���ʾ������f��ͬ,��δʵ������
		//f------->����
		if(isalpha(ch1)){
			//represent function
			if((ch1 == 'f'||ch1 == 'F')&&IsRpfunction(iter)){
				if(!isdigit(ch2)){
					//cout<<"f------>wrong"<<endl;
					return false;
				}
			}

			//not function
			else{
				if(ch2!=')'&&!isdigit(ch2)){
					//cout<<"��ĸ--->wrong"<<endl;
					return false;

				}
			}
	
		}

		//�߼������--->(,  f
		if(IsLogic(ch1)){
			if(ch2!='('&&ch2!='f'){
				//cout<<endl<<"�߼������---> wrong";
				return false;
			}
		}
		
		//)--->�߼������, ), ��,��ϵ�����
		if(ch1==')'){
			if(!IsLogic(ch2)&&ch2!=')'&&ch2!='#'&&!IsRelation(ch2))
			{
				//cout<<endl<<")---> wrong";
				return false;
				
			}

			if(IsRelation(ch2))
			{
				if(ch3 == '>'&& ch3 == '<')
				{
					return false;
				}
			}
		}
		
		//��ϵ�����->���֣�=   ���ܼ���===���ƵĴ���
		if(IsRelation(ch1))
		{
			if(ch2 != '=' && !isdigit(ch2))
			{
				return false;
			}
		}
		
		//����--->(
		if(isdigit(ch1)){
			if(ch2!='(' &&ch2!=')'&& !isdigit(ch2) && ch2!='.'&&!IsLogic(ch2)){
				//cout<<endl<<"����---> wrong";
				return false;
			}
		}

		
		
		//С����--->����
		if(ch1=='.'){
			if(!isdigit(ch2)){
			//	cout<<endl<<"С����---> wrong";
				return false;
				
			}
		}
		
	
/*		//9	�����ŨD�D�D������

		if(ch1 == '+'|ch1=='-'){
			if(!isdigit(ch2)){
				cout<<"�����š�������������wrong";
				return false;
			}
		}
		
		
	}
	*/
	}
	return true;
}
bool CLogicLikeCal::IsLogic(char ch){
	if(ch!='&'&&ch!='|')
		return false;
	else 
		return true;
}

bool CLogicLikeCal::IsRpfunction(string::iterator iter){
	string::iterator iter1;
	char ch;
	for(iter1 = iter+1;iter1!=m_strExp.end();iter1++){
		ch = *iter1;
		if(ch == '(')  return true;
		if(ch == ')')  return false;
	}
	return false;
}

bool CLogicLikeCal::PostFixLize(int nodenum){

	if(LogicLize(nodenum)!= true)
		return false;
	
	m_sOperate.push('#');
	int num = m_strExp.length();
	string strtmp;
	//char strresult[MAX_LEN];
	//int j = 0;
	char ch ,y;
	for(int i = 0;i<num;i++){
		ch = m_strExp[i];
		if(isdigit(ch))
			strtmp+= ch;
		else if(ch == ')')
			for(y = m_sOperate.top(),m_sOperate.pop() ;y!='(';y = m_sOperate.top(),m_sOperate.pop())
				strtmp+= y;
			else{
				
				for(y = m_sOperate.top(),m_sOperate.pop();isp(y)>icp(ch);y = m_sOperate.top(),m_sOperate.pop())
					strtmp+= y;
				
				m_sOperate.push(y);
				m_sOperate.push(ch);
				
			}
			
	}
	while(!m_sOperate.empty()){
		y = m_sOperate.top();
		m_sOperate.pop();
		strtmp+= y;
	}
	
	//strresult[--j]='\0';
	string::iterator iter1 = strtmp.end();
	strtmp.erase(iter1-1);
	m_strExp = strtmp;
	//cout<<endl<<"��׺���ʽΪ��"<<m_strExp<<endl;
	

	
	return true;
}


int CLogicLikeCal::icp(char c){
	int returnvalue;
	switch(c) {
	case '#':
		returnvalue = 0;
		break;
	case '(':
		returnvalue = 8;
		break;
	case '!':
		returnvalue = 7;
		break;
	case '&':
		returnvalue = 4;
		break;
	case '|':
		returnvalue = 2;
		break;
	case ')':
		returnvalue = 1;
		break;
	default:returnvalue = ERR_NOEXIST;
		break;
	}
	
	return returnvalue;
}


int CLogicLikeCal::isp(char c){
	int returnvalue;
	switch(c) {
	case '#':
		returnvalue = 0;
		break;
	case '(':
		returnvalue = 1;
		break;
	case '!':
		returnvalue = 6;
		break;
	case '&':
		returnvalue = 5;
		break;
	case '|':
		returnvalue = 3;
		break;
	case ')':
		returnvalue = 8;
		break;
	default:returnvalue = ERR_NOEXIST;
		break;
	}
	
	return returnvalue;
}

bool CLogicLikeCal::LogicLize(int nodenum){
	string strtmp;
	char ch1,ch2,ch3;
	char index = '0';
	string::iterator iter;
	for(iter = m_strExp.begin();iter!=m_strExp.end();iter++){
		ch1 = *iter;
		ch2 = *(iter+1);
		if(ch1 == 'f'&&isdigit(ch2)){//if it is a function
			string paraname;
			iter+=3;
			while(*iter!=')'){
				paraname+=(*iter);
				iter++;
			}
			
			/*
			 *	evaluate the value here!!!
			 */

			double x;//�����Ա���
			if(m_Paras.find(paraname)!=m_Paras.end()){
				x = m_Paras[paraname];

			}
			else 
				return false;

		    int dataid;//��������ID
			if(g_ParaTable.find(paraname)!=g_ParaTable.end()){
				dataid = g_ParaTable[paraname];
			}
			else
				return false;

			int funid = ch2-'0';



		    double result;
			if(FunctionValue(nodenum,funid,dataid,x,result) == false) 
				return false;

			/*
			CString str;
			str.Format("f%d(%4.1f) = %f",funid,x,result);
			AfxMessageBox(str);
			*/
			

			//************************************************************************
			//��� ʽ�����ӹ���  f1(u)&f2(I)-->f1(u)>0.4&f2(I)
			ch1 = *(iter+1);
			//�����f1(u)>0.4��������֡�������
			if(IsRelation(ch1))
			{
				string op; //�����������
				op+=ch1;
				ch1 = *(++iter);
				if(IsRelation(ch1))
				{
					op+=ch1;
					ch1 = *(++iter);
				}

				if(isdigit(ch1))
				{
					string dstrvalue;
					while(!IsLogic((*iter))){//������ֵ
						dstrvalue+=(*iter);
						iter++;
					}
					double dvalue = atof(dstrvalue.c_str());
					//��ʼ�Ƚ�
					if(op == ">") 
						if(!(result>dvalue))  return false;
					if(op == "<") 
						if(!(result<dvalue))  return false;
					if(op == ">=") 
						if(!(result>=dvalue))  return false;
					if(op == "<=") 
						if(!(result<=dvalue))  return false;
					if(op == "=="||op == "=") 
						if(!(fabs(result-dvalue)<EPSILON))  return false;
							
							
				}
				else 
					return false;
			}

			//*******************************************************************************
			//cout<<result;
			m_vecvalue.push_back(result);
			strtmp+=index++;

		}
		else{

			strtmp+=ch1;
		}
	}
	m_strExp = strtmp;
	//cout<<strtmp;

	return true;
}

bool CLogicLikeCal::Calculate(double &value){

	int num = m_strExp.length();
	char ch;
	for(int i = 0;i<num;i++){
		ch = m_strExp[i];
		if(isdigit(ch)){
			AddOperand(ch);
		}	
		else{
			SingleCalculate(ch);
		}
	}
	
	ch = m_sOperand.top();
	int index = ch - '0';
	value = m_vecvalue[index];
	//cout<<endl<<"���Ϊ��"<<m_vecvalue[index];
	

	return true;
}

void CLogicLikeCal::AddOperand(char c){
	m_sOperand.push(c);
}

bool CLogicLikeCal::Get2Operands(char &cLeft,char &cRight){
	if(m_sOperand.empty()){
		//cout<<"no operands!!!"<<endl;
		return false;
	}
	cRight = m_sOperand.top();
	m_sOperand.pop();
	
	if(m_sOperand.empty()){
		//cout<<"no operands!!!";
		return false;
	}
	cLeft = m_sOperand.top();
	m_sOperand.pop();
	
	return true;
}

//������һ��DOUBLE ����
bool CLogicLikeCal::SingleCalculate(char op){
	char left,right,operand;
	switch(op) {
	case '&':
		if(this->Get2Operands(left,right)==true){
			int nleft = left - '0';
			int nright = right - '0';
			double result = m_vecvalue[nleft]>m_vecvalue[nright]?m_vecvalue[nright]:m_vecvalue[nleft];
			m_sOperand.push(left);
			m_vecvalue[nleft] = result;
		    
		}
		break;
		
	case '|':
		if(this->Get2Operands(left,right)==true){
			int nleft = left - '0';
			int nright = right - '0';
			double result = m_vecvalue[nleft]<m_vecvalue[nright]?m_vecvalue[nright]:m_vecvalue[nleft];
			m_sOperand.push(left);
			m_vecvalue[nleft] = result;
			
		}
		break;
	default:return false;
	}
	return true;
}



void CLogicLikeCal::AddPara(string strpara,double dbValue /* = 0.0 */){
	m_Paras.insert(SdPair(strpara,dbValue));
}

void CLogicLikeCal::DelPara(string strpara){
	m_Paras.erase(strpara);
}

void CLogicLikeCal::SetParaValue(string strpara,double dbValue){
	m_Paras[strpara] = dbValue;
}
void CLogicLikeCal::SetParas(map<string,double> Paras){
	m_Paras = Paras;
}










































