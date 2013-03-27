#include<iostream>
#include "LogicWordAnalyser.h"
#include "LogicSyntaxAnalyser.h"
#include "LogicPriorityTable.h"
#include "Calculator.h"
#include "ArithWordAnalyser.h"
#include "ArithSyntaxAnalyser.h"
#include "ArithPriorityTable.h"

using namespace std;

int main(){
	
/*	while(1){
	
	char str[100];
	cout<<"please input expression:";
	cin>>str;
	CCalculator c(str);
	CArithWordAnalyser lwa;//("U>0",c);

	if(lwa.AnalyseWords(str,c))
		cout<<"word analyse right\n";
	else
		cout<<"word analyse wrong\n";

	CArithSyntaxAnalyser asa;

	if(asa.AnalyseSyntax(c))
		cout<<"syntax analyse right\n";
	else
		cout<<"syntax analyse wrong\n";

	}
	*/

	//CLogicSyntaxAnalyser lsa;
	//CLogicPriorityTable lpt;
	//CCalculator c(lwa,lsa,lpt,str);

    
	while(1){
		
		char str[100];
		cout<<"please input expression:";
		cin>>str;
		CLogicWordAnalyser lwa;//("U>0",c);
		CLogicSyntaxAnalyser lsa;
		CLogicPriorityTable lpt;
		//CCalculator c(lwa,lsa,lpt,str);

		CArithWordAnalyser awa;//("U>0",c);
		CArithSyntaxAnalyser asa;
		CArithPriorityTable apt;
		CCalculator ca(awa,asa,apt,str);
		ca.AddVariable("u",3);
		ca.AddVariable("i",4);
		double dResult;
		int iresult = ca.Calculate(dResult);
		if(WORD_ERR == iresult)
			cout<<"word analyse wrong\n";
		else if(SYNTAX_ERR == iresult)
			cout<<"syntax analyse wrong\n";
		else if(NO_VALUE == iresult)
			cout<<"varible has no value\n";
		else if(OPERATOR_ERR == iresult)
			cout<<"Operator wrong\n";
		else{
			cout<<"the result is:"<<dResult<<endl;
		}
	}
	
		/*if(lwa.AnalyseWords(str,c)){
			cout<<"words analyse true\n";

			if(lsa.AnalyseSyntax(c))
				cout<<"syntax analyse true\n";
			else
				cout<<"syntax analyse wrong\n";
		}
		else
			cout<<"words analyse wrong\n";
	}
	//lwa.GenerateWord();*/
	return 1;
}




















