//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "result.h"
#include "keyboard.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "manager.h"
#include "score.h"
#include "controller.h"
#include "sound.h"
#include "fade.h"
#include "client_ranking.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CCrient_ranking* CResult::m_pCrient_ranking = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_apScene2D = NULL;
	m_pSound = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CResult::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/BG/rankingbg001.png",//�t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
void CResult::Unload(void)
{
	CScore::Unload();
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CResult* CResult::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CResult* pResult = NULL;
	pResult = new CResult;
	pResult->Init(pos, size_x * 2, size_y * 2);
	return pResult;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CScore::Load();
	if (m_apScene2D == NULL)
	{
		m_apScene2D = new CScene2d;
		m_apScene2D->Init(pos, size_x, size_y);
		m_apScene2D->BindTexture(m_pTexture);
	}
	//m_pCrient_ranking = CCrient_ranking::Create(D3DXVECTOR3(600.0f, 100.0f, 0.0f), SCORE_WIDTH, 85);
	//�T�E���h���~�߂�
	m_pSound->StopSound((m_pSound = CManager::GetSound())->SOUND_LABEL_GAME_BGM);
	//�T�E���h���~�߂�
	m_pSound->StopSound((m_pSound = CManager::GetSound())->SOUND_LABEL_2FBOSS_BATTLE_BGM);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	CScore::Unload();
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	bool bFadeSwitch = false;
	CInputKeyboard* pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();
	CInputController* pInputController = NULL;
	pInputController = CManager::GetController();
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) ||
		pInputController->GetJoypadTrigger(CInputController::BUTTON_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			//���[�h�ڍs
			bFadeSwitch = true;
			CFade::SetFade(CManager::MODE_TITLE);
			CFade::SetFadeSwitch(bFadeSwitch);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}

