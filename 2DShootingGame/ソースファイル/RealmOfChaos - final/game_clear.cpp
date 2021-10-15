//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game_clear.h"
//#include "game.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "controller.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CGameClear::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameClear::CGameClear(int nPriority) : CScene(nPriority)
{
	m_apScene2D = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameClear::~CGameClear()
{

}

//=============================================================================
// �e�N�X�`���̕`�揈��
//=============================================================================
HRESULT CGameClear::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/UI/gameclear000.png",//�t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CGameClear::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CGameClear* CGameClear::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CGameClear* pGameClear = NULL;

	pGameClear == new CGameClear;
	pGameClear->Init(pos, size_x * 2, size_y * 2);
	return pGameClear;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGameClear::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CGameClear::Load();

	if (m_apScene2D == NULL)
	{
		m_apScene2D = new CScene2d;
		m_apScene2D->Init(pos, size_x, size_y);
		m_apScene2D->BindTexture(m_pTexture);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGameClear::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGameClear::Update(void)
{
	VERTEX_2D* pVtx;
	bool bFadeSwitch = false;
	CInputKeyboard* pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();
	CInputController* pInputController = NULL;
	pInputController = CManager::GetController();

	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN)
		|| pInputController->GetJoypadTrigger(CInputController::BUTTON_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			//���[�h�ڍs
			bFadeSwitch = true;
			CFade::SetFade(CManager::MODE_RESULT);
			CFade::SetFadeSwitch(bFadeSwitch);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGameClear::Draw(void)
{

}
