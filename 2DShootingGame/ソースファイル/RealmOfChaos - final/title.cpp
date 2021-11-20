//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "title.h"
#include "keyboard.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h" 
#include "controller.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[TITLETYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_titletype = TITLETYPE_START;
	m_pSound = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// �e�N�X�`���̕`�揈��
//=============================================================================
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/BG/titlebg003.png",//�t�@�C���̖��O
		&m_pTexture[TITLETYPE_BG]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/BG/titlename001.png",//�t�@�C���̖��O
		&m_pTexture[TITLETYPE_NAME]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/BG/start001.png",//�t�@�C���̖��O
		&m_pTexture[TITLETYPE_START]);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CTitle* CTitle::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CTitle* pTitle = NULL;
	pTitle = new CTitle;
	pTitle->Init(pos, size_x * 2, size_y * 2);
	return pTitle;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			m_apScene2D[nCount] = new CScene2d;
			if (m_apScene2D[nCount] != NULL)
			{
				m_apScene2D[nCount]->Init(pos, size_x, size_y);

				m_apScene2D[nCount]->BindTexture(m_pTexture[nCount]);
			}
		}
	}

	//�T�E���h�̃Z�b�g
	m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_TITLE_BGM);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	VERTEX_2D* pVtx;

	bool bFadeSwitch = false;
	CInputKeyboard* pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();
	CInputController* pInputController = NULL;
	pInputController = CManager::GetController();

	if (m_titletype == TITLETYPE_START)
	{
		if (m_col.a >= 0.0f)
		{
			m_col.a -= 0.01f;
		}
		else if (m_col.a <= 0.0f)
		{
			m_col.a = 1.0f;
		}
	}

	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN)
		|| pInputController->GetJoypadTrigger(CInputController::BUTTON_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			//���[�h�ڍs
			bFadeSwitch = true;
			CFade::SetFade(CManager::MODE_TUTORIAL);
			CFade::SetFadeSwitch(bFadeSwitch);
		}
	}
	else if (m_titletype == TITLETYPE_START)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_apScene2D[2]->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_apScene2D[2]->m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}
