//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "title.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//�T�E���h�̍Đ�
	//CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	//�Q�[���^�C�g����UI�̐���
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_TITLE);
	CUi::Create(PRESSSTART_POS, PRESSSTART_SIZE, CUi::TYPE_PRESSSTART);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_START))
		{
			//�T�E���h�̍Đ�
			//CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECISION);

			//�t�F�[�h�̐���
			CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}