// Sounders.h: interface for the CSounders class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDERS_H__FBF5DD3E_4442_4573_B3D4_E9F5EF169B30__INCLUDED_)
#define AFX_SOUNDERS_H__FBF5DD3E_4442_4573_B3D4_E9F5EF169B30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3dsounder.h"
#include<list>
using std::list;

namespace DXSound{
	class CSounders  
	{
	public:
		CSounders(char* filename,bool b3D = false)
		{
			if(b3D)
			{
				m_list.push_back( new C3DSounder( filename ) );
				
			}
			else
			{
				
				m_list.push_back( new CSounder( filename ) );
			}
		}
		
		
		
		~CSounders()
		{
			std::list< CSounder* >::iterator iter;
			for( iter = m_list.begin(); 
			iter != m_list.end();
			iter++ )
			{
				delete (*iter);
			}
			
		}
		
		
		
		void Play()   //play the first nonplaying sound to play
		{
			std::list< CSounder* >::iterator iter;
			for( 
				iter = m_list.begin(); 
			iter != m_list.end();
			iter++ )
			{
				if( !(*iter)->IsPlaying() )
				{
					(*iter)->Play();
					return;
				}
			}
			
			/**
			if no sound can play
			* We need to add a new sound
			*/
			CSounder* pNew = new CSounder( *(CSounder*)(*m_list.begin()) );
			pNew->Play();
			m_list.push_back( pNew );
		}
		
		
	public:
		list< CSounder* > m_list;
		
	};
}
#endif // !defined(AFX_SOUNDERS_H__FBF5DD3E_4442_4573_B3D4_E9F5EF169B30__INCLUDED_)
