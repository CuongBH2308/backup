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
#include "mh_crvnurbs.h"
#include <math.h>
#include "mh_crdsys.h"
#include "mh_crvbezier.h"
#include "mh_crvline.h"
#include "mh_point3.h"
#include "mh_srfnurbs.h"
#include "mh_srfpt.h"
#include "mh_util.h"
#include "mh_vector3.h"
#include "sl_mm.h"

#ifdef _DEBUG
void MH_CrvNurbs::Dump()
{
	CString str, s;
	for(MH_CVVect::const_iterator it = m_vCV.begin(); it != m_vCV.end(); it++)
	{
		s.Format(_T("(%f,%f,%f,%f),"), (*it).m_f[0]/(*it).m_f[3], (*it).m_f[1]/(*it).m_f[3], (*it).m_f[2]/(*it).m_f[3], (*it).m_f[3]);
		str += s;
	}
	str += _T("\n");

	for(FloatVect::const_iterator it = m_vKnot.begin(); it != m_vKnot.end(); it++)
	{
		s.Format(_T("%f,"), *it);
		str += s;
	}
	::MessageBox(NULL,str,"",MB_OK);
}
#endif

MH_CrvNurbs::MH_CrvNurbs(void)
{
}

MH_CrvNurbs::MH_CrvNurbs(const MH_CrvNurbs& nurbs)
{
	SetInfo(nurbs.m_nOrder, nurbs.m_vCV, nurbs.m_vKnot);
}

MH_CrvNurbs::MH_CrvNurbs(size_t nOrder, const MH_CVVect& vCV, const FloatVect& vKnot)
{
	SetInfo(nOrder, vCV, vKnot);
}

MH_CrvNurbs::~MH_CrvNurbs(void)
{
}

// Tessellate the curve
// The points are stored in m_vPts
// virtual 
bool MH_CrvNurbs::Tessellate(float fTolerance)
{
	Cleanup();
	
#ifdef _DEBUG
	DWORD dw1 = GetTickCount();
#endif
	bool bOK = Subdivision(fTolerance, m_vCrvPt);

#ifdef _DEBUG
	DWORD dwTimeCost = GetTickCount() - dw1;
#endif
	return bOK;
}

