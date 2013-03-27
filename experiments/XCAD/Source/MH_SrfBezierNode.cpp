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
#include "mh_srfbeziernode.h"
#include <algorithm>
#include "mh_plane.h"
#include "mh_srfpt.h"
#include "mh_srffacet.h"

MH_SrfBezierNode::MH_SrfBezierNode(MH_SrfBezierNode* pParent, const MH_SrfBezier& srfBezier)
: m_pParent(pParent), m_srfBezier(srfBezier), m_nChildNumS(2)
{
}

MH_SrfBezierNode::MH_SrfBezierNode(const MH_SrfBezierVect& vSrfBezier, size_t nChildNumS)
: m_pParent(NULL), m_nChildNumS(nChildNumS)
{
	MH_SrfBezierVect::const_iterator it		= vSrfBezier.begin();
	MH_SrfBezierVect::const_iterator itEnd	= vSrfBezier.end();
	for(; it!=itEnd; ++it)
	{
		MH_SrfBezierNode* pSrfBezierNode = new MH_SrfBezierNode(this, *it);
		m_vChild.push_back(pSrfBezierNode);
	}
}


MH_SrfBezierNode::~MH_SrfBezierNode(void)
{
	if(m_pParent)
	{
		MH_SrfBezierNodeNPtrVect::iterator itThis = std::find(m_pParent->m_vChild.begin(), 
			m_pParent->m_vChild.end(), 
			this);
		if(itThis != m_pParent->m_vChild.end())
			(*itThis) = NULL;		
	}

	MH_SrfBezierNodeNPtrVect::const_iterator it		= m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	= m_vChild.end();
	for(; it!=itEnd; ++it)
		delete (*it);

	m_vChild.clear();
}

// Subdivide the surface
bool MH_SrfBezierNode::SubdivideChildren(float fTol)
{
	MH_SrfBezierNodeNPtrVect::const_iterator it		= m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	= m_vChild.end();
	for(; it!=itEnd; ++it)
	{
		if(!(*it)->Subdivision(fTol))
			return false;
	}
	return true;
}

// Subdivide the surface
bool MH_SrfBezierNode::Subdivision(float fTol)
{
	float fTol2				= fTol*fTol;
	const MH_CVVect& vCV	= m_srfBezier.GetCVs();
	size_t nCVNum			= vCV.size();
	size_t nCVNumS			= m_srfBezier.GetCVNumS();
	MH_Point3 ptStart		= vCV[0].GetPoint3();
	MH_Point3 ptS			= vCV[nCVNumS-1].GetPoint3();
	MH_Point3 ptT			= vCV[nCVNum-nCVNumS].GetPoint3();
	MH_Point3 ptEnd			= vCV[nCVNum-1].GetPoint3();
	MH_Plane plane;
	if(ptStart != ptS && ptEnd != ptS)
		plane = MH_Plane(ptStart, ptS, ptEnd);
	else if(ptStart != ptT && ptEnd != ptT)
		plane = MH_Plane(ptStart, ptT, ptEnd);
	else
		ASSERT(0);

	bool bStop = true;
	for(size_t i = 1; i<(nCVNum-1); ++i)
	{
		if(vCV[i].GetPoint3().DistanceTo2(plane, MH_Point3()) > fTol2)
		{
			bStop = false;
			break;
		}
	}
	if(!bStop)
	{
		MH_SrfBezier bezier1, bezier2;

		// Divide S
		if(m_srfBezier.DivideHalf(true, bezier1, bezier2))
		{
			MH_SrfBezier bezierNew[4];

			if(bezier1.DivideHalf(false, bezierNew[0], bezierNew[1]))
			{
				MH_SrfBezierNode* pSrfBezierNode[2];
				pSrfBezierNode[0] = new MH_SrfBezierNode(this, bezierNew[0]);
				m_vChild.push_back(pSrfBezierNode[0]);

				pSrfBezierNode[1] = new MH_SrfBezierNode(this, bezierNew[1]);
				m_vChild.push_back(pSrfBezierNode[1]);

				pSrfBezierNode[0]->Subdivision(fTol);
				pSrfBezierNode[1]->Subdivision(fTol);
			}
			if(bezier2.DivideHalf(false, bezierNew[2], bezierNew[3]))
			{
				MH_SrfBezierNode* pSrfBezierNode[2];
				pSrfBezierNode[0] = new MH_SrfBezierNode(this, bezierNew[2]);
				m_vChild.push_back(pSrfBezierNode[0]);

				pSrfBezierNode[1] = new MH_SrfBezierNode(this, bezierNew[3]);
				m_vChild.push_back(pSrfBezierNode[1]);

				pSrfBezierNode[0]->Subdivision(fTol);
				pSrfBezierNode[1]->Subdivision(fTol);
			}
		}
	}
	return true;
}

