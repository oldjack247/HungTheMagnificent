//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "scene2d.h"
#include "scene3d.h"
#include "camera.h"
#include "ui.h"
#include "model.h"
#include "light.h"
#include "player.h"
#include "tutorial.h"
#include "result.h"
#include "title.h"
#include "game.h"
#include "gameover.h"
#include "fade.h"
#include "particle.h"
#include "map.h"
#include "skybox.h"
#include "sound.h"
#include "loadmodeldata.h"
#include "debugcollision.h"
#include "mouse.h"

//=============================================================================
// �X�^�e�B�b�N�ϐ�������
//=============================================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CInputMouse* CManager::m_pInputMouse = NULL;
CInputJoystick* CManager::m_pInputJoystick = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CSound* CManager::m_pSound = NULL;
CFade* CManager::m_pFade = NULL;
CMode* CManager::m_pMode = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_NONE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	//�N���X�����Ə�����	
	//�����_���[
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);

	//�L�[�{�[�h
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�Q�[���p�b�h
	m_pInputJoystick = new CInputJoystick;
	m_pInputJoystick->Init(hInstance, hWnd);

	//�}�E�X
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//�T�E���h
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		// ����������
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return -1;
		}
	}

	//�e�N�X�`���̓ǂݍ���
	LoadAll();

	//���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	// �t�F�[�h�̃N���G�C�g
	CManager::CreateFade();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// ���ׂĂ̏I��
	CScene::ReleaseAll();

	//�e�N�X�`���̔j��
	UnloadAll();

	//���C�g�̏I��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�Q�[���p�b�h�̏I��
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}

	//�L�[�{�[�h�̏I��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�}�E�X�̏I��
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̏I������
		m_pMode->Uninit();
	}

	if (m_pSound != NULL)
	{
		//�T�E���h�I��
		m_pSound->CSound::StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//�����_���[�̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputKeyboard != NULL)
	{
		//�L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoystick != NULL)
	{
		//�}�E�X�̍X�V����
		m_pInputJoystick->Update();
	}

	if (m_pInputMouse != NULL)
	{
		//�W���C�X�e�B�b�N�̍X�V����
		m_pInputMouse->Update();
	}

	if (m_pRenderer != NULL)
	{
#ifdef _DEBUG
		// FPS�̃Z�b�g
		m_pRenderer->SetNumFPS(m_nCountFPS);
#endif
		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}

	if (m_pCamera != NULL)
	{
		//�J�����̂̍X�V����
		m_pCamera->Update();
	}

	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̍X�V����
		m_pMode->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}

	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̕`�揈��
		m_pMode->Draw();
	}
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��݂܂Ƃ�
//=============================================================================
void CManager::LoadAll(void)
{
	CParticle::Load();
	CUi::Load();
	CMap::Load();
	CSkyBox::Load();
	CGameover::Load();
	CLoadmodeldata::LoadModelData("data/MODELNAME/player_model_name.txt", CHARACTERTYPE_PLAYER);
	CDebugCollision::Load();
}

//=============================================================================
// �e�N�X�`���̔j���܂Ƃ�
//=============================================================================
void CManager::UnloadAll(void)
{
	CParticle::Unload();
	CMap::Unload();
	CUi::Unload();
	CSkyBox::Unload();
	CGameover::Unload();
	CDebugCollision::Unload();
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̏I������
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	if (m_pMode == NULL)
	{
		m_mode = mode;

		switch (m_mode)
		{
		case MODE_TITLE:

			//�^�C�g���̐���
			m_pMode = new CTitle;

			//�^�C�g���̏���������
			m_pMode->Init();
			break;

		case MODE_GAME:
			if (m_pCamera != NULL)
			{
				m_pCamera->Uninit();
				delete m_pCamera;
				m_pCamera = NULL;
			}
			//�Q�[���̐���
			m_pMode = new CGame;

			//�Q�[���̏���������
			m_pMode->Init();
			break;

		case MODE_TUTORIAL:

			//�`���[�g���A���̐���
			m_pMode = new CTutorial;

			//�`���[�g���A���̏���������
			m_pMode->Init();
			break;

		case MODE_RESULT:

			//�N���A��ʂ̐���
			m_pMode = new CResult;

			//�N���A��ʂ̏���������
			m_pMode->Init();

			break;

		case MODE_GAMEOVER:

			//�Q�[���I�[�o�[��ʂ̐���
			m_pMode = new CGameover;

			//�Q�[���I�[�o�[��ʂ̏���������
			m_pMode->Init();
			break;
		}
	}
}

//=============================================================================
// �J�����̐���
//=============================================================================
void CManager::CreateCamera(void)
{
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		if (m_pCamera != NULL)
		{
			m_pCamera->Init();
		}
	}
}

//=============================================================================
// ���C�g�̐���
//=============================================================================
void CManager::CreateLight(void)
{
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}
}

//=============================================================================
// �t�F�[�h�̐���
//=============================================================================
void CManager::CreateFade(void)
{
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();
	}
}