//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_nScore = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CScore::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/number000.png",//�t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
void CScore::Unload(void)
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
CScore* CScore::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CScore* pScore = NULL;
	pScore = new CScore;
	pScore->Init(pos, size_x, size_y);
	return pScore;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	int nCntPlace;
	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		m_apScene2D[nCntPlace] = new CScene2d(GetPriority());
		m_apScene2D[nCntPlace]->BindTexture(m_pTexture);

		//�f�o�C�X�̎擾
		CRenderer* pRenderer = NULL;
		pRenderer = CManager::GetRenderer();

		VERTEX_2D* pVtx;

		//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		pRenderer->GetDevice()->CreateVertexBuffer(
			sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@
			FVF_VERTEX_2D,								// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&m_apScene2D[nCntPlace]->m_pVtxBuff,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL);										// NULL�ɐݒ�

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_apScene2D[nCntPlace]->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pos.x + nCntPlace * SCORE_INTERVAL_X, pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + nCntPlace * SCORE_INTERVAL_X + size_x, pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x + nCntPlace * SCORE_INTERVAL_X, pos.y + size_y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + nCntPlace * SCORE_INTERVAL_X + size_x, pos.y + size_y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_apScene2D[nCntPlace]->m_pVtxBuff->Unlock();
	}


	return S_OK;
}

//=============================================================================
// �I����������
//=============================================================================
void CScore::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
// �`�揈������
//=============================================================================
void CScore::Draw(void)
{

}

//=============================================================================
//�X�R�A�̉��Z����
//=============================================================================
void CScore::AddScore(int nValue)
{
	VERTEX_2D* pVtx;
	int nCntPlace;
	int nNumber;

	m_nScore += nValue;
	if (m_nScore < 0)
	{
		m_nScore = 0;
	}
	else if (m_nScore >= (int)(powf(10.0f, (float)(NUM_PLACE))))
	{
		m_nScore = (int)(powf(10.0f, (float)(NUM_PLACE))) - 1;
	}

	for (nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_apScene2D[nCntPlace]->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �X�R�A�����̍X�V
		nNumber = (m_nScore % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_apScene2D[nCntPlace]->m_pVtxBuff->Unlock();
	}

}

