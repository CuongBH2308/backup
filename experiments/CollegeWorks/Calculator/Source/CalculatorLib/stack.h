/*�Զ����ջģ����*/

//��Ϊ�޷�������룬ʵ��Ҳ����ͷ�ļ���
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


	void Push(T data) //��β������һ�����
	{
		Node* tem;   
		tem = Head->Next;  //tem = NULL,����
		Head->Next = new Node;
		Head->Next->Next = tem;
		Head->Next->Data = data;
	}
	


	BOOL Pop(T& data)//��β�����һ����㣬�������ջ��ɾ��
	{
		if(Head->Next)
		{
			data = Head->Next->Data;
			Node* tem = Head->Next->Next;//����NULL
			delete Head->Next;
			Head->Next = tem;
			return TRUE;
		}
		else
			return FALSE;
	}

	BOOL GetTop(T& data)//���ջ�����
	{
		if(Head->Next)
		{
			data = Head->Next->Data;
			return TRUE;
		}
		return FALSE;
	}

	virtual ~CStack()//��ͷ��ʼ���ɾ�����
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