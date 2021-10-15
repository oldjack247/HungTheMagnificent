//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLife::~CLife()
{
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CLife::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/player/life000.png",//�t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CLife::Unload(void)
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
CLife* CLife::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CLife* pLife = NULL;
	pLife = new CLife;
	pLife->Init(pos, size_x, size_y);
	return pLife;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		if (m_apScene2D[nCnt] == NULL)
		{
			m_apScene2D[nCnt] = new CScene2d(GetPriority());
			m_apScene2D[nCnt]->Init(pos, size_x, size_y);
			m_apScene2D[nCnt]->BindTexture(m_pTexture);
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLife::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLife::Update(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	int nLife = CPlayer::GetLife();
	int nScene = 2;
	//�|�C���^�̐���
	VERTEX_2D* pVtx;
	for (int nCnt = 0; nCnt < nLife; nCnt++)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_apScene2D[nCnt]->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(0.0f + HP_SIZE_X * (nCnt * 3), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + HP_SIZE_X * (nCnt * 3), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + HP_SIZE_X * (nCnt * 3), 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + HP_SIZE_X * (nCnt * 3), 50.0f, 0.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
				  //���_�f�[�^���A�����b�N����
		m_apScene2D[nCnt]->m_pVtxBuff->Unlock();
	}
	for (int nCnt = nLife; nCnt < MAX_LIFE; nCnt++)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_apScene2D[nCnt]->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//���_�f�[�^���A�����b�N����
		m_apScene2D[nCnt]->m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLife::Draw(void)
{
}
