//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "game.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[BULLETTYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_type = BULLETTYPE_PLAYER;
	m_r = 0.0f;
	m_fAngle = 0.0f;
	m_fAngle2 = 0.0f;
	m_pSound = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	if (pRenderer == NULL)
	{
		pRenderer = CManager::GetRenderer();
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/bullet000.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_PLAYER]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/bullet001.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_PLAYER_2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/bullet002.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_PLAYER_3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/enemy_bullet002.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_ENEMY]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/enemy_bullet000.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_1FBOSS]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/enemy_bullet003.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_2FBOSS]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Bullet/flame000.png",//�t�@�C���̖��O
		&m_pTexture[BULLETTYPE_2FBOSS2]);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCount = 0; nCount < BULLETTYPE_MAX; nCount++)
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
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, int nLife, BULLETTYPE type)
{
	CBullet* pBullet = NULL;
	if (pBullet == NULL)
	{
		pBullet = new CBullet;
		if (pBullet != NULL)
		{
			pBullet->Init(pos, move, size_x, size_y, nLife, type);
		}
	}

	return pBullet;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, int nLife, BULLETTYPE type)
{
	CScene2d::Init(pos, size_x, size_y);

	BindTexture(m_pTexture[type]);
	m_pos = pos;
	m_type = type;
	m_move = move;
	m_nLife = nLife;

	//��]����
	m_r = sqrtf(100 / 2 * 100 / 2 + 100 / 2 * 100 / 2);
	m_fAngle = atan2f((100 / 2) + (100 / 2), (100 / 2) + (100 / 2));
	m_fAngle2 = atan2f((100 / 2) + (100 / 2), (100 / 2) + (100 / 2));
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CBullet::Update(void)
{
	VERTEX_2D* pVtx;

	m_fAngle -= ANGLE;
	m_fAngle2 += ANGLE2;

	m_r = RADIUS;

	//�ʒu���擾
	m_pos = GetPosition();

	m_nCounterAnim++;

	for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			CScene* pScene = GetScene(nPriority, nCount);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if (m_type == BULLETTYPE_1FBOSS ||
					m_type == BULLETTYPE_2FBOSS3)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;
					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							CGame::SetPlayerLife(1);
						}
					}
				}

				if (m_type == BULLETTYPE_ENEMY)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;

					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 1.0f);
					if (m_nCounterAnim >= 3)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 4)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}

					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							CGame::SetPlayerLife(1);
						}
					}
				}

				if (m_type == BULLETTYPE_2FBOSS2)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;

					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f + 0.2f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f + 0.2f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f, 1.0f);
					if (m_nCounterAnim >= 3)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 5)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}

					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							CGame::SetPlayerLife(1);
						}
					}
				}

				if (m_type == BULLETTYPE_2FBOSS)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;

					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f + 0.333f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f + 0.333f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.333f, 1.0f);
					if (m_nCounterAnim >= 3)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 9)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}

					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							CGame::SetPlayerLife(1);
						}
					}
				}

				//�v���C���[��������
				if (m_type == BULLETTYPE_PLAYER)
				{
					//�L���X�g
					CEnemy* pEnemy = (CEnemy*)pScene;
					//�G��������
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 1.0f);
					if (m_nCounterAnim >= 3)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 9)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}

					/*	CBulletEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),
							BULLET_EFFECT_SIZE_X, BULLET_EFFECT_SIZE_Y);*/

					if (objType == CScene::OBJTYPE_ENEMY)
					{
						//�����蔻��
						if (HitCcollision(pEnemy->GetPosition(), ENEMY_SIZE, ENEMY_SIZE))
						{
							//�G��1�_���[�W
							pEnemy->SetLife(1);
							CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								0.0f, 0.0f,
								CEffect::TYPE_BULLET_DEATH);
							//�e�̃��C�t��0�ɂ���
							m_nLife = 0;
							m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_BULLET_HIT);
						}
					}
				}
				if (m_type == BULLETTYPE_PLAYER_2)
				{
					//�L���X�g
					CEnemy* pEnemy = (CEnemy*)pScene;
					//�G��������

					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 1.0f);
					if (m_nCounterAnim >= 3)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 3)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}

					if (objType == CScene::OBJTYPE_ENEMY)
					{
						//�����蔻��
						if (HitCcollision(pEnemy->GetPosition(), ENEMY_SIZE, ENEMY_SIZE))
						{
							//�G��1�_���[�W
							pEnemy->SetLife(1);
							CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								0.0f, 0.0f,
								CEffect::TYPE_BULLET_DEATH);
							//�e�̃��C�t��0�ɂ���
							m_nLife = 0;
							m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_BULLET_HIT);
						}
					}
				}

				if (m_type == BULLETTYPE_PLAYER_3)
				{
					//�L���X�g
					CEnemy* pEnemy = (CEnemy*)pScene;
					//�G��������

					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.083f + 0.083f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.083f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.083f + 0.083f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.083f, 1.0f);
					if (m_nCounterAnim >= 3)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 11)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}

					if (objType == CScene::OBJTYPE_ENEMY)
					{
						//�����蔻��
						if (HitCcollision(pEnemy->GetPosition(), ENEMY_SIZE, ENEMY_SIZE))
						{
							//�G��1�_���[�W
							pEnemy->SetLife(1);
							CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								0.0f, 0.0f,
								CEffect::TYPE_BULLET_DEATH);
							//�e�̃��C�t��0�ɂ���
							m_nLife = 0;
						}
					}
				}
			}
		}
	}

	//�{�X��������
	if (m_type == BULLETTYPE_1FBOSS)
	{
		D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		SetCol(col);

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 1.0f);
		if (m_nCounterAnim >= 3)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 4)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
	}

	//���C�t�����炷
	m_nLife--;
	//�ʒu�X�V
	m_pos += m_move;
	//�ʒu���Z�b�g
	SetPosition(m_pos);

	if (m_nLife <= 0 && m_type == BULLETTYPE_2FBOSS)
	{
		for (int nCount = 0; nCount < 16; nCount++)
		{
			//�~�`�ɔ�΂�
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				D3DXVECTOR3(3.0f * cosf((float)nCount) * 2.0f, 3.0f * sinf((float)nCount) * 2.0f, 0.0f),
				BULLET_SIZE, BULLET_SIZE,
				100,
				CBullet::BULLETTYPE_2FBOSS2);
		}
	}

	if (m_nLife <= 0 || m_pos.y <= 0.0f || m_pos.y >= 720.0f || m_pos.x <= 0.0f || m_pos.y >= 1280.0f && m_type != BULLETTYPE_2FBOSS)
	{
		Uninit();
	}
	else if (m_type == BULLETTYPE_PLAYER)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (PLAYER_BULLET_SIZE), m_pos.y - (PLAYER_BULLET_SIZE), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (PLAYER_BULLET_SIZE), m_pos.y - (PLAYER_BULLET_SIZE), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (PLAYER_BULLET_SIZE), m_pos.y + (PLAYER_BULLET_SIZE), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (PLAYER_BULLET_SIZE), m_pos.y + (PLAYER_BULLET_SIZE), 0.0f);

		m_pVtxBuff->Unlock();
	}
	else if (m_type == BULLETTYPE_PLAYER_2)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (PLAYER_BULLET_2_SIZE), m_pos.y - (PLAYER_BULLET_2_SIZE), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (PLAYER_BULLET_2_SIZE), m_pos.y - (PLAYER_BULLET_2_SIZE), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (PLAYER_BULLET_2_SIZE), m_pos.y + (PLAYER_BULLET_2_SIZE), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (PLAYER_BULLET_2_SIZE), m_pos.y + (PLAYER_BULLET_2_SIZE), 0.0f);

		m_pVtxBuff->Unlock();
	}
	else if (m_type == BULLETTYPE_PLAYER_3)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (PLAYER_BULLET_3_SIZE), m_pos.y - (PLAYER_BULLET_3_SIZE), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (PLAYER_BULLET_3_SIZE), m_pos.y - (PLAYER_BULLET_3_SIZE), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (PLAYER_BULLET_3_SIZE), m_pos.y + (PLAYER_BULLET_3_SIZE), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (PLAYER_BULLET_3_SIZE), m_pos.y + (PLAYER_BULLET_3_SIZE), 0.0f);

		m_pVtxBuff->Unlock();
	}
	else if (m_type == BULLETTYPE_1FBOSS)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_r * cosf(m_fAngle)), m_pos.y - (m_r * sinf(m_fAngle)), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_r * cosf(m_fAngle2)), m_pos.y - (m_r * sinf(m_fAngle2)), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_r * cosf(m_fAngle2)), m_pos.y + (m_r * sinf(m_fAngle2)), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_r * cosf(m_fAngle)), m_pos.y + (m_r * sinf(m_fAngle)), 0.0f);

		m_pVtxBuff->Unlock();
	}
	else if (m_type == BULLETTYPE_2FBOSS)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (BOSS2_BULLET_SIZE / 2), m_pos.y - (BOSS2_BULLET_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BOSS2_BULLET_SIZE / 2), m_pos.y - (BOSS2_BULLET_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (BOSS2_BULLET_SIZE / 2), m_pos.y + (BOSS2_BULLET_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BOSS2_BULLET_SIZE / 2), m_pos.y + (BOSS2_BULLET_SIZE / 2), 0.0f);

		m_pVtxBuff->Unlock();
	}
	else if (m_type == BULLETTYPE_ENEMY)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_BULLET_SIZE), m_pos.y - (ENEMY_BULLET_SIZE), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_BULLET_SIZE), m_pos.y - (ENEMY_BULLET_SIZE), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_BULLET_SIZE), m_pos.y + (ENEMY_BULLET_SIZE), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_BULLET_SIZE), m_pos.y + (ENEMY_BULLET_SIZE), 0.0f);

		m_pVtxBuff->Unlock();
	}
	else
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (BULLET_SIZE / 2), m_pos.y - (BULLET_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BULLET_SIZE / 2), m_pos.y - (BULLET_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (BULLET_SIZE / 2), m_pos.y + (BULLET_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BULLET_SIZE / 2), m_pos.y + (BULLET_SIZE / 2), 0.0f);

		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//�����蔻�菈��
//=============================================================================
bool CBullet::HitCcollision(D3DXVECTOR3 Pos, float size_x, float size_y)
{
	bool bHit = false;
	m_pos = GetPosition();
	if (m_pos.x <= Pos.x + (size_x / 2) &&
		m_pos.x >= Pos.x - (size_x / 2) &&
		m_pos.y <= Pos.y + (size_y / 2) &&
		m_pos.y >= Pos.y - (size_y / 2))//�����蔻��
	{
		bHit = true;
	}
	return bHit;
}


