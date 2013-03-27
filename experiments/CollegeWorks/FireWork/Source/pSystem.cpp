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
	//���㻺�����Ĵ�С���Ǹպõ���������������ʹ�ö��㻺��һ��������Ⱦ���ӣ�ÿ����С��m_vbSize����
	m_device = device; 

	HRESULT hr = 0;

	hr = device->CreateVertexBuffer( //�������㻺��
		m_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED ����� D3DUSAGE_DYNAMIC һ��ʹ��
		&m_vb,
		0);
	
	if(FAILED(hr))
	{
		::MessageBox(0, "CreateVertexBuffer() - FAILED", "CPSystem", 0);
		return false;
	}

	hr = D3DXCreateTextureFromFile( //���ļ���������
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

	m_particles.push_back(attribute);  //һ�����Ӷ�Ӧ ����Ե�����
}

void CPSystem::preRender()
{
	m_device->SetRenderState(D3DRS_LIGHTING, false);
	m_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_device->SetRenderState(D3DRS_POINTSCALEENABLE, true); 
	m_device->SetRenderState(D3DRS_POINTSIZE, d3dbase::FtoDw(m_size));
	m_device->SetRenderState(D3DRS_POINTSIZE_MIN, d3dbase::FtoDw(0.0f));

	//���ݾ���������Ӵ�С
	m_device->SetRenderState(D3DRS_POINTSCALE_A, d3dbase::FtoDw(0.0f));
	m_device->SetRenderState(D3DRS_POINTSCALE_B, d3dbase::FtoDw(0.0f));
	m_device->SetRenderState(D3DRS_POINTSCALE_C, d3dbase::FtoDw(1.0f));
		
	// ʹ������͸��
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
	//��������Ⱦһ�������ӵ�ͬʱ������һ�����ӽ�������

	if( !m_particles.empty() )  //����ϵͳ�ǿ�,��ʼ����
	{
		
		//������Ⱦ״̬
		preRender();
		
		m_device->SetTexture(0, m_tex);   //����
		m_device->SetFVF(Particle::FVF); //�����ʽ
		m_device->SetStreamSource(0, m_vb, 0, sizeof(Particle)); //���ö��㻺��

		//��������
		if(m_vbOffset >= m_vbSize)
			m_vbOffset = 0;

		Particle* v = 0;

		m_vb->Lock(
			m_vbOffset    * sizeof( Particle ), //��ʼλ��
			m_vbBatchSize * sizeof( Particle ), //����
			(void**)&v,
			m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD); //why

		DWORD numParticlesInBatch = 0; //������¼��ǰ���л��Ƶĸ���

	
		std::list<Attribute>::iterator i;
		for(i = m_particles.begin(); i != m_particles.end(); i++)
		{
			if( i->m_isAlive )  //ֻ�����
			{
		
				//��һ�����ӿ������㻺����
				v->m_position = i->m_position;
				v->m_color    = (D3DCOLOR)i->m_color;
				v++; //

				numParticlesInBatch++; 

				if(numParticlesInBatch == m_vbBatchSize) 
				{
					
					//
					m_vb->Unlock();

					//�Ȼ���һ��
					m_device->DrawPrimitive(
						D3DPT_POINTLIST,
						m_vbOffset,
						m_vbBatchSize);

					
					
					m_vbOffset += m_vbBatchSize; 

					//�ڻ�����һ����ͬʱ,��ʼ������һ���붥�㻺����
					
					
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

		
		//������ϻ�δ������Ϊ:����(numParticlesInBatch == m_vbBatchSize)δ����
		if( numParticlesInBatch )
		{
			m_device->DrawPrimitive(
				D3DPT_POINTLIST,
				m_vbOffset,
				numParticlesInBatch);
		}

	//��һ��
		m_vbOffset += m_vbBatchSize;  //ʹm_vbOffset >= m_vbSize

		//ȡ��һЩ����״̬
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
			// erase ����������һ��iterator���������ﲻ�ü�1
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

	// ѩ�������λ�ã�x,z ���꣩
	d3dbase::GetRandomVector(
		&attribute->m_position,
		&m_boundingBox._min,
		&m_boundingBox._max);

	//y�������ߴ���ʼ�������������
	attribute->m_position.y = m_boundingBox._max.y; 

	// ѩ�����䲢������Ʈ
	attribute->m_velocity.x = d3dbase::GetRandomFloat(0.0f, 1.0f) * -3.0f;
	attribute->m_velocity.y = d3dbase::GetRandomFloat(0.0f, 1.0f) * -10.0f;
	attribute->m_velocity.z = 0.0f;

	// ��ɫ��ѩ��
	attribute->m_color = d3dbase::WHITE;
}

void CSnow::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for(i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->m_position += i->m_velocity * timeDelta;

		// �Ƿ��ڱ߽���
		if( m_boundingBox.isPointInside( i->m_position ) == false ) 
		{
			//�����磬��������
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
	m_size          = 0.9f; //���Ӵ�С
	m_vbSize        = 2048; //�ܻ����С
	m_vbOffset      = 0;    //������ƫ����
	m_vbBatchSize   = 512;  //���������С

	for(int i = 0; i < numParticles; i++)//����numParticles������ 
		addParticle();
}

void CFirework::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive  = true;
	attribute->m_position = m_origin; //ÿ�����Ӷ��Ǵ��̻𱬷��㿪ʼ��

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3( 1.0f,  1.0f,  1.0f);

	d3dbase::GetRandomVector(      //�õ�һ�����ⷽ����ٶ�
		&attribute->m_velocity,
		&min,
		&max);

	// normalize to make spherical  ��һ��
	D3DXVec3Normalize(
		&attribute->m_velocity,
		&attribute->m_velocity);

	attribute->m_velocity *= 100.0f;  //�ӿ��ٶ�

	attribute->m_color = D3DXCOLOR(    //����һ�������ɫ
		d3dbase::GetRandomFloat(0.0f, 1.0f),
		d3dbase::GetRandomFloat(0.0f, 1.0f),
		d3dbase::GetRandomFloat(0.0f, 1.0f),
		1.0f);

	attribute->m_age      = 0.0f;
	attribute->m_lifeTime = 2.0f; // ����Ϊ2��
}

void CFirework::update(float timeDelta)
{
	std::list<Attribute>::iterator i;

	for(i = m_particles.begin(); i != m_particles.end(); i++)//����ϵͳ��ÿ������
	{
		// ֻ���¡����ŵġ������ӡ�
		if( i->m_isAlive )
		{
			i->m_position += i->m_velocity * timeDelta; //���ٶȸı�λ��

			i->m_age += timeDelta;   //����ʱ���Լ�

			if(i->m_age > i->m_lifeTime) // kill ������ʱ���������, kill  it
				i->m_isAlive = false;
		}
	}
}

void CFirework::preRender()
{
	CPSystem::preRender();

	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// z-bufferֻ��
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

	// ת������ռ�
	attribute->m_position = CCameraPos;
	attribute->m_position.y -= 1.0f; //���Ե��Ա�ʾ���Ƕ��Ű�ǹ

	// �ٶȷ���Ϊ���ǵĳ���
	attribute->m_velocity = CCameraDir * 100.0f;

	//�ӵ���ɫ
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

	// ת������ռ�
	attribute->m_position = CCameraPos;
	attribute->m_position.y -= 1.0f; //���Ե��Ա�ʾ���Ƕ��Ű�ǹ

	/// �ٶȷ���Ϊ���ǵĳ���
	attribute->m_velocity = CCameraDir * 300.0f;

	//�ӵ���ɫ
	attribute->m_color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	attribute->m_age      = 0.0f; 
	attribute->m_lifeTime = 1.0f; // ����1��
}

//�����Ѿ���ʱ���ӵ�����ΪҪ��ը���̻�
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