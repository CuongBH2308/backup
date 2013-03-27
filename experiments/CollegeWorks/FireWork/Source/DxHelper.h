/*
 文件描述：提供一些常用　的结构，类型，函数，常量等
 */
#ifndef _DDHELPER_H
#define _DDHELPER_H

#include <memory.h>
#include <d3d9.h>
#include<string>
using std::string;

typedef unsigned char uChar;
typedef unsigned short uShort;
typedef unsigned long uLong;
typedef unsigned int uInt;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned int uint;



enum eResult
{
	resAllGood		= 0, // function passed with flying colors
		resFalse		= 1, // function worked and returns value 'false'
		resFailed		= -1, // function failed miserably
		resNotImpl		= -2, // function has not been implemented
		resForceDWord = 0x7FFFFFFF
};

#define D3DLIGHT_RANGE_MAX      ((float)sqrt(FLT_MAX))
/**
 * This class takes care of the annoying gruntwork
 * of having to zero-out and set the size parameter
 * of our Windows and DirectX structures.
 */
template <class T>
struct sAutoZero : public T
{
	sAutoZero()
	{
		memset( this, 0, sizeof(T) );
		dwSize = sizeof(T);
	}
};


/**
 * The Right Way to release our COM interfaces.
 * If they're still valid, release them, then
 * invalidate them.
 */
template <class T>
inline void SafeRelease( T& iface )
{
	if( iface )
	{
		iface->Release();
		iface = NULL;
	}
}


/**
 * Make sure the release brings our refcount to 0.
 */
template <class T>
inline void ExtraSafeRelease( T& iface )
{
	long refCount = 0;

	if( iface )
	{
		if( 0 < ( refCount = iface->Release() ) )
		{
			//DP0("[ExtraSafeRelease]: ERROR: Interface was not released enough!");
		}
		iface = NULL;
	}
}

class cGameError{
public:
	cGameError(char* strErrorIfo):strError(strErrorIfo)
	{
		
	}

private:
	string strError;
};




#endif // _DDHELPER_H