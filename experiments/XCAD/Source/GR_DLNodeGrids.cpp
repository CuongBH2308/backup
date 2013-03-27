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
#include "gr_dlnodegrids.h"
#include "dr_stxform.h"
#include "mh_crvlineseg.h"
#include "gr_dlcrv.h"
#include "gr_dlattribtransform.h"
#include "sl_mm.h"

#define HALF_X_WIDTH	20.0f
#define HALF_Y_WIDTH	20.0f
#define STEP	1.0f

GR_DLNodeGrids::GR_DLNodeGrids(const SL_Ptr<GR_DLNode>& pDLNode,
							   const SL_Ptr<DR_StXform>& pStXform)
:GR_DLNode(pDLNode),
m_pStXform(pStXform)
{
	MH_CrvLineSeg* pLineSeg = NULL;
	GR_DLCrv* pCrv = NULL;
	for(float i = 0; i < HALF_X_WIDTH; i += STEP)
	{
		pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(i,-HALF_Y_WIDTH,0), MH_Point3(i,HALF_Y_WIDTH,0));
		pCrv = NEW_OBJ(GR_DLCrv, this)(this, pLineSeg);
		m_vDLCrvGrids.push_back(pCrv);

		if(i>0)
		{
			pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(-i,-HALF_Y_WIDTH,0), MH_Point3(-i,HALF_Y_WIDTH,0));
			pCrv = NEW_OBJ(GR_DLCrv, this)(this, pLineSeg);
			m_vDLCrvGrids.push_back(pCrv);
		}
	}

	for(float i = 0; i < HALF_Y_WIDTH; i += STEP)
	{
		pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(-HALF_X_WIDTH,i,0), MH_Point3(HALF_X_WIDTH,i,0));
		pCrv = NEW_OBJ(GR_DLCrv, this)(this, pLineSeg);
		m_vDLCrvGrids.push_back(pCrv);

		if(i>0)
		{
			pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(-HALF_X_WIDTH,-i,0), MH_Point3(HALF_X_WIDTH,-i,0));
			pCrv = NEW_OBJ(GR_DLCrv, this)(this, pLineSeg);
			m_vDLCrvGrids.push_back(pCrv);
		}
	}

	// Set transform matrix
	SetTransform(m_pStXform->GetXform());
}

GR_DLNodeGrids::~GR_DLNodeGrids(void)
{
	//// Delete the child display lists
	//for(GR_DLCrvPtrVect::iterator it = m_vDLCrvGrids.begin(); it != m_vDLCrvGrids.end(); it++)
	//{
	//	// Delete MH obj
	//	if((*it).GetTarget())
	//		DEL_OBJ((*it)->GetCrv().GetTarget());
	//}
	m_vDLCrvGrids.clear();
}

// Render the child nodes and display list
// We should adjust the h/w of the grid here according to the view
// virtual 
bool GR_DLNodeGrids::Render()
{
	// Re-set transform matrix
	SetTransform(m_pStXform->GetXform());

	// Start to apply the attributes and render
	return GR_DLNode::Render();
}