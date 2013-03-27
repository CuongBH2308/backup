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
#include "brep_wire.h"
#include <map>
#include "brep_coedge.h"
#include "brep_edge.h"
#include "sl_mm.h"

// The constructed wire is owned by pEntity
BREP_Wire::BREP_Wire(const SL_Ptr<BREP_Entity>& pEntity)
:m_pEntity(pEntity)
{
}

// The constructed wire is owned by pEntity
BREP_Wire::BREP_Wire(const SL_Ptr<BREP_Entity>& pEntity, const BREP_CoEdgePtrVect& vCoEdge)
:m_pEntity(pEntity),
m_vCoEdge(vCoEdge)
{
}

// De-constructor
BREP_Wire::~BREP_Wire(void)
{
}

// Copy the entity
BREP_Wire* BREP_Wire::Copy(const SL_Ptr<BREP_Entity>& pEntity)
{
	BREP_Wire* pWire = NEW_OBJ(BREP_Wire, pEntity.GetTarget())(pEntity);
	if(pWire)
	{
		std::map<SL_Ptr<BREP_Edge>, BREP_CoEdgePtrVect> mEdge_CoEdges;
		BREP_CoEdgePtrVect::const_iterator itCoEdge		= m_vCoEdge.begin();
		BREP_CoEdgePtrVect::const_iterator itCoEdgeEnd	= m_vCoEdge.end();
		for(; itCoEdge!=itCoEdgeEnd; ++itCoEdge)
		{
			SL_Ptr<BREP_Edge> pEdge = (*itCoEdge)->GetEdge();
			ASSERT(pEdge.GetTarget());
			mEdge_CoEdges[pEdge].push_back(*itCoEdge);
		}

		std::map<SL_Ptr<BREP_Edge>, BREP_CoEdgePtrVect>::const_iterator it = mEdge_CoEdges.begin();
		std::map<SL_Ptr<BREP_Edge>, BREP_CoEdgePtrVect>::const_iterator itEnd = mEdge_CoEdges.end();
		for(; it!=itEnd; ++it)
		{
			BREP_Edge* pEdge = (it->first)->Copy(pWire);
			ASSERT(pEdge);

			itCoEdge	= it->second.begin();
			itCoEdgeEnd	= it->second.end();
			for(; itCoEdge!=itCoEdgeEnd; ++itCoEdge)
			{
				BREP_CoEdge* pCoEdge = (*itCoEdge)->Copy(pWire);
				ASSERT(pCoEdge);
				if(pCoEdge)
				{
					pCoEdge->SetEdge(pEdge);
					pWire->AddCoEdge(pCoEdge);
				}
			}
		}
	}

	return pWire;
}

// Get m_pEntity
const SL_Ptr<BREP_Entity>& BREP_Wire::GetEntity() const
{
	return m_pEntity;
}

// Add CoEdge into m_vCoEdge
void BREP_Wire::AddCoEdge(const SL_Ptr<BREP_CoEdge>& pCoEdge)
{
	m_vCoEdge.push_back(pCoEdge);
}

// Get m_vCoEdge
const BREP_CoEdgePtrVect& BREP_Wire::GetCoEdges() const
{
	return m_vCoEdge;
}