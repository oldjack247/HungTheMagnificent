//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "pause.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "fade.h"
#include "input.h"
#include "controller.h"
#include "keyboard.h"
#include "game.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPause::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CPause::m_pVtxBuff = NULL;
int CPause::m_nSelect = PAUSE_RETURN;

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPause::CPause()
{
	m_nSelect = PAUSE_RETURN;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// �e�N�X�`���̕`�揈��
//=============================================================================
HRESULT CPause::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data/TEXTURE/pause002.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CPause::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CPause* CPause::Create(void)
{
	CPause* pPause;
	pPause = new CPause;
	pPause->Init();

	return pPause;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_2D* pVtx;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * 6,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	m_nSelect = PAUSE_RETURN;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.001f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.001f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		pVtx[nCount].rhw = 1.0f;

		pVtx[nCount].col = D3DCOLOR_RGBA(0, 0, 0, 180);

	}

	// ����������
	for (int nCount = 0; nCount < PAUSE_MAX; nCount++)
	{
		pVtx[4].pos = D3DXVECTOR3(D3DXVECTOR3((SCREEN_WIDTH / 2 - POLYGON_SIZE * 2) + nCount * 50 - POLYGON_SIZE * 2,
			(SCREEN_HEIGHT / 2 - POLYGON_SIZE * 2) + nCount * POLYGON_SIZE * 1.5 - POLYGON_SIZE / 2, 0.0f));

		pVtx[5].pos = D3DXVECTOR3(D3DXVECTOR3((SCREEN_WIDTH / 2 - POLYGON_SIZE * 2) + nCount * 50 + POLYGON_SIZE * 2,
			(SCREEN_HEIGHT / 2 - POLYGON_SIZE * 2) + nCount * POLYGON_SIZE * 1.5 - POLYGON_SIZE / 2, 0.0f));

		pVtx[6].pos = D3DXVECTOR3(D3DXVECTOR3((SCREEN_WIDTH / 2 - POLYGON_SIZE * 2) + nCount * 50 - POLYGON_SIZE * 2,
			(SCREEN_HEIGHT / 2 - POLYGON_SIZE * 2) + nCount * POLYGON_SIZE * 1.5 + POLYGON_SIZE / 2, 0.0f));

		pVtx[7].pos = D3DXVECTOR3(D3DXVECTOR3((SCREEN_WIDTH / 2 - POLYGON_SIZE * 2) + nCount * 50 + POLYGON_SIZE * 2,
			(SCREEN_HEIGHT / 2 - POLYGON_SIZE * 2) + nCount * POLYGON_SIZE * 1.5 + POLYGON_SIZE / 2, 0.0f));

		pVtx[4].tex = D3DXVECTOR2(nCount * 0.25f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(nCount * 0.25f + 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(nCount * 0.25f, 0.5f);
		pVtx[7].tex = D3DXVECTOR2(nCount * 0.25f + 0.25f, 0.5f);

		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	CRenderer::ResumeGame();

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	VERTEX_2D* pVtx;
	CInputKeyboard* pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();
	CInputController* pInputController = NULL;
	pInputController = CManager::GetController();
	DIJOYSTATE2 Controller = pInputController->GetController();
	bool bFadeSwitch = false;

	// ���ֈړ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_W) || pInputController->GetJoypadTrigger(CInputController::BUTTON_UP))
	{
		m_nSelect--;

		if (m_nSelect < PAUSE_RETURN)
		{
			m_nSelect = PAUSE_END;
		}
	}
	// �E�ֈړ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_S) || pInputController->GetJoypadTrigger(CInputController::BUTTON_DOWN))
	{
		m_nSelect++;

		if (m_nSelect > PAUSE_END)
		{
			m_nSelect = PAUSE_RETURN;
		}
	}

	// ���菈��
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputController->GetJoypadTrigger(CInputController::BUTTON_A))
	{
		switch (m_nSelect)
		{
		case PAUSE_RETURN:
			Uninit();
			break;

		case PAUSE_RETRY:
			Uninit();
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				bFadeSwitch = true;
				CFade::SetFade(CManager::MODE_GAME);
				CFade::SetFadeSwitch(bFadeSwitch);
			}
			break;

		case PAUSE_TITLE:
			Uninit();
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				bFadeSwitch = true;
				CFade::SetFade(CManager::MODE_TITLE);
				CFade::SetFadeSwitch(bFadeSwitch);
			}
			break;

		case PAUSE_END:
			DestroyWindow(FindWindow(CLASS_NAME, NULL));
			break;
		default:
			break;
		}

	}
	else
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCount = 0; nCount < PAUSE_MAX; nCount++)
		{
			if (nCount == m_nSelect)
			{
				pVtx[4].tex = D3DXVECTOR2(nCount * 0.25f, 0.5f);
				pVtx[5].tex = D3DXVECTOR2(nCount * 0.25f + 0.25f, 0.5f);
				pVtx[6].tex = D3DXVECTOR2(nCount * 0.25f, 1.0f);
				pVtx[7].tex = D3DXVECTOR2(nCount * 0.25f + 0.25f, 1.0f);
			}
			else
			{
				pVtx[4].tex = D3DXVECTOR2(nCount * 0.25f, 0.0f);
				pVtx[5].tex = D3DXVECTOR2(nCount * 0.25f + 0.25f, 0.0f);
				pVtx[6].tex = D3DXVECTOR2(nCount * 0.25f, 0.5f);
				pVtx[7].tex = D3DXVECTOR2(nCount * 0.25f + 0.25f, 0.5f);
			}

			pVtx += 4;
		}

		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{
	CRenderer* pRenderer = CManager::GetRenderer();

	for (int nCount = 0; nCount < PAUSE_MAX + 1; nCount++)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pRenderer->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		if (nCount == 0)
		{
			pRenderer->GetDevice()->SetTexture(0, NULL);
		}
		else
		{
			pRenderer->GetDevice()->SetTexture(0, m_pTexture);
		}

		// �|���S���̕`��
		pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, NUM_POLYGON);
	}
}


