//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "warning.h"
#include "game.h"
#include "renderer.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CWarning::m_pTexture[WARNINGTYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWarning::CWarning(int nPriority) : CScene2d(nPriority)
{
	for (int nCount = 0; nCount < WARNINGTYPE_MAX; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_type = WARNINGTYPE_NONE;
	m_pSound = NULL;
	nStopCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWarning::~CWarning()
{

}

//=============================================================================
// �e�N�X�`���̕`�揈��
//=============================================================================
HRESULT CWarning::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/warning/warning001.png",//�t�@�C���̖��O
		&m_pTexture[WARNINGTYPE_BOSS1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/warning/warning002.png",//�t�@�C���̖��O
		&m_pTexture[WARNINGTYPE_BOSS2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CWarning::Unload(void)
{
	for (int nCount = 0; nCount < WARNINGTYPE_MAX; nCount++)
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
CWarning* CWarning::Create(D3DXVECTOR3 pos, float size_x, float size_y, WARNINGTYPE type)
{
	CWarning* pWarning = NULL;
	pWarning = new CWarning;
	pWarning->Init(pos, size_x * 2, size_y * 2, type);
	return pWarning;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWarning::Init(D3DXVECTOR3 pos, float size_x, float size_y, WARNINGTYPE type)
{
	CScene2d::Init(pos, size_x, size_y);

	BindTexture(m_pTexture[type]);
	m_pos = pos;
	m_size_x = size_x;
	m_size_y = size_y;
	m_type = type;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWarning::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWarning::Update(void)
{
	VERTEX_2D* pVtx;
	nStopCount++;

	if (m_type == WARNINGTYPE_BOSS1)
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

	if (m_type == WARNINGTYPE_BOSS2)
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

	if (nStopCount >= 100 && m_type == WARNINGTYPE_BOSS1)
	{
		Uninit();
	}
	else if (nStopCount >= 100 && m_type == WARNINGTYPE_BOSS2)
	{
		Uninit();
	}

	else if (m_type == WARNINGTYPE_BOSS1)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == WARNINGTYPE_BOSS2)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWarning::Draw(void)
{
	CRenderer* pRenderer = NULL;
	//NILL��������
	if (pRenderer == NULL)
	{
		pRenderer = CManager::GetRenderer();
	}

	// ���Z�������s��
	pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//�f�B�X�e�B�l�[�V�����J���[�̎w��
	pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	CScene2d::Draw();
}
