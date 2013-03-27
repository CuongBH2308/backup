// Courtyard.h: interface for the CCourtyard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COURTYARD_H__10A382ED_A232_4F7E_9A35_1CDB62492EF3__INCLUDED_)
#define AFX_COURTYARD_H__10A382ED_A232_4F7E_9A35_1CDB62492EF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
#include<list>
#include <algorithm>


#include "file.h"
#include "dxhelper.h"
#include "math3D\point3.h"
#include "math3D\plane3.h"
#define MAX_CELL_POLY_VERTS 15

using namespace std;

namespace d3dbase
{
	class CCourtyard  
	{
	friend bool DrawBasicScene(CCourtyard* pcy,IDirect3DDevice9* device, float scale);	
	public:
		CCourtyard(cFile& file);
		virtual ~CCourtyard();
		
		
	protected:
		struct sPolyIndex   //多边形顶点
		{
			ushort	m_ind;//点的索引
			ulong	m_col;//颜色
			float			m_u;//纹理坐标
			float			m_v;
		};
		
		struct sPolygon  //多边形
		{
			sPolyIndex	m_vList[ MAX_CELL_POLY_VERTS ];//多边形顶点
			int			m_nVerts;
			plane3		m_plane;
			string		m_texfile; //用来填充这个多边形的纹理
		};

		struct sObject//实体，即由MESH组成的物体
		{
			string                          m_meshfile;//文件
			point3                          m_pos;        //　位置
			float                           m_angle;       //旋转的角度
	
		};

		struct sTerrain//实体，即由MESH组成的物体
		{
			string                          m_terrainfile;//文件
			point3                          m_pos;        //　左上角的位置
			int                             m_numVertsPerRow;           //每行的顶点数
			int                             m_numVertsPerCol;           //每列的顶点数
			int                             m_cellSpacing;           //单元格的宽度
			float                           m_heightScale;          //缩放
			
		};
		
		private:
			vector< point3 >	m_ptList;      //房间点集
			vector< sPolygon >	m_polyList;    //房间多边形集
			vector< sObject >   m_objList;     //游戏世界中的物体	
			vector< sTerrain >  m_TerrainList;     //游戏世界中 的地形
			
	};
}

#endif // !defined(AFX_COURTYARD_H__10A382ED_A232_4F7E_9A35_1CDB62492EF3__INCLUDED_)
