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

class DR_Ct;
class DR_UCt;
class DR_UCtCVCrv;
class DR_St;
class DR_StBodyWire;
class DR_StCrv;
class DR_StPoint;
typedef std::vector< SL_Ptr<DR_Ct>/*, MM_Allocator<SL_Ptr<DR_Ct> >*/ > DR_CtPtrVect;
typedef std::vector< SL_Ptr<DR_UCt>/*, MM_Allocator<SL_Ptr<DR_UCt> >*/ > DR_UCtPtrVect;
typedef std::vector< SL_Ptr<DR_UCtCVCrv>/*, MM_Allocator<SL_Ptr<DR_UCtCVCrv> >*/ > DR_UCtCVCrvPtrVect;
typedef std::vector< SL_Ptr<DR_St>/*, MM_Allocator<SL_Ptr<DR_St> >*/ > DR_StPtrVect;
typedef std::vector< SL_Ptr<DR_StBodyWire>/*, MM_Allocator<SL_Ptr<DR_StBodyWire> >*/ > DR_StBodyWireVect;
typedef std::vector< SL_Ptr<DR_StCrv>/*, MM_Allocator<SL_Ptr<DR_StCrv> >*/ > DR_StCrvPtrVect;
typedef std::vector< SL_Ptr<DR_StPoint>/*, MM_Allocator<SL_Ptr<DR_StPoint> >*/ > DR_StPointPtrVect;

