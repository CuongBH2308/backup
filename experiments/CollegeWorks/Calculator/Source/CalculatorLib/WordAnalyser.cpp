// WordAnalyser.cpp: implementation of the CWordAnalyser class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "WordAnalyser.h"
#include<string.h>
//#include "Calculator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CWordAnalyser::CWordAnalyser(){
	
}


CWordAnalyser::~CWordAnalyser()
{
	
}


bool CWordAnalyser::IsAlpha(char ch){
	if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z'))
		return true;
	return false;
}

bool CWordAnalyser::IsNumber(char ch){
	if(ch >= '0' && ch <= '9')
		return true;
	return false;
}


//д╛хой╣ож

bool CWordAnalyser::GenerateWord(CCalculator& Cal){
	return true;
}

bool CWordAnalyser::IsOperator(char ch){
	
	return true;
}

bool CWordAnalyser::AnalyseWords(char* Expression,CCalculator& Cal){
	
	return true;
}