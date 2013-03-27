/*
�ļ�������һ������CPSystem��ʾ���ӡ�ϵͳ��������������಻ͬ�����ӡ��࣬�磺�̻�
ѩ���ӵ���
 */
#ifndef _PSystem_H
#define _PSystem_H

#include "d3dBase.h"
#include "Camera.h"
#include <list>

namespace d3d
{
	//�����ʽ
	struct Particle  
	{
		D3DXVECTOR3 m_position;
		D3DCOLOR    m_color;
		static const DWORD FVF;
	};
	
	struct Attribute //��������
	{
		Attribute()
		{
			m_lifeTime = 0.0f;  
			m_age      = 0.0f;
			m_isAlive  = true;
		}

		D3DXVECTOR3 m_position;     
		D3DXVECTOR3 m_velocity;     
		D3DXVECTOR3 m_acceleration; 
		float       m_lifeTime;     // ������
		float       m_age;          //   ������ʱ��
		D3DXCOLOR   m_color;        // ����ǰ��ɫ
		D3DXCOLOR   m_colorFade;    // ����ǰ��ɫ����
		bool        m_isAlive;      //������������
	};


	class CPSystem
	{
	public:
		CPSystem();
		virtual ~CPSystem();

		virtual bool init(IDirect3DDevice9* device, char* texFileName);
		virtual void reset();
		
		//��һ�����ӡ������ˡ�����ʱ�����ǲ����ͷ������ڴ棬��������������������
		virtual void resetParticle(Attribute* attribute) = 0;

		//��������
		virtual void addParticle();

		//������ǰʱ�̵���������
		virtual void update(float timeDelta) = 0;
		virtual std::list<Attribute> Getupdate(float timeDelta){return std::list<Attribute>();}

		virtual void preRender();
		virtual void render();
		virtual void postRender();

		bool isEmpty();
		bool isDead();

	protected:
		virtual void removeDeadParticles();

	protected:
		IDirect3DDevice9*       m_device;
		D3DXVECTOR3             m_origin;
		d3dbase::BoundingBox        m_boundingBox;
		float                   m_emitRate;   // �µ����ӡ��ӵ�ϵͳ��ȥ���ٶ�
		float                   m_size;       //���ӡ��Ĵ�С
		IDirect3DTexture9*      m_tex;
		IDirect3DVertexBuffer9* m_vb;
		std::list<Attribute>    m_particles;
		int                     m_maxParticles; // ϵͳ��������������

		//
		// ������������ʹ��Ⱦ���ӿ�
		//

		DWORD m_vbSize;      // vb�Ĵ�С
		DWORD m_vbOffset;    // ����vb  ��ƫ����
		DWORD m_vbBatchSize; // ����
	};


	class CSnow : public CPSystem
	{
	public:
		CSnow(d3dbase::BoundingBox* boundingBox, int numParticles);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
	};

	class CFirework : public CPSystem
	{
	public:
		CFirework(D3DXVECTOR3* origin, int numParticles);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
		void preRender();
		void postRender();
	};

	class CParticleGun : public CPSystem
	{
	public:
		CParticleGun(CCamera* CCamera);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
	private:
		CCamera* m_CCamera;
	};

	class CParticleFireworkGun : public CPSystem
	{
	public:
		CParticleFireworkGun(CCamera* CCamera);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
		std::list<Attribute> Getupdate(float timeDelta);
	private:
		CCamera* m_CCamera;
	};
}

#endif // _PSystem_H