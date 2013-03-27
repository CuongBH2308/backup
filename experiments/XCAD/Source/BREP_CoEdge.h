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

/************************************************************************/
/* 
							   Body
								|
						  |----------
					     Lump
						  |
					  |-------
					Shell
					  |
				 |--------
				Face
				 |
			 |--------
			Loop
			 |
		  |----	 
	    CoEdge

*/
/************************************************************************/
class BREP_Edge;
class BREP_CoEdge :	public BREP_Entity
{
public:
	// The constructed CoEdge is owned by pEntity
	BREP_CoEdge(const SL_Ptr<BREP_Entity>& pEntity);

	// The constructed CoEdge is owned by pEntity
	BREP_CoEdge(const SL_Ptr<BREP_Entity>& pEntity, const SL_Ptr<BREP_Edge>& pEdge);

	// De-constructor
	virtual ~BREP_CoEdge(void);

	// Copy the entity
	BREP_CoEdge* Copy(const SL_Ptr<BREP_Entity>& pEntity);

	// Get m_pEntity
	const SL_Ptr<BREP_Entity>& GetEntity() const;

	// Set m_pEdge
	void SetEdge(const SL_Ptr<BREP_Edge>& pEdge);

	// Get m_pEdge
	const SL_Ptr<BREP_Edge>& GetEdge() const;

	// Set reverse flag
	void SetRev(bool bRev);

	// Is reversed
	bool GetRev() const;
private:
	// Owner of this co-edge
	// It can be a loop or wire
	SL_Ptr<BREP_Entity>	m_pEntity;

	// The co-edge lies on the edge
	SL_Ptr<BREP_Edge> m_pEdge;

	// If the face's normal is upward, the tangent of the edge is forward,
	// then the face is in the left
	// clockwise rule
	// This flag determine whether the co-edge is reversed to the edge
	bool m_bRev;
};
