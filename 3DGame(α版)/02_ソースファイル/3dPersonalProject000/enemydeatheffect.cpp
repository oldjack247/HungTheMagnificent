#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "particle.h"
#include "enemydeatheffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemydeatheffect::CEnemydeatheffect(int nPriority) : CParticle(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemydeatheffect::~CEnemydeatheffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CEnemydeatheffect* CEnemydeatheffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, int Life)
{
	// CEnemydeatheffect�|�C���^
	CEnemydeatheffect* pSwordeffect = NULL;

	// �������m��
	pSwordeffect = new CEnemydeatheffect;

	// �ʒu���W�ݒ�
	pSwordeffect->SetPos(pos);

	// �T�C�Y�ݒ�
	pSwordeffect->SetSize(size);

	// �J���[�ݒ�
	pSwordeffect->SetColor(col);

	// ���C�t�ݒ�
	pSwordeffect->SetLife(Life);

	// ���������̑��
	pSwordeffect->SetMove(move);

	// ������
	pSwordeffect->Init();

	// �|�C���^��Ԃ�
	return pSwordeffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemydeatheffect::Init()
{
	SetAnimation(ENEMYDEATHEFFEC_COUNTANIM, ENEMYDEATHEFFEC_PATTERNANIM, ENEMYDEATHEFFEC_TIMEANIM);
	CParticle::Init(TEX_TYPE_ENEMYDEATH);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemydeatheffect::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemydeatheffect::Update(void)
{
	// �X�V
	CParticle::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemydeatheffect::Draw(void)
{
	// ���Z�����̃t���O
	SetAdditiveSynthesis();

	// Z�o�b�t�@�̃t���O
	SetZbuffer();

	// �`��
	CParticle::Draw();
}