#include "..\\StdAfx.h"
#include "LogicCal.h"



CLogicCal::CLogicCal(void)
{
}

CLogicCal::~CLogicCal(void)
{
}

CLogicCal::CLogicCal(string strExp)
{
	m_strExp = strExp;
}

void CLogicCal::SetExpression(string strExp){
	m_strExp = strExp;
	//cout<<m_strExp;
}

bool CLogicCal::CheckAndFormat(string strExp){
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

	//check if the brackets is  right ,if there is () ,erase it
	char ch1,ch2;
	int nbrackets = 0;
	string strtmp;
	for(iter = begin;iter!=end;iter++){
		ch1 = *iter;
		if(ch1 == '('){
			if((ch2 = *(iter+1)) == ')'){
				iter++;
				continue;
			}
			else nbrackets++;
		}

		if(ch1 == ')'){
			nbrackets--;
			if(nbrackets<0)
				break;;
		}

		strtmp+=ch1;
	}

	if(nbrackets != 0){
		//cout<<endl<<"bracket not right \n";
		return false;
	}

	strExp = strtmp;
	////////////////////////
	////cout<<endl<<strtmp;
	//////////////////////////


	if(CheckRegulation()==false){
		//cout<<endl<<"wrong regulation!";
		return false;
	}

	return true;
}

bool CLogicCal::CheckRegulation(){

	//Expression's format regulation

	//首位为 (, 字母, !
	string::iterator iter, begin,end;
	char ch1,ch2,ch3;
	begin = m_strExp.begin();
	end = m_strExp.end();
	ch1 = *begin;
	if(ch1!='('&&ch1!='!'&&!isalpha(ch1)){
		//cout<<endl<<"the first char is wrong!";
		return false;
	}
	for(iter = begin+1;iter!=end;iter++){
		ch1 = *iter;
		ch2 = *(iter+1);
		if(iter+1 == end) ch2 = '#';
		char ch3 = *(iter+2);

		//(->字母, !(逻辑非,不是!=中的!),  (
		if(ch1 == '('){
			if(ch2!='('&&ch2!='!'&&!isalpha(ch2)){
				//cout<<endl<<"(---> wrong";
				return false;
			}

			if(ch2=='!'&&ch3=='='){
				//cout<<endl<<"(---> wrong";
				return false;
			}

		}

		//字母--->字母, 关系运算符
		if(isalpha(ch1)){
			if(!IsRelation(ch2)&&ch2!='!'&&!isalpha(ch2)){
				//cout<<endl<<"字母---> wrong";
				return false;
			}
		}

		//关系运算符--->数字,=，+，-
		if(IsRelation(ch1)){
			if(!isdigit(ch2)&&ch2!='='&&ch2!='+'&&ch2!='-'){
				//cout<<endl<<"关系运算符---> wrong";
				return false;
			}

			if(ch2 == '='&&ch3 == '='){
				//cout<<endl<<"关系运算符---> wrong";
				return false;
			}
		}


		//数字--->数字, 小数点, ), 逻辑运算符, 空
		if(isdigit(ch1)){
			if(!isdigit(ch2)&&ch2!='.'&&ch2!=')'&&!IsLogic(ch2)&&ch2!='#'){
				//cout<<endl<<"数字---> wrong";
				return false;
			}
		}

		//小数点--->数字
		if(ch1=='.'){
			if(!isdigit(ch2)){
				//cout<<endl<<"小数点---> wrong";
				return false;

			}
		}


		//逻辑运算符--->(,  !(逻辑非,不是!=中的!),  字母
		if(IsLogic(ch1)){
			if(ch2!='('&&ch2!='!'&&!isalpha(ch2)&&ch2!='='){
				//cout<<endl<<"逻辑运算符---> wrong";
				return false;
			}
			if(ch1 != '!'&&ch2 == '='){
				//cout<<endl<<"逻辑运算符!---> wrong";
				return false;
			}
		}

		//)--->逻辑运算符, ), 空
		if(ch1==')'){
			if(!IsLogic(ch2)&&ch2!=')'&&ch2!='#'){
				//cout<<endl<<")---> wrong";
				return false;

			}
		}


	}

	return true;


}

bool CLogicCal::IsAccept(char ch){
	if(!isdigit(ch)) {
		if(!isalpha(ch)) {
			if(ch!='.'){
				if(ch!='>'&&ch!='<'&&ch!='!'&&ch!='=')
					if(ch!='&'&&ch!='!'&&ch!='|'&&ch!='('&&ch!=')'){
						if(ch!='+'&&ch!='-')
							return false;
					}
			}
		}
	}
	return true;
}

