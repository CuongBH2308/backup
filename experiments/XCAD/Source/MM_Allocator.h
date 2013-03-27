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
#include <xmemory>
#include "mm_manager.h"

template<class T>
class MM_Allocator : public std::allocator<T>
{
public:
	~MM_Allocator() {}

	typedef value_type _FARQ *pointer;
	typedef value_type _FARQ& reference;
	typedef const value_type _FARQ *const_pointer;
	typedef const value_type _FARQ& const_reference;

	typedef _SIZT size_type;
	typedef _PDFT difference_type;

	template<class _Other>
	struct rebind
	{	// convert an allocator<T> to an allocator <_Other>
		typedef MM_Allocator<_Other> other;
	};

	pointer address(reference _Val) const
	{	// return address of mutable _Val
		return (&_Val);
	}

	const_pointer address(const_reference _Val) const
	{	// return address of nonmutable _Val
		return (&_Val);
	}

	MM_Allocator()
	{	// construct default allocator (do nothing)
	}

	MM_Allocator(const MM_Allocator<T>&)
	{	// construct by copying (do nothing)
	}

	template<class _Other>
	MM_Allocator(const MM_Allocator<_Other>&)
	{	// construct from a related allocator (do nothing)
	}

	template<class _Other>
	MM_Allocator<T>& operator=(const MM_Allocator<_Other>&)
	{	// assign from a related allocator (do nothing)
		return (*this);
	}

	void deallocate(pointer _Ptr, size_type)
	{	// deallocate object at _Ptr, ignore size
		MM_Manager* pMemMgr = MM_Manager::Get();
		if(pMemMgr->IsStorage(_Ptr))
		{
			(*_Ptr).~T(); 
			pMemMgr->FreeStorage(_Ptr); 
		}
	}

	pointer allocate(size_type _Count)
	{	
		// allocate storage for _Count elements of type T
		return (T _FARQ *)MM_Manager::Get()->AllocStorage(_Count * sizeof (T));
	}

	pointer allocate(size_type _Count, const void _FARQ *)
	{	// allocate array of _Count elements, ignore hint
		return (allocate(_Count));
	}

	void construct(pointer _Ptr, const T& _Val)
	{	
		// construct object at _Ptr with value _Val
		new ((void _FARQ *)_Ptr) T(_Val);
	}

	void destroy(pointer _Ptr)
	{	
		// destroy object at _Ptr
		// _Ptr->~T();
		(*_Ptr).~T(); 
	}

	_SIZT max_size() const
	{	// estimate maximum array size
		_SIZT _Count = (_SIZT)(-1) / sizeof (T);
		return (0 < _Count ? _Count : 1);
	}
};
