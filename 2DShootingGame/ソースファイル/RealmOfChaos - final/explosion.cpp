//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "explosion.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2d(nPriority)
{
	m_nCounterAnim = NULL;
	m_nPatternAnim = NULL;
	m_type = TYPE_SIMPLE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_size_x = 0.0f;
	m_size_y = 0.0f;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Explosion/explosion000.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_SIMPLE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Explosion/bossFog.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_ENEMY2_DEATH]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Explosion/playerExplosion.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_PLAYER_DEATH]);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CExplosion::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̊J��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//��������
//=============================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EXPLOSIONTYPE type)
{
	CExplosion* pExplosion = NULL;
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		if (pExplosion != NULL)
		{
			pExplosion->Init(pos, move, col, size_x, size_y, type);
		}
	}

	return pExplosion;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EXPLOSIONTYPE type)
{
	CScene2d::Init(pos, size_x, size_y);


	BindTexture(m_pTexture[type]);

	m_pos = pos;
	m_move = move;
	m_col = col;
	m_size_x = size_x;
	m_size_y = size_y;
	m_type = type;
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CExplosion::Update(void)
{
	VERTEX_2D* pVtx;

	m_nCounterAnim++;
	//�����̃J�E���^�[��i�߂ăp�^�[����؂�ւ���
	if (m_nCounterAnim >= 1 && m_type == TYPE_SIMPLE)
	{//��莞�Ԍo�߂���
		m_nCounterAnim = 0;
		m_nPatternAnim++;
	}

	if (m_type == TYPE_ENEMY2_DEATH)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 1.0f);
		if (m_nCounterAnim >= 2)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 10)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
	}

	if (m_type == TYPE_PLAYER_DEATH)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f + 0.09f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f + 0.09f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f, 1.0f);
		if (m_nCounterAnim >= 3)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 11)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
	}

	//�ʒu�X�V
	m_pos += m_move;
	//�ʒu���Z�b�g
	SetPosition(m_pos);
	//�F���Z�b�g
	SetCol(m_col);

	if (m_nPatternAnim >= 8 && m_type == TYPE_SIMPLE)
	{
		Uninit();
	}
	if (m_nPatternAnim >= 10 && m_type == TYPE_PLAYER_DEATH)
	{
		Uninit();
	}
	else if (m_col <= 0)
	{
		Uninit();
	}
	else if (m_type == TYPE_SIMPLE)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 1.0f);

		m_pVtxBuff->Unlock();
	}
	else if (m_type == TYPE_ENEMY2_DEATH)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((EXPLOSION_SIZE + m_size_x) / 2), m_pos.y - ((EXPLOSION_SIZE + m_size_y) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((EXPLOSION_SIZE + m_size_x) / 2), m_pos.y - ((EXPLOSION_SIZE + m_size_y) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((EXPLOSION_SIZE + m_size_x) / 2), m_pos.y + ((EXPLOSION_SIZE + m_size_y) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((EXPLOSION_SIZE + m_size_x) / 2), m_pos.y + ((EXPLOSION_SIZE + m_size_y) / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_PLAYER_DEATH)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((PLAYER_EXPLOSION_SIZE + m_size_x) / 2), m_pos.y - ((PLAYER_EXPLOSION_SIZE + m_size_y) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((PLAYER_EXPLOSION_SIZE + m_size_x) / 2), m_pos.y - ((PLAYER_EXPLOSION_SIZE + m_size_y) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((PLAYER_EXPLOSION_SIZE + m_size_x) / 2), m_pos.y + ((PLAYER_EXPLOSION_SIZE + m_size_y) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((PLAYER_EXPLOSION_SIZE + m_size_x) / 2), m_pos.y + ((PLAYER_EXPLOSION_SIZE + m_size_y) / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}


