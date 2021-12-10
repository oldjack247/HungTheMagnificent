#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "particle.h"
#include "swordeffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSwordeffect::CSwordeffect(int nPriority) : CParticle(nPriority)
{
	m_MoveAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSwordeffect::~CSwordeffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CSwordeffect* CSwordeffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, int Life)
{
	// CSwordeffect�|�C���^
	CSwordeffect* pSwordeffect = NULL;

	// �������m��
	pSwordeffect = new CSwordeffect;

	// �ʒu���W�ݒ�
	pSwordeffect->SetPos(pos);

	// �T�C�Y�ݒ�
	pSwordeffect->SetSize(size);

	// �J���[�ݒ�
	pSwordeffect->SetColor(col);

	// �J���[�ݒ�
	pSwordeffect->SetLife(Life);

	// �ړ��ʐݒ�
	pSwordeffect->SetMove(move);

	// ������
	pSwordeffect->Init();

	// �|�C���^��Ԃ�
	return pSwordeffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSwordeffect::Init()
{
	CParticle::Init(TEX_TYPE_FIRE);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSwordeffect::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSwordeffect::Update(void)
{
	// �X�V
	CParticle::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSwordeffect::Draw(void)
{
	// �`��
	CParticle::Draw();
}