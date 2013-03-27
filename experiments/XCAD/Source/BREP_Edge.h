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
#include "sl_ptr.h"

class MH_Crv;
class BREP_CoEdge;
class BREP_Vertex;
class BREP_Edge : public BREP_Entity
{
public:
	// The constructed Edge is owned by pCoEdge
	BREP_Edge(const SL_Ptr<BREP_CoEdge>& pCoEdge);

	// The constructed Edge is owned by pCoEdge
	BREP_Edge(const SL_Ptr<BREP_CoEdge>& pCoEdge, const SL_Ptr<MH_Crv>& crv,
		const SL_Ptr<BREP_Vertex>& pVtxStart, const SL_Ptr<BREP_Vertex>& pVtxEnd);

	// De-constructor
	virtual ~BREP_Edge(void);

	// The constructed shell is copied from pEdge, and it is owned by pCoEdge
	BREP_Edge*					Copy(const SL_Ptr<BREP_CoEdge>& pCoEdge);

	// Set m_pCoEdge
	void						SetCoEdge(const SL_Ptr<BREP_CoEdge>& pCoEdge);

	// Get m_pCoEdge
	const SL_Ptr<BREP_CoEdge>&	GetCoEdge() const;

	// Set m_pCrv
	void						SetCrv(const SL_Ptr<MH_Crv>& pCrv);

	// Get m_pCrv
	const SL_Ptr<MH_Crv>&		GetCrv() const;

	// Set start vertex
	void						SetStartVertex(const SL_Ptr<BREP_Vertex>& pVertex);

	// Get start vertex
	const SL_Ptr<BREP_Vertex>&	GetStartVertex() const;

	// Set end vertex
	void						SetEndVertex(const SL_Ptr<BREP_Vertex>& pVertex);

	// Get end vertex
	const SL_Ptr<BREP_Vertex>&	GetEndVertex() const;
private:
	// The Co-edge lies on this edge
	SL_Ptr<BREP_CoEdge> m_pCoEdge;

	// Geometry information
	SL_Ptr<MH_Crv>		m_pCrv;

	// Start vertex
	SL_Ptr<BREP_Vertex> m_pVtxStart;

	// End vertex
	SL_Ptr<BREP_Vertex> m_pVtxEnd;
};
