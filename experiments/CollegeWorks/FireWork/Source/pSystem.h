/*
文件描述：一个基类CPSystem表示粒子　系统，从其派生出许多不同的粒子　类，如：烟火，
雪，子弹等
 */
#ifndef _PSystem_H
#define _PSystem_H

#include "d3dBase.h"
#include "Camera.h"
#include <list>

namespace d3d
{
	//顶点格式
	struct Particle  
	{
		D3DXVECTOR3 m_position;
		D3DCOLOR    m_color;
		static const DWORD FVF;
	};
	
	struct Attribute //粒子属性
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
		float       m_lifeTime;     // 　寿命
		float       m_age;          //   已生存时间
		D3DXCOLOR   m_color;        // 　当前颜色
		D3DXCOLOR   m_colorFade;    // 　当前颜色消隐
		bool        m_isAlive;      //　　还活着吗
	};


	class CPSystem
	{
	public:
		CPSystem();
		virtual ~CPSystem();

		virtual bool init(IDirect3DDevice9* device, char* texFileName);
		virtual void reset();
		
		//当一个粒子　“死了”　的时候，我们并不释放它的内存，而是让他重新生成粒子
		virtual void resetParticle(Attribute* attribute) = 0;

		//增加粒子
		virtual void addParticle();

		//画出当前时刻的所有粒子
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
		float                   m_emitRate;   // 新的粒子　加到系统中去的速度
		float                   m_size;       //粒子　的大小
		IDirect3DTexture9*      m_tex;
		IDirect3DVertexBuffer9* m_vb;
		std::list<Attribute>    m_particles;
		int                     m_maxParticles; // 系统允许的最大粒子数

		//
		// 以下三个变量使渲染更加快
		//

		DWORD m_vbSize;      // vb的大小
		DWORD m_vbOffset;    // 加锁vb  的偏移量
		DWORD m_vbBatchSize; // 批数
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