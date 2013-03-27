#include "terrain.h"
#include <fstream>
#include <cmath>
using d3d::CTerrain;
using namespace d3dbase;
const DWORD CTerrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

//���ظ߶�ͼ���������㻺�壬�������岢�������
CTerrain::CTerrain(IDirect3DDevice9* device,
				 std::string heightmapFileName,//�ļ����ݰ����˸���λ�õĸ߶�
				 D3DXVECTOR3 lucorner,                //�������Ͻǵ�λ�ã��������б�
				 int numVertsPerRow,           //ÿ�еĶ�����
				 int numVertsPerCol,           //ÿ�еĶ�����
				 int cellSpacing,              //��Ԫ��Ŀ��
				 float heightScale)            //����
{
	m_device         = device;

	m_pLucorner = lucorner;

	m_numVertsPerRow = numVertsPerRow;
	m_numVertsPerCol = numVertsPerCol;
	m_cellSpacing    = cellSpacing;

	m_numCellsPerRow = m_numVertsPerRow - 1;//ÿ�еĵ�Ԫ����
	m_numCellsPerCol = m_numVertsPerCol - 1;//ÿ�еĵ�Ԫ����

	m_width = m_numCellsPerRow * m_cellSpacing;//�����ܿ��
	m_depth = m_numCellsPerCol * m_cellSpacing;//����

	m_numVertices  = m_numVertsPerRow * m_numVertsPerCol;//�ܵĶ�����
	m_numTriangles = m_numCellsPerRow * m_numCellsPerCol * 2;//�ܵ�����������

	m_heightScale = heightScale;

	// load heightmap ���ļ����ݵ�m_heightmap ȥ
	if( !readRawFile(heightmapFileName) )
	{
		::MessageBox(0, "readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// scale heights  ���Ÿ߶�
	for(int i = 0; i < m_heightmap.size(); i++)
		m_heightmap[i] *= heightScale;

	// compute the vertices
	//�������㲢�������
	if( !computeVertices() )
	{
		::MessageBox(0, "computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// compute the indices
	//�����������岢�������
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

//���ָ��λ�õĸ߶�
int CTerrain::getHeightmapEntry(int row, int col)
{
	return m_heightmap[row * m_numVertsPerRow + col];
}

//����ָ��λ�õĸ߶�
void CTerrain::setHeightmapEntry(int row, int col, int value)
{
	m_heightmap[row * m_numVertsPerRow + col] = value;
}


//�������㻺�岢�������(λ�����꣬��������)
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

	//�����Ͻǣ������½�
	int startX = m_pLucorner.x;
	int startZ = m_pLucorner.z;//������ʵ��ʾz����

	// ���½�
	int endX = startX + m_width;
	int endZ = startZ - m_depth;

	// 
	//�����������������
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
			// �����±�
			int index = i * m_numVertsPerRow + j;

			v[index] = TerrainVertex(
				(float)x,                       //λ������
				(float)(m_heightmap[index]+m_pLucorner.y),
				(float)z,
				(float)j * uCoordIncrementSize,  //��������
				(float)i * vCoordIncrementSize); 

			j++; // ��һ��
		}
		i++; // ��һ��
	}

	m_vb->Unlock();

	return true;
}

//�����������岢�������
bool CTerrain::computeIndices()
{
	HRESULT hr = 0;

	hr = m_device->CreateIndexBuffer(
		m_numTriangles * 3 * sizeof(WORD), // ÿ������������������
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_ib,
		0);

	if(FAILED(hr))
		return false;

	WORD* indices = 0;
	m_ib->Lock(0, 0, (void**)&indices, 0);

	// �ġ������±ꡡ�Ŀ�ʼ��
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

			// ��һ���ı���
			baseIndex += 6;
		}
	}

	m_ib->Unlock();

	return true;
}

//���ļ���������ͼ
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

//������������ÿ��λ�õĸ߶�����������ɫ��������ɫ��
bool CTerrain::genTexture(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	// 
	int texWidth  = m_numCellsPerRow;
	int texHeight = m_numCellsPerCol;


	//�����������Լ�������
	hr = D3DXCreateTexture(
		m_device,
		texWidth, texHeight,
		0, // 
		0, // 
		D3DFMT_X8R8G8B8,// 32 λ XRGB 
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
 
	//����ÿ��λ�õĸ߶�����������ɫ��������ɫ��
	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < texHeight; i++)
	{
		for(int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			//���Ͻ�
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

   //���ݹ��շ��������������ɫ
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


//���ݹ��շ������������ͼ����m_tex����������ɫ(������Ӱ����)
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

		
			//����ƽ�淨�ߺ͹��߷���ļн��������ǿ��
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

	//  ����������ϵ���������
	D3DXVECTOR3 u(m_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f,         heightC - heightA, -m_cellSpacing);

	
	// �������
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	//�Ƕ�Խ��Խ��б������ǿ�Ⱦ�ԽС��
	float cosine = D3DXVec3Dot(&n, directionToLight);


	//��С��0����Ȼ��û�й��գ�����ȡС��0
	if(cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}

// �����ļ������ݶ���m_heightmap��ȥ����ʾ���εĸ߶�
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


//���ݵ�ǰλ�ã�ƽ������xz���꣨Ϊ��ȷ�����У����ڼ��㣩����ֵ�����ȷ�߶�
float CTerrain::getHeight(float x, float z)
{
	
	//�����Ͻǵĵ��Ƶ�ԭ�㣬ƽ�ƺ������
	// ��Ϊ��߶ȣ�X��Z��ƽ�Ʋ���Ӱ��,
	//Z�᷽��Ҳȡ��
	x = x - ((float)m_pLucorner.x);
	z = ((float)m_pLucorner.z) - z;

	
	//x,z  �ı�������Ҳ��Ӱ��
	x /= (float)m_cellSpacing;
	z /= (float)m_cellSpacing;

	

	

	//������к���
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



	// ���A�����λ��
	float dx = x - col;
	float dz = z - row;


	//ͨ����ֵ����侫ȷ�߶�
	float height = 0.0f;
	// dx+dz<1.0
	if(dz < 1.0f - dx) //������ 
	{
		float uy = B - A; 
		float vy = C - A; 

	
		height = A + d3dbase::Lerp(0.0f, uy, dx) + d3dbase::Lerp(0.0f, vy, dz);
	}
	else //������
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B

	
		height = D + d3dbase::Lerp(0.0f, uy, 1.0f - dx) + d3dbase::Lerp(0.0f, vy, 1.0f - dz);
	}

	//height *= m_heightScale;
	return height;
}

//�������Σ����drawTrisΪtrue, ͬʱ����������
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

		//�ص��ƹ⣬����ɫ��ʾ
		m_device->SetRenderState(D3DRS_LIGHTING, false);

		hr =m_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			m_numVertices,
			0,
			m_numTriangles);

		m_device->SetRenderState(D3DRS_LIGHTING, true);

		// ��������
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
	int startZ = m_pLucorner.z;//������ʵ��ʾz����
	
	int endX = startX + m_width;
	int endZ = startZ - m_depth;    

	if((p.x<endX && p.x>startX)&&(p.z<startZ&&p.z>endZ))
		return true;
	else
		return false;
}
