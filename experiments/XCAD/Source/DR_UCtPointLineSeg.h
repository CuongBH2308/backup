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
#include "dr_uct.h"

class DR_StPoint;
class DR_StCrvLineSeg;
class DR_UCtPointLineSeg : public DR_UCt
{
public:
	DR_UCtPointLineSeg(const SL_Ptr<DR_DCtSolver>& pSolver, 
		const SL_Ptr<DR_StPoint>& pStPoint,
		const SL_Ptr<DR_StCrvLineSeg>& pStCrvLineSeg);
	virtual ~DR_UCtPointLineSeg(void);

	// Compute the output in new condition
	virtual HRESULT Compute();

	// eStart means m_pStPoint relate to the start point of m_pStCrvLineSeg
	// eEnd means m_pStPoint relate to the end point of m_pStCrvLineSeg
	enum EPtInLnSeg
	{
		eStart,
		eEnd
	};

	// Get point
	const SL_Ptr<DR_StPoint>& GetStPoint() const;

	// Get line segment
	const SL_Ptr<DR_StCrvLineSeg>& GetStCrvLineSeg() const;

	// Get EPtInLnSeg
	EPtInLnSeg GetType() const;
private:
	SL_Ptr<DR_StPoint>		m_pStPoint;
	SL_Ptr<DR_StCrvLineSeg> m_pStCrvLineSeg;
	EPtInLnSeg				m_ePtInLnSeg;
};
