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
#include "gr_dlnode.h"
#include "gr_collect.h"

class GR_DLNodeGrids;
class DR_DCtSketch2D;
class GR_DLNodeSketch2D : public GR_DLNode
{
public:
	GR_DLNodeSketch2D(const SL_Ptr<GR_DLNode>& pDLNode, 
		const SL_Ptr<DR_DCtSketch2D>& pDCtSketch2D);
	virtual ~GR_DLNodeSketch2D(void);

	// Get active sketch node 
	// Recursive search pDLNode and its children
	static GR_DLNodeSketch2D* GetActive(const SL_Ptr<GR_DLNode>& pDLNode);

	// Get DCtSketch2D
	const SL_Ptr<DR_DCtSketch2D>& GetDCtSketch2D() const;

	// Set the sketch node active or not
	// Only active sketch can be edited.
	void SetActive(bool bActive);

	// Whether this sketch is active
	bool GetActive() const;

	// Update DL according to m_StDLMap
	void Update();

	// Update m_StDLMap
	void Add(const SL_Ptr<DR_St> pSt, const SL_Ptr<GR_DL>& pDL);

	// Update m_StDLMap
	void Add(const SL_Ptr<DR_St> pSt, const GR_DLPtrVect& vDL);

	// Get GR_DLPtrVect
	const GR_DLPtrVect& Get(const SL_Ptr<DR_St> pSt) const;

	// Look for DR_St that contains pDL
	SL_Ptr<DR_St> Get(const SL_Ptr<GR_DL>& pDL) const;
private:
	// The plane that this node depends on
	SL_Ptr<DR_DCtSketch2D>	m_pDCtSketch2D;

	// Grids
	SL_Ptr<GR_DLNodeGrids>	m_pDLNodeGrids;

	// m_bActive is true if the user is editing a sketch
	bool					m_bActive;

	// St1 -- [DL, DL, ...]1
	// St2 -- [DL, DL, ...]2
	// A map used to store the relationship between the St and a serial of DLs
	// Such as: DR_StCrv -- GR_DLCrv
	StDLMap				m_StDLMap;
};
