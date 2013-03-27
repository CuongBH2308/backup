#include "terrain.h"
#include <fstream>
#include <cmath>
using d3d::CTerrain;
using namespace d3dbase;
const DWORD CTerrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

//加载高度图，创建顶点缓冲，索引缓冲并填充数据
CTerrain::CTerrain(IDirect3DDevice9* device,
				 std::string heightmapFileName,//文件内容包含了各个位置的高度
				 D3DXVECTOR3 lucorner,                //地形左上角的位置（与坐标有别）
				 int numVertsPerRow,           //每行的顶点数
				 int numVertsPerCol,           //每列的顶点数
				 int cellSpacing,              //单元格的宽度
				 float heightScale)            //缩放
{
	m_device         = device;

	m_pLucorner = lucorner;

	m_numVertsPerRow = numVertsPerRow;
	m_numVertsPerCol = numVertsPerCol;
	m_cellSpacing    = cellSpacing;

	m_numCellsPerRow = m_numVertsPerRow - 1;//每行的单元格数
	m_numCellsPerCol = m_numVertsPerCol - 1;//每列的单元格数

	m_width = m_numCellsPerRow * m_cellSpacing;//地形总宽度
	m_depth = m_numCellsPerCol * m_cellSpacing;//长度

	m_numVertices  = m_numVertsPerRow * m_numVertsPerCol;//总的顶点数
	m_numTriangles = m_numCellsPerRow * m_numCellsPerCol * 2;//总的三角形数　

	m_heightScale = heightScale;

	// load heightmap 读文件内容到m_heightmap 去
	if( !readRawFile(heightmapFileName) )
	{
		::MessageBox(0, "readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// scale heights  缩放高度
	for(int i = 0; i < m_heightmap.size(); i++)
		m_heightmap[i] *= heightScale;

	// compute the vertices
	//创建顶点并填充数据
	if( !computeVertices() )
	{
		::MessageBox(0, "computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// compute the indices
	//创建索引缓冲并填充数据
	if( !computeIndices() )
	{
		::MessageBox(0, "computeIndices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
}

CTerrain::~CTerrain()
{
	d3dbase::Release<IDirect3DVertexBuffer9*>(m_vb);
	d3dbase::Release<IDirect3DIndexBuffer9*>(m_ib);
	d3dbase::Release<IDirect3DTexture9*>(m_tex);
}

//获得指定位置的高度
int CTerrain::getHeightmapEntry(int row, int col)
{
	return m_heightmap[row * m_numVertsPerRow + col];
}

//设置指定位置的高度
void CTerrain::setHeightmapEntry(int row, int col, int value)
{
	m_heightmap[row * m_numVertsPerRow + col] = value;
}


//创建顶点缓冲并填充数据(位置坐标，纹理坐标)
bool CTerrain::computeVertices()
{
	HRESULT hr = 0;

	hr = m_device->CreateVertexBuffer(
		m_numVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&m_vb,
		0);

	if(FAILED(hr))
		return false;

	//　左上角－＞右下角
	int startX = m_pLucorner.x;
	int startZ = m_pLucorner.z;//这里其实表示z坐标

	// 右下角
	int endX = startX + m_width;
	int endZ = startZ - m_depth;

	// 
	//、　纹理坐标的增量
	float uCoordIncrementSize = 1.0f / (float)m_numCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)m_numCellsPerCol;

	TerrainVertex* v = 0;
	m_vb->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for(int z = startZ; z >= endZ; z -= m_cellSpacing)
	{
		int j = 0;
		for(int x = startX; x <= endX; x += m_cellSpacing)
		{
			// 计算下标
			int index = i * m_numVertsPerRow + j;

			v[index] = TerrainVertex(
				(float)x,                       //位置坐标
				(float)(m_heightmap[index]+m_pLucorner.y),
				(float)z,
				(float)j * uCoordIncrementSize,  //纹理坐标
				(float)i * vCoordIncrementSize); 

			j++; // 下一列
		}
		i++; // 下一行
	}

	m_vb->Unlock();

	return true;
}

//创建索引缓冲并填充数据
bool CTerrain::computeIndices()
{
	HRESULT hr = 0;

	hr = m_device->CreateIndexBuffer(
		m_numTriangles * 3 * sizeof(WORD), // 每个三角形三个索引点
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_ib,
		0);

	if(FAILED(hr))
		return false;

	WORD* indices = 0;
	m_ib->Lock(0, 0, (void**)&indices, 0);

	// 四　边形下标　的开始　
	int baseIndex = 0;

	// 
	for(int i = 0; i < m_numCellsPerCol; i++)
	{
		for(int j = 0; j < m_numCellsPerRow; j++)
		{
			indices[baseIndex]     =   i   * m_numVertsPerRow + j;
			indices[baseIndex + 1] =   i   * m_numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i+1) * m_numVertsPerRow + j;

			indices[baseIndex + 3] = (i+1) * m_numVertsPerRow + j;
			indices[baseIndex + 4] =   i   * m_numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i+1) * m_numVertsPerRow + j + 1;

			// 下一个四边形
			baseIndex += 6;
		}
	}

	m_ib->Unlock();

	return true;
}

//从文件加载纹理图
bool CTerrain::loadTexture(std::string fileName)
{
	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFile(
		m_device,
		fileName.c_str(),
		&m_tex);

	if(FAILED(hr))
		return false;

	return true;
}

//创建纹理并根据每个位置的高度来设置其颜色（纹理颜色）
bool CTerrain::genTexture(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	// 
	int texWidth  = m_numCellsPerRow;
	int texHeight = m_numCellsPerCol;


	//创建并设置自己的纹理
	hr = D3DXCreateTexture(
		m_device,
		texWidth, texHeight,
		0, // 
		0, // 
		D3DFMT_X8R8G8B8,// 32 位 XRGB 
		D3DPOOL_MANAGED, &m_tex);

	if(FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc; 
	m_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	
	if( textureDesc.Format != D3DFMT_X8R8G8B8 )
		return false;
		
	D3DLOCKED_RECT lockedRect;
	m_tex->LockRect(0,               
	            	&lockedRect, 
		            0,               
					0);                 
 
	//根据每个位置的高度来设置其颜色（纹理颜色）
	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < texHeight; i++)
	{
		for(int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			//左上角
			float height = (float)getHeightmapEntry(i, j) / m_heightScale;

			if( (height) < 42.5f ) 		 c = d3dbase::BEACH_SAND;
			else if( (height) < 85.0f )	 c = d3dbase::LIGHT_YELLOW_GREEN;
			else if( (height) < 127.5f ) c = d3dbase::PUREGREEN;
			else if( (height) < 170.0f ) c = d3dbase::DARK_YELLOW_GREEN;
			else if( (height) < 212.5f ) c = d3dbase::DARKBROWN;
			else	                     c = d3dbase::WHITE;

			
			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	m_tex->UnlockRect(0);

   //根据光照方向调整其纹理颜色
	if(!lightTerrain(directionToLight))
	{
		::MessageBox(0, "lightTerrain() - FAILED", 0, 0);
		return false;
	}
	
	hr = D3DXFilterTexture(
		m_tex,
		0, 
		0, 
		D3DX_DEFAULT); 

	if(FAILED(hr))
	{
		::MessageBox(0, "D3DXFilterTexture() - FAILED", 0, 0);
		return false;
	}

	return true;
}


//根据光照方向调整其纹理图对象（m_tex）的纹理颜色(光照阴影作用)
bool CTerrain::lightTerrain(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc; 
	m_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	
	if( textureDesc.Format != D3DFMT_X8R8G8B8 )
		return false;
		
	D3DLOCKED_RECT lockedRect;
	m_tex->LockRect(
		0,          
		&lockedRect,
		0,          
		0);         

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < textureDesc.Height; i++)
	{
		for(int j = 0; j < textureDesc.Width; j++)
		{
			
			int index = i * lockedRect.Pitch / 4 + j;

			
			D3DXCOLOR c( imageData[index] );

		
			//根据平面法线和光线方向的夹角算出光照强度
			c *= computeShade(i, j, directionToLight);;

		
			imageData[index] = (D3DCOLOR)c;
		}
	}

	m_tex->UnlockRect(0);

	return true;
}


float CTerrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
{
	
	float heightA = getHeightmapEntry(cellRow,   cellCol);
	float heightB = getHeightmapEntry(cellRow,   cellCol+1);
	float heightC = getHeightmapEntry(cellRow+1, cellCol);

	//  先求出该面上的两个向量
	D3DXVECTOR3 u(m_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f,         heightC - heightA, -m_cellSpacing);

	
	// 求出法线
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	//角度越大，越倾斜，光照强度就越小了
	float cosine = D3DXVec3Dot(&n, directionToLight);


	//若小于0，自然就没有光照，不能取小于0
	if(cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}

// 将此文件的内容读到m_heightmap中去，表示地形的高度
bool CTerrain::readRawFile(std::string fileName)
{
	std::vector<BYTE> in( m_numVertices );

	std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if( inFile == 0 )
		return false;

	inFile.read(
		(char*)&in[0], 
		in.size());

	inFile.close();


	m_heightmap.resize( m_numVertices );

	for(int i = 0; i < in.size(); i++)
		m_heightmap[i] = in[i];

	return true;
}


//根据当前位置，平移缩放xz坐标（为了确定行列，便于计算），插值求出精确高度
float CTerrain::getHeight(float x, float z)
{
	
	//把左上角的点移到原点，平移后的坐标
	// 因为求高度，X，Z的平移并无影响,
	//Z轴方向也取反
	x = x - ((float)m_pLucorner.x);
	z = ((float)m_pLucorner.z) - z;

	
	//x,z  的比例缩放也无影响
	x /= (float)m_cellSpacing;
	z /= (float)m_cellSpacing;

	

	

	//分离出行和列
	float col = ::floorf(x);
	float row = ::floorf(z);

	// 
    //  A   B
    //  *---*
    //  | / |
    //  *---*  
    //  C   D

	float A = getHeightmapEntry(row,   col);
	float B = getHeightmapEntry(row,   col+1);
	float C = getHeightmapEntry(row+1, col);
	float D = getHeightmapEntry(row+1, col+1);



	// 与点A的相对位置
	float dx = x - col;
	float dz = z - row;


	//通过插值求出其精确高度
	float height = 0.0f;
	// dx+dz<1.0
	if(dz < 1.0f - dx) //上三角 
	{
		float uy = B - A; 
		float vy = C - A; 

	
		height = A + d3dbase::Lerp(0.0f, uy, dx) + d3dbase::Lerp(0.0f, vy, dz);
	}
	else //下三角
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B

	
		height = D + d3dbase::Lerp(0.0f, uy, 1.0f - dx) + d3dbase::Lerp(0.0f, vy, 1.0f - dz);
	}

	//height *= m_heightScale;
	return height;
}

//画出地形，如果drawTris为true, 同时画出三角线
bool CTerrain::draw(D3DXMATRIX* world, bool drawTris)
{
	HRESULT hr = 0;

	if( m_device )
	{
		m_device->SetTransform(D3DTS_WORLD, world);

		m_device->SetStreamSource(0, m_vb, 0, sizeof(TerrainVertex));
		m_device->SetFVF(TerrainVertex::FVF);
		
		m_device->SetIndices(m_ib);
		
		m_device->SetTexture(0, m_tex);

		//关掉灯光，用颜色表示
		m_device->SetRenderState(D3DRS_LIGHTING, false);

		hr =m_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			m_numVertices,
			0,
			m_numTriangles);

		m_device->SetRenderState(D3DRS_LIGHTING, true);

		// 画三角线
		if( drawTris )
		{
			m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			hr =m_device->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				m_numVertices,
				0,
				m_numTriangles);

			m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		if(FAILED(hr))
			return false;
	}

	return true;
}


void CTerrain::addHeight(float height)
{
	TerrainVertex* v = 0;
	m_vb->Lock(0, 0, (void**)&v, 0);
	
	for(int index = 0; index<m_numVertices; index++)
	{
		
		
		v[index].m_y += height;
	}
	
	m_vb->Unlock();
	
	
}

bool CTerrain::IsInside(D3DXVECTOR3 p)
{
	int startX = m_pLucorner.x;
	int startZ = m_pLucorner.z;//这里其实表示z坐标
	
	int endX = startX + m_width;
	int endZ = startZ - m_depth;    

	if((p.x<endX && p.x>startX)&&(p.z<startZ&&p.z>endZ))
		return true;
	else
		return false;
}
