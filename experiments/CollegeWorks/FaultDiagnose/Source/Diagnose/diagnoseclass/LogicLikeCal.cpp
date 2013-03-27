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
extern map<string,int> g_ParaTable;  //用来放征兆数据ID和征兆数据符号（如U，I R）

IBlurAlgo * pBlurAlgo;
IDispatch * pDispatch;
IClassFactory * pClassFactory;	// 类厂接口指针


//函数对象，用来判断两值是否相等
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
	//初始化COM库
	//HRESULT hr=::CoInitialize(0);

	//if(hr!=S_OK) return hr;
	//	获取对象的类厂接口指针
	HRESULT hr=::CoGetClassObject(CLSID_AlgorithmCOM,
		CLSCTX_INPROC,
		NULL,
		IID_IClassFactory,
		(void**)&pClassFactory);

//	if(hr!=S_OK) return hr;
	
	// 真正创建对象
	hr = pClassFactory->CreateInstance(NULL,IID_IBlurAlgo,(void**)&pBlurAlgo);
	// 此方法的好处在于可以一次创建多个对象, 不需要
////	if(hr!=S_OK) return hr;
	
	
	//查询对象实现的接口pDispatch
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
		//str.Format("select MAX(层号) from 结点表 where 结点号=%d",j );
		recordset.SetQuery("select * from 征兆数据");
		recordset.Open();
		ParaTable.clear();
		while(recordset.IsEof()!=TRUE){
		   recordset.GetFieldValue(_T("征兆数据类型ID"),id);
		   recordset.GetFieldValue(_T("征兆数据类型符号"),str);
		   str.TrimRight();
		   ParaTable[str.GetBuffer(0)] = id;
		   recordset.MoveNext();
		}
		//cout<<ParaTable.size();
		return true;
	}
	return false;

}

//获得对应隶属函数的各个参数
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
		//str.Format("select MAX(层号) from 结点表 where 结点号=%d",j );
		CString strQuery;
		strQuery.Format("select * from rule_unit_sub_table where nodesn = %d and dataname = '%s' and busfun = %d ",
			nodenum,str.c_str(),fuctype);
		recordset.SetQuery(strQuery);
		recordset.Open();
		if(recordset.GetRecordCount()==0){
			//AfxMessageBox("没有对应的隶属函数！！！");
			return false;
		}
		else if(recordset.GetRecordCount()>1){
			//AfxMessageBox("多于一个隶属函数！！！请修改该规则！！！");
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

	//DISPPARAMS disp = { pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
	//hr=pDispatch->Invoke(0x1, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
	
	
	varResult.Clear();
	HRESULT hr;
	
	switch(fuctype) {
	case 1://正态分布
		pvars[0] = paras.para2;//k
		pvars[1] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
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
	case 2://三角分布
		pvars[0] = paras.para2;//b
		pvars[1] = paras.para3;//c
		pvars[2] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
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
	case 3: //梯形分布
		pvars[0] = paras.para2;//b
		pvars[1] = paras.para3;//c
		pvars[2] = paras.para4;//d
		pvars[3] = paras.para5;//e
		pvars[4] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
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
		
	case 4: //升正态分布
		pvars[0] = paras.para2;//k
		pvars[1] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
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
	case 5:  //降正态分布
		pvars[0] = paras.para2;//k
		pvars[1] = paras.para1;//a
		//disp = {pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
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
		cout<<"连接数据库失败!"<<endl;
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
	//if(strExp.empty()!=0) 对于string对象,""不等于empty
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
		//首位为 (, 字符f
	if(ch1!='('&&ch1!='f'){
		//cout<<endl<<"the first char is wrong!";
		return false;
	}

	
	for(iter = begin;iter!=end;iter++){
		ch1 = *iter;
		ch2 = *(iter+1);
		if(iter+1 == end) ch2 = '#';
		char ch3 = *(iter+2);
		
		//(->字母,  (
		if(ch1 == '('){
			if(ch2!='('&&!isalpha(ch2)){
				//cout<<endl<<"(---> wrong";
				return false;
			}
			
		}
		
		//字母--->字母, ) ,数字 //此处字母与表示函数的f不同,还未实现区分
		//f------->数字
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
					//cout<<"字母--->wrong"<<endl;
					return false;

				}
			}
	
		}

		//逻辑运算符--->(,  f
		if(IsLogic(ch1)){
			if(ch2!='('&&ch2!='f'){
				//cout<<endl<<"逻辑运算符---> wrong";
				return false;
			}
		}
		
		//)--->逻辑运算符, ), 空,关系运算符
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
		
		//关系运算符->数字，=   不能检测出===类似的错误
		if(IsRelation(ch1))
		{
			if(ch2 != '=' && !isdigit(ch2))
			{
				return false;
			}
		}
		
		//数字--->(
		if(isdigit(ch1)){
			if(ch2!='(' &&ch2!=')'&& !isdigit(ch2) && ch2!='.'&&!IsLogic(ch2)){
				//cout<<endl<<"数字---> wrong";
				return false;
			}
		}

		
		
		//小数点--->数字
		if(ch1=='.'){
			if(!isdigit(ch2)){
			//	cout<<endl<<"小数点---> wrong";
				return false;
				
			}
		}
		
	
/*		//9	正负号―――＞数字

		if(ch1 == '+'|ch1=='-'){
			if(!isdigit(ch2)){
				cout<<"正负号　－－－－－＞wrong";
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
	//cout<<endl<<"后缀表达式为："<<m_strExp<<endl;
	

	
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

			double x;//函数自变量
			if(m_Paras.find(paraname)!=m_Paras.end()){
				x = m_Paras[paraname];

			}
			else 
				return false;

		    int dataid;//数据类型ID
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
			//表达 式中增加功能  f1(u)&f2(I)-->f1(u)>0.4&f2(I)
			ch1 = *(iter+1);
			//如果有f1(u)>0.4的情况出现。。。。
			if(IsRelation(ch1))
			{
				string op; //解析出运算符
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
					while(!IsLogic((*iter))){//解析出值
						dstrvalue+=(*iter);
						iter++;
					}
					double dvalue = atof(dstrvalue.c_str());
					//开始比较
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
	//cout<<endl<<"结果为："<<m_vecvalue[index];
	

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

//借助于一个DOUBLE 数组
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










































