#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "particle.h"
#include "magiccircle.h"
#include "Fire.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMagiccercle::CMagiccercle(int nPriority) : CParticle(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMagiccercle::~CMagiccercle()
{
}

//=============================================================================
// ��������
//=============================================================================
CMagiccercle* CMagiccercle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int Life, MAGICCIRCLETYPE type)
{
	// CMagiccercle�|�C���^
	CMagiccercle* pMagiccerclet = NULL;

	// �������m��
	pMagiccerclet = new CMagiccercle;

	// �ʒu���W�ݒ�
	pMagiccerclet->SetPos(pos);

	// �p�x�ݒ�
	pMagiccerclet->SetRot(rot);

	// �T�C�Y�ݒ�
	pMagiccerclet->SetSize(size);

	// �J���[�ݒ�
	pMagiccerclet->SetColor(col);

	// �J���[�ݒ�
	pMagiccerclet->SetLife(Life);

	// ������
	pMagiccerclet->Init(type);

	// �|�C���^��Ԃ�
	return pMagiccerclet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMagiccercle::Init(MAGICCIRCLETYPE type)
{
	switch (type)
	{
	case MAGICCIRCLETYPE_PLAYER:
		CParticle::Init(TEX_TYPE_MAGICCIRCLE);
		break;

	case MAGICCIRCLETYPE_ENEMY:
		SetAnimation(MAGICCERCLE_ENEMY_COUNTANIM, MAGICCERCLE_ENEMY_PATTERNANIM, MAGICCERCLE_ENEMY_TIMEANIM);
		CParticle::Init(TEX_TYPE_ENEMYCREATE_MAGICCIRCLE);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMagiccercle::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMagiccercle::Update(void)
{
	// �X�V
	CParticle::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMagiccercle::Draw(void)
{
	// �`��
	CParticle::Draw();
}