// Courtyard.cpp: implementation of the CCourtyard class.
//
//////////////////////////////////////////////////////////////////////

#include <string>
#include "Courtyard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using d3dbase::CCourtyard;
#define nextTok(x) x.front();assert(!x.empty());x.pop();
CCourtyard::CCourtyard(cFile& file)
{
	queue<string> tokQueue;//文件中一行的所有单词
	string tok;

	do
	{
		file.TokenizeNextNCLine( &tokQueue, '#' );
		
		tok = nextTok( tokQueue );
		
		if( tok == "COURTYARD_START" )
		{
			// do nothing
		}
		
		else if( tok == "COURTYARD_END" )
		{
			break;
		}
		
		//取得点集
		else if( tok == "PT" ) // 房间组成 的 点
		{
			point3 pt;
			
			// Read in the point
			tok = nextTok( tokQueue );
			pt.x = atof( tok.c_str() );
			
			tok = nextTok( tokQueue );
			pt.y = atof( tok.c_str() );
			
			tok = nextTok( tokQueue );
			pt.z = atof( tok.c_str() );
			
			// Append it to the list
			m_ptList.push_back( pt );
		}
		
	   //取得面集
		else if( tok == "FACE" )//房间中的各个平面(墙面，地面)
		{
			tok = nextTok( tokQueue );
			
			int nInd = atoi( tok.c_str() );//组成面的 点的个数
			
			// Create the polygon structure to fill
			sPolygon currPoly;
			currPoly.m_nVerts = nInd;
			
			/**
			* The next line is the indices.  //点对应的索引
			*/
			file.TokenizeNextNCLine( &tokQueue, '#' );
			
			// Fill in the indices
			int i=0; 
			for(i=0; i< nInd; i++ )
			{
				tok = nextTok( tokQueue );
				currPoly.m_vList[i].m_ind = atoi( tok.c_str() );
			}
			
			// Now we can build the plane.
			
			currPoly.m_plane = plane3( 
			m_ptList[currPoly.m_vList[0].m_ind],
			m_ptList[currPoly.m_vList[1].m_ind],
			m_ptList[currPoly.m_vList[2].m_ind] );
			
			
			/**
			* Next line is the colors
			*/
			file.TokenizeNextNCLine( &tokQueue, '#' );
			
			// Fill in the colors
			for( i=0; i< nInd; i++ )
			{
				tok = nextTok( tokQueue );
				sscanf( tok.c_str(), "%x", &currPoly.m_vList[i].m_col );
			}
			
			/**
			* Final line is the texture info.
			*/
			file.TokenizeNextNCLine( &tokQueue, '#' );
			
			point3  m, n, p;
			
			// First token says whether to auto generate textures
			// Or explicitly read them.
			tok = nextTok( tokQueue );
			
			if( tok == "AUTO" )
			{
				// Automatically generate the texture vectors
				p = (m_ptList[currPoly.m_vList[0].m_ind]);
				
				tok = nextTok( tokQueue );
				currPoly.m_texfile =  tok;//texID
				tok = nextTok( tokQueue );
				
				float mScale = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );          
				float nScale = atof( tok.c_str() );
				
				// Run tests to figure out which way the plane faces
				if( point3::i == currPoly.m_plane.n || -1*point3::i == currPoly.m_plane.n )
				{
					// plane points in the +/-x direction
					m.Assign(0,0,1);  //纹理坐标？？？
					n.Assign(0,1,0);
				}
				else if( point3::j == currPoly.m_plane.n || -1*point3::j == currPoly.m_plane.n )
				{
					// plane points in the +/-y direction
					m.Assign(0,0,1);
					n.Assign(1,0,0);
				}
				else if( point3::k == currPoly.m_plane.n || -1*point3::k == currPoly.m_plane.n )
				{
					// plane points in the +/-z direction
					m.Assign(1,0,0);
					n.Assign(0,1,0);
				}
				
				// No easy guess... just estimate using the first two points as one vector
				// and the cross as the other.
				else
				{
					m = m_ptList[currPoly.m_vList[1].m_ind] - m_ptList[currPoly.m_vList[0].m_ind];
					m.Normalize();
					n = m ^ currPoly.m_plane.n;
				}
				
				// scale the vectors by the provided scaling values.
				m *= mScale;
				n *= nScale;
			}
		/*	else if( tok == "EXP" )
			{
				// Explicit tex-gen.  texture ID and then 9 floats (p,m,n).
				tok = nextTok( tokQueue );
				currPoly.m_texfile =  tok;
				
				// P
				tok = nextTok( tokQueue );
				p.x = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );
				p.y = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );
				p.z = atof( tok.c_str() );
				
				// M
				tok = nextTok( tokQueue );
				m.x = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );
				m.y = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );
				m.z = atof( tok.c_str() );
				
				// N
				tok = nextTok( tokQueue );
				n.x = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );
				n.y = atof( tok.c_str() );
				
				tok = nextTok( tokQueue );
				n.z = atof( tok.c_str() );
				
			}
			*/
			else throw cGameError( "Bad texture gen token" );
			
			float mMag = m.Mag();
			m /= mMag;
			
			float nMag = n.Mag();
			n /= nMag;
			
			// We have the n,m,p vectors; let's generate the coordinates.
			for( i=0; i<nInd; i++ )
			{
				//以点P为基准
				point3 pt = m_ptList[currPoly.m_vList[i].m_ind] - p;
				
				//为了防止出现负值，P应该是该面中最左下角的点
				float u = (pt * m);//纹理坐标
				float v = (pt * n);
				
				currPoly.m_vList[i].m_u = u / mMag;
				currPoly.m_vList[i].m_v = v / nMag;
			}
			
			// Add the poly
			m_polyList.push_back( currPoly );
			
		}//else if

		else if(tok == "OBJECT" )
		{
			sObject curobj;
			point3 p;
			//模型文件名
			tok = nextTok( tokQueue );
			curobj.m_meshfile = tok;

			//所在位置
			tok = nextTok( tokQueue );
			p.x = atoi(tok.c_str());

			tok = nextTok( tokQueue );
			p.y = atoi(tok.c_str());

			tok = nextTok( tokQueue );
			p.z = atoi(tok.c_str());
			curobj.m_pos = p;

			//旋转的角度
			tok = nextTok( tokQueue );
			curobj.m_angle = atof(tok.c_str());

			m_objList.push_back(curobj);
			
		}

		else if(tok == "TERRAIN" )
		{
			sTerrain curterrain;
			point3 p;
			//文件
			tok = nextTok( tokQueue );
			curterrain.m_terrainfile = tok;
			
			//左上位置点
			tok = nextTok( tokQueue );
			p.x = atoi(tok.c_str());
			
			tok = nextTok( tokQueue );
			p.y = atoi(tok.c_str());
			
			tok = nextTok( tokQueue );
			p.z = atoi(tok.c_str());
			curterrain.m_pos = p;

			//每行的顶点数
			tok = nextTok( tokQueue );
			curterrain.m_numVertsPerRow = atoi(tok.c_str());
			
			//每列的顶点数
			tok = nextTok( tokQueue );
			curterrain.m_numVertsPerCol = atoi(tok.c_str());
			
			////单元格的宽度
			tok = nextTok( tokQueue );
			curterrain.m_cellSpacing = atoi(tok.c_str());

			//缩放的高度
			tok = nextTok( tokQueue );
			curterrain.m_heightScale = atof(tok.c_str());

			m_TerrainList.push_back(curterrain);
			
		}
	}while(1);
	
	
}

CCourtyard::~CCourtyard()
{
	
}





















