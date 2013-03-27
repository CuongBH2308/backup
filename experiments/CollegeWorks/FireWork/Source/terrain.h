/*
 文件描述：地形系统，高度的产生，纹理的计算
 */
#ifndef __terrainH__
#define __terrainH__

#include "d3dbase.h"
#include <string>
#include <vector>

namespace d3d{
	
	class CTerrain
	{
		//****************************构造　析构***********************************************
	public:
		//加载高度图，创建顶点缓冲，索引缓冲并填充数据
		CTerrain(IDirect3DDevice9* device,
			std::string heightmapFileName,//文件内容包含了各个位置的高度
			D3DXVECTOR3 lucorner,                //地形左上角的位置（与坐标有别 位置　＝　坐标＊cellSpacing）
			int numVertsPerRow,           //每行的顶点数
			int numVertsPerCol,           //每列的顶点数
			int cellSpacing,              //单元格的宽度
			float heightScale);            //缩放
		
		
		~CTerrain();
		
		//*****************************接口　功能**********************************************
	public:
		
		//获得指定位置的高度（顶点处的）
		int  getHeightmapEntry(int row, int col);

		//增加或减少地形的整体高度
		void addHeight(float height);
		
		//设置指定位置的高度
		void setHeightmapEntry(int row, int col, int value);
		
		//根据当前坐标（非顶点处的）平移缩放xz坐标（为了确定行列，便于计算），插值求出精确高度坐标
		float getHeight(float x, float z);
		
		//从文件加载纹理图
		bool  loadTexture(std::string fileName);
		
		//创建纹理并根据每个位置的高度来设置其颜色（纹理颜色）（调用lightTerrain以模拟光照效果）
		bool  genTexture(D3DXVECTOR3* directionToLight);
		
		//画出地形，如果drawTris为true, 同时画出三角线
		bool  draw(D3DXMATRIX* world, bool drawTris);

		//判断点P是否在地形内
		bool IsInside(D3DXVECTOR3 p);

		
		
		
		//*******************************辅助函数********************************************
	private:
		//将此文件的内容读到m_heightmap中去，表示地形的高度
		bool  readRawFile(std::string fileName);
		
		//创建顶点缓冲并填充数据
		bool  computeVertices();
		
		//创建索引缓冲并填充数据
		bool  computeIndices();
		
		//根据光照方向调整其纹理图对象（m_tex）的纹理颜色(光照阴影作用)（调用computeShade计算光照强度）
		bool  lightTerrain(D3DXVECTOR3* directionToLight);
		
		//根据平面法线和光线反方向的夹角算出光照强度
		float computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight);
		
		
		
		//****************************数据成员***********************************************
		
	private:
		IDirect3DDevice9*       m_device;
		IDirect3DTexture9*      m_tex;
		IDirect3DVertexBuffer9* m_vb;//顶点缓冲
		IDirect3DIndexBuffer9*  m_ib;//索引缓冲
		
		
		D3DXVECTOR3 m_pLucorner;     //地形左上角的位置
		
		int m_numVertsPerRow;//每行顶点数
		int m_numVertsPerCol;//每列顶点数
		int m_cellSpacing;   //单元格的宽度
		
		int m_numCellsPerRow;//每行的单元格数
		int m_numCellsPerCol;//每列的单元格数
		int m_width;
		int m_depth;
		int m_numVertices;
		int m_numTriangles;
		
		float m_heightScale;
		
		std::vector<int> m_heightmap;
		
		//************************内部数据结构***************************************************
		
	private:
		//顶点格式
		struct TerrainVertex
		{
			TerrainVertex(){}
			TerrainVertex(float x, float y, float z, float u, float v)
			{
				m_x = x; m_y = y; m_z = z; m_u = u; m_v = v;
			}
			float m_x, m_y, m_z;
			float m_u, m_v;
			
			static const DWORD FVF;
		};
	};
}
#endif // __terrainH__