//not include !
bool CLogicCal::IsRelation(char ch){
	if(ch=='>'||ch=='<'||ch=='=')
		return true;
	else 
		return false;
}

bool CLogicCal::IsLogic(char ch){
	if(ch=='&'||ch=='|'||ch=='!')
		return true;
	else
		return false;
}



bool CLogicCal::LogicLize(){
	string strtmp;
	char ch1,ch2,ch3;
	string::iterator iter;
	for(iter = m_strExp.begin();iter!=m_strExp.end();iter++){
		ch1 = *iter;
		if(!isalpha(ch1))//如果不是关系表达式的一部分,按原样保存
			strtmp+=ch1;
		else{
			string paraname;

			//get the para name
			do{
				paraname+=ch1;
				iter++;
				ch1 = *iter;
			}while(isalpha(ch1));

			if(m_Paras.count(paraname) == 0){
				//cout<<"paraments not exist!"<<endl;
				return false;
			}

			string op;

			//get the relation operator
			op+=ch1;
			ch2 = *(iter+1);
			if(ch2 == '='){
				op+=ch2;
				iter++;
			}

			string numeric;

			//get the numerical value 

			ch1 = *(++iter);
			if(ch1 == '+'||ch1 =='-'){
				numeric+=ch1;
				ch1 = *(++iter);
			}
			while (isdigit(ch1)||ch1 == '.')
			{
				numeric += ch1;
				iter++;
				ch1 = *iter;

			}

			iter--;
			//calculate the values;
			double dleft = m_Paras[paraname];
			double dright = atof(numeric.c_str());
			char cresult = Compare(dleft,dright,op);


			strtmp+=cresult;

		}//else

	}//for

	m_strExp = strtmp;
	//cout<<m_strExp;
	return true;
}

char CLogicCal::Compare(double left,double right,string op){
	//根据运算符算出每个子关系表达式 的值
	char cresult;
	if(op == ">"){
		if(left>right) cresult = '1';
		else           cresult = '0';
	}

	if(op == ">="){
		if(left>=right) cresult = '1';
		else            cresult = '0';
	}

	if(op == "<"){
		if(left<right) cresult = '1';
		else           cresult = '0';
	}

	if(op == "<="){
		if(left<=right) cresult = '1';
		else            cresult = '0';
	}

	if(op == "!="){
		if(left!=right) cresult = '1';
		else           cresult = '0';
	}

	if(op == "=="){
		//if(left==right) cresult = '1';
		if(fabs(left-right)<0.00001) cresult = '1';
		else           cresult = '0';
	}
	//cout<<"关系子表达式："<<left<<op<<right<<endl;

	return cresult;

}



bool CLogicCal::PostFixLize(){
	if(LogicLize()!= true)
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

int CLogicCal::isp(char c){
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

int CLogicCal::icp(char c){
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


bool CLogicCal::Calculate(double &value){
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
	if(ch == '0')  return false;
	//cout<<endl<<"结果为："<<ch;

	return true;
}

void CLogicCal::AddOperand(char c){
	m_sOperand.push(c);
}

bool CLogicCal::Get1Operand(char &cOperand){
	if(m_sOperand.empty()){
		//cout<<"no operands!!!"<<endl;
		return false;
	}

	cOperand = m_sOperand.top();
	m_sOperand.pop();
	return true;
}

bool CLogicCal::Get2Operands(char &cLeft,char &cRight){
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


bool CLogicCal::SingleCalculate(char op){
	char left,right,operand;
	switch(op) {
	case '!':
		if(this->Get1Operand(operand) == true){
			if(operand == '1') m_sOperand.push('0');
			else m_sOperand.push('1');
		}
		break;

	case '&':
		if(this->Get2Operands(left,right)==true){
			if(left=='0'||right=='0') m_sOperand.push('0');
			else  m_sOperand.push('1');
		}
		break;

	case '|':
		if(this->Get2Operands(left,right)==true){
			if(left=='0'&&right=='0') m_sOperand.push('0');
			else  m_sOperand.push('1');
		}
		break;
	default:return false;
	}
	return true;
}

void CLogicCal::AddPara(string strpara,double dbValue /* = 0.0 */){
	m_Paras.insert(SdPair(strpara,dbValue));
}

void CLogicCal::DelPara(string strpara){
	m_Paras.erase(strpara);
}

void CLogicCal::SetParaValue(string strpara,double dbValue){
	m_Paras[strpara] = dbValue;
}

void CLogicCal::SetParas(map<string,double> Paras){
	m_Paras = Paras;
}