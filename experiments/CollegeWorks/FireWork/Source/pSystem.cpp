#include <cstdlib>
#include "PSystem.h"

using namespace d3d;

const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

CPSystem::CPSystem()
{
	m_device = 0;
	m_vb     = 0;
	m_tex    = 0;
}

CPSystem::~CPSystem()
{
	d3dbase::Release<IDirect3DVertexBuffer9*>(m_vb);
	d3dbase::Release<IDirect3DTexture9*>(m_tex);
}

bool CPSystem::init(IDirect3DDevice9* device, char* texFileName)
{
	//顶点缓冲区的大小不是刚好等于粒子数，我们使用顶点缓冲一批批的渲染粒子，每批大小由m_vbSize决定
	m_device = device; 

	HRESULT hr = 0;

	hr = device->CreateVertexBuffer( //创建顶点缓冲
		m_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED 必须和 D3DUSAGE_DYNAMIC 一起使用
		&m_vb,
		0);
	
	if(FAILED(hr))
	{
		::MessageBox(0, "CreateVertexBuffer() - FAILED", "CPSystem", 0);
		return false;
	}

	hr = D3DXCreateTextureFromFile( //从文件创建纹理
		device,
		texFileName,
		&m_tex);

	if(FAILED(hr))
	{
		::MessageBox(0, "D3DXCreateTextureFromFile() - FAILED", "CPSystem", 0);
		return false;
	}

	return true;
}

void CPSystem::reset()
{
	std::list<Attribute>::iterator i;
	for(i = m_particles.begin(); i != m_particles.end(); i++)
	{
		resetParticle( &(*i) );
	}
}

void CPSystem::addParticle()
{
	Attribute attribute;

	resetParticle(&attribute);

	m_particles.push_back(attribute);  //一个粒子对应 其各自的属性
}

void CPSystem::preRender()
{
	m_device->SetRenderState(D3DRS_LIGHTING, false);
	m_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_device->SetRenderState(D3DRS_POINTSCALEENABLE, true); 
	m_device->SetRenderState(D3DRS_POINTSIZE, d3dbase::FtoDw(m_size));
	m_device->SetRenderState(D3DRS_POINTSIZE_MIN, d3dbase::FtoDw(0.0f));

	//根据距离控制粒子大小
	m_device->SetRenderState(D3DRS_POINTSCALE_A, d3dbase::FtoDw(0.0f));
	m_device->SetRenderState(D3DRS_POINTSCALE_B, d3dbase::FtoDw(0.0f));
	m_device->SetRenderState(D3DRS_POINTSCALE_C, d3dbase::FtoDw(1.0f));
		
	// 使用纹理透明
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CPSystem::postRender()
{
	m_device->SetRenderState(D3DRS_LIGHTING,          true);
	m_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_device->SetRenderState(D3DRS_POINTSCALEENABLE,  false);
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE,  false);
}

