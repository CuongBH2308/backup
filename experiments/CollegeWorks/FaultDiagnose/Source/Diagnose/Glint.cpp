// Glint.cpp: implementation of the CGlint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Diagnose.h"
#include "Glint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlint::CGlint()
{
	m_glintNode=NULL;
	m_glintBmp=FALSE;
	m_bmpIndex=-1;
}

CGlint::~CGlint()
{
	m_glintNode=NULL;
}

BOOL CGlint::IsActiveGlint()
{
	return (m_glintNode!=NULL);
}

void CGlint::BeginNode(Node *pNode)
{
	if (pNode==NULL) return;
    m_glintNode=pNode;
}

void CGlint::EndNode()
{
	m_glintNode=NULL;
}

void CGlint::BeginBmp(int index)
{
	m_bmpIndex=index;
}

void CGlint::EndBmp()
{
	m_bmpIndex=-1;
}

BOOL CGlint::IsActiveBmp()
{
	return (m_bmpIndex!=-1);
}
