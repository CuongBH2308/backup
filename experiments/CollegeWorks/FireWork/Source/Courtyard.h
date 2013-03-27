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
		struct sPolyIndex   //����ζ���
		{
			ushort	m_ind;//�������
			ulong	m_col;//��ɫ
			float			m_u;//��������
			float			m_v;
		};
		
		struct sPolygon  //�����
		{
			sPolyIndex	m_vList[ MAX_CELL_POLY_VERTS ];//����ζ���
			int			m_nVerts;
			plane3		m_plane;
			string		m_texfile; //��������������ε�����
		};

		struct sObject//ʵ�壬����MESH��ɵ�����
		{
			string                          m_meshfile;//�ļ�
			point3                          m_pos;        //��λ��
			float                           m_angle;       //��ת�ĽǶ�
	
		};

		struct sTerrain//ʵ�壬����MESH��ɵ�����
		{
			string                          m_terrainfile;//�ļ�
			point3                          m_pos;        //�����Ͻǵ�λ��
			int                             m_numVertsPerRow;           //ÿ�еĶ�����
			int                             m_numVertsPerCol;           //ÿ�еĶ�����
			int                             m_cellSpacing;           //��Ԫ��Ŀ��
			float                           m_heightScale;          //����
			
		};
		
		private:
			vector< point3 >	m_ptList;      //����㼯
			vector< sPolygon >	m_polyList;    //�������μ�
			vector< sObject >   m_objList;     //��Ϸ�����е�����	
			vector< sTerrain >  m_TerrainList;     //��Ϸ������ �ĵ���
			
	};
}

#endif // !defined(AFX_COURTYARD_H__10A382ED_A232_4F7E_9A35_1CDB62492EF3__INCLUDED_)
