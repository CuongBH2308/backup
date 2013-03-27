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
#include "mm_manager.h"
#include "sl_manager.h"
#include "sl_obj.h"
#include "sl_streamobj.h"

inline void* operator new(size_t sz, SL_Obj* pObj, SL_StreamObj* pStreamObj)
{
	void* pNew = MM_Manager::Get()->AllocStorage(sz);
	ASSERT(pNew);
	if(pNew)
	{
		if(!pStreamObj && pObj)
			pStreamObj = SL_Manager::Get()->GetStream(pObj);
		if(pStreamObj)
			pStreamObj->AddObj(reinterpret_cast<SL_Obj*>(pNew));
	}

	return pNew;
}

// Delete an object
template <class T>
inline void DeleteObj(T* pObj)
{
	MM_Manager* pMemMgr = MM_Manager::Get();
	if(pMemMgr->IsStorage(pObj))
	{
		(*pObj).~T(); 
		pMemMgr->FreeStorage(pObj); 
	}
	else
		delete pObj;
}

// Delete a block of memory
inline void DeleteMem(void* p)
{
	MM_Manager* pMemMgr = MM_Manager::Get();
	if(pMemMgr->IsStorage(p))
		pMemMgr->FreeStorage(p); 
	else
		delete p;
}

#define NEW_MM(nSize)				MM_Manager::Get()->AllocStorage(nSize)
#define NEW_OBJ(cls, pWhere)		new(pWhere, reinterpret_cast<SL_StreamObj*>(0))cls
#define NEW_OBJ1(cls, pStreamObj)	new(reinterpret_cast<SL_Obj*>(0), pStreamObj)cls
#define NEW_OBJ2(cls)				new(MM_Manager::Get()->AllocStorage(sizeof(cls)))cls

#define DEL_MM(p)					DeleteMem(p)
#define DEL_OBJ(pObj)				DeleteObj(pObj)
