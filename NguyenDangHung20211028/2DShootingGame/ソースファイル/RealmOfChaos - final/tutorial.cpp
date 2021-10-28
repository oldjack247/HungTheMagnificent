//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "keyboard.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "controller.h"
#include "sound.h"
#include "manager.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial(int nPriority) :CScene(nPriority)
{
	m_apScene2D = NULL;
	m_pSound = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CTutorial::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/BG/tutorial000.png",//�t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
void CTutorial::Unload(void)
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
CTutorial* CTutorial::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CTutorial* pTutorial = NULL;
	pTutorial = new CTutorial;
	pTutorial->Init(pos, size_x * 2, size_y * 2);
	return pTutorial;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CTutorial::Load();
	if (m_apScene2D == NULL)
	{
		m_apScene2D = new CScene2d;
		m_apScene2D->Init(pos, size_x, size_y);
		m_apScene2D->BindTexture(m_pTexture);
	}
	//�T�E���h���~�߂�
	m_pSound->StopSound((m_pSound = CManager::GetSound())->SOUND_LABEL_TITLE_BGM);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
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
			CFade::SetFade(CManager::MODE_GAME);
			CFade::SetFadeSwitch(bFadeSwitch);
		}
	}
	//if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) ||
	//	pInputController->GetJoypadTrigger(CInputController::BUTTON_START))
	//{
	//	CManager::SetMode(CManager::MODE_GAME);
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}
