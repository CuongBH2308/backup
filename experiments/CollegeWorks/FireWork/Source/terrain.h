/*
 �ļ�����������ϵͳ���߶ȵĲ���������ļ���
 */
#ifndef __terrainH__
#define __terrainH__

#include "d3dbase.h"
#include <string>
#include <vector>

namespace d3d{
	
	class CTerrain
	{
		//****************************���졡����***********************************************
	public:
		//���ظ߶�ͼ���������㻺�壬�������岢�������
		CTerrain(IDirect3DDevice9* device,
			std::string heightmapFileName,//�ļ����ݰ����˸���λ�õĸ߶�
			D3DXVECTOR3 lucorner,                //�������Ͻǵ�λ�ã��������б� λ�á��������꣪cellSpacing��
			int numVertsPerRow,           //ÿ�еĶ�����
			int numVertsPerCol,           //ÿ�еĶ�����
			int cellSpacing,              //��Ԫ��Ŀ��
			float heightScale);            //����
		
		
		~CTerrain();
		
		//*****************************�ӿڡ�����**********************************************
	public:
		
		//���ָ��λ�õĸ߶ȣ����㴦�ģ�
		int  getHeightmapEntry(int row, int col);

		//���ӻ���ٵ��ε�����߶�
		void addHeight(float height);
		
		//����ָ��λ�õĸ߶�
		void setHeightmapEntry(int row, int col, int value);
		
		//���ݵ�ǰ���꣨�Ƕ��㴦�ģ�ƽ������xz���꣨Ϊ��ȷ�����У����ڼ��㣩����ֵ�����ȷ�߶�����
		float getHeight(float x, float z);
		
		//���ļ���������ͼ
		bool  loadTexture(std::string fileName);
		
		//������������ÿ��λ�õĸ߶�����������ɫ��������ɫ��������lightTerrain��ģ�����Ч����
		bool  genTexture(D3DXVECTOR3* directionToLight);
		
		//�������Σ����drawTrisΪtrue, ͬʱ����������
		bool  draw(D3DXMATRIX* world, bool drawTris);

		//�жϵ�P�Ƿ��ڵ�����
		bool IsInside(D3DXVECTOR3 p);

		
		
		
		//*******************************��������********************************************
	private:
		//�����ļ������ݶ���m_heightmap��ȥ����ʾ���εĸ߶�
		bool  readRawFile(std::string fileName);
		
		//�������㻺�岢�������
		bool  computeVertices();
		
		//�����������岢�������
		bool  computeIndices();
		
		//���ݹ��շ������������ͼ����m_tex����������ɫ(������Ӱ����)������computeShade�������ǿ�ȣ�
		bool  lightTerrain(D3DXVECTOR3* directionToLight);
		
		//����ƽ�淨�ߺ͹��߷�����ļн��������ǿ��
		float computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight);
		
		
		
		//****************************���ݳ�Ա***********************************************
		
	private:
		IDirect3DDevice9*       m_device;
		IDirect3DTexture9*      m_tex;
		IDirect3DVertexBuffer9* m_vb;//���㻺��
		IDirect3DIndexBuffer9*  m_ib;//��������
		
		
		D3DXVECTOR3 m_pLucorner;     //�������Ͻǵ�λ��
		
		int m_numVertsPerRow;//ÿ�ж�����
		int m_numVertsPerCol;//ÿ�ж�����
		int m_cellSpacing;   //��Ԫ��Ŀ��
		
		int m_numCellsPerRow;//ÿ�еĵ�Ԫ����
		int m_numCellsPerCol;//ÿ�еĵ�Ԫ����
		int m_width;
		int m_depth;
		int m_numVertices;
		int m_numTriangles;
		
		float m_heightScale;
		
		std::vector<int> m_heightmap;
		
		//************************�ڲ����ݽṹ***************************************************
		
	private:
		//�����ʽ
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
