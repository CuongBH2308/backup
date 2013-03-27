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
#include ".\uc_rotatedlnode.h"
#include <math.h>
#include "MH_Point3.h"
#include "MH_CrvCircle.h"
#include "GR_RRManager.h"
#include "GR_RR.h"
#include "GR_DLCrv.h"
#include "GR_DLAttribColor.h"

UC_RotateDLNode::UC_RotateDLNode(GR_RR* pRR, GR_DLNode* pDLNode)
:GR_DLNode(pRR, pDLNode)
{
	// Get projection matrix. It is an orthographic matrix.
	MH_Matrix44 mtxProjection = pRR->GetMatrix(GR_RR::eProjection);

	//MH_Point3 ptCenter((fLeft+fRight)/2.0f, (fBottom+fTop)/2.0f, 0.0f);
	//float fRadius = min(abs(fRight-fLeft)/2.0f, abs(fTop-fBottom)/2.0f)*0.8f;
	MH_Point3 ptCenter(-mtxProjection[3]/mtxProjection[0], -mtxProjection[7]/mtxProjection[5], 0.0f);
	float fRadius = min(abs(1.0f/mtxProjection[0]), abs(1.0f/mtxProjection[5]))*0.8f;

	m_pDLCrv = new GR_DLCrv(this, new MH_CrvCircle(ptCenter, MH_Vector3(0.0f,0.0f,1.0f), fRadius));
	m_pDLCrv->AddAttrib(new GR_DLAttribColor(GR_Color(1.0f, 1.0f, 1.0f, 1.0f)));
}

UC_RotateDLNode::~UC_RotateDLNode(void)
{
	if(m_pDLCrv && m_pDLCrv->GetCrv())
		delete m_pDLCrv->GetCrv();
}

// Get m_pDLCrv;
GR_DLCrv* UC_RotateDLNode::GetDL() const
{
	return m_pDLCrv;
}

// Render the child nodes and display list
// virtual
bool UC_RotateDLNode::Render() const
{
	GR_RR* pRR = GetRR();
	if(!pRR)
		return false;

	// Backup current Model-View matrix
	MH_Matrix44 mtxModelView = pRR->GetMatrix(GR_RR::eModelView);

	// Backup current Projection matrix
	MH_Matrix44 mtxProjection = pRR->GetMatrix(GR_RR::eProjection);

	// Reset the Model-View matrix
	pRR->SetMatrix(GR_RR::eModelView, MH_Matrix44());

	// Reset the Projection matrix
	MH_Matrix44 mtxProjTemp = mtxProjection;
	mtxProjTemp[3] = 0.0;
	mtxProjTemp[7] = 0.0;
	mtxProjTemp[11] = 0.0;
	pRR->SetMatrix(GR_RR::eProjection, mtxProjTemp);

	// Render the node
	bool bOK = GR_DLNode::Render();

	// Restore the Model-View matrix
	pRR->SetMatrix(GR_RR::eModelView, mtxModelView);

	// Restore the Projection matrix
	pRR->SetMatrix(GR_RR::eProjection, mtxProjection);

	return bOK;
}