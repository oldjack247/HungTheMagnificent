//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2d(nPriority)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_type = TYPE_2FBOSS;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_size_x = 0.0f;
	m_size_y = 0.0f;
	m_nEffectFade = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	if (pRenderer == NULL)
	{
		pRenderer = CManager::GetRenderer();
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Effect/2FBossAwakening.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_2FBOSS]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Effect/death_effect000.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_ENEMY2_DEATH]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Effect/bullet_spawn000.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_BULLET_SPAWN]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Effect/bullet_death000.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_BULLET_DEATH]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Effect/bulletEffect000.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_BULLET_EFFECT]);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CEffect::Unload(void)
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
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EFFECTTYPE type)
{
	CEffect* pEffect = NULL;
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		if (pEffect != NULL)
		{
			pEffect->Init(pos, move, col, size_x, size_y, type);
		}
	}
	return pEffect;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EFFECTTYPE type)
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
void CEffect::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CEffect::Update(void)
{
	VERTEX_2D* pVtx;
	m_nCounterAnim++;

	//���ŃJ�E���g��i�߂�
	m_nEffectFade++;

	if (m_type == TYPE_2FBOSS)
	{
		//���X�ɑ傫��
		m_col.a = 0.0f;
		m_size_x += 5.0f;
		m_size_y += 5.0f;
	}

	if (m_type == TYPE_BULLET_EFFECT)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f + 0.333f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f + 0.333f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f, 1.0f);
		if (m_nCounterAnim >= 3)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 3)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
	}

	if (m_type == TYPE_ENEMY2_DEATH)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.111f + 0.111f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.111f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.111f + 0.111f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.111f, 1.0f);
		if (m_nCounterAnim >= 3)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 9)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
	}

	if (m_type == TYPE_BULLET_SPAWN)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 1.0f);
		if (m_nCounterAnim >= 2)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 4)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
	}

	if (m_type == TYPE_BULLET_DEATH)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.16f + 0.16f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.16f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.16f + 0.16f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.16f, 1.0f);
		if (m_nCounterAnim >= 2)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 6)
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

	if (m_nPatternAnim >= 8 && m_type == TYPE_ENEMY2_DEATH)
	{
		Uninit();
	}

	/*else if ((m_nEffectFade % FADE_COUNT) == 1 && m_type == TYPE_BULLET_EFFECT)
	{
		Uninit();
	}*/

	else if (m_nPatternAnim >= 5 && m_type == TYPE_BULLET_DEATH)
	{
		Uninit();
	}
	else if (m_nPatternAnim >= 3 && m_type == TYPE_BULLET_SPAWN)
	{
		Uninit();
	}
	else if (m_type == TYPE_ENEMY2_DEATH)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((ENEMY_EFFECT_SIZE) / 2), m_pos.y - ((ENEMY_EFFECT_SIZE) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((ENEMY_EFFECT_SIZE) / 2), m_pos.y - ((ENEMY_EFFECT_SIZE) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((ENEMY_EFFECT_SIZE) / 2), m_pos.y + ((ENEMY_EFFECT_SIZE) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((ENEMY_EFFECT_SIZE) / 2), m_pos.y + ((ENEMY_EFFECT_SIZE) / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;


		m_pVtxBuff->Unlock();
	}
	else if (m_type == TYPE_2FBOSS)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((BOSS_EFFECT_SIZE + m_size_x) / 2), m_pos.y - ((BOSS_EFFECT_SIZE + m_size_y) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((BOSS_EFFECT_SIZE + m_size_x) / 2), m_pos.y - ((BOSS_EFFECT_SIZE + m_size_y) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((BOSS_EFFECT_SIZE + m_size_x) / 2), m_pos.y + ((BOSS_EFFECT_SIZE + m_size_y) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((BOSS_EFFECT_SIZE + m_size_x) / 2), m_pos.y + ((BOSS_EFFECT_SIZE + m_size_y) / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_BULLET_EFFECT)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((BULLET_EFFECT_SIZE_X + m_size_x) / 2), m_pos.y - ((BULLET_EFFECT_SIZE_Y + m_size_y) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((BULLET_EFFECT_SIZE_X + m_size_x) / 2), m_pos.y - ((BULLET_EFFECT_SIZE_Y + m_size_y) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((BULLET_EFFECT_SIZE_X + m_size_x) / 2), m_pos.y + ((BULLET_EFFECT_SIZE_Y + m_size_y) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((BULLET_EFFECT_SIZE_X + m_size_x) / 2), m_pos.y + ((BULLET_EFFECT_SIZE_Y + m_size_y) / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_BULLET_SPAWN)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((BULLET_SPAWN_SIZE + m_size_x) / 2), m_pos.y - ((BULLET_SPAWN_SIZE + m_size_y) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((BULLET_SPAWN_SIZE + m_size_x) / 2), m_pos.y - ((BULLET_SPAWN_SIZE + m_size_y) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((BULLET_SPAWN_SIZE + m_size_x) / 2), m_pos.y + ((BULLET_SPAWN_SIZE + m_size_y) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((BULLET_SPAWN_SIZE + m_size_x) / 2), m_pos.y + ((BULLET_SPAWN_SIZE + m_size_y) / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_BULLET_DEATH)
	{
		if (m_nPatternAnim >= 6)
		{
			Uninit();
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - ((BULLET_DEATH_SIZE + m_size_x) / 2), m_pos.y - ((BULLET_DEATH_SIZE + m_size_y) / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((BULLET_DEATH_SIZE + m_size_x) / 2), m_pos.y - ((BULLET_DEATH_SIZE + m_size_y) / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - ((BULLET_DEATH_SIZE + m_size_x) / 2), m_pos.y + ((BULLET_DEATH_SIZE + m_size_y) / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((BULLET_DEATH_SIZE + m_size_x) / 2), m_pos.y + ((BULLET_DEATH_SIZE + m_size_y) / 2), 0.0f);

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
void CEffect::Draw(void)
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


