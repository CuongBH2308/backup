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
#include "mh_matrix44.h"
#include "mh_point3.h"

/************************************************************************/
/* 
										Body
										 |
									|---------
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
					|---------	 
				 CoEdge (Edge, bDir)

 Definition:
 1. Start point of CoEdge: if bDir is true, then it is the start point of Edge, otherwise, it is the end point of Edge
 2. End point of CoEdge: if bDir is true, then it is the end point of Edge, otherwise, it is the start point of Edge

 Assuming a short man is in atmosphere (not in a solid), stands on a face:
 Assuming he stands at the start point of CoEdge, facing to the end point of CoEdge, then
 1. His LEFT hand is in the face 
 2. His head is in a shell

*/
/************************************************************************/
class BREP_Body : public BREP_Entity
{
public:
	BREP_Body(void);
	virtual ~BREP_Body(void);

#ifdef _DEBUG
	// Dump the fragment into a file
	// if bRunDotty is true, then run dotty.exe
	// Refer to http:www.graphviz.org/ for this tool
	void Dump(LPCTSTR lpFileName, BOOL bRunDotty = TRUE) const;
#endif

	// Copy the entity
	BREP_Body* Copy();

	void SetTransformation(const MH_Matrix44& mtx);
	const MH_Matrix44& GetTransformation() const;

	void AddLump(const SL_Ptr<BREP_Lump>& pLump);
	const BREP_LumpPtrVect& GetLumps() const;

	void AddWire(const SL_Ptr<BREP_Wire>& pWire);
	const BREP_WirePtrVect& GetWires() const;

	// Get one point from the body
	MH_Point3 GetPoint() const;
private:
	// Matrix used to convert to local coordinate system
	MH_Matrix44 m_mtxTransform;

	// This body includes these lumps
	BREP_LumpPtrVect m_vLump;

	// This body includes these wires
	BREP_WirePtrVect m_vWire;
};
