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
#include "brep_vertex.h"
#include "brep_edge.h"
#include "sl_mm.h"

// The constructed Vertex is owned by pEdge
BREP_Vertex::BREP_Vertex(const SL_Ptr<BREP_Edge>& pEdge)
:m_pEdge(pEdge)
{
}

// The constructed Vertex is owned by pEdge
BREP_Vertex::BREP_Vertex(const SL_Ptr<BREP_Edge>& pEdge, const MH_Point3& pt)
:m_pEdge(pEdge),
m_pt(pt)
{
}

// De-constructor
BREP_Vertex::~BREP_Vertex(void)
{
}

// Copy the entity
BREP_Vertex* BREP_Vertex::Copy(const SL_Ptr<BREP_Edge>& pEdge)
{
	return NEW_OBJ(BREP_Vertex, pEdge.GetTarget())(pEdge, m_pt);
}

// Set edge to m_pEdge
void BREP_Vertex::SetEdge(const SL_Ptr<BREP_Edge>& pEdge)
{
	m_pEdge = pEdge;
}

// Get m_pEdge
const SL_Ptr<BREP_Edge>& BREP_Vertex::GetEdge() const
{
	return m_pEdge;
}

// Get all edges lie on this vertex
BREP_EdgePtrVect BREP_Vertex::GetEdges() const
{
	BREP_EdgePtrVect vEdge;
	return vEdge;
}

// Set point
void BREP_Vertex::SetPt(const MH_Point3& pt)
{
	m_pt = pt;
}

// Get point
const MH_Point3& BREP_Vertex::GetPt() const
{
	return m_pt;
}