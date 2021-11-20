//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_pUi = NULL;
	m_nCountTexture = 1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//�`���[�g���A����UI�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_TUTORIAL);
	m_pUi->SetTextureSelect(m_nCountTexture, 2);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_START))
		{
			if (m_nCountTexture == TEXTURE_END_NUM)
			{
				//�t�F�[�h�̐���
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}

			// �e�N�X�`�������炷����������������
			if (m_nCountTexture < TEXTURE_END_NUM)
			{
				m_nCountTexture++;
			}
		}
	}

	// �e�N�X�`�������炷
	m_pUi->SetTextureSelect(m_nCountTexture, TEXTURE_END_NUM);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}