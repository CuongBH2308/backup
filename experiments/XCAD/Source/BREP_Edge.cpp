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
#include "brep_edge.h"
#include "brep_coedge.h"
#include "sl_mm.h"

// The constructed Edge is owned by pCoEdge
BREP_Edge::BREP_Edge(const SL_Ptr<BREP_CoEdge>& pCoEdge)
:m_pCoEdge(pCoEdge)
{
	if(m_pCoEdge.GetTarget())
		m_pCoEdge->SetEdge(this);
}

// The constructed Edge is owned by pCoEdge
BREP_Edge::BREP_Edge(const SL_Ptr<BREP_CoEdge>& pCoEdge, const SL_Ptr<MH_Crv>& pCrv,
					 const SL_Ptr<BREP_Vertex>& pVtxStart, const SL_Ptr<BREP_Vertex>& pVtxEnd)
:m_pCoEdge(pCoEdge),
m_pCrv(pCrv),
m_pVtxStart(pVtxStart),
m_pVtxEnd(pVtxEnd)
{
	if(m_pCoEdge.GetTarget())
		m_pCoEdge->SetEdge(this);
}

// De-constructor
BREP_Edge::~BREP_Edge(void)
{
}

// Copy the entity
BREP_Edge* BREP_Edge::Copy(const SL_Ptr<BREP_CoEdge>& pCoEdge)
{
	return NEW_OBJ(BREP_Edge, pCoEdge.GetTarget())(pCoEdge);
}

// Set m_pCoEdge
void BREP_Edge::SetCoEdge(const SL_Ptr<BREP_CoEdge>& pCoEdge)
{
	m_pCoEdge = pCoEdge;
}

// Get m_pCoEdge
const SL_Ptr<BREP_CoEdge>& BREP_Edge::GetCoEdge() const
{
	return m_pCoEdge;
}

// Set m_pCrv
void BREP_Edge::SetCrv(const SL_Ptr<MH_Crv>& pCrv)
{
	m_pCrv = pCrv;
}

// Get m_pCrv
const SL_Ptr<MH_Crv>& BREP_Edge::GetCrv() const
{
	return m_pCrv;
}

// Set start vertex
void BREP_Edge::SetStartVertex(const SL_Ptr<BREP_Vertex>& pVertex)
{
	m_pVtxStart = pVertex;
}

// Get start vertex
const SL_Ptr<BREP_Vertex>& BREP_Edge::GetStartVertex() const
{
	return m_pVtxStart;
}


// Set end vertex
void BREP_Edge::SetEndVertex(const SL_Ptr<BREP_Vertex>& pVertex)
{
	m_pVtxEnd = pVertex;
}

// Get end vertex
const SL_Ptr<BREP_Vertex>& BREP_Edge::GetEndVertex() const
{
	return m_pVtxEnd;
}