#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "hiteffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHiteffect::CHiteffect()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHiteffect::~CHiteffect()
{
}
//=============================================================================
// ��������
//=============================================================================
CHiteffect* CHiteffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int Life, HITEFFECTTYPE type)
{
	// CHiteffect�N���X�̃|�C���^
	CHiteffect* pHiteffect;

	// �������m��
	pHiteffect = new CHiteffect;

	// �ʒu���W�ݒ�
	pHiteffect->SetPos(pos);

	// �T�C�Y�ݒ�
	pHiteffect->SetSize(size);

	// �J���[�ݒ�
	pHiteffect->SetColor(col);

	// �J���[�ݒ�
	pHiteffect->SetLife(Life);

	// ������
	pHiteffect->Init(type);

	// CHiteffect�N���X�̃|�C���^��Ԃ�
	return pHiteffect;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CHiteffect::Init(HITEFFECTTYPE type)
{
	switch (type)
	{
	case HITEFFECTTYPE_PLAYER:
		// �A�j���[�V�����̐ݒ�
		SetAnimation(HITEFFECT_PLAYER_COUNTANIM, HITEFFECT_PLAYER_PATTERNANIM, HITEFFECT_PLAYER_TIMEANIM);

		// CParticle�N���X��Init
		CParticle::Init(TEX_TYPE_PLAYERATTACK);
		break;

	case HITEFFECTTYPE_ENEMY:
		// �A�j���[�V�����̐ݒ�
		SetAnimation(HITEFFECT_ENEMY_COUNTANIM, HITEFFECT_ENEMY_PATTERNANIM, HITEFFECT_ENEMY_TIMEANIM);

		// CParticle�N���X��Init
		CParticle::Init(TEX_TYPE_ENEMYATTACK);
		break;

	default:
		break;
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CHiteffect::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CHiteffect::Update(void)
{
	// �X�V
	CParticle::Update();

}
//=============================================================================
// �`�揈��
//=============================================================================
void CHiteffect::Draw(void)
{
	// �`��
	CParticle::Draw();
}