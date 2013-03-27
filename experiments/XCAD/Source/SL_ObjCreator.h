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
#include "sl_manager.h"
#include "sl_obj.h"
#include "sl_mm.h"

class SL_GUID;
class SL_StreamObj;
template<class T>
class SL_ObjCreator
{
public:
	SL_ObjCreator(void)
	{
		SL_Manager::Get()->RegCreator(T::GetTypeId(), CreateObj);
	}

	virtual ~SL_ObjCreator(void)
	{
	}

	// Create an object and push it into the stream's vector
	static SL_Obj* CreateObj(const SL_GUID& guidType, SL_StreamObj* pStreamObj)
	{
		if(T::GetTypeId() == guidType)
			return NEW_OBJ1(T, pStreamObj)(pStreamObj);
		return NULL;
	}
};
