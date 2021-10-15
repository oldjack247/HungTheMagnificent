#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "specialattackeffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSpecialattackeffect::CSpecialattackeffect()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpecialattackeffect::~CSpecialattackeffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CSpecialattackeffect* CSpecialattackeffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int Life)
{
	// CSpesialattackeffect�N���X�̃|�C���^
	CSpecialattackeffect* pSpecialattackeffect;

	// �������m��
	pSpecialattackeffect = new CSpecialattackeffect;

	// �ʒu���W�ݒ�
	pSpecialattackeffect->SetPos(pos);

	// �T�C�Y�ݒ�
	pSpecialattackeffect->SetSize(size);

	// �J���[�ݒ�
	pSpecialattackeffect->SetColor(col);

	// �J���[�ݒ�
	pSpecialattackeffect->SetLife(Life);

	// �A�j���[�V�����̐ݒ�
	pSpecialattackeffect->SetAnimation(SPECIALATTACKEFFECT_COUNTANIM, SPECIALATTACKEFFECT_PATTERNANIM, SPECIALATTACKEFFECT_TIMEANIM);

	// ������
	pSpecialattackeffect->Init();

	// CSpark�N���X�̃|�C���^��Ԃ�
	return pSpecialattackeffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSpecialattackeffect::Init()
{
	// CParticle�N���X��Init
	CParticle::Init(TEX_TYPE_SPESIALATTACK);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSpecialattackeffect::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSpecialattackeffect::Update(void)
{
	// �X�V
	CParticle::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSpecialattackeffect::Draw(void)
{
	// ���Z�����̃t���O
	SetAdditiveSynthesis();

	// �`��
	CParticle::Draw();
}