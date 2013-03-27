/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "StdAfx.h"
#include ".\gr_rropengldlnode.h"
#include "GR_DLNode.h"
#include <Gl\Gl.h>

GR_RROpenGLDLNode::GR_RROpenGLDLNode(GR_DLNode* pDLNode)
:GR_RRDLNode(pDLNode)
{
}

GR_RROpenGLDLNode::~GR_RROpenGLDLNode(void)
{
}

// Render the display list node
// virtual 
bool GR_RROpenGLDLNode::OnRender() const
{
	if(!m_pDLNode)
		return false;

	// The glMultMatrix function multiplies the current matrix by the one specified in m. 
	// That is, if M is the current matrix and T is the matrix passed to glMultMatrix, 
	// then M is replaced with M*T.

	// Select the Model View Matrix
	::glMultMatrixf(&(m_pDLNode->GetTransform().Transpose()[0]));

	return true;
}