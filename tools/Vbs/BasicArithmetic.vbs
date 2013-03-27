' 
' This is a simple and funny vb script for you to practise your:
' 1. English listening for numbers
' 2. Swift calculation of 2 numbers
' You can adjust parameters to change difficulty, as default in only includes + and - operators
' for numbers between 0 - 100
'
' Author: Baiyan Huang
' Date: 10/20/2010
'
'==============================Main==============================
Dim bContinue 
bContinue = True
While bContinue
	' Generate expression and read aloud!
	Dim op1, op2, op
	op1 = GetOperand()
	op2 = GetOperand()
	op = GetOperator()

	Dim strExp
	strExp = op1 & op & op2 & "="
	CreateObject("SAPI.SpVoice").Speak strExp
	
	' Calculate the final result
	Dim result
	If op = "plus" then
		result = op1 + op2
	Elseif op = "minus" then
		result = op1 - op2
	Elseif op = "multiply" then
		result = op1 * op2
	Elseif op = "divided by" then
		result = op1 / op2
	End If
	
	' Print the expression and result in a clearer manner
	strExp = Replace(strExp, "plus", "+")
	strExp = Replace(strExp, "minus", "-")
	strExp = Replace(strExp, "multiply", "*")
	strExp = Replace(strExp, "divided by", "/")
	bContinue = MsgBox(strExp & result & vbCrLf & "Click Ok to continue!", vbOKCancel) <> vbCancel
WEnd

'================Utility Functions=======================
Function GetRandomNum(lowerbound, upperbound)
	call Randomize()
	GetRandomNum = Int((upperbound - lowerbound + 1) * Rnd + lowerbound)
End Function

Function GetOperand()
	GetOperand = GetRandomNum(1, 100) ' 0 - 100
End Function

Function GetOperator()
	Dim operators(3)
	operators(0) = "plus"
	operators(1) = "minus"
	operators(2) = "multiply"
	operators(3) = "divided by"

	Dim Index
	Index = GetRandomNum(0, 1) ' Only include + and - for now
	GetOperator = operators(Index)
End Function