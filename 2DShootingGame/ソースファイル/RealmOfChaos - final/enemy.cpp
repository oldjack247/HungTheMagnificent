//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "item.h"
#include "fade.h"
#include "effect.h"
#include "game_clear.h"
#include "sound.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[TYPE_ENEMY_MAX] = {};
int CEnemy::nCnt2FBossAvatar = 0;
D3DXVECTOR3 CEnemy::m_2FBossPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CEnemy::m_b2FBossAwakening = false;
CGameClear* CEnemy::m_pGameClear = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCntEnemy = 0;
	m_nCnt2FBoss = 0;
	nCnt2FBossChange = 0;
	m_type = TYPE_ENEMY_HARPY;
	m_movetype = ACTION_MOVE_NONE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_b1FBossInvisible = false;
	m_b2FBossBullet = false;
	m_b2FBossAttack = false;
	m_fAngle = 0.0f;
	m_pSound = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/enemy003.png",
		&m_pTexture[TYPE_ENEMY_HARPY]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/enemy002.png",
		&m_pTexture[TYPE_ENEMY_GHOST]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/Mephisto.png",
		&m_pTexture[TYPE_ENEMY_1FBOSS]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/enemy004.png",
		&m_pTexture[TYPE_ENEMY_2FGHOST]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/enemy005.png",
		&m_pTexture[TYPE_ENEMY_2FBAT]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/enemy006.png",
		&m_pTexture[TYPE_ENEMY_2FGHOST_AVATAR]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/boss000.png",
		&m_pTexture[TYPE_ENEMY_2FBOSS]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/avatar001.png",
		&m_pTexture[TYPE_ENEMY_2FBOSS_AVATAR]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/bossFog001.png",
		&m_pTexture[TYPE_ENEMY_BOSS_FOG]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/3FBoss.png",
		&m_pTexture[TYPE_ENEMY_3FBOSS]);

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pRenderer->GetDevice(),
	//	"data/TEXTURE/Enemy/avatar001.png",
	//	&m_pTexture[TYPE_ENEMY_3FGHOST]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/Enemy/3FDemon.png",
		&m_pTexture[TYPE_ENEMY_3FDEMON]);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_ENEMY_MAX; nCount++)
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
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, int nLife, TYPEENEMY nType, ENEMY_ACTION_PATTERN MoveType)
{
	CEnemy* pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		if (pEnemy != NULL)
		{
			pEnemy->Init(pos, move, col, size_x, size_y, nLife, nType, MoveType);
		}
	}
	return pEnemy;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, int nLife, TYPEENEMY nType, ENEMY_ACTION_PATTERN MoveType)
{
	VERTEX_2D* pVtx;
	CScene2d::Init(pos, size_x, size_y);

	BindTexture(m_pTexture[nType]);

	m_nLife = nLife;

	m_type = nType;

	m_move = move;

	m_col = col;

	m_movetype = MoveType;

	SetObjType(OBJTYPE_ENEMY);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	if (m_type == TYPE_ENEMY_BOSS_FOG || m_movetype == ACTION_ENEMY2_DROP_ITEM)
	{
		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.33f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[3].tex = D3DXVECTOR2(0.33f, 0.25f);
	}
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CEnemy::Update(void)
{
	VERTEX_2D* pVtx;

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = CPlayer::GetPos();
	bool b1FBossSpawn = false;
	int nEnemyBulletCount = 0;
	nEnemyBulletCount++;
	m_nCntEnemy++;
	m_nCounterAnim++;
	m_nCnt2FBoss++;
	m_pos = GetPosition();

	switch (m_type)
	{
	case TYPE_ENEMY_HARPY:
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1111f + 0.1111f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1111f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1111f + 0.1111f, 0.25f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1111f, 0.25f);
		if (m_nCounterAnim >= 6)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 15)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		//�v���C���[�Ƃ̋������v�Z���ăv���C���[�ɓˌ�����悤�ɂ���
		m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
		m_move = D3DXVECTOR3(D3DXVECTOR3(sinf(m_fAngle) * -2.0f, cosf(m_fAngle) * -2.0f, 0.0f));
		break;

	case TYPE_ENEMY_BOSS_FOG:
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 1.0f);
		if (m_nCounterAnim >= 6)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 10)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();

	case TYPE_ENEMY_GHOST: //���΂�
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		if (m_movetype == ACTION_MOVE_RIGHT)
		{//�E�����̂Ƃ�
			pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.75f);
			pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.75f);
			if (m_nCounterAnim >= 8)
			{//��莞�Ԍo�߂���
				m_nCounterAnim = 0;
				m_nPatternAnim++;
				if (m_nPatternAnim >= 12)
				{//�p�^�[�����𒴂���
					m_nPatternAnim = 0;
				}
			}

			if ((rand() % (nEnemyBulletCount * 100)) == 0)
			{
				m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
					D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
					BULLET_SIZE, BULLET_SIZE,
					100,
					CBullet::BULLETTYPE_ENEMY);
			}
		}

		else if (m_movetype == ACTION_MOVE_NONE)
		{
			//�ǔ��e
			m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI * 2.0f;
			}
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle += D3DX_PI * 2.0f;
			}
			pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.25f);
			pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.25f);
			if (m_nCounterAnim >= 8)
			{//��莞�Ԍo�߂���
				m_nCounterAnim = 0;
				m_nPatternAnim++;
				if (m_nPatternAnim >= 12)
				{//�p�^�[�����𒴂���
					m_nPatternAnim = 0;
				}
			}
			if ((rand() % (nEnemyBulletCount * 100)) == 0)
			{
				m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
					D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
					BULLET_SIZE, BULLET_SIZE,
					100,
					CBullet::BULLETTYPE_ENEMY);
			}

		}
		else if (m_movetype == ACTION_ENEMY2_DROP_ITEM)
		{
			pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 1.0f);
			if (m_nCounterAnim >= 8)
			{//��莞�Ԍo�߂���
				m_nCounterAnim = 0;
				m_nPatternAnim++;
				if (m_nPatternAnim >= 12)
				{//�p�^�[�����𒴂���
					m_nPatternAnim = 0;
				}
			}
			//���X�ɓ�������߂�
			if (m_col.a <= 1.0f)
			{
				m_col.a += 0.01f;
			}
		}
		else if (m_movetype == ACTION_MOVE_BACK)
		{
			m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
			if (m_nCntEnemy == 50)
			{
				m_move.y = 0.0f;
			}
			else if (m_nCntEnemy == 120)
			{
				m_move.y = -2.0f;
			}
			if ((rand() % (nEnemyBulletCount * 100)) == 0)
			{
				m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
					D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
					BULLET_SIZE, BULLET_SIZE,
					100,
					CBullet::BULLETTYPE_ENEMY);
			}
			pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.25f);
			pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.25f);
			if (m_nCounterAnim >= 8)
			{//��莞�Ԍo�߂���
				m_nCounterAnim = 0;
				m_nPatternAnim++;
				if (m_nPatternAnim >= 8)
				{
					m_nPatternAnim = 0;
				}
			}
		}
		m_pVtxBuff->Unlock();
		break;
	case TYPE_ENEMY_1FBOSS:
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.077f + 0.077f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.077f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.077f + 0.077f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.077f, 1.0f);
		if (m_nCounterAnim >= 5)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 13)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		//�������珙�X�ɖ߂�
		if (m_col.a <= 1.0f)
		{
			m_col.a += 0.1f;
		}

		if (m_movetype == ACTION_MOVE_NONE)
		{//�ʏ���
			//�̗͂�50�ȏ�̎�
			if (m_nLife >= 50)
			{
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y - (PLAYER_SIZE / 2)), 0.0f), D3DXVECTOR3(0.0f, 8.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, 100, CBullet::BULLETTYPE_1FBOSS);
					CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y - (PLAYER_SIZE / 2)), 0.0f), D3DXVECTOR3(3.0f, 3.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, 100, CBullet::BULLETTYPE_1FBOSS);
					CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y - (PLAYER_SIZE / 2)), 0.0f), D3DXVECTOR3(-5.0f, 2.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, 100, CBullet::BULLETTYPE_1FBOSS);
					//���ˉ�
					m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
				}
			}
			//�̗͂�60�ɂȂ��ē�������Ȃ�������
			if (m_nLife >= 60 && m_nLife <= 63 &&
				m_b1FBossInvisible == false)
			{
				m_b1FBossInvisible = true;
				if (m_b1FBossInvisible == true)
				{
					m_col.a = 0.0f;
					m_pos = D3DXVECTOR3(1100.0f, 250.0f, 0.0f);
				}
			}
			else if (m_nLife < 50 && m_nLife >= 10)
			{//�̗͂�50��菬������10�ȏゾ������
				//�ʒu���ړ�
				m_pos = D3DXVECTOR3(640.0f, 250.0f, 0.0f);
				//�e�𔭎�
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					for (int nCount = 0; nCount < 3; nCount++)
					{
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						//���ˉ�
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
					}
				}
			}
			else if (m_nLife < 10)
			{
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					for (int nCount = 0; nCount < 15; nCount++)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
							D3DXVECTOR3(3.0f * cosf((float)nCount) * 2.0f, 3.0f * sinf((float)nCount) * 2.0f, 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						//���ˉ�
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
					}
				}
			}
		}
		break;
	case TYPE_ENEMY_2FGHOST: //2�t���A�ڂ̓G�L����
		//120�t���[���܂ł�Y���ɉ��Z
		if (m_nCntEnemy <= 120)
		{
			m_move.y = 6.5f;
		}
		if (m_movetype == ACTION_CIRCLE_RIGHT)
		{
			//120�t���[���𒴂������]������
			if (m_nCntEnemy > 120)
			{
				m_move.x = (float)(sin(D3DX_PI * (m_nCntEnemy - 100.0f) / 120.0f)) * 3.5f;
				m_move.y = (float)(sin(D3DX_PI * (m_nCntEnemy - 60.0f) / 120.0f)) * 3.5f;
			}

			//800�t���[���ȏ�ɂȂ������ʊO�ɏo��
			if (m_nCntEnemy >= 800)
			{
				m_move.x = -5.0f;
			}
		}
		else if (m_movetype == ACTION_CIRCLE_LEFT)
		{
			//120�t���[���𒴂������]������
			if (m_nCntEnemy > 120)
			{
				m_move.x = (float)(sin(D3DX_PI * (m_nCntEnemy - 100.0f) / 120.0f)) * (-3.5f);
				m_move.y = (float)(sin(D3DX_PI * (m_nCntEnemy - 60.0f) / 120.0f)) * (-3.5f);
			}

			//800�t���[���ȏ�ɂȂ������ʊO�ɏo��
			if (m_nCntEnemy >= 800)
			{
				m_move.x = 5.0f;
			}
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f + 0.2f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f + 0.2f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.2f, 1.0f);
		if (m_nCounterAnim >= 8)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 8)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		break;
	case TYPE_ENEMY_2FBAT://�΂߂ɔ��ł�����
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 1.0f);
		if (m_nCounterAnim >= 8)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 8)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		break;
	case TYPE_ENEMY_2FGHOST_AVATAR:
		m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
		for (int nCount = 0; nCount < 20; nCount++)
		{
			if (m_nCntEnemy == 30 * nCount)
			{
				m_move.x = 2.0f * sinf(m_fAngle);
			}
			else
			{
				m_move.x = -2.0f * sinf(m_fAngle);
			}
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 1.0f);
		if (m_nCounterAnim >= 5)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 5)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		break;
	case TYPE_ENEMY_2FBOSS:
		m_2FBossPos = m_pos;
		//�{�X�̖{��
		if (m_movetype == ACTION_2FBOSS_AWAKENING)
		{
			if (m_nLife <= 110 && m_b2FBossAttack == true)
			{//�̗͂�110�ȏ��m_b2FBossAttack��true�̂Ƃ�
				//�e�𔭎�
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (ENEMY_1FBOSS_SIZE / 2), 0.0f),
					D3DXVECTOR3(0.0f, 8.0f, 0.0f),
					BOSS2_BULLET_SIZE, BOSS2_BULLET_SIZE,
					50,
					CBullet::BULLETTYPE_2FBOSS);
				//���ˉ�
				m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_2FBOSS_BULLET_FIRE);
				m_b2FBossAttack = false;
			}

			else if (m_nLife % 2 == 0)
			{
				if ((rand() % (nEnemyBulletCount * 40)) == 0)
				{
					for (int nCount = 0; nCount < 15; nCount++)
					{

						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
							D3DXVECTOR3(3.0f * cosf((float)nCount) * 2.0f, 3.0f * sinf((float)nCount) * 2.0f, 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_2FBOSS2);
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_2FBOSS_FIRE_LOOP);
					}
				}
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					for (int nCount = 0; nCount < 5; nCount++)
					{
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
					}
				}
			}

			else if (m_nCnt2FBoss == 2000 ||
				m_nCnt2FBoss == 3000)
			{//�J�E���g��2000��3000�̂Ƃ�
				//�e�𔭎�
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (ENEMY_1FBOSS_SIZE / 2), 0.0f),
					D3DXVECTOR3(0.0f, 8.0f, 0.0f),
					BOSS2_BULLET_SIZE, BOSS2_BULLET_SIZE,
					50,
					CBullet::BULLETTYPE_2FBOSS);
				//���ˉ�
				m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_2FBOSS_BULLET_FIRE);
			}
			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
			pVtx[0].tex = D3DXVECTOR2(0.66f, -(m_nPatternAnim * 0.25f + 0.25f));
			pVtx[1].tex = D3DXVECTOR2(0.99f, -(m_nPatternAnim * 0.25f + 0.25f));
			pVtx[2].tex = D3DXVECTOR2(0.66f, -m_nPatternAnim * 0.25f);
			pVtx[3].tex = D3DXVECTOR2(0.99f, -m_nPatternAnim * 0.25f);
			if (m_nCounterAnim >= 8)
			{//��莞�Ԍo�߂���
				m_nCounterAnim = 0;
				m_nPatternAnim++;
				if (m_nPatternAnim >= 8)
				{//�p�^�[�����𒴂���
					m_nPatternAnim = 0;
				}
			}
			m_pVtxBuff->Unlock();
		}

		if (m_movetype == ACTION_MOVE_NONE)
		{
			if (m_b2FBossBullet == true && m_nLife > ENEMY_2FBOSS_AWAKENING_LIFE)
			{
				if ((rand() % (nEnemyBulletCount * 40)) == 0 && m_movetype == ACTION_MOVE_NONE)
				{
					m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
					CEnemy::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f),
						D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						ENEMY_1FBOSS_SIZE, ENEMY_1FBOSS_SIZE, 1,
						CEnemy::TYPE_ENEMY_2FBOSS_AVATAR, CEnemy::ACTION_MOVE_NONE);
				}
			}
			if (m_nLife <= ENEMY_2FBOSS_AWAKENING_LIFE && m_b2FBossAwakening == false)
			{
				if ((rand() % (nEnemyBulletCount * 50)) == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y - (PLAYER_SIZE / 2)), 0.0f),
						D3DXVECTOR3(0.0f, 8.0f, 0.0f),
						BULLET_SIZE, BULLET_SIZE,
						100,
						CBullet::BULLETTYPE_2FBOSS2);
					CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y - (PLAYER_SIZE / 2)), 0.0f),
						D3DXVECTOR3(3.0f, 3.0f, 0.0f),
						BULLET_SIZE, BULLET_SIZE,
						100,
						CBullet::BULLETTYPE_2FBOSS2);
					CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y - (PLAYER_SIZE / 2)), 0.0f),
						D3DXVECTOR3(-5.0f, 2.0f, 0.0f),
						BULLET_SIZE, BULLET_SIZE,
						100,
						CBullet::BULLETTYPE_2FBOSS2);
				}
			}

			//�J�E���g��1000�𒴂���m_b2FBossBullet��true�̂Ƃ�
			if (m_nCntEnemy >= 1000 && m_b2FBossBullet == true)
			{
				//���g���o���Ȃ��悤�ɂ���
				m_b2FBossBullet = false;
				m_nCntEnemy = 0;
			}

			//���g��20�̈ȏ��荞�񂾂�
			if (m_b2FBossAwakening == true && nCnt2FBossAvatar >= COUNT_BOSS_AVATAR && m_nLife >= ENEMY_2FBOSS_AWAKENING_LIFE)
			{
				//�J�E���g��100�ȏ�ɂȂ�܂ł̎�
				if (nCnt2FBossChange <= 100)
				{
					//�J�E���g�v���X
					nCnt2FBossChange++;
					//�G�t�F�N�g���Z�b�g
					CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f, 0.0f,
						CEffect::TYPE_2FBOSS);
				}
				else
				{
					//�U���ł���悤�ɂ���
					m_b2FBossAttack = true;
					//�o��
					m_movetype = ACTION_2FBOSS_AWAKENING;
					//�̗͂�ύX
					m_nLife = ENEMY_2FBOSS_AWAKENING_LIFE;
				}

				if (nCnt2FBossChange % 4 == 0)
				{
					//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[1].tex = D3DXVECTOR2(0.33f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[2].tex = D3DXVECTOR2(0.0f, -m_nPatternAnim * 0.25f);
					pVtx[3].tex = D3DXVECTOR2(0.33f, -m_nPatternAnim * 0.25f);
					m_pVtxBuff->Unlock();
				}
				else
				{
					//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(0.66f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[1].tex = D3DXVECTOR2(0.99f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[2].tex = D3DXVECTOR2(0.66f, -m_nPatternAnim * 0.25f);
					pVtx[3].tex = D3DXVECTOR2(0.99f, -m_nPatternAnim * 0.25f);
					m_pVtxBuff->Unlock();
				}
			}
			else if (m_b2FBossAwakening == true && nCnt2FBossAvatar <= COUNT_BOSS_AVATAR && m_nLife >= ENEMY_2FBOSS_AWAKENING_LIFE)
			{//���g��20�̈ȏ��荞�߂Ȃ�������
				if (nCnt2FBossChange <= 100)
				{
					//�J�E���g�A�b�v
					nCnt2FBossChange++;
					//�G�t�F�N�g���Z�b�g
					CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f, 0.0f,
						CEffect::TYPE_2FBOSS);
				}
				else
				{
					//�̗͂�ύX
					m_nLife = ENEMY_2FBOSS_AWAKENING_LIFE;
					m_b2FBossAwakening = false;
				}

				if (nCnt2FBossChange % 4 == 0)
				{
					//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(0.66f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[1].tex = D3DXVECTOR2(0.99f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[2].tex = D3DXVECTOR2(0.66f, -m_nPatternAnim * 0.25f);
					pVtx[3].tex = D3DXVECTOR2(0.99f, -m_nPatternAnim * 0.25f);
					m_pVtxBuff->Unlock();
				}
				else
				{
					//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
					pVtx[0].tex = D3DXVECTOR2(0.0f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[1].tex = D3DXVECTOR2(0.33f, -(m_nPatternAnim * 0.25f + 0.25f));
					pVtx[2].tex = D3DXVECTOR2(0.0f, -m_nPatternAnim * 0.25f);
					pVtx[3].tex = D3DXVECTOR2(0.33f, -m_nPatternAnim * 0.25f);
					if (m_nCounterAnim >= 12)
					{//��莞�Ԍo�߂���
						m_nCounterAnim = 0;
						m_nPatternAnim++;
						if (m_nPatternAnim >= 12)
						{//�p�^�[�����𒴂���
							m_nPatternAnim = 0;
						}
					}
					m_pVtxBuff->Unlock();
				}
			}
			else
			{
				//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, -(m_nPatternAnim * 0.25f + 0.25f));
				pVtx[1].tex = D3DXVECTOR2(0.33f, -(m_nPatternAnim * 0.25f + 0.25f));
				pVtx[2].tex = D3DXVECTOR2(0.0f, -m_nPatternAnim * 0.25f);
				pVtx[3].tex = D3DXVECTOR2(0.33f, -m_nPatternAnim * 0.25f);
				if (m_nCounterAnim >= 8)
				{//��莞�Ԍo�߂���
					m_nCounterAnim = 0;
					m_nPatternAnim++;
					if (m_nPatternAnim >= 8)
					{//�p�^�[�����𒴂���
						m_nPatternAnim = 0;
					}
				}
				m_pVtxBuff->Unlock();
			}
		}
		break;
	case TYPE_ENEMY_2FBOSS_AVATAR:
		if (m_nLife <= 0)
		{
			//2F�{�X�Ƃ̊p�x���v�Z
			m_fAngle = atan2f(m_pos.x - CEnemy::m_2FBossPos.x, m_pos.y - CEnemy::m_2FBossPos.y);
			m_move = D3DXVECTOR3(sinf(m_fAngle) * (-5.0f), cosf(m_fAngle) * (-5.0f), 0.0f);
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f + 0.165f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f + 0.165f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f, 1.0f);
		if (m_nCounterAnim >= 8)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 8)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		break;

		//3F
	case TYPE_ENEMY_3FBOSS:
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.0625f + 0.0625f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.0625f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.0625f + 0.0625f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.0625f, 1.0f);
		if (m_nCounterAnim >= 6)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 16)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		//�������珙�X�ɖ߂�
		if (m_col.a <= 1.0f)
		{
			m_col.a += 0.1f;
		}

		if (m_movetype == ACTION_MOVE_NONE)
		{//�ʏ���
			//�̗͂�50�ȏ�̎�
			if (m_nLife >= 250)
			{
				for (int nCount = 0; nCount < 3; nCount++)
				{
					m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
						D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
						BULLET_SIZE, BULLET_SIZE,
						100,
						CBullet::BULLETTYPE_1FBOSS);
					m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
						D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
						BULLET_SIZE, BULLET_SIZE,
						100,
						CBullet::BULLETTYPE_1FBOSS);
					m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f),
						D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
						BULLET_SIZE, BULLET_SIZE,
						100,
						CBullet::BULLETTYPE_1FBOSS);
					//���ˉ�
					m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
				}
			}

			else if (m_nLife < 250 && m_nLife >= 100)
			{//�̗͂�50��菬������10�ȏゾ������
				//�ʒu���ړ�
				m_pos = D3DXVECTOR3(640.0f, 250.0f, 0.0f);
				//�e�𔭎�
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					for (int nCount = 0; nCount < 3; nCount++)
					{
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(0.0f, -350.0f, 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(1250.0f, -350.0f, 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						//���ˉ�
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
					}
				}
			}
			else if (m_nLife < 100)
			{
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					for (int nCount = 0; nCount < 15; nCount++)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
							D3DXVECTOR3(3.0f * cosf((float)nCount) * 2.0f, 3.0f * sinf((float)nCount) * 2.0f, 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						//���ˉ�
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
					}
				}
				if ((rand() % (nEnemyBulletCount * 30)) == 0)
				{
					for (int nCount = 0; nCount < 3; nCount++)
					{
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(0.0f, -350.0f, 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
						CBullet::Create(D3DXVECTOR3(1250.0f, -350.0f, 0.0f),
							D3DXVECTOR3(sinf(m_fAngle) * (-8.0f), cosf(m_fAngle) * (-8.0f), 0.0f),
							BULLET_SIZE, BULLET_SIZE,
							100,
							CBullet::BULLETTYPE_1FBOSS);
						//���ˉ�
						m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_1FBOSS_BULLET);
					}
				}
			}
		}
		break;

		//case TYPE_ENEMY_3FGHOST:
		//	if (m_nLife <= 0)
		//	{
		//		//2F�{�X�Ƃ̊p�x���v�Z
		//		m_fAngle = atan2f(m_pos.x - CEnemy::m_2FBossPos.x, m_pos.y - CEnemy::m_2FBossPos.y);
		//		m_move = D3DXVECTOR3(sinf(m_fAngle) * (-5.0f), cosf(m_fAngle) * (-5.0f), 0.0f);
		//	}
		//	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f + 0.165f, 0.0f);
		//	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f, 0.0f);
		//	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f + 0.165f, 1.0f);
		//	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.165f, 1.0f);
		//	if (m_nCounterAnim >= 8)
		//	{//��莞�Ԍo�߂���
		//		m_nCounterAnim = 0;
		//		m_nPatternAnim++;
		//		if (m_nPatternAnim >= 8)
		//		{//�p�^�[�����𒴂���
		//			m_nPatternAnim = 0;
		//		}
		//	}
		//	m_pVtxBuff->Unlock();
		//	break;

	case TYPE_ENEMY_3FDEMON:
		if (m_nLife <= 0)
		{
			//2F�{�X�Ƃ̊p�x���v�Z
			m_fAngle = atan2f(m_pos.x - CEnemy::m_2FBossPos.x, m_pos.y - CEnemy::m_2FBossPos.y);
			m_move = D3DXVECTOR3(sinf(m_fAngle) * (-5.0f), cosf(m_fAngle) * (-5.0f), 0.0f);
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.071f + 0.071f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.071f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.071f + 0.071f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.071f, 1.0f);
		if (m_nCounterAnim >= 8)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 14)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();
		m_fAngle = atan2f(m_pos.x - PlayerPos.x, m_pos.y - PlayerPos.y);
		m_move = D3DXVECTOR3(D3DXVECTOR3(sinf(m_fAngle) * -5.0f, cosf(m_fAngle) * -5.0f, 0.0f));
		break;
		break;
	default:
		break;
	}

	for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//�L���X�g
			CScene* pScene = GetScene(nPriority, nCount);
			if (pScene != NULL)
			{//NULL����Ȃ�������
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//�L���X�g
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
		}
	}
	//�ʒu�X�V
	m_pos += m_move;

	SetPosition(m_pos);
	SetCol(m_col);

	//��ʊO�ɏo��������悤�ɂ���
	if (m_pos.y >= 730.0f || m_pos.x >= 1280.0f)
	{
		Uninit();
	}
	else if (m_type == TYPE_ENEMY_BOSS_FOG && m_movetype == ACTION_ENEMY2_DROP_ITEM && m_nLife <= 0)
	{//�A�C�e�����h���b�v�����ď���
		for (int nCntEffect = 0; nCntEffect < 30; nCntEffect++)
		{
			//100����200�̊Ԃ������_���Ō��߂�
			int Rand_Y = GetRandNum(100, 200);
			int Rand_X = GetRandNum(100, 200);

			//�����_���ŏo��������100�Ŋ���
			Rand_Y = Rand_Y / 100;
			Rand_X = Rand_X / 100;

			//1��2�������_���Ō��߂�
			int Min_Y = GetRandNum(1, 2);
			int Min_X = GetRandNum(1, 2);

			//2��������-1�ɂ���
			if (Min_Y == 2)
			{
				Min_Y = -1;
			}
			if (Min_X == 2)
			{
				Min_X = -1;
			}
			//�������Z�b�g
			CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				D3DXVECTOR3((float)((Rand_X * Min_X) + (nCntEffect * Min_X)), (float)((Rand_Y * Rand_Y) + (nCntEffect * Min_Y)), 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				EXPLOSION_SIZE, EXPLOSION_SIZE,
				CExplosion::TYPE_ENEMY2_DEATH);
		}
		//�{�X�o��
		b1FBossSpawn = true;
		CGame::Set1FBossSpawn(b1FBossSpawn);
		//�A�C�e���Z�b�g
		CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			ITEM_SIZE, ITEM_SIZE, CItem::TYPE_ITEM_BULLET);
		Uninit();
	}

	else if (m_type == TYPE_ENEMY_GHOST)
	{//�{�X����
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_GHOST_SIZE / 2), m_pos.y - (ENEMY_GHOST_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_GHOST_SIZE / 2), m_pos.y - (ENEMY_GHOST_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_GHOST_SIZE / 2), m_pos.y + (ENEMY_GHOST_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_GHOST_SIZE / 2), m_pos.y + (ENEMY_GHOST_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_ENEMY_BOSS_FOG)
	{//�{�X����
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_GHOST_SIZE / 2), m_pos.y - (ENEMY_GHOST_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_GHOST_SIZE / 2), m_pos.y - (ENEMY_GHOST_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_GHOST_SIZE / 2), m_pos.y + (ENEMY_GHOST_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_GHOST_SIZE / 2), m_pos.y + (ENEMY_GHOST_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_ENEMY_1FBOSS)
	{//�{�X����
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_1FBOSS_SIZE / 2), m_pos.y - (ENEMY_1FBOSS_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_1FBOSS_SIZE / 2), m_pos.y - (ENEMY_1FBOSS_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_1FBOSS_SIZE / 2), m_pos.y + (ENEMY_1FBOSS_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_1FBOSS_SIZE / 2), m_pos.y + (ENEMY_1FBOSS_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}

	else if (m_type == TYPE_ENEMY_1FBOSS)
	{//�{�X����
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_1FBOSS_SIZE / 2), m_pos.y - (ENEMY_1FBOSS_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_1FBOSS_SIZE / 2), m_pos.y - (ENEMY_1FBOSS_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_1FBOSS_SIZE / 2), m_pos.y + (ENEMY_1FBOSS_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_1FBOSS_SIZE / 2), m_pos.y + (ENEMY_1FBOSS_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}
	else if (m_type == TYPE_ENEMY_2FBOSS || m_type == TYPE_ENEMY_2FBAT)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_2FBOSS_SIZE / 2), m_pos.y - (ENEMY_2FBOSS_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_2FBOSS_SIZE / 2), m_pos.y - (ENEMY_2FBOSS_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_2FBOSS_SIZE / 2), m_pos.y + (ENEMY_2FBOSS_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_2FBOSS_SIZE / 2), m_pos.y + (ENEMY_2FBOSS_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
	}
	else if (m_type == TYPE_ENEMY_2FBOSS_AVATAR || m_type == TYPE_ENEMY_2FBAT)
	{//2F�{�X�̕��g
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (BOSS_AVATAR_SIZE / 2), m_pos.y - (BOSS_AVATAR_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BOSS_AVATAR_SIZE / 2), m_pos.y - (BOSS_AVATAR_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (BOSS_AVATAR_SIZE / 2), m_pos.y + (BOSS_AVATAR_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BOSS_AVATAR_SIZE / 2), m_pos.y + (BOSS_AVATAR_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();
		if (m_pos.y <= CEnemy::m_2FBossPos.y && m_nLife <= 0)
		{
			CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0.0f, 0.0f,
				CEffect::TYPE_2FBOSS);
			//�`���[�W��
			m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_2FBOSS_CHARGE);
			nCnt2FBossAvatar += 1;
			Uninit();
		}
	}
	else if (m_type == TYPE_ENEMY_2FGHOST_AVATAR)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_2FGHOST_AVATAR_SIZE / 2), m_pos.y - (ENEMY_2FGHOST_AVATAR_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_2FGHOST_AVATAR_SIZE / 2), m_pos.y - (ENEMY_2FGHOST_AVATAR_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_2FGHOST_AVATAR_SIZE / 2), m_pos.y + (ENEMY_2FGHOST_AVATAR_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_2FGHOST_AVATAR_SIZE / 2), m_pos.y + (ENEMY_2FGHOST_AVATAR_SIZE / 2), 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		m_pVtxBuff->Unlock();

	}
	else
	{//���̑�
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ENEMY_SIZE), m_pos.y - (ENEMY_SIZE), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ENEMY_SIZE), m_pos.y - (ENEMY_SIZE), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ENEMY_SIZE), m_pos.y + (ENEMY_SIZE), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ENEMY_SIZE), m_pos.y + (ENEMY_SIZE), 0.0f);

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
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//�_���[�W���󂯂��Ƃ�
//=============================================================================
void CEnemy::SetLife(int nLife)
{
	VERTEX_2D* pVtx;
	bool bFadeSwitch = false;
	m_nLife -= nLife;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	m_pVtxBuff->Unlock();

	if (m_type == TYPE_ENEMY_2FBOSS && m_nLife > ENEMY_2FBOSS_AWAKENING_LIFE)
	{//�̗͂�200��葽���Ƃ�
		//�e���o���悤�ɂ���
		m_b2FBossBullet = true;
	}

	//���C�t��0�ɂȂ�����2F�̃{�X�̕��g����Ȃ��Ƃ�
	if (m_nLife <= 0 && m_type != TYPE_ENEMY_2FBOSS_AVATAR)
	{
		if (m_type == TYPE_ENEMY_2FBOSS)
		{//2F�̃{�X��|������X�R�A3000����
			CGame::SetScore(SECOND_BOSS_SCORE);
		}
		else if (m_type == TYPE_ENEMY_1FBOSS)
		{//1F�̃{�X��|������X�R�A2000����
			CGame::SetScore(FIRST_BOSS_SCORE);
		}
		else if (m_type == TYPE_ENEMY_1FBOSS)
		{//1F�̃{�X��|������X�R�A2000����
			CGame::SetScore(THIRD_BOSS_SCORE);
		}
		else
		{//���̂ق���100
			CGame::SetScore(NOMAL_ENEMY_SCORE);
		}

		//���΂��̕��g�ȊO��������G�t�F�N�g���Z�b�g
		if (m_type != TYPE_ENEMY_2FGHOST_AVATAR)
		{
			//for (int nCount = 0; nCount < 1; nCount++)
			//{
			CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0.0f, 0.0f,
				CEffect::TYPE_ENEMY2_DEATH);
			//}
		}

		if (m_type == TYPE_ENEMY_BOSS_FOG)
		{//�A�C�e���𗎂Ƃ����΂��ȊO��������
			if (m_movetype != ACTION_ENEMY2_DROP_ITEM)
			{
				Uninit();
			}
		}
		else if (m_type == TYPE_ENEMY_2FGHOST && m_movetype == ACTION_CIRCLE_LEFT)
		{//2F�S�[�X�g�̍���|�����珬�����G���o��
			for (int nCount = 0; nCount < 5; nCount++)
			{
				CEnemy::Create(D3DXVECTOR3(m_pos.x + 20.0f * (-(nCount * 2)), m_pos.y, 0.0f),
					D3DXVECTOR3(0.0f, 5.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					ENEMY_2FGHOST_AVATAR_SIZE, ENEMY_2FGHOST_AVATAR_SIZE, 3,
					CEnemy::TYPE_ENEMY_2FGHOST_AVATAR, CEnemy::ACTION_MOVE_NONE);
			}
			Uninit();
		}
		else if (m_type == TYPE_ENEMY_2FGHOST && m_movetype == ACTION_CIRCLE_RIGHT)
		{//2F�S�[�X�g�̉E��|�����珬�����G���o��
			for (int nCount = 0; nCount < 5; nCount++)
			{
				CEnemy::Create(D3DXVECTOR3(m_pos.x + 20.0f * (-(nCount * 2)), m_pos.y, 0.0f),
					D3DXVECTOR3(0.0f, 5.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					ENEMY_2FGHOST_AVATAR_SIZE, ENEMY_2FGHOST_AVATAR_SIZE, 3,
					CEnemy::TYPE_ENEMY_2FGHOST_AVATAR, CEnemy::ACTION_MOVE_NONE);
			}
			Uninit();
		}
		else if (m_type == TYPE_ENEMY_1FBOSS && m_movetype == ACTION_MOVE_NONE)
		{//1F�{�X��|������2F�X�^�[�g
			bool b2FEnemySpawm = true;
			CGame::Set2FEnemySpawn(b2FEnemySpawm);
			Uninit();
		}
		else if (m_type == TYPE_ENEMY_2FBOSS)
		{//�{�X��|������
			Uninit();
			bFadeSwitch = true;
			m_b2FBossAwakening = false;
			CFade::SetFade(CManager::MODE_GAMECLEAR);
			CFade::SetFadeSwitch(bFadeSwitch);
		}
		else if (m_type == TYPE_ENEMY_3FBOSS && m_movetype == ACTION_MOVE_NONE)
		{//1F�{�X��|������2F�X�^�[�g
			bool b3FEnemySpawm = true;
			CGame::Set3FEnemySpawn(b3FEnemySpawm);
			Uninit();
		}
		else
		{//���̑�
			Uninit();
		}
	}
}

//=============================================================================
// ���C�t�̏��֐�
//=============================================================================
int CEnemy::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
//�͈͂������_���Ō��߂鎞�̏���
//=============================================================================
int CEnemy::GetRandNum(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

//=============================================================================
//�͈͂������_���Ō��߂鎞�̏���
//=============================================================================
void CEnemy::Set2FBossAwakening(bool b2FBossAwakening)
{
	m_b2FBossAwakening = b2FBossAwakening;
}

//=============================================================================
//�����蔻��
//=============================================================================
bool CEnemy::HitCcollision(D3DXVECTOR3 Pos, float size_x, float size_y)
{
	bool bHit = false;
	D3DXVECTOR3 pos;
	pos = GetPosition();
	if (pos.x <= Pos.x + (size_x / 2) &&
		pos.x >= Pos.x - (size_x / 2) &&
		pos.y <= Pos.y + (size_y / 2) &&
		pos.y >= Pos.y - (size_y / 2))//�����蔻��
	{
		bHit = true;
	}
	return bHit;
}