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
#include "mh_facet.h"
#include "mh_vector3.h"

MH_Facet::MH_Facet(void)
{
}

MH_Facet::MH_Facet(const MH_Point3& pt1, const MH_Point3& pt2, const MH_Point3& pt3)
{
	Set(pt1, pt2, pt3);
}

MH_Facet::~MH_Facet(void)
{
}

// Transform this object
// virtual 
void MH_Facet::Transform(const MH_Matrix44& mtx)
{

}

// Set points
void MH_Facet::Set(const MH_Point3& pt1, const MH_Point3& pt2, const MH_Point3& pt3)
{
	m_pt[0] = pt1;
	m_pt[1] = pt2;
	m_pt[2] = pt3;
}

// Get Normal
MH_Vector3 MH_Facet::GetNormal() const
{
	return (m_pt[0]-m_pt[1])^(m_pt[0]-m_pt[2]);
}

bool MH_Facet::CheckPoint(const MH_Point3& pt, int* piRegion, float* pS, float* pT) const
{
	MH_Vector3 v1 = m_pt[1] - m_pt[0];
	MH_Vector3 v2 = m_pt[2] - m_pt[1];
	MH_Vector3 v  = pt - m_pt[0];

	float v1v1 = v1*v1;
	float v2v1 = v2*v1;
	float vv1  = v*v1;
	float v1v2 = v1*v2;
	float v2v2 = v2*v2;
	float vv2  = v*v2;

	float s = ( vv1*v2v2 - v2v1*vv2);
	if(s==0)
	{
		if(pS) *pS = 0;
		if(pT) *pT = 0;
		if(piRegion) *piRegion = 0;
		return true;
	}	

	s /=( v1v1*v2v2 - v2v1*v1v2 );
	if(pS) *pS = s;

	float t = (vv2 - v1v2*s)/(v2v2 * s);
	if(pT) *pT = t;

	if(0<s && s<=1 && 0<=t && t<=1)
	{
		if(piRegion) *piRegion = 0;
		return true;
	}
	if(!piRegion)
		return false;

	if(s>=1 && t<=0)
		*piRegion = 2;
	else if(s>=1 && t>=1)
		*piRegion = 4;
	else if(s<=0 && 0<=t && t<=1)
		*piRegion = 6;
	else if( (0<s && s<1 && t<0) || (s<0 && t>1) )
		*piRegion = 1;
	else if(s>1 && 0<t && t<1)
		*piRegion = 3;
	else
		*piRegion = 5;
	return false;
}


