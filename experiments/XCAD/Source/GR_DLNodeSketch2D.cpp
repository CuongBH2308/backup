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
#include <algorithm>
#include "gr_dlnodesketch2d.h"
#include "gr_dlnodegrids.h"
#include "gr_dlcrv.h"
#include "gr_dlpoint.h"
#include "gr_selectorsketch.h"
#include "dr_stxform.h"
#include "dr_dctsketch2d.h"
#include "dr_stcrvlineseg.h"
#include "dr_stcrvnurbs.h"
#include "dr_stpoint.h"
#include "sl_mm.h"

GR_DLNodeSketch2D::GR_DLNodeSketch2D(const SL_Ptr<GR_DLNode>& pDLNode, 
									 const SL_Ptr<DR_DCtSketch2D>& pDCtSketch2D)
:GR_DLNode(pDLNode, new GR_SelectorSketch()),
m_pDCtSketch2D(pDCtSketch2D),
m_bActive(false)
{
	// Get the transform of the sketch
	const SL_Ptr<DR_StXform>& pStXform = m_pDCtSketch2D->GetStXform();
	ASSERT(pStXform.GetTarget());

	//m_pDLNodeGrids = NEW_OBJ(GR_DLNodeGrids, this)(this, pStXform);
	//ASSERT(m_pDLNodeGrids.GetTarget());
}

GR_DLNodeSketch2D::~GR_DLNodeSketch2D(void)
{
}

// Get active sketch node 
// Recursive search pDLNode and its children
// static 
GR_DLNodeSketch2D* GR_DLNodeSketch2D::GetActive(const SL_Ptr<GR_DLNode>& pDLNode)
{
	// Get DLNodes and DLs
	GR_DLNodePtrVect*	pDLNodeVect = NULL;
	GR_DLPtrVect*	pDLVect = NULL;
	pDLNode->GetChildren(pDLNodeVect, pDLVect);

	// Look for the active sketch node
	GR_DLNodePtrVect::const_iterator itDLNode;
	GR_DLNodePtrVect::const_iterator itDLNodeBegin	= pDLNodeVect->begin();
	GR_DLNodePtrVect::const_iterator itDLNodeEnd	= pDLNodeVect->end();
	for(itDLNode=itDLNodeBegin; itDLNode!=itDLNodeEnd; ++itDLNode)
	{
		GR_DLNodeSketch2D* pDLNodeSketch2D = dynamic_cast<GR_DLNodeSketch2D*>((*itDLNode).GetTarget());
		if(pDLNodeSketch2D && pDLNodeSketch2D->GetActive())
			return pDLNodeSketch2D;
	}

	for(itDLNode=itDLNodeBegin; itDLNode!=itDLNodeEnd; ++itDLNode)
		return GetActive(*itDLNode);

	return NULL;
}

// Get DCtSketch2D
const SL_Ptr<DR_DCtSketch2D>& GR_DLNodeSketch2D::GetDCtSketch2D() const
{
	return m_pDCtSketch2D;
}

void GR_DLNodeSketch2D::SetActive(bool bActive)
{
	m_bActive = bActive;
}

bool GR_DLNodeSketch2D::GetActive() const
{
	return m_bActive;
}

// Update m_StDLMap
void GR_DLNodeSketch2D::Add(const SL_Ptr<DR_St> pSt, const SL_Ptr<GR_DL>& pDL)
{
	StDLMap::iterator it = m_StDLMap.find(pSt);
	if(it == m_StDLMap.end())
		m_StDLMap[pSt].push_back(pDL);
	else
	{
		GR_DLPtrVect* pvDL = &it->second;
		GR_DLPtrVect::const_iterator itDL = std::find(pvDL->begin(), pvDL->end(), pDL);
		if(itDL == pvDL->end())
			pvDL->push_back(pDL);
	}
}

// Update m_StDLMap
void GR_DLNodeSketch2D::Add(const SL_Ptr<DR_St> pSt, const GR_DLPtrVect& vDL)
{
	GR_DLPtrVect::const_iterator it = vDL.begin();
	GR_DLPtrVect::const_iterator itEnd = vDL.end();
	for(; it!=itEnd; ++it)
		Add(pSt, *it);
}

// Get GR_DLPtrVect
const GR_DLPtrVect& GR_DLNodeSketch2D::Get(const SL_Ptr<DR_St> pSt) const
{
	StDLMap::const_iterator it = m_StDLMap.find(pSt);
	ASSERT(it != m_StDLMap.end());
	return it->second;
}

// Look for DR_St that contains pDL
SL_Ptr<DR_St> GR_DLNodeSketch2D::Get(const SL_Ptr<GR_DL>& pDL) const
{
	StDLMap::const_iterator it		= m_StDLMap.begin();
	StDLMap::const_iterator itEnd	= m_StDLMap.end();

	for(; it!=itEnd; ++it)
	{
		GR_DLPtrVect::const_iterator itDL = std::find(it->second.begin(), it->second.end(), pDL);
		if(itDL != it->second.end())
			return (it->first);
	}
	return NULL_PTR(DR_St);
}

// Update DL according to m_StDLMap
void GR_DLNodeSketch2D::Update()
{
	StDLMap::iterator it	= m_StDLMap.begin();
	StDLMap::iterator itEnd	= m_StDLMap.end();

	for(; it!=itEnd; ++it)
	{
		DR_St* pSt = it->first.GetTarget();
		GR_DLPtrVect *pvDL = &it->second;

		DR_StPoint* pStPoint = dynamic_cast<DR_StPoint*>(pSt);
		DR_StCrvLineSeg* pStCrvLineSeg = dynamic_cast<DR_StCrvLineSeg*>(pSt);
		DR_StCrvNurbs* pStCrvNurbs = dynamic_cast<DR_StCrvNurbs*>(pSt);
		if(pStPoint)
		{
			ASSERT(pvDL->size() == 1);
			GR_DLPoint* pDLPoint = dynamic_cast<GR_DLPoint*>(pvDL->front().GetTarget());
			ASSERT(pDLPoint);
			*(pDLPoint->GetPoint()) = pStPoint->GetPoint();
			pDLPoint->Invalidate();
		}
		else if(pStCrvLineSeg)
		{
			ASSERT(pvDL->size() == 1);
			GR_DLCrv* pDLCrv = dynamic_cast<GR_DLCrv*>(pvDL->front().GetTarget());
			ASSERT(pDLCrv);
			MH_CrvLineSeg* pCrvLineSeg = dynamic_cast<MH_CrvLineSeg*>(pDLCrv->GetCrv().GetTarget());
			ASSERT(pCrvLineSeg);
			*pCrvLineSeg = pStCrvLineSeg->GetLineSeg();
			pDLCrv->Invalidate();
		}
		else if(pStCrvNurbs)
		{
			ASSERT(pvDL->size() == 1);
			GR_DLCrv* pDLCrv = dynamic_cast<GR_DLCrv*>(pvDL->front().GetTarget());
			ASSERT(pDLCrv);
			MH_CrvNurbs* pCrvNurbs = dynamic_cast<MH_CrvNurbs*>(pDLCrv->GetCrv().GetTarget());
			ASSERT(pCrvNurbs);
			*pCrvNurbs = pStCrvNurbs->GetNurbs();
			pCrvNurbs->Invalidate(true);
			pDLCrv->Invalidate();
		}
		else
		{
			ASSERT(0);
		}
	}
}