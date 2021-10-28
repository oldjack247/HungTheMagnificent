//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CFade::FADE CFade::m_Fade = FADE_NONE;
CManager::MODE CFade::m_ModeNext = CManager::MODE_TITLE;
D3DXCOLOR CFade::m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
bool CFade::m_bFadeSwitch = false;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
//��������
//=============================================================================
CFade* CFade::Create(D3DXVECTOR3 pos, float size_x, float size_y, CManager::MODE modenext)
{
	CFade* pFade = NULL;
	if (pFade == NULL)
	{
		pFade = new CFade;
		if (pFade != NULL)
		{
			pFade->Init(pos, size_x, size_y, modenext);
		}
	}
	return pFade;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, float size_x, float size_y, CManager::MODE modenext)
{
	m_ModeNext = modenext;
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//�I�u�W�F�N�g�̒��_�o�b�t�@����
	pRenderer->GetDevice()->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�j
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&m_pVtxBuff,//�ϐ������ς��ƕύX���K�v
		NULL);
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size_x, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, size_y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size_x, size_y, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//�I����������
//=============================================================================
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//�X�V��������
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^
	if (m_bFadeSwitch == true)
	{
		if (m_Fade != FADE_NONE)
		{//�t�F�[�h�������̎�
			if (m_Fade == FADE_IN)
			{//�t�F�[�h�C��
				m_col.a -= FADE_RATE;
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_Fade = FADE_NONE;
					if (m_col.a >= 0)
					{
						m_bFadeSwitch = false;
					}
				}
			}
			if (m_Fade == FADE_OUT)
			{//�t�F�[�h
				m_col.a += FADE_RATE;
				if (m_col.a >= 1.0f)
				{
					m_col.a = 1.0f;
					m_Fade = FADE_IN;

					CManager::SetMode(m_ModeNext);//���[�h�̐ݒ�
				}
			}
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//���_���(�J���[�̂ݍX�V)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;
		//���_�f�[�^�A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CFade::Draw(void)
{
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	if (pRenderer != NULL)
	{
		pRenderer->GetDevice()->SetTexture(0, NULL);
		//���_�o�b�t�@���f�o�C�X�̃X�g���[���Ƀo�C���h
		pRenderer->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

		//�|���S���̕`��
		pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
//�t�F�[�h�̃Z�b�g
//=============================================================================
void CFade::SetFade(CManager::MODE modenext)
{
	m_Fade = FADE_OUT;
	m_ModeNext = modenext;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//�Z�b�g
//=============================================================================
void CFade::SetFadeSwitch(bool bFadeSwitch)
{
	m_bFadeSwitch = bFadeSwitch;
}