void CPSystem::render()
{
	//我们在渲染一部分粒子的同时拷贝下一批粒子进缓冲区

	if( !m_particles.empty() )  //粒子系统非空,开始绘制
	{
		
		//设置渲染状态
		preRender();
		
		m_device->SetTexture(0, m_tex);   //纹理
		m_device->SetFVF(Particle::FVF); //顶点格式
		m_device->SetStreamSource(0, m_vb, 0, sizeof(Particle)); //设置顶点缓冲

		//分批绘制
		if(m_vbOffset >= m_vbSize)
			m_vbOffset = 0;

		Particle* v = 0;

		m_vb->Lock(
			m_vbOffset    * sizeof( Particle ), //起始位置
			m_vbBatchSize * sizeof( Particle ), //长度
			(void**)&v,
			m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD); //why

		DWORD numParticlesInBatch = 0; //用来记录当前批中绘制的个数

	
		std::list<Attribute>::iterator i;
		for(i = m_particles.begin(); i != m_particles.end(); i++)
		{
			if( i->m_isAlive )  //只画活的
			{
		
				//将一批粒子拷到顶点缓冲区
				v->m_position = i->m_position;
				v->m_color    = (D3DCOLOR)i->m_color;
				v++; //

				numParticlesInBatch++; 

				if(numParticlesInBatch == m_vbBatchSize) 
				{
					
					//
					m_vb->Unlock();

					//先绘制一批
					m_device->DrawPrimitive(
						D3DPT_POINTLIST,
						m_vbOffset,
						m_vbBatchSize);

					
					
					m_vbOffset += m_vbBatchSize; 

					//在绘制上一批的同时,开始复制下一批入顶点缓冲区
					
					
					if(m_vbOffset >= m_vbSize) 
						m_vbOffset = 0;       

					m_vb->Lock(
						m_vbOffset    * sizeof( Particle ),
						m_vbBatchSize * sizeof( Particle ),
						(void**)&v,
						m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; 
				}	
			}//if( i->m_isAlive )
		}//for

		m_vb->Unlock();

		
		//自制完毕还未绘制因为:最后的(numParticlesInBatch == m_vbBatchSize)未满足
		if( numParticlesInBatch )
		{
			m_device->DrawPrimitive(
				D3DPT_POINTLIST,
				m_vbOffset,
				numParticlesInBatch);
		}

	//下一块
		m_vbOffset += m_vbBatchSize;  //使m_vbOffset >= m_vbSize

		//取消一些绘制状态
		postRender();  
	}
}

bool CPSystem::isEmpty()
{
	return m_particles.empty();
}

bool CPSystem::isDead()
{
	std::list<Attribute>::iterator i;
	for(i = m_particles.begin(); i != m_particles.end(); i++)
	{
		if( i->m_isAlive )
			return false;
	}

	return true;
}

void CPSystem::removeDeadParticles()
{
	std::list<Attribute>::iterator i;

	i = m_particles.begin();

	while( i != m_particles.end() )
	{
		if( i->m_isAlive == false )
		{
			// erase 操作返回下一个iterator，所有这里不用加1
			i = m_particles.erase(i); 
		}
		else
		{
			i++; 
		}
	}
}

//*****************************************************************************
// Snow System
//***************

CSnow::CSnow(d3dbase::BoundingBox* boundingBox, int numParticles)
{
	m_boundingBox   = *boundingBox;
	m_size          = 0.25f;
	m_vbSize        = 2048;
	m_vbOffset      = 0; 
	m_vbBatchSize   = 512; 
	
	for(int i = 0; i < numParticles; i++)
		addParticle();
}

void CSnow::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive  = true;

	// 雪花的随机位置（x,z 坐标）
	d3dbase::GetRandomVector(
		&attribute->m_position,
		&m_boundingBox._min,
		&m_boundingBox._max);

	//y坐标从最高处开始，不用随机产生
	attribute->m_position.y = m_boundingBox._max.y; 

	// 雪花下落并稍向左飘
	attribute->m_velocity.x = d3dbase::GetRandomFloat(0.0f, 1.0f) * -3.0f;
	attribute->m_velocity.y = d3dbase::GetRandomFloat(0.0f, 1.0f) * -10.0f;
	attribute->m_velocity.z = 0.0f;

	// 白色的雪花
	attribute->m_color = d3dbase::WHITE;
}

void CSnow::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for(i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->m_position += i->m_velocity * timeDelta;

		// 是否在边界内
		if( m_boundingBox.isPointInside( i->m_position ) == false ) 
		{
			//若出界，重新设置
			resetParticle( &(*i) );
		}
	}
}

//*****************************************************************************
// Explosion System
//********************

CFirework::CFirework(D3DXVECTOR3* origin, int numParticles)
{
	m_origin        = *origin;
	m_size          = 0.9f; //粒子大小
	m_vbSize        = 2048; //总缓冲大小
	m_vbOffset      = 0;    //缓冲区偏移量
	m_vbBatchSize   = 512;  //成批传输大小

	for(int i = 0; i < numParticles; i++)//加入numParticles个粒子 
		addParticle();
}

