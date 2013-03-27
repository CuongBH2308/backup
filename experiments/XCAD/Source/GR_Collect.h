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
#include "mh_point3.h"
#include "mm_allocator.h"
#include "sl_ptr.h"

class GR_DL;
class GR_DLAttrib;
class GR_DLCrv;
class GR_DLNode;
class GR_Selection;
class GR_SelectionFilter;
class DR_St;
typedef std::vector< SL_Ptr<GR_DL>/*,			MM_Allocator<SL_Ptr<GR_DL> >*/ >			GR_DLPtrVect;
typedef std::vector< SL_Ptr<GR_DLAttrib>/*,	MM_Allocator<SL_Ptr<GR_DLAttrib> >*/ >	GR_DLAttribPtrVect;
typedef std::vector< SL_Ptr<GR_DLCrv>/*,		MM_Allocator<SL_Ptr<GR_DLCrv> >*/ >		GR_DLCrvPtrVect;
typedef std::vector< SL_Ptr<GR_DLNode>/*,		MM_Allocator<SL_Ptr<GR_DLNode> >*/ >		GR_DLNodePtrVect;
typedef std::map< SL_Ptr<DR_St>, GR_DLPtrVect/*, std::less<SL_Ptr<DR_St> >, MM_Allocator<std::pair<const SL_Ptr<DR_St>, GR_DLPtrVect> >*/ > StDLMap;

typedef std::map<SL_Ptr<GR_DL>, MH_Point3>		DLPtMap;
typedef std::map<SL_Ptr<GR_DLNode>, MH_Point3>	DLNodePtMap;
typedef std::vector<GR_Selection*>				GR_SelectionPtrVect;
typedef std::vector<GR_SelectionFilter*>		GR_SelectionFilterPtrVect;
