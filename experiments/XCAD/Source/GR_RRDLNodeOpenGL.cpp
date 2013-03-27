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


#include "stdafx.h"
#include "gr_rrdlnodeopengl.h"
#include <gl\gl.h>
#include "gr_dlnode.h"

GR_RRDLNodeOpenGL::GR_RRDLNodeOpenGL(GR_DLNode* pDLNode)
:GR_RRDLNode(pDLNode)
{
}

GR_RRDLNodeOpenGL::~GR_RRDLNodeOpenGL(void)
{
}

// Render the display list node
// virtual 
bool GR_RRDLNodeOpenGL::OnRender() const
{
	::glPushAttrib(GL_TRANSFORM_BIT);
	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glMultMatrixf(&m_pDLNode->GetTransform().Transpose()[0]);
	bool bOK = GR_RRDLNode::OnRender();
	::glPopMatrix();
	::glPopAttrib();
	return bOK;
}