void CFirework::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive  = true;
	attribute->m_position = m_origin; //每个粒子都是从烟火爆发点开始的

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3( 1.0f,  1.0f,  1.0f);

	d3dbase::GetRandomVector(      //得到一个任意方向的速度
		&attribute->m_velocity,
		&min,
		&max);

	// normalize to make spherical  归一化
	D3DXVec3Normalize(
		&attribute->m_velocity,
		&attribute->m_velocity);

	attribute->m_velocity *= 100.0f;  //加快速度

	attribute->m_color = D3DXCOLOR(    //产生一个随机颜色
		d3dbase::GetRandomFloat(0.0f, 1.0f),
		d3dbase::GetRandomFloat(0.0f, 1.0f),
		d3dbase::GetRandomFloat(0.0f, 1.0f),
		1.0f);

	attribute->m_age      = 0.0f;
	attribute->m_lifeTime = 2.0f; // 寿命为2秒
}

void CFirework::update(float timeDelta)
{
	std::list<Attribute>::iterator i;

	for(i = m_particles.begin(); i != m_particles.end(); i++)//遍历系统中每个粒子
	{
		// 只更新“活着的”　粒子　
		if( i->m_isAlive )
		{
			i->m_position += i->m_velocity * timeDelta; //由速度改变位置

			i->m_age += timeDelta;   //生存时间自加

			if(i->m_age > i->m_lifeTime) // kill 若生存时间大于寿命, kill  it
				i->m_isAlive = false;
		}
	}
}

void CFirework::preRender()
{
	CPSystem::preRender();

	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// z-buffer只读
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void CFirework::postRender()
{
	CPSystem::postRender();

	m_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//*****************************************************************************
// Laser System
//****************

CParticleGun::CParticleGun(CCamera* CCamera)
{
	m_CCamera          = CCamera;
	m_size            = 0.8f;
	m_vbSize          = 2048;
	m_vbOffset        = 0;  
	m_vbBatchSize     = 512; 
}

void CParticleGun::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive  = true;

	D3DXVECTOR3 CCameraPos;
	m_CCamera->getPosition(&CCameraPos);

	D3DXVECTOR3 CCameraDir;
	m_CCamera->getLook(&CCameraDir);

	// 转到相机空间
	attribute->m_position = CCameraPos;
	attribute->m_position.y -= 1.0f; //　稍低以表示我们端着把枪

	// 速度方向为我们的朝向
	attribute->m_velocity = CCameraDir * 100.0f;

	//子弹颜色
	attribute->m_color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	attribute->m_age      = 0.0f; 
	attribute->m_lifeTime = 1.0f; // lives for 1 seconds
}

void CParticleGun::update(float timeDelta)
{
	std::list<Attribute>::iterator i;

	for(i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->m_position += i->m_velocity * timeDelta;

		i->m_age += timeDelta;

		if(i->m_age > i->m_lifeTime) // kill 
			i->m_isAlive = false;
	}
	removeDeadParticles();
}


//*****************************************************************************
// FireworkGun System
//****************

CParticleFireworkGun::CParticleFireworkGun(CCamera* CCamera)
{
	m_CCamera          = CCamera;
	m_size            = 0.8f;
	m_vbSize          = 2048;
	m_vbOffset        = 0;  
	m_vbBatchSize     = 512; 
}

void CParticleFireworkGun::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive  = true;

	D3DXVECTOR3 CCameraPos;
	m_CCamera->getPosition(&CCameraPos);

	D3DXVECTOR3 CCameraDir;
	m_CCamera->getLook(&CCameraDir);

	// 转到相机空间
	attribute->m_position = CCameraPos;
	attribute->m_position.y -= 1.0f; //　稍低以表示我们端着把枪

	/// 速度方向为我们的朝向
	attribute->m_velocity = CCameraDir * 300.0f;

	//子弹颜色
	attribute->m_color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	attribute->m_age      = 0.0f; 
	attribute->m_lifeTime = 1.0f; // 寿命1秒
}

//返回已经过时的子弹：成为要爆炸的烟火
std::list<Attribute> CParticleFireworkGun::Getupdate(float timeDelta)
{
	std::list<Attribute>::iterator i;

	std::list<Attribute> DeadList;

	for(i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->m_position += i->m_velocity * timeDelta;

		i->m_age += timeDelta;

		if(i->m_age > i->m_lifeTime) // kill 
		{
			i->m_isAlive = false;
			DeadList.push_back(*i);

		}
	}
	removeDeadParticles();
	return DeadList;
}

void CParticleFireworkGun::update(float timeDelta)
{

}