/*自定义堆栈模板类*/

//因为无法分离编译，实现也放在头文件中
#ifndef _STACK_H
#define _STACK_H

#include<windows.h>
template<class T>
class CStack  
{
public:
	CStack()
	{
		Head = new Node;
		Head->Next = NULL;
	}


	void Push(T data) //在尾部加入一个结点
	{
		Node* tem;   
		tem = Head->Next;  //tem = NULL,保存
		Head->Next = new Node;
		Head->Next->Next = tem;
		Head->Next->Data = data;
	}
	


	BOOL Pop(T& data)//从尾部获得一个结点，并将其从栈中删除
	{
		if(Head->Next)
		{
			data = Head->Next->Data;
			Node* tem = Head->Next->Next;//保存NULL
			delete Head->Next;
			Head->Next = tem;
			return TRUE;
		}
		else
			return FALSE;
	}

	BOOL GetTop(T& data)//获得栈顶结点
	{
		if(Head->Next)
		{
			data = Head->Next->Data;
			return TRUE;
		}
		return FALSE;
	}

	virtual ~CStack()//从头开始逐个删除结点
	{
		Node* pNode = Head;
		Node* tem;
		while(pNode)
		{
			tem = pNode->Next;
			delete pNode;
			pNode = tem;
		}
	}


protected:
	struct Node
	{
		T Data;
		Node* Next;
	};

	Node* Head;

};

#endif