// Transform this object
// virtual 
void MH_CrvNurbs::Transform(const MH_Matrix44& mtx)
{
	MH_CVVect::iterator it		= m_vCV.begin();
	MH_CVVect::iterator itCVEnd	= m_vCV.end();
	for(; it!=itCVEnd; ++it)
		(*it).Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvNurbs::Copy()
{
	MH_CrvNurbs* pCrv = NEW_OBJ(MH_CrvNurbs, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual
MH_CrvNurbs MH_CrvNurbs::GetNurbs() const
{
	return (*this);
}

// Assignment
MH_CrvNurbs& MH_CrvNurbs::operator = (const MH_CrvNurbs& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_nOrder= crv.m_nOrder;
	m_vKnot = crv.m_vKnot;
	m_vCV	= crv.m_vCV;
	return *this;
}

// Equals
bool MH_CrvNurbs::operator == (const MH_CrvNurbs& nurbs) const
{
	if(m_nOrder == nurbs.m_nOrder && m_vKnot == nurbs.m_vKnot && m_vCV == nurbs.m_vCV)
		return true;
	return false;
}

// Is the NURBS valid
bool MH_CrvNurbs::IsValid() const
{
	if(m_vCV.size() <2 || m_vKnot.size()<2 || m_nOrder+m_vCV.size() != m_vKnot.size())
		return false;
	
	return true;
}

// Get order of the curve
size_t MH_CrvNurbs::GetOrder() const
{
	return m_nOrder;
}

// Get all control points
const MH_CVVect& MH_CrvNurbs::GetCVs() const
{
	return m_vCV;
}

// Get knot vector
const FloatVect& MH_CrvNurbs::GetKnots() const
{
	return m_vKnot;
}

// Set curve's info
void MH_CrvNurbs::SetInfo(size_t nOrder, const MH_CVVect& vCV, const FloatVect& vKnot)
{
	m_nOrder= nOrder;
	m_vCV	= vCV;
	if(vKnot.size() > 0)
		m_vKnot = vKnot;
	else if(m_vCV.size() >= m_nOrder)
	{
		m_vKnot.clear();
		size_t iCV=m_vCV.size();
		size_t i=0;
		for(i=0; i<m_nOrder; i++)
			m_vKnot.push_back(0);
		for(i=0; i<iCV-m_nOrder; i++)
			m_vKnot.push_back(((float)(i+1))/(iCV-m_nOrder+1));
		for(i=0; i<m_nOrder; i++)
			m_vKnot.push_back(1.0f);
	}
}

// Get curve's info
void MH_CrvNurbs::GetInfo(size_t& nOrder, MH_CVVect& vCV, FloatVect& vKnot) const
{
	nOrder	= m_nOrder;
	vCV		= m_vCV;
	vKnot	= m_vKnot;
}

// Set the nIndex-th CV
bool MH_CrvNurbs::SetCV(size_t nIndex, const MH_CV& cv)
{
	bool bOK = true;
	ASSERT(nIndex < m_vCV.size());
	if(nIndex < m_vCV.size())
		m_vCV[nIndex] = cv;
	else
		bOK = false;
	return bOK;
}

// Get the nIndex-th CV
bool MH_CrvNurbs::GetCV(size_t nIndex, MH_CV& cv) const
{
	bool bOK = true;
	ASSERT(nIndex < m_vCV.size());
	if(nIndex < m_vCV.size())
		cv = m_vCV[nIndex];
	else
		bOK = false;
	return bOK;
}

// Get point at param u, upon De Boor Algorithm
bool MH_CrvNurbs::GetPoint(float u, MH_CV& cv) const
{
	ASSERT(m_nOrder > 0);

	size_t nKnots = m_vKnot.size();
	if(u < m_vKnot[0] || u > m_vKnot[nKnots-1])
		return false;

	size_t p = m_nOrder-1;
	size_t	i, j, k, r, s;
	i = j = k = r = s = 0;

	bool bK = false;
	for(i = 0; i < nKnots; i++)
	{
		if(m_vKnot[i] == u)
			s++;
		else if(u < m_vKnot[i])
		{
			bK = true;
			k = i-1;
			break;
		}
	}

	if(!bK)
		k = m_vCV.size()+p-1;

	bool bOK = false;
	size_t iNum = p-s+1;

	//iNum<1 means that u equals to one or more than one of the knots,
	//and the property of the NURBS curve tells us that the curve's continuity
	//is p-s+1 at knot
	if(iNum < 1)
	{
		iNum = 1;
		s = p+1-iNum;
	}

	MH_CV *pPt = new MH_CV[iNum];
	if(!pPt)
		goto wrapup;

	for(i=0; i<iNum; i++)
		pPt[i] = m_vCV[k-p+i];

	for(r=1; r<=p-s; r++)
	{
		for(i=k-p+r,j=0; i<=k-s; i++,j++)
		{
			float fT = (u-m_vKnot[i])/(m_vKnot[i+p-r+1]-m_vKnot[i]);
			pPt[j] = pPt[j]*(1-fT) + pPt[j+1]*fT;
		}
	}

	cv = pPt[0];
	bOK = true;
wrapup:
	if(pPt && iNum>0)
		delete [] pPt;

	return bOK;
}


// Get derivative at param u
// u, double
// return k+1 items if OK
MH_CVVect MH_CrvNurbs::GetDrv(size_t k, float u) const
{
	return MH_CVVect();
//	bool bOK = false;
//	MH_CVVect vCV, vCVTemp;
//	size_t n = m_vCV.size()-1;
//	size_t p = m_nOrder-1;
//	size_t i,j;
//
//	MH_CVVect vCV;
//	vCV.reserve(k+1);
//
//	vCVTemp = m_vCV;
//	bOK = MH_CrvNurbs(m_nOrder, vCVTemp, m_vKnot).GetPoint(u, vCV[0]);
//	if(!bOK)
//		goto wrapup;
//
//	for(j=1; j<=k; j++)
//	{
//		for(i=0; i<=n+1; i++)
//		{
//			float fKnotInterval = m_vKnot[i+p]-m_vKnot[i];
//			if(fKnotInterval == 0)
//				continue;
//
//			MH_CV ptCV;
//			if(i == 0)
//			{
//				ptCV.m_pt3	= vCVTemp[i].m_pt3*p/fKnotInterval;
//				ptCV.m_fW	= vCVTemp[i].m_fW*p/fKnotInterval;
//			}
//			else if(i == n+1)
//			{
//				ptCV.m_pt3	= -vCVTemp[i-1].m_pt3*p/fKnotInterval;
//				ptCV.m_fW	= -vCVTemp[i-1].m_fW*p/fKnotInterval;
//			}
//			else
//			{
//				ptCV.m_pt3	= MH_Point3(vCVTemp[i].m_pt3-vCVTemp[i-1].m_pt3)*p/fKnotInterval;
//				ptCV.m_fW	= (vCVTemp[i].m_fW-vCVTemp[i-1].m_fW)*p/fKnotInterval;
//			}
//			vCV.push_back(ptCV);
//		}
//		vCVTemp = vCV;
//		vCV.clear();
//		n++;
//		p--;
//
//		bOK = MH_CrvNurbs(m_nOrder-j, vCVTemp, m_vKnot).GetPoint(u, vPt3[j], vW[j]);
//		if(!bOK)
//			goto wrapup;
//	}
//
//	for(j=1;j<=k;j++)
//	{
//		for(i=1;i<=j;i++)
//			vPt3[j] = MH_Point3(vPt3[j] - (vPt3[j-i]*vW[i]*MH::GetCkl(j,i)));
//		vPt3[j] = vPt3[j]/vW[0];
//	}
//wrapup:
//	if(!bOK)
//		vPt3.clear();
//	return vPt3;
}

// Insert a knot
bool MH_CrvNurbs::InsertKnot(float u)
{
	int i,k,s,n;
	int p		= (int)m_nOrder-1;
	int nKnots	= (int)m_vKnot.size();

	s = 0;
	for(k=0; k<nKnots-1; k++)
	{
		if(m_vKnot[k] == u)
			s++;
		if(m_vKnot[k]<=u && m_vKnot[k+1]>u)
			break;
	}
	if(m_vKnot[nKnots-1] == u)
		s++;

	ASSERT(k+1 >= s);
	ASSERT(p > s);
	if(k+1 < s || p <= s)
		return false;

	for(i=k-s; i>=(k-p+1); i--)
	{
		if(i <= 0)
		{
			if(k-s <= 0)
				m_vCV.insert(m_vCV.begin(), m_vCV.front());
			break;
		}
		else if(i >= (int)m_vCV.size())
		{
			i = (int)m_vCV.size();
			if(k-p+1 >= i)
				m_vCV.push_back(m_vCV.back());
			continue;
		}
		else
		{
			float dbTemp = m_vKnot[i+p]-m_vKnot[i];
			if(dbTemp != 0)
				dbTemp = (u-m_vKnot[i])/dbTemp;

			MH_CV vCV = m_vCV[i-1]*(1-dbTemp) + m_vCV[i]*dbTemp;
			if(i==k-s || i==m_vCV.size()-1)
			{
				n = (int)m_vCV.size()-1;
				m_vCV.insert(m_vCV.end()-(n-(i-1)),vCV);
			}
			else
				m_vCV[i] = vCV;
		}
	}
	m_vKnot.insert(m_vKnot.begin()+k+1, u);
	return true;;
}

// Remove a knot
bool MH_CrvNurbs::RemoveKnot(float u)
{
	bool bOK = false;

	int i,k,s;
	int p		= (int)m_nOrder-1;
	int nKnots	= (int)m_vKnot.size();
	for(k=0,s=0; k<nKnots; k++)
	{
		if(m_vKnot[k] == u)
		{
			s++;
			if( (k<nKnots-1 && u<m_vKnot[k+1]) || (k==nKnots-1) )
				break;
		}
		else if(k<nKnots-1 && m_vKnot[k]<u && u<m_vKnot[k+1])
			break;
	}
	if(s==0 || s>p-1)
		return bOK;

	m_vKnot.erase(m_vKnot.begin()+k);
	s--;
	k--;
	nKnots--;

	MH_CV cv = m_vCV[k-p];
	for(i=k-p+1; i<=k-s-1; i++)
	{
		float a = (u-m_vKnot[i]) / (m_vKnot[p+i]-m_vKnot[i]);
		MH_CV cvTemp = m_vCV[i];
		m_vCV[i] = (m_vCV[i] - cv*(1-a))/a;
		cv = cvTemp;
	}
	m_vCV.erase(m_vCV.begin()+(k-s));

	return true;
}

// Insert u h times
bool MH_CrvNurbs::InsertKnot(float u, size_t h)
{
	int nKnots = (int)m_vKnot.size();
	if( u<m_vKnot.front() || u>m_vKnot.back() )
		return false;

	int i,k,s,r;
	int p		= (int)m_nOrder-1;
	int n		= (int)m_vCV.size()-1;

	s = 0;
	for(k=0; k<nKnots-1; k++)
	{
		if(m_vKnot[k] == u)
			s++;
		if(m_vKnot[k]<=u && m_vKnot[k+1]>u)
			break;
	}
	if(m_vKnot[nKnots-1] == u)
		s++;

	ASSERT(k+1 >= s);
	ASSERT(p > int(s+h-1));
	if(k+1 < s || p <= int(s+h-1))
		return false;

	MH_CV cv;
	for(r=1; r<=int(h); r++)
	{
		cv = m_vCV[k-p+r-1];
		for(i=k-p+r; i<=k-s; i++)
		{
			float a = (u-m_vKnot[i]) / (m_vKnot[i+p-r+1]-m_vKnot[i]);
			if(i == k-s)
				m_vCV.insert(m_vCV.end()-(n-(k-s))-r, cv*(1-a) + m_vCV[i]*a);
			else
			{
				MH_CV cvT = m_vCV[i];
				m_vCV[i] = cv*(1-a) + m_vCV[i]*a;
				cv = cvT;
			}
		}
	}

	m_vKnot.insert(m_vKnot.begin()+k+1, h, u);
	return true;
}

// Elevate degree from p to p+1
bool MH_CrvNurbs::ElevateDegree()
{
	bool bOK = false;

	int i,j,m;
	int p		= (int)m_nOrder-1;
	int n		= (int)m_vCV.size()-1;
	int nKnots	= (int)m_vKnot.size();
	FloatVect vKnot = m_vKnot;
	for(i=nKnots-1; i>0; i--)
	{
		if(vKnot[i] != vKnot[i-1])
			vKnot.insert(vKnot.begin()+i, vKnot[i]);
	}
	vKnot.insert(vKnot.begin(), vKnot[0]);


	MH_CVVect vCV;
	MH_CVVect vCVTemp;
	FloatVect vKnotTemp;

	MH_CrvNurbs* pCurve = new MH_CrvNurbs[p+1];
	if(!pCurve)
		goto wrapup;

	for(j=1; j<=p+1; j++)
	{
		vCVTemp		= m_vCV;
		vKnotTemp	= m_vKnot;

		m=0;
		while(1)//vKnotTemp.size()<m_vKnot.size()+p+1)
		{
			if(j+m < (int)vCVTemp.size())
				vCVTemp.insert(vCVTemp.begin()+j+m, vCVTemp[j+m]);
			if(j+m < (int)vKnotTemp.size())
				vKnotTemp.insert(vKnotTemp.begin()+j+m, vKnotTemp[j+m]);
			else
				break;
			m += (p+2);
		}

		if(j==p+1)
		{
			vCVTemp.insert(vCVTemp.begin(), vCVTemp[0]);
			vKnotTemp.insert(vKnotTemp.begin(), vKnotTemp[0]);
		}

		pCurve[j-1].SetInfo(p+2, vCVTemp, vKnotTemp);
		for(i=0; i<(int)vKnot.size(); i++)
		{	
			if(i>(int)vKnotTemp.size() || (i<(int)vKnotTemp.size() && vKnot[i]!=vKnotTemp[i]))
			{
				bOK = pCurve[j-1].InsertKnot(vKnot[i]);
				if(!bOK)
					goto wrapup;
			}
		}

		for(i=0; i<(int)vCVTemp.size(); i++)
		{
			if(j==1)
				vCV.push_back(vCVTemp[i]);
			else if((int)vCV.size()>i)
				vCV[i] = vCV[i]+vCVTemp[i];
			else if((int)vCV.size()<=i)
				vCV.push_back(vCVTemp[i]);
		}
	}

	m_nOrder++;
	m_vCV	= vCV;
	m_vKnot	= vKnot;
	bOK = true;

wrapup:
	if(pCurve)
		delete [] pCurve;

	return bOK;
}

// Divide this curve into two curves at u
bool MH_CrvNurbs::Divide(float u, MH_CrvNurbs& nurbs1, MH_CrvNurbs& nurbs2) const
{
	int nKnots = (int)m_vKnot.size();
	if( u<m_vKnot.front() || u>m_vKnot.back() )
		return false;

	MH_CVVect vCV1, vCV2;
	FloatVect vKnot1, vKnot2;

	int i,j,r,s,k;
	int p = (int)m_nOrder-1;

	s = 0;
	k = -1;
	for(i=0; i<nKnots; i++)
	{
		float fKnot = m_vKnot[i];
		if(fKnot < u)
			vKnot1.push_back(fKnot);
		else if(fKnot == u)
		{
			vKnot1.push_back(fKnot);
			s++;
		}
		else if(u < fKnot)
		{
			if(k == -1)
			{
				k = i-1;
				for(j=0; j<p-s+1; j++)
					vKnot1.push_back(u);
				for(j=0; j<p+1; j++)
					vKnot2.push_back(u);
			}
			vKnot2.push_back(fKnot);
		}
	}

	ASSERT(k != -1);

	MH_CVVect::const_iterator itCVBegin	= m_vCV.begin();
	MH_CVVect::const_iterator itCVEnd	= m_vCV.end();
	MH_CVVect::const_iterator it;
	for(it=itCVBegin; it!=itCVBegin+k-p+1; ++it)
		vCV1.push_back(*it);

	for(it=itCVBegin+(k-s); it!=itCVEnd; ++it)
		vCV2.push_back(*it);

	bool bOK = false;
	int iNum = p-s+1;

	MH_CV* pCV = new MH_CV[iNum]; 
	if(!pCV)
	{
		bOK = false;
		goto wrapup;
	}
	
	for(i=0; i<iNum; i++)
		pCV[i] = m_vCV[k-p+i];

	for(r=1; r<=p-s; r++)
	{
		for(i=k-p+r,j=0; i<=k-s; i++,j++)
		{
			float dbT = 0;
			if(m_vKnot[i+p-r+1]-m_vKnot[i] != 0)
				dbT = (u-m_vKnot[i])/(m_vKnot[i+p-r+1]-m_vKnot[i]);

			pCV[j]	= pCV[j]*(1-dbT) + pCV[j+1]*dbT;
			if(j == 0)
				vCV1.push_back(pCV[j]);
			if(j == iNum-1-r)
				vCV2.insert(vCV2.begin(), pCV[j]);
		}
	}

	bOK = true;
	nurbs1.SetInfo(m_nOrder, vCV1, vKnot1);
	nurbs2.SetInfo(m_nOrder, vCV2, vKnot2);

wrapup:
	if(pCV)
		delete [] pCV;
	return bOK;
}

// Divide this curve into two curves at u/2
bool MH_CrvNurbs::DivideHalf(MH_CrvNurbs& nurbs1, MH_CrvNurbs& nurbs2) const
{
	return Divide((m_vKnot.front()+m_vKnot.back())/2.0f, nurbs1, nurbs2);
}

// Subdivide the curve
bool MH_CrvNurbs::Subdivision(float fTol, MH_CrvPtVect& vCrvPt, MH_CrvNurbsVect* pvCrvNurbs)
{
	// Is the NURBS valid
	if(!IsValid())
		return false;

	float fTol2			= fTol*fTol;
	size_t nCVNum		= m_vCV.size();
	MH_Point3 ptStart	= m_vCV[0].GetPoint3();
	MH_Point3 ptEnd		= m_vCV[nCVNum-1].GetPoint3();
	MH_CrvLine line(ptStart, ptEnd-ptStart);

	bool bStop			= true;
	for(size_t i = 1; i<(nCVNum-1); ++i)
	{
		if(m_vCV[i].GetPoint3().DistanceTo2(line, MH_Point3()) > fTol2)
		{
			bStop = false;
			break;
		}
	}

	if(bStop)
	{
		if(pvCrvNurbs)
			pvCrvNurbs->push_back(*this);

		// Store the start point of the curve
		// And later, only store the end point of each sub-curve
		if(vCrvPt.size() == 0)
			vCrvPt.push_back(MH_CrvPt(ptStart, m_vKnot.front()));
		vCrvPt.push_back(MH_CrvPt(ptEnd, m_vKnot.back()));
	}
	else
	{
		MH_CrvNurbs nurbs1, nurbs2;
		if(DivideHalf(nurbs1, nurbs2))
		{
			nurbs1.Subdivision(fTol, vCrvPt, pvCrvNurbs);
			nurbs2.Subdivision(fTol, vCrvPt, pvCrvNurbs);
		}
	}
	return true;
}

// Convert this curve to Bezier curves
bool MH_CrvNurbs::ConvertToBeziers(MH_CrvBezierVect& beziers, MH_CrvNurbs& nurbs) const
{
	beziers.clear();
	nurbs = (*this);
	int p = (int)m_nOrder - 1;
	int nKnots	= (int)m_vKnot.size();
	int i = 0, j=0;
	for(i=nKnots-1; i>=0;)
	{
		float fKnot = m_vKnot[i];
		int s = 1;
		for(int j=i-1; j>=0; j--)
		{
			if(m_vKnot[j] == fKnot)
				s++;
			else 
				break;
		}
		if(p-s>0)
			nurbs.InsertKnot(fKnot, p-s);
		i -= s;
	}

	i = 0;
	int n = (int)nurbs.m_vCV.size()-1;
	while(i<n)
	{
		MH_CVVect vCV;
		for(j=0; j<(int)m_nOrder; j++)
			vCV.push_back(nurbs.m_vCV[i+j]);
		i = i+j-1;
		beziers.push_back(MH_CrvBezier(vCV));
	}
	return true;
}

// Revolve this nurbs around crvLine 
MH_SrfNurbs MH_CrvNurbs::Revolve(const MH_CrvLine& crvLine) const
{
	const float w = float(1.0/sqrt(2.0));
	MH_Vector3 vNormal = crvLine.GetDir();
	vNormal.Normalize();
	MH_CVVect vCV;
	for(size_t i = 0; i<m_vCV.size(); i++)
	{
		MH_Point3 ptOrigin;
		float fRadius = sqrt(m_vCV[i].GetPoint3().DistanceTo2(crvLine, ptOrigin));
		MH_CrdSys cs(ptOrigin, vNormal);
		vCV.push_back( MH_CV(cs.PointAt(fRadius, 0.0f), 1.0f)  );
		vCV.push_back( MH_CV(cs.PointAt(fRadius, fRadius), w)  );
		vCV.push_back( MH_CV(cs.PointAt(0.0f, fRadius), 1.0f)  );
		vCV.push_back( MH_CV(cs.PointAt(-fRadius, fRadius), w) );
		vCV.push_back( MH_CV(cs.PointAt(-fRadius, 0.0f), 1.0f) );
		vCV.push_back( MH_CV(cs.PointAt(-fRadius, -fRadius), w));
		vCV.push_back( MH_CV(cs.PointAt(0.0f, -fRadius), 1.0f) );
		vCV.push_back( MH_CV(cs.PointAt(fRadius, -fRadius), w) );
		vCV.push_back( MH_CV(cs.PointAt(fRadius, 0.0f), 1.0f)  );
	}

	FloatVect vKnotS;
	//vKnotS.push_back(0.0f);
	//vKnotS.push_back(0.0f);
	//vKnotS.push_back(0.0f);
	//vKnotS.push_back(0.5f);
	//vKnotS.push_back(0.5f);
	//vKnotS.push_back(1.0f);
	//vKnotS.push_back(1.0f);
	//vKnotS.push_back(1.0f);

	vKnotS.push_back(0.0f);
	vKnotS.push_back(0.0f);
	vKnotS.push_back(0.0f);
	vKnotS.push_back(0.25f);
	vKnotS.push_back(0.25f);
	vKnotS.push_back(0.5f);
	vKnotS.push_back(0.5f);
	vKnotS.push_back(0.75f);
	vKnotS.push_back(0.75f);
	vKnotS.push_back(1.0f);
	vKnotS.push_back(1.0f);
	vKnotS.push_back(1.0f);
	return MH_SrfNurbs(vCV, 9, 3, m_nOrder, vKnotS, m_vKnot);

	//return MH_SrfNurbs(vCV, 5, 3, m_nOrder, vKnotS, m_vKnot);
}