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


#pragma once
#include "brep_entity.h"
#include "brep_collect.h"
#include "mh_point3.h"

class BREP_Vertex :	public BREP_Entity
{
public:
	// The constructed Vertex is owned by pEdge
	BREP_Vertex(const SL_Ptr<BREP_Edge>& pEdge);

	// The constructed Vertex is owned by pEdge
	BREP_Vertex(const SL_Ptr<BREP_Edge>& pEdge, const MH_Point3& pt);

	// De-constructor
	virtual ~BREP_Vertex(void);

	// Copy the entity
	BREP_Vertex* Copy(const SL_Ptr<BREP_Edge>& pEdge);

	// Set edge to m_pEdge
	void SetEdge(const SL_Ptr<BREP_Edge>& pEdge);

	// Get m_pEdge
	const SL_Ptr<BREP_Edge>& GetEdge() const;

	// Get all edges lie on this vertex
	BREP_EdgePtrVect GetEdges() const;

	// Set point
	void SetPt(const MH_Point3& pt);

	// Get point
	const MH_Point3& GetPt() const;
private:
	// One Edge that own the vertex
	SL_Ptr<BREP_Edge>	m_pEdge;

	// Geometry information
	MH_Point3			m_pt;
};
