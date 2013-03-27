// Glint.h: interface for the CGlint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLINT_H__EE015F45_4D35_4CE4_A596_F43219C6B645__INCLUDED_)
#define AFX_GLINT_H__EE015F45_4D35_4CE4_A596_F43219C6B645__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGlint  
{
public:
	BOOL IsActiveBmp();
	void EndBmp();
	void BeginBmp(int index);
	void EndNode();
	void BeginNode(Node *pNode);
	BOOL IsActiveGlint();
	CGlint();
	virtual ~CGlint();
//设置变量
	Node *m_glintNode; //闪烁节点
	BOOL *m_glintBmp;
	int m_bmpIndex;

};

#endif // !defined(AFX_GLINT_H__EE015F45_4D35_4CE4_A596_F43219C6B645__INCLUDED_)
