#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "fire.h"
#include "magiccircle.h"
#include "swordeffect.h"
#include "enemy.h"
#include "collision.h"
#include "debugcollision.h"
#include "enemydeatheffect.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TEX_TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticle::CParticle(int nPriority) : CBillboard(nPriority)
{
	m_fAngle = 0.0f;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CParticle::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/slash_effect_1.png", &m_pTexture[TEX_TYPE_1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/slash_effect_2.png", &m_pTexture[TEX_TYPE_2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect.png", &m_pTexture[TEX_TYPE_SWORD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/spark_effect.png", &m_pTexture[TEX_TYPE_PLAYERATTACK]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fire.png", &m_pTexture[TEX_TYPE_FIRE]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/magiccircle.png", &m_pTexture[TEX_TYPE_MAGICCIRCLE]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemycreateeffect.png", &m_pTexture[TEX_TYPE_ENEMYCREATE_MAGICCIRCLE]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemydeatheffect.png", &m_pTexture[TEX_TYPE_ENEMYDEATH]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemyattackeffect.png", &m_pTexture[TEX_TYPE_ENEMYATTACK]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CParticle::Unload(void)
{
	// �e�N�X�`����ޕ��J��Ԃ�
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			// �e�N�X�`��Release
			m_pTexture[nCnt]->Release();

			// m_pTexture��NULL��
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticle::Init(TEX_TYPE TexType)
{
	// �e�N�X�`���^�C�v
	m_TexType = TexType;

	// ������
	CBillboard::Init();

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture[TexType]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CParticle::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticle::Update(void)
{
	// �󂯎��
	D3DXVECTOR3 pos = GetPos();
	float fAngle = GetAngle();
	D3DXVECTOR3 rot = GetRot();
	D3DXCOLOR col = GetColor();
	D3DXVECTOR3 size = GetSize();

	switch (m_TexType)
	{
	case TEX_TYPE_1:
		// �X�V
		CBillboard::Update();
		break;

	case TEX_TYPE_2:
		// �X�V
		CBillboard::Update();
		break;

	case TEX_TYPE_SWORD:
		// �X�V
		CBillboard::Update();

		col.a -= SWORD_EFFECT_ALPHA_SUBTRACT;
		pos += m_Move * SWORD_EFFECT_SPEED;

		SetColor(col);
		SetPos(pos);
		break;

	case TEX_TYPE_PLAYERATTACK:
		// �X�V
		CBillboard::Update();
		break;

	case TEX_TYPE_FIRE:
		// �X�V
		CBillboard::Update(m_fAngle);

		// �F�ⓧ���x�����炷
		col.a -= FIRE_SUBTRACT_COLOR_ALPHA;
		col.r -= FIRE_SUBTRACT_COLOR_RED_GREEN;
		col.g -= FIRE_SUBTRACT_COLOR_RED_GREEN;

		// �e�N�X�`�����񂷊p�x�̉��Z
		fAngle += D3DXToRadian(4.0f);
		pos += m_Move;

		size.x -= 0.01f;
		size.y -= 0.01f;

		// y�����グ��
		m_Move.y += FIRE_SPEED_ADD_Y;

		// �ړ��ʂ����炵�Ă���
		if (m_Move.z <= 0.0f)
		{
			m_Move.z += FIRE_SPEED_ADD_SUBTRACT_Z;
		}
		else if (m_Move.z >= 0.0f)
		{
			m_Move.z -= FIRE_SPEED_ADD_SUBTRACT_Z;
		}

		// ���W�Ɖ�]�ƐF�̃Z�b�g
		SetPos(pos);
		SetAngle(fAngle);
		SetColor(col);
		break;

	case TEX_TYPE_MAGICCIRCLE:
		// �X�V
		CBillboard::Update();

		if (rot.y < D3DX_PI)
		{
			rot.y += D3DXToRadian(2.0f);
			size += D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		}
		else
		{
			// ����pos
			D3DXVECTOR3 firepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���̐�������p�x
			float fFireAngle = D3DXToRadian((rand() % FIRE_CREATE_ANGLE_MAX));

			// �ړ��ʂƋ���
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, cosf(fFireAngle) * FIRE_MOVE_Y, sinf(fFireAngle) * FIRE_MOVE_Z);
			D3DXVECTOR3 Distance = D3DXVECTOR3(size.x, 0.0f, size.y) / 2;

			// �����o�������̊p�x
			float fFireCreateAngle = D3DXToRadian((float)FIRE_CREATE_ANGLE_MAX / (float)MAGICCERCLE_FLAMECREATE_NUM);

			// ���S�ɂł��������o��
			CFire::Create(pos, FIR_SIZE * 2, move * 2, FIRE_COLOR, FIRE_LIFE);

			// �������镪�����o��
			for (int nCount = 0; nCount < MAGICCERCLE_FLAMECREATE_NUM; nCount++)
			{
				firepos.x = pos.x - Distance.x * sinf(rot.y + fFireCreateAngle * (float)nCount);
				firepos.z = pos.z - Distance.z * cosf(rot.y + fFireCreateAngle * (float)nCount);
				CFire::Create(firepos, FIR_SIZE, move, FIRE_COLOR, FIRE_LIFE);
			}

			// ���@�w�̓����ɂ���G�̔���
			MagiccircleCollision();

			CScene::SetbUpdate(false, CScene::OBJTYPE_ENEMY);

#ifdef _DEBUG
			// �����蔻��̉���
			CDebugCollision::Create(pos, D3DXVECTOR3(GetSize().x, GetSize().z, GetSize().y), CDebugCollision::TYPE_SPHERE);
#endif
		}

		SetRot(rot);
		SetSize(size);
		break;


	case TEX_TYPE_ENEMYCREATE_MAGICCIRCLE:
		// �X�V
		CBillboard::Update();

		if (GetLife() == MAGICCERCLE_ENEMY_CREATE_TIME)
		{
			// �G�̐���
			CEnemy::Create(D3DXVECTOR3(pos.x, 55.0f, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SIZE, CEnemy::ENEMYSTATE_NOMAL);
		}
		break;

	case TEX_TYPE_ENEMYDEATH:
		// �X�V
		CBillboard::Update();
		col.a -= ENEMYDEATHEFFEC_SUBTRACT_COLOR_ALPHA;
		pos += m_Move;

		// ���W�ƐF�̃Z�b�g
		SetPos(pos);
		SetColor(col);
		break;

	case TEX_TYPE_ENEMYATTACK:
		// �X�V
		CBillboard::Update();
		break;

	default:
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CParticle::Draw(void)
{
	// �`��
	CBillboard::Draw();
}

//=============================================================================
// ���@�w�̓����ɂ���G�̔���
//=============================================================================
void CParticle::MagiccircleCollision(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	CScene* pScene = GetSceneTop(OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// ���W�̎󂯎��
				D3DXVECTOR3 Getpos = ((CEnemy*)pScene)->GetPos();

				// �����蔻��
				if (CCollision::SphereCollisionInside(pos, size.x / 2, Getpos) == true)
				{
					// �G�ւ̃_���[�W
					((CEnemy*)pScene)->HitDamage(5, CEnemy::DAMAGESTATE_MAGICCIRCLE);
				}
			}
			// ���̃|�C���^�̎󂯎��
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}