bool MH_SrfBezierNode::GetFacets(MH_SrfFacetVect& vSrfFacet)
{
	MH_SrfBezierNodeNPtrVect::const_iterator it		= m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	= m_vChild.end();
	for(; it!=itEnd; ++it)
		(*it)->GetFacets(vSrfFacet);
	if(m_vChild.size()>0)
		return true;

	MH_SrfBezierNode* pSrfBezierNode[4];
	pSrfBezierNode[0] = GetRight();
	pSrfBezierNode[1] = GetDown();
	pSrfBezierNode[2] = GetLeft();
	pSrfBezierNode[3] = GetUp();

	if(1)//pSrfBezierNode[0] && pSrfBezierNode[1] && pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		const MH_CVVect& vCV	= m_srfBezier.GetCVs();
		size_t nSize			= vCV.size();
		if(nSize==0)
			return true;
		size_t nCVNumS			= m_srfBezier.GetCVNumS();
		MH_CV ptCVStart			= vCV[0];
		MH_CV ptCVS				= vCV[nCVNumS-1];
		MH_CV ptCVT				= vCV[nSize-nCVNumS];
		MH_CV ptCVEnd			= vCV[nSize-1];

		MH_SrfFacet srfFacet1(MH_SrfPt(ptCVStart.GetPoint3(), m_srfBezier.m_fS[0], m_srfBezier.m_fT[0]), 
			MH_SrfPt(ptCVS.GetPoint3(), m_srfBezier.m_fS[1], m_srfBezier.m_fT[0]),
			MH_SrfPt(ptCVEnd.GetPoint3(), m_srfBezier.m_fS[1], m_srfBezier.m_fT[1]));
		vSrfFacet.push_back(srfFacet1);

		MH_SrfFacet srfFacet2(MH_SrfPt(ptCVStart.GetPoint3(), m_srfBezier.m_fS[0], m_srfBezier.m_fT[0]), 
			MH_SrfPt(ptCVEnd.GetPoint3(), m_srfBezier.m_fS[1], m_srfBezier.m_fT[1]),
			MH_SrfPt(ptCVT.GetPoint3(), m_srfBezier.m_fS[0], m_srfBezier.m_fT[1]));
		vSrfFacet.push_back(srfFacet2);
	}
	else if(!pSrfBezierNode[0] && pSrfBezierNode[1] && pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && !pSrfBezierNode[1] && pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && pSrfBezierNode[1] && !pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && pSrfBezierNode[1] && pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && !pSrfBezierNode[1] && pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && pSrfBezierNode[1] && !pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && pSrfBezierNode[1] && pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && !pSrfBezierNode[1] && !pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && !pSrfBezierNode[1] && pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && pSrfBezierNode[1] && !pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && !pSrfBezierNode[1] && !pSrfBezierNode[2] && pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && !pSrfBezierNode[1] && pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && pSrfBezierNode[1] && !pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(pSrfBezierNode[0] && !pSrfBezierNode[1] && !pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	else if(!pSrfBezierNode[0] && !pSrfBezierNode[1] && !pSrfBezierNode[2] && !pSrfBezierNode[3])
	{
		int i=0;
	}
	//else
	//	ASSERT(0);


	return 1;
}

// In s direction, get next 
MH_SrfBezierNode* MH_SrfBezierNode::GetRight() const
{
	if(!m_pParent)
		return NULL;

	MH_SrfBezierNodeNPtrVect::const_iterator itBegin = m_pParent->m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	 = m_pParent->m_vChild.end();
	MH_SrfBezierNodeNPtrVect::const_iterator it		 = std::find(itBegin, itEnd, this);
	ASSERT(it != itEnd);
	if(it == itEnd)
		return NULL;

	size_t nIndex = it-itBegin;
	if(m_pParent->m_nChildNumS > 1)
	{
		if(nIndex == 0 || (nIndex > 0 && (nIndex+1)%m_pParent->m_nChildNumS != 0))
			return (*(it+1));
	}

	MH_SrfBezierNode* pParentRight = m_pParent->GetRight();
	if(pParentRight)
	{
		if(pParentRight->m_vChild.size() > 0)
		{
			size_t nRow			= nIndex/m_pParent->m_nChildNumS;
			size_t nChildIndex	= pParentRight->m_nChildNumS*nRow;
			if(nChildIndex < pParentRight->m_vChild.size())
				return pParentRight->m_vChild[nChildIndex];
		}
		else
			return pParentRight;
	}

	return NULL;
}

// In s direction, get previous 
MH_SrfBezierNode* MH_SrfBezierNode::GetLeft() const
{
	if(!m_pParent)
		return NULL;

	MH_SrfBezierNodeNPtrVect::const_iterator itBegin = m_pParent->m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	 = m_pParent->m_vChild.end();
	MH_SrfBezierNodeNPtrVect::const_iterator it		 = std::find(itBegin, itEnd, this);
	ASSERT(it != itEnd);
	if(it == itEnd)
		return NULL;

	size_t nIndex		= it-itBegin;
	size_t nChildNum	= m_pParent->m_vChild.size();
	size_t nChildNumT	= nChildNum/m_pParent->m_nChildNumS;

	if(m_pParent->m_nChildNumS > 1)
	{
		if(nIndex%m_pParent->m_nChildNumS != 0)
			return (*(it-1));
	}

	MH_SrfBezierNode* pParentLeft = m_pParent->GetLeft();
	if(pParentLeft)
	{
		if(pParentLeft->m_vChild.size() > 0)
		{
			size_t nRow			= nIndex/m_pParent->m_nChildNumS;
			size_t nChildIndex	= pParentLeft->m_nChildNumS*(nRow+1)-1;
			if(nChildIndex < pParentLeft->m_vChild.size())
				return pParentLeft->m_vChild[nChildIndex];
		}
		else
			return pParentLeft;
	}

	return NULL;
}

// In s direction, get next in the same level
MH_SrfBezierNode* MH_SrfBezierNode::GetDown() const
{
	if(!m_pParent)
		return NULL;

	MH_SrfBezierNodeNPtrVect::const_iterator itBegin = m_pParent->m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	 = m_pParent->m_vChild.end();
	MH_SrfBezierNodeNPtrVect::const_iterator it		 = std::find(itBegin, itEnd, this);
	ASSERT(it != itEnd);
	if(it == itEnd)
		return NULL;

	size_t nIndex		= it-itBegin;
	size_t nChildNum	= m_pParent->m_vChild.size();
	size_t nChildNumT	= nChildNum/m_pParent->m_nChildNumS;

	if(nChildNumT > 1)
	{
		size_t nRow = nIndex/m_pParent->m_nChildNumS;
		if(nRow >= 0 && nRow < nChildNumT-1)
			return (*(it+m_pParent->m_nChildNumS));
	}

	MH_SrfBezierNode* pParentDown = m_pParent->GetDown();
	if(pParentDown)
	{
		if(pParentDown->m_vChild.size() > 0)
		{
			size_t nColumn = nIndex%m_pParent->m_nChildNumS;
			if(nColumn < pParentDown->m_vChild.size())
				return pParentDown->m_vChild[nColumn];
		}
		else
			return pParentDown;
	}

	return NULL;
}

// In s direction, get previous in the same level
MH_SrfBezierNode* MH_SrfBezierNode::GetUp() const
{
	if(!m_pParent)
		return NULL;

	MH_SrfBezierNodeNPtrVect::const_iterator itBegin = m_pParent->m_vChild.begin();
	MH_SrfBezierNodeNPtrVect::const_iterator itEnd	 = m_pParent->m_vChild.end();
	MH_SrfBezierNodeNPtrVect::const_iterator it		 = std::find(itBegin, itEnd, this);
	ASSERT(it != itEnd);
	if(it == itEnd)
		return NULL;

	size_t nIndex		= it-itBegin;
	size_t nChildNum	= m_pParent->m_vChild.size();
	size_t nChildNumT	= nChildNum/m_pParent->m_nChildNumS;

	if(nChildNumT > 1)
	{
		size_t nRow = nIndex/m_pParent->m_nChildNumS;
		if(nRow > 0 && nRow < nChildNumT)
			return (*(it-m_pParent->m_nChildNumS));
	}

	MH_SrfBezierNode* pParentUp = m_pParent->GetUp();
	if(!pParentUp)
		return NULL;

	size_t nParentUpChildNum	= pParentUp->m_vChild.size();
	if(nParentUpChildNum > 0)
	{
		size_t nColumn = nIndex % m_pParent->m_nChildNumS;
		size_t nRightChildIndex = nParentUpChildNum - pParentUp->m_nChildNumS + nColumn;
		if(nRightChildIndex < nParentUpChildNum)
			return pParentUp->m_vChild[nRightChildIndex];
	}
	else
		return pParentUp;

	return NULL;
}