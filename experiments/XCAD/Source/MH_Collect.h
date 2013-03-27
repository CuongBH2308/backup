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
#include <vector>
#include "mm_allocator.h"
#include "sl_ptr.h"

class MH_CV;
class MH_Point3;
class MH_Crv;
class MH_CrvNurbs;
class MH_CrvBezier;
class MH_CrvPt;
class MH_SrfPt;
class MH_SrfFacet;
class MH_SrfBezier;
class MH_SrfNurbs;
class MH_SrfBezierNode;

typedef std::vector< float/*,			MM_Allocator<float> */>		FloatVect;
typedef std::vector< MH_Point3/*,		MM_Allocator<MH_Point3>*/ >	MH_Point3Vect;
typedef std::vector< MH_CV/*,	MM_Allocator<MH_CV> */>	MH_CVVect;
typedef std::vector< MH_CrvNurbs/*,	MM_Allocator<MH_CrvNurbs> */>	MH_CrvNurbsVect;
typedef std::vector< MH_CrvBezier/*,	MM_Allocator<MH_CrvBezier> */>	MH_CrvBezierVect;
typedef std::vector< MH_CrvPt/*,	MM_Allocator<MH_CrvPt> */>	MH_CrvPtVect;
typedef std::vector< MH_SrfBezier/*,	MM_Allocator<MH_SrfBezier> */>	MH_SrfBezierVect;
typedef std::vector< MH_SrfNurbs/*,	MM_Allocator<MH_SrfNurbs> */>	MH_SrfNurbsVect;
typedef std::vector< MH_SrfPt/*,	MM_Allocator<MH_SrfPt> */>	MH_SrfPtVect;
typedef std::vector< MH_SrfFacet/*,	MM_Allocator<MH_SrfFacet> */>	MH_SrfFacetVect;
typedef std::vector< SL_Ptr<MH_Crv>/*,	MM_Allocator<SL_Ptr<MH_Crv> > */>	MH_CrvPtrVect;


typedef std::vector< MH_SrfBezierNode* >	MH_SrfBezierNodeNPtrVect;
