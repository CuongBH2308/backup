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

class BREP_Lump;
class BREP_Face;
class BREP_CoEdge;
class BREP_Edge;
class BREP_Loop;
class BREP_Wire;
class BREP_Shell;
typedef std::vector< SL_Ptr<BREP_Lump>	/*, MM_Allocator<SL_Ptr<BREP_Lump> >*/ > BREP_LumpPtrVect;
typedef std::vector< SL_Ptr<BREP_Face>	/*, MM_Allocator<SL_Ptr<BREP_Face> >*/ > BREP_FacePtrVect;
typedef std::vector< SL_Ptr<BREP_CoEdge>/*, MM_Allocator<SL_Ptr<BREP_CoEdge> >*/ > BREP_CoEdgePtrVect;
typedef std::vector< SL_Ptr<BREP_Edge>/*, MM_Allocator<SL_Ptr<BREP_Edge> >*/ > BREP_EdgePtrVect;
typedef std::vector< SL_Ptr<BREP_Loop>	/*, MM_Allocator<SL_Ptr<BREP_Loop> >*/ > BREP_LoopPtrVect;
typedef std::vector< SL_Ptr<BREP_Wire>	/*, MM_Allocator<SL_Ptr<BREP_Wire> >*/ > BREP_WirePtrVect;
typedef std::vector< SL_Ptr<BREP_Shell>	/*, MM_Allocator<SL_Ptr<BREP_Shell> >*/ > BREP_ShellPtrVect;