float MH_Facet::DistanceTo2(const MH_Facet& fct, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const
{
	float fDist = 0.0f;

	//// Compute vectors along the 6 sides
	//MH_Vector3 vFrom[3], vTo[3];
	//MH_Vector3 vFrom[0] = m_pt[1] - m_pt[0]; // v01From
	//MH_Vector3 vFrom[1] = m_pt[2] - m_pt[1]; // v12From
	//MH_Vector3 vFrom[2] = m_pt[0] - m_pt[2]; // v20From 

	//MH_Vector3 vTo[0] = fct.m_pt[1] - fct.m_pt[0]; // v01To
	//MH_Vector3 vTo[1] = fct.m_pt[2] - fct.m_pt[1]; // v12To
	//MH_Vector3 vTo[2] = fct.m_pt[0] - fct.m_pt[2]; // v20To

	//MH_Point3 ptCrossThisMin, ptCrossThatMin;
	//MH_Vector3 vZ, vVec, vV;

	//// For each edge pair, the vector connecting the closest points 
	//// of the edges defines a slab (parallel planes at head and tail
	//// enclose the slab). If we can show that the off-edge vertex of 
	//// each triangle is outside of the slab, then the closest points
	//// of the edges are the closest points for the triangles.
	//// Even if these tests fail, it may be helpful to know the closest
	//// points found, and whether the triangles were shown disjoint

	//// Set first minimum safely high
	//float mindd = m_pt[0].DistanceToSqr(fct.m_pt[0]) + 1; 

	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		// Find closest points on edges i & j, plus the 
	//		// vector (and distance squared) between these points
	//		float dd = MH_CrvLineSeg(m_pt[i], vFrom[i]).DistanceTo(MH_CrvLineSeg(fct.m_pt[j], vTo[j]), ptCrossThis, ptCrossThat);
	//		dd *= dd;
	//		vVec = ptCrossThat - ptCrossThis;
	//		vV = ptCrossThat - ptCrossThis;

	//		// Verify this closest point pair only if the distance 
	//		// squared is less than the minimum found thus far.
	//		if (dd <= mindd)
	//		{
	//			ptCrossThisMin = ptCrossThis;
	//			ptCrossThatMin = ptCrossThat;

	//			vZ = m_pt[(i+2)%3] - ptCrossThis;
	//			float a = vZ*vVec;
	//			vZ = fct.m_pt[(j+2)%3] - ptCrossThat;
	//			float b = vZ*vVec;
	//			if ((a <= 0) && (b >= 0))
 //return sqrt(dd);


	//			VcV(minP,P);
	//			VcV(minQ,Q);
	//			mindd = dd;

	//			VmV(Z,S[(i+2)%3],P);
	//			PQP_REAL a = VdotV(Z,VEC);
	//			VmV(Z,T[(j+2)%3],Q);
	//			PQP_REAL b = VdotV(Z,VEC);

	//			if ((a <= 0) && (b >= 0)) return sqrt(dd);

	//			PQP_REAL p = VdotV(V, VEC);

	//			if (a < 0) a = 0;
	//			if (b > 0) b = 0;
	//			if ((p - a + b) > 0) shown_disjoint = 1;	
	//		}
	//	}
	//}






	//PQP_REAL Sv[3][3], Tv[3][3];
	//PQP_REAL VEC[3];

	//VmV(Sv[0],S[1],S[0]);
	//VmV(Sv[1],S[2],S[1]);
	//VmV(Sv[2],S[0],S[2]);

	//VmV(Tv[0],T[1],T[0]);
	//VmV(Tv[1],T[2],T[1]);
	//VmV(Tv[2],T[0],T[2]);

	//// For each edge pair, the vector connecting the closest points 
	//// of the edges defines a slab (parallel planes at head and tail
	//// enclose the slab). If we can show that the off-edge vertex of 
	//// each triangle is outside of the slab, then the closest points
	//// of the edges are the closest points for the triangles.
	//// Even if these tests fail, it may be helpful to know the closest
	//// points found, and whether the triangles were shown disjoint

	//PQP_REAL V[3];
	//PQP_REAL Z[3];
	//PQP_REAL minP[3], minQ[3], mindd;
	//int shown_disjoint = 0;

	//mindd = VdistV2(S[0],T[0]) + 1;  // Set first minimum safely high

	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		// Find closest points on edges i & j, plus the 
	//		// vector (and distance squared) between these points

	//		SegPoints(VEC,P,Q,S[i],Sv[i],T[j],Tv[j]);

	//		VmV(V,Q,P);
	//		PQP_REAL dd = VdotV(V,V);

	//		// Verify this closest point pair only if the distance 
	//		// squared is less than the minimum found thus far.

	//		if (dd <= mindd)
	//		{
	//			VcV(minP,P);
	//			VcV(minQ,Q);
	//			mindd = dd;

	//			VmV(Z,S[(i+2)%3],P);
	//			PQP_REAL a = VdotV(Z,VEC);
	//			VmV(Z,T[(j+2)%3],Q);
	//			PQP_REAL b = VdotV(Z,VEC);

	//			if ((a <= 0) && (b >= 0)) return sqrt(dd);

	//			PQP_REAL p = VdotV(V, VEC);

	//			if (a < 0) a = 0;
	//			if (b > 0) b = 0;
	//			if ((p - a + b) > 0) shown_disjoint = 1;	
	//		}
	//	}
	//}

	//// No edge pairs contained the closest points.  
	//// either:
	//// 1. one of the closest points is a vertex, and the
	////    other point is interior to a face.
	//// 2. the triangles are overlapping.
	//// 3. an edge of one triangle is parallel to the other's face. If
	////    cases 1 and 2 are not true, then the closest points from the 9
	////    edge pairs checks above can be taken as closest points for the
	////    triangles.
	//// 4. possibly, the triangles were degenerate.  When the 
	////    triangle points are nearly colinear or coincident, one 
	////    of above tests might fail even though the edges tested
	////    contain the closest points.

	//// First check for case 1

	//PQP_REAL Sn[3], Snl;       
	//VcrossV(Sn,Sv[0],Sv[1]); // Compute normal to S triangle
	//Snl = VdotV(Sn,Sn);      // Compute square of length of normal

	//// If cross product is long enough,

	//if (Snl > 1e-15)  
	//{
	//	// Get projection lengths of T points

	//	PQP_REAL Tp[3]; 

	//	VmV(V,S[0],T[0]);
	//	Tp[0] = VdotV(V,Sn);

	//	VmV(V,S[0],T[1]);
	//	Tp[1] = VdotV(V,Sn);

	//	VmV(V,S[0],T[2]);
	//	Tp[2] = VdotV(V,Sn);

	//	// If Sn is a separating direction,
	//	// find point with smallest projection

	//	int point = -1;
	//	if ((Tp[0] > 0) && (Tp[1] > 0) && (Tp[2] > 0))
	//	{
	//		if (Tp[0] < Tp[1]) point = 0; else point = 1;
	//		if (Tp[2] < Tp[point]) point = 2;
	//	}
	//	else if ((Tp[0] < 0) && (Tp[1] < 0) && (Tp[2] < 0))
	//	{
	//		if (Tp[0] > Tp[1]) point = 0; else point = 1;
	//		if (Tp[2] > Tp[point]) point = 2;
	//	}

	//	// If Sn is a separating direction, 

	//	if (point >= 0) 
	//	{
	//		shown_disjoint = 1;

	//		// Test whether the point found, when projected onto the 
	//		// other triangle, lies within the face.

	//		VmV(V,T[point],S[0]);
	//		VcrossV(Z,Sn,Sv[0]);
	//		if (VdotV(V,Z) > 0)
	//		{
	//			VmV(V,T[point],S[1]);
	//			VcrossV(Z,Sn,Sv[1]);
	//			if (VdotV(V,Z) > 0)
	//			{
	//				VmV(V,T[point],S[2]);
	//				VcrossV(Z,Sn,Sv[2]);
	//				if (VdotV(V,Z) > 0)
	//				{
	//					// T[point] passed the test - it's a closest point for 
	//					// the T triangle; the other point is on the face of S

	//					VpVxS(P,T[point],Sn,Tp[point]/Snl);
	//					VcV(Q,T[point]);
	//					return sqrt(VdistV2(P,Q));
	//				}
	//			}
	//		}
	//	}
	//}

	//PQP_REAL Tn[3], Tnl;       
	//VcrossV(Tn,Tv[0],Tv[1]); 
	//Tnl = VdotV(Tn,Tn);      

	//if (Tnl > 1e-15)  
	//{
	//	PQP_REAL Sp[3]; 

	//	VmV(V,T[0],S[0]);
	//	Sp[0] = VdotV(V,Tn);

	//	VmV(V,T[0],S[1]);
	//	Sp[1] = VdotV(V,Tn);

	//	VmV(V,T[0],S[2]);
	//	Sp[2] = VdotV(V,Tn);

	//	int point = -1;
	//	if ((Sp[0] > 0) && (Sp[1] > 0) && (Sp[2] > 0))
	//	{
	//		if (Sp[0] < Sp[1]) point = 0; else point = 1;
	//		if (Sp[2] < Sp[point]) point = 2;
	//	}
	//	else if ((Sp[0] < 0) && (Sp[1] < 0) && (Sp[2] < 0))
	//	{
	//		if (Sp[0] > Sp[1]) point = 0; else point = 1;
	//		if (Sp[2] > Sp[point]) point = 2;
	//	}

	//	if (point >= 0) 
	//	{ 
	//		shown_disjoint = 1;

	//		VmV(V,S[point],T[0]);
	//		VcrossV(Z,Tn,Tv[0]);
	//		if (VdotV(V,Z) > 0)
	//		{
	//			VmV(V,S[point],T[1]);
	//			VcrossV(Z,Tn,Tv[1]);
	//			if (VdotV(V,Z) > 0)
	//			{
	//				VmV(V,S[point],T[2]);
	//				VcrossV(Z,Tn,Tv[2]);
	//				if (VdotV(V,Z) > 0)
	//				{
	//					VcV(P,S[point]);
	//					VpVxS(Q,S[point],Tn,Sp[point]/Tnl);
	//					return sqrt(VdistV2(P,Q));
	//				}
	//			}
	//		}
	//	}
	//}

	//// Case 1 can't be shown.
	//// If one of these tests showed the triangles disjoint,
	//// we assume case 3 or 4, otherwise we conclude case 2, 
	//// that the triangles overlap.

	//if (shown_disjoint)
	//{
	//	VcV(P,minP);
	//	VcV(Q,minQ);
	//	return sqrt(mindd);
	//}
	//else return 0;

	return fDist;
}
