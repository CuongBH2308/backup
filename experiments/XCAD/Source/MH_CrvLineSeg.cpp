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
#include "mh_crvlineseg.h"
#include "mh_crvline.h"
#include "mh_facet.h"
#include "mh_plane.h"
#include "sl_mm.h"

MH_CrvLineSeg::MH_CrvLineSeg(void)
{
}

MH_CrvLineSeg::MH_CrvLineSeg(const MH_Point3& ptFrom,const MH_Point3& ptTo)
:m_ptFrom(ptFrom),
m_ptTo(ptTo)
{
}

MH_CrvLineSeg::MH_CrvLineSeg(const MH_Point3& ptFrom,const MH_Vector3& vFrom2To)
:m_ptFrom(ptFrom),
m_ptTo(ptFrom+vFrom2To)
{
}

MH_CrvLineSeg::~MH_CrvLineSeg(void)
{
}

// Transform this lineseg's points
// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
void MH_CrvLineSeg::Transform(const MH_Matrix44& mtx)
{
	m_ptFrom.Transform(mtx);
	m_ptTo.Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvLineSeg::Copy()
{
	MH_CrvLineSeg* pCrv = NEW_OBJ(MH_CrvLineSeg, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual 
MH_CrvNurbs MH_CrvLineSeg::GetNurbs() const
{
	MH_CVVect vCV;
	FloatVect vKnot;
	vCV.push_back(m_ptFrom);
	vCV.push_back(m_ptTo);
	vKnot.insert(vKnot.end(), 2, 0.0f);
	vKnot.insert(vKnot.end(), 2, 1.0f);
	return MH_CrvNurbs(2, vCV, vKnot);
}

// Assignment
MH_CrvLineSeg& MH_CrvLineSeg::operator = (const MH_CrvLineSeg& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_ptFrom	= crv.m_ptFrom;
	m_ptTo		= crv.m_ptTo;
	return *this;
}

void MH_CrvLineSeg::SetFrom(const MH_Point3& pt)
{
	m_ptFrom = pt;
}

void MH_CrvLineSeg::SetTo(const MH_Point3& pt)
{
	m_ptTo = pt;
}

const MH_Point3& MH_CrvLineSeg::GetFrom() const
{
	return m_ptFrom;
}

const MH_Point3& MH_CrvLineSeg::GetTo() const
{
	return m_ptTo;
}

// Triangulate the curve
// The triangles are stored in m_vLineSegs
// virtual 
bool MH_CrvLineSeg::Tessellate(float fTolerance)
{
	Cleanup();

	m_vCrvPt.push_back(MH_CrvPt(m_ptFrom, 0.0f));
	m_vCrvPt.push_back(MH_CrvPt(m_ptTo, 1.0f));

	return MH_Crv::Tessellate(fTolerance);
}

bool MH_CrvLineSeg::CheckPoint(const MH_Point3& pt, int* piRegion, float* pS) const
{
	MH_Vector3 vDir = m_ptTo-m_ptFrom;
	MH_Vector3 v = pt-m_ptFrom;
	float s = v/vDir;
	if(pS)	*pS = s;

	if(0<=s && s<=1)
	{
		if(piRegion)
			*piRegion = 0;
		return true;
	}
	else if(s<0)
	{
		if(piRegion)
			*piRegion = 1;
		return false;
	}
	else
	{
		if(piRegion)
			*piRegion = 2;
		return false;
	}
}

float MH_CrvLineSeg::DistanceTo2(const MH_CrvLineSeg& lineSeg, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const
{
	const MH_Point3& ptFrom = lineSeg.GetFrom();
	const MH_Point3& ptTo = lineSeg.GetTo();

	// Parallel to each other
	if( !((m_ptFrom-m_ptTo)^(ptFrom-ptTo)).IsValid() )
	{
		float s[2];
		int iRegion[2];
		MH_Point3 ptCross;
		MH_CrvLine line(lineSeg);
		float fDist2 = m_ptFrom.DistanceTo2(line, ptCross);
		if(lineSeg.CheckPoint(ptCross, &iRegion[0], &s[0]))
		{
			ptCrossThis = m_ptFrom;
			ptCrossThat = ptCross;
			return fDist2;
		}

		fDist2 = m_ptTo.DistanceTo2(line, ptCross);
		if(lineSeg.CheckPoint(ptCross, &iRegion[1], &s[1]))
		{
			ptCrossThis = m_ptTo;
			ptCrossThat = ptCross;
			return fDist2;
		}

		if(iRegion[0]==1 && iRegion[1]==1)
		{
			ASSERT(s[0]<0 && s[1]<0);

			ptCrossThat = ptFrom;
			if(s[1] < s[0])
				ptCrossThis = m_ptFrom;
			else
				ptCrossThis = m_ptTo;

			return ptCrossThis.DistanceTo2(ptCrossThat);
		}
		else if(iRegion[0]==2 && iRegion[1]==2)
		{
			ASSERT(s[0]>0 && s[1]>0);

			ptCrossThat = ptTo;
			if(s[0] < s[1])
				ptCrossThis = m_ptFrom;
			else
				ptCrossThis = m_ptTo;
		}
		else if( (iRegion[0]==1 && iRegion[1]==2) || (iRegion[0]==1 && iRegion[1]==2) )
		{
			ptCrossThat = ptFrom;
			return ptCrossThat.DistanceTo2((*this), ptCrossThis);
		}
		else
		{
			ASSERT(0);
			return 0.0f;
		}
	}

	float fDist2 = MH_CrvLine(*this).DistanceTo2(MH_CrvLine(lineSeg), ptCrossThis, ptCrossThat);

	int iRegion[2];
	CheckPoint(ptCrossThis, &iRegion[0]);
	if(iRegion[0]==1)
	{
		ptCrossThis = m_ptFrom;
		return m_ptFrom.DistanceTo2(lineSeg, ptCrossThat);
	}
	else if(iRegion[0]==2)
	{
		ptCrossThis = m_ptTo;
		return m_ptFrom.DistanceTo2(lineSeg, ptCrossThat);
	}

	CheckPoint(ptCrossThat, &iRegion[1]);
	if(iRegion[1]==1)
	{
		ptCrossThat = ptFrom;
		return ptCrossThat.DistanceTo2(ptCrossThis);
	}
	else if(iRegion[1]==2)
	{
		ptCrossThat = ptTo;
		return ptCrossThat.DistanceTo2(ptCrossThis);
	}

	return fDist2;
}


// ptCrossThat = fct.m_pt[0] + (fct.m_pt[1]-fct.m_pt[0])*s + (fct.m_pt[2]-fct.m_pt[1])*t
float MH_CrvLineSeg::DistanceTo2(const MH_Facet& fct, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const
{
	MH_Point3 ptCross;
	MH_Plane plane(fct);
	bool bCross = MH_CrvLine(*this).CrossPoint(plane, &ptCross);
	
	MH_Point3 ptFrom2Plane, ptTo2Plane;
	float fFrom2Plane	= m_ptFrom.DistanceTo2(plane, ptFrom2Plane);
	float fTo2Plane		= m_ptTo.DistanceTo2(plane, ptTo2Plane);

	if(bCross)
	{
		int nCrossRegion;
		if(fct.CheckPoint(ptCross, &nCrossRegion))
		{
			ptCrossThis = ptCross;
			ptCrossThat = ptCross;
			return 0.0f;
		}
		else
		{
			int nRegion[2];
			fct.CheckPoint(ptFrom2Plane,&nRegion[0]);
			if(nRegion[0]==0 && fFrom2Plane<fTo2Plane)
			{
				ptCrossThis = m_ptFrom;
				ptCrossThat = ptFrom2Plane;
				return fFrom2Plane;
			}
			fct.CheckPoint(ptTo2Plane, &nRegion[1]);
			if(nRegion[1]==0 && fFrom2Plane>fTo2Plane)
			{
				ptCrossThis = m_ptTo;
				ptCrossThat = ptTo2Plane;
				return fTo2Plane;
			}

			if(nRegion[0]==2 && nRegion[1]==2)
			{
				ptCrossThat = fct.m_pt[1];
				return ptCrossThat.DistanceTo2((*this), ptCrossThis);
			}

			else if(nRegion[0]==4 && nRegion[1]==4)
			{
				ptCrossThat = fct.m_pt[2];
				return ptCrossThat.DistanceTo2((*this), ptCrossThis);
			}

			else if(nRegion[0]==6 && nRegion[1]==6)
			{
				ptCrossThat = fct.m_pt[0];
				return ptCrossThat.DistanceTo2((*this), ptCrossThis);
			}

			else if( (nRegion[0]==1 && nRegion[1]==1) ||
				(nRegion[0]==1 && nRegion[1]==0) || (nRegion[0]==0 && nRegion[1]==1) ||
				(nRegion[0]==1 && nRegion[1]==2) || (nRegion[0]==2 && nRegion[1]==1) ||
				(nRegion[0]==1 && nRegion[1]==6) || (nRegion[0]==6 && nRegion[1]==1) )
				return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);

			else if( (nRegion[0]==3 && nRegion[1]==3) ||
				(nRegion[0]==3 && nRegion[1]==0) || (nRegion[0]==0 && nRegion[1]==3) ||
				(nRegion[0]==3 && nRegion[1]==4) || (nRegion[0]==4 && nRegion[1]==3) ||
				(nRegion[0]==3 && nRegion[1]==2) || (nRegion[0]==2 && nRegion[1]==3) )
				return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);

			else if( (nRegion[0]==5 && nRegion[1]==5) ||
				(nRegion[0]==5 && nRegion[1]==0) || (nRegion[0]==0 && nRegion[1]==5) ||
				(nRegion[0]==5 && nRegion[1]==4) || (nRegion[0]==4 && nRegion[1]==5) ||
				(nRegion[0]==5 && nRegion[1]==6) || (nRegion[0]==6 && nRegion[1]==5) )
				return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);




			else if( (nRegion[0]==1 && nRegion[1]==3) || (nRegion[0]==3 && nRegion[1]==3) ) 
			{
				if(nCrossRegion==1 || nCrossRegion==5 || nCrossRegion==6)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);
				if(nCrossRegion==2)
				{
					ptCrossThat = fct.m_pt[1];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==3 || nCrossRegion==4)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);
			}
			else if( (nRegion[0]==1 && nRegion[1]==5) || (nRegion[0]==5 && nRegion[1]==1) )
			{
				if(nCrossRegion==1 || nCrossRegion==2)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==3 || nCrossRegion==4 || nCrossRegion==5)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==6)
				{
					ptCrossThat = fct.m_pt[0];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
			}
			else if( (nRegion[0]==3 && nRegion[1]==5) || (nRegion[0]==5 && nRegion[1]==3) )
			{
				if(nCrossRegion==1 || nCrossRegion==2 || nCrossRegion==3)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==4)
				{
					ptCrossThat = fct.m_pt[2];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==5 || nCrossRegion==6)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);
			}
			else if( (nRegion[0]==1 && nRegion[1]==4) || (nRegion[0]==4 && nRegion[1]==1) )
			{
				if(nCrossRegion==1)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==2)
				{
					ptCrossThat = fct.m_pt[1];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==3)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==4)
				{
					ptCrossThat = fct.m_pt[2];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==6)
				{
					ptCrossThat = fct.m_pt[0];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==5)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);
			}
			else if( (nRegion[0]==3 && nRegion[1]==6) || (nRegion[0]==6 && nRegion[1]==3) )
			{
				if(nCrossRegion==3)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==4)
				{
					ptCrossThat = fct.m_pt[2];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==5)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==6)
				{
					ptCrossThat = fct.m_pt[0];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==2)
				{
					ptCrossThat = fct.m_pt[1];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==1)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);
			}
			else if( (nRegion[0]==5 && nRegion[1]==2) || (nRegion[0]==2 && nRegion[1]==5) )
			{
				if(nCrossRegion==5)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==6)
				{
					ptCrossThat = fct.m_pt[0];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==1)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);
				else if(nCrossRegion==2)
				{
					ptCrossThat = fct.m_pt[1];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==4)
				{
					ptCrossThat = fct.m_pt[2];
					return ptCrossThat.DistanceTo2((*this), ptCrossThis);
				}
				else if(nCrossRegion==3)
					return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);
			}
			else if( (nRegion[0]==2 && nRegion[1]==4) || (nRegion[0]==4 && nRegion[1]==2) )
				return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);
			else if( (nRegion[0]==4 && nRegion[1]==6) || (nRegion[0]==6 && nRegion[1]==4) )
				return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);
			else if( (nRegion[0]==6 && nRegion[1]==2) || (nRegion[0]==2 && nRegion[1]==6) )
				return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);
		}
	}
	else
	{
		int nRegion[2];
		fct.CheckPoint(ptFrom2Plane, &nRegion[0]);
		if(nRegion[0]==0)
		{
			ptCrossThis = m_ptFrom;
			ptCrossThat = ptFrom2Plane;
			return fFrom2Plane;
		}
		fct.CheckPoint(ptTo2Plane, &nRegion[1]);
		if(nRegion[1]==0)
		{
			ptCrossThis = m_ptTo;
			ptCrossThat = ptTo2Plane;
			return fTo2Plane;
		}

		if(nRegion[0]==2 && nRegion[1]==2)
		{
			ptCrossThat = fct.m_pt[1];
			return ptCrossThat.DistanceTo2((*this), ptCrossThis);
		}

		else if(nRegion[0]==4 && nRegion[1]==4)
		{
			ptCrossThat = fct.m_pt[2];
			return ptCrossThat.DistanceTo2((*this), ptCrossThis);
		}

		else if(nRegion[0]==6 && nRegion[1]==6)
		{
			ptCrossThat = fct.m_pt[0];
			return ptCrossThat.DistanceTo2((*this), ptCrossThis);
		}

		else if( (nRegion[0]==1 && nRegion[1]==1) ||
			(nRegion[0]==1 && nRegion[1]==2) || (nRegion[0]==2 && nRegion[1]==1) ||
			(nRegion[0]==1 && nRegion[1]==6) || (nRegion[0]==6 && nRegion[1]==1) )
			return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0],fct.m_pt[1]), ptCrossThis, ptCrossThat);

		else if( (nRegion[0]==3 && nRegion[1]==3) ||
			(nRegion[0]==3 && nRegion[1]==4) || (nRegion[0]==4 && nRegion[1]==3) ||
			(nRegion[0]==3 && nRegion[1]==2) || (nRegion[0]==2 && nRegion[1]==3) )
			return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1],fct.m_pt[2]), ptCrossThis, ptCrossThat);

		else if( (nRegion[0]==5 && nRegion[1]==5) ||
			(nRegion[0]==5 && nRegion[1]==4) || (nRegion[0]==4 && nRegion[1]==5) ||
			(nRegion[0]==5 && nRegion[1]==6) || (nRegion[0]==6 && nRegion[1]==5) )
			return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2],fct.m_pt[0]), ptCrossThis, ptCrossThat);

	}
	return 0.0f;
}

// Is the line segment selected
// virtual 
bool MH_CrvLineSeg::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	return (MH_CrvLine(ray).DistanceTo2(*this, MH_Point3(), ptHit)<=(fTolerance*fTolerance));
}