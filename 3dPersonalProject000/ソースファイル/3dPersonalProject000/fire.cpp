#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "particle.h"
#include "fire.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFire::CFire(int nPriority) : CParticle(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFire::~CFire()
{
}

//=============================================================================
// ��������
//=============================================================================
CFire* CFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, int Life)
{
	// CFire�|�C���^
	CFire* pSwordeffect = NULL;

	// �������m��
	pSwordeffect = new CFire;

	// �ʒu���W�ݒ�
	pSwordeffect->SetPos(pos);

	// �T�C�Y�ݒ�
	pSwordeffect->SetSize(size);

	// �J���[�ݒ�
	pSwordeffect->SetColor(col);

	// �J���[�ݒ�
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
HRESULT CFire::Init()
{
	CParticle::Init(TEX_TYPE_FIRE);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFire::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFire::Update(void)
{
	// �X�V
	CParticle::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFire::Draw(void)
{
	// ���Z�����̃t���O
	SetAdditiveSynthesis();

	// Z�o�b�t�@�̃t���O
	SetZbuffer();

	// �`��
	CParticle::Draw();
}