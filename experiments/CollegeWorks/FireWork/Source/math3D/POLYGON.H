/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/

#ifndef _POLYGON3_H
#define _POLYGON3_H


//¶à±ßÐÎ
template <class type>
struct polygon 
{
	int nElem;        // number of elements in the polygon
	int maxElem;

	type *pList;

	polygon()
	{
		nElem = 0;
		maxElem = 0;
		pList = NULL;
	}

	polygon( int maxSize )
	{
		maxElem = maxSize;
		pList = new type[maxSize];
	}

	polygon( const polygon &in )  //copy constructor function
	{
		CloneData( in );
	}

	~polygon()
	{
		DestroyData();
	}

	void CloneData( const polygon &in )
	{
		if( !in.pList ) //if have no element
			return;

		pList = new type[in.maxElem];
		maxElem = in.maxElem;
		nElem = in.nElem;
		for( int i=0; i<in.nElem; i++ )
		{
			pList[i] = in.pList[i];  //copy one (point) by one
		}
	}

	void DestroyData( )
	{
		if( pList )
		{
			delete[] pList;
		}
		pList = NULL;
	}

	polygon& operator=( const polygon<type> &in )  //assignment function ,it would be better to return the ref 
	{
		if( &in != this ) //is itself?
		{
			DestroyData();  //delete his own resoure

			CloneData( in ); //copy others' resource
		}
		
		return *this;
	}
};

#endif /*_POLYGON3_H*/