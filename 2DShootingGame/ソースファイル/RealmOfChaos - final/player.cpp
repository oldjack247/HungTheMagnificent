#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "bullet.h"
#include "result.h"
#include "item.h"
#include "enemy.h"
#include <stdio.h>
#include "score.h"
#include "game.h"
#include "controller.h" 
#include "fade.h"
#include "sound.h"
#include "effect.h"
#include "explosion.h"
#include "game_clear.h"
#include "client_ranking.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
int CPlayer::m_nLife = NULL;
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CPlayer::m_bBulletChange = false;
bool CPlayer::m_bUseMinion = false;
CGameClear* CPlayer::m_pGameClear = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nInvincible = 0;
	m_State = PLAYERSTATE_NORMAL;
	m_bBulletChange = false;
	m_bUseMinion = false;
	m_pSound = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/player/Spaceship001.png",
		&m_pTexture);
	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CPlayer::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//��������
//=============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float size_x, float size_y)
{
	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init(pos, col, size_x, size_y);
	m_nLife = MAX_LIFE;

	return pPlayer;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float size_x, float size_y)
{
	VERTEX_2D* pVtx;
	CScene2d::Init(pos, size_x, size_y);
	m_col = col;
	BindTexture(m_pTexture);

	SetObjType(OBJTYPE_PLAYER);
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	//���_���W�̐ݒ�(�E���)
	pVtx[0].pos = D3DXVECTOR3(pos.x - (PLAYER_SIZE / 2), pos.y - (PLAYER_SIZE / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (PLAYER_SIZE / 2), pos.y - (PLAYER_SIZE / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (PLAYER_SIZE / 2), pos.y + (PLAYER_SIZE / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (PLAYER_SIZE / 2), pos.y + (PLAYER_SIZE / 2), 0.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPlayer::Update(void)
{
	VERTEX_2D* pVtx;
	bool b2FBossAwakening = false;
	CInputKeyboard* pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();
	CInputController* pInputController = NULL;
	pInputController = CManager::GetController();
	DIJOYSTATE2 Controller = pInputController->GetController();
	m_nCounterAnim++;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.01075f + 0.01075f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.01075f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.01075f + 0.01075f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.01075f, 1.0f);
	if (m_nCounterAnim >= 2)
	{//��莞�Ԍo�߂���
		m_nCounterAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim >= 93)
		{//�p�^�[�����𒴂���
			m_nPatternAnim = 0;
		}
	}
	m_pVtxBuff->Unlock();

	m_pos = GetPosition();

	if (pInputKeyboard->GetKeyboardPress(DIK_D))
	{
		m_move += D3DXVECTOR3(3.0f, 0.0f, 0.0f);
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_A))
	{
		m_move += D3DXVECTOR3(-3.0f, 0.0f, 0.0f);
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_W))
	{
		m_move += D3DXVECTOR3(0.0f, -3.0f, 0.0f);
	}
	if (pInputKeyboard->GetKeyboardPress(DIK_S))
	{
		m_move += D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	}
	if (Controller.lX != 0 || Controller.lY != 0)
	{//�R���g���[���[
		float fAngle = (float)atan2(Controller.lX, Controller.lY * 1.0f);
		float fPlayerAngle = atan2f(Controller.lX * -1.0f, Controller.lY * 1.0f);
		m_move.x += sinf(fAngle) * 3.0f;
		m_move.y += cosf(fAngle) * 3.0f;
	}
	//SPACE�L�[���R���g���[���[��A�{�^������������e�����˂����
	if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) ||
		pInputController->GetJoypadTrigger(CInputController::BUTTON_A))
	{
		/*if (m_bUseMinion == true)
		{
			CMinion::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_SIZE);
		}*/

		if (m_bBulletChange == true)
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f), D3DXVECTOR3(0.0f, -12.0f, 0.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_SIZE, 50, CBullet::BULLETTYPE_PLAYER);
			CBullet::Create(D3DXVECTOR3(m_pos.x + (PLAYER_SIZE / 2), m_pos.y - (PLAYER_SIZE / 2), 0.0f), D3DXVECTOR3(0.0f, -12.0f, 0.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_SIZE, 50, CBullet::BULLETTYPE_PLAYER_2);
			CBullet::Create(D3DXVECTOR3(m_pos.x - (PLAYER_SIZE / 2), m_pos.y - (PLAYER_SIZE / 2), 0.0f), D3DXVECTOR3(0.0f, -12.0f, 0.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_SIZE, 50, CBullet::BULLETTYPE_PLAYER_2);
		}
		else
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - (PLAYER_SIZE / 2), 0.0f), D3DXVECTOR3(0.0f, -12.0f, 0.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_SIZE, 50, CBullet::BULLETTYPE_PLAYER);
		}

		CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0.0f, 0.0f,
			CEffect::TYPE_BULLET_SPAWN);
		//���ˉ�
		m_pSound->PlaySound((m_pSound = CManager::GetSound())->SOUND_LABEL_PLAYER_BULLET);
	}

	//�_���[�W���󂯂��Ƃ�
	if (m_State == PLAYERSTATE_DAMAGE)
	{
		m_nInvincible--;
		if (m_nInvincible <= 80)
		{
			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
			//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			m_pVtxBuff->Unlock();
		}

		if (m_nInvincible <= 0)
		{
			m_State = PLAYERSTATE_NORMAL;
		}
	}

	//��ʊO�ɏo�Ȃ��悤�ɂ���
	if (m_pos.x < 100.0f - (PLAYER_SIZE / 2))
	{
		m_pos.x = 100.0f - (PLAYER_SIZE / 2);
	}
	if (m_pos.x > SCREEN_WIDTH - (PLAYER_SIZE / 2))
	{
		m_pos.x = SCREEN_WIDTH - (PLAYER_SIZE / 2);
	}
	if (m_pos.y < 100.0f - (PLAYER_SIZE / 2))
	{
		m_pos.y = 100.0f - (PLAYER_SIZE / 2);
	}
	if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE / 2))
	{
		m_pos.y = SCREEN_HEIGHT - (PLAYER_SIZE / 2);
	}

	//����
	m_move.x += ((0.0f) - m_move.x) * 0.5f;
	m_move.y += ((0.0f) - m_move.y) * 0.5f;
	m_move.x -= ((0.0f) - m_move.x) * 0.5f;
	m_move.y -= ((0.0f) - m_move.y) * 0.5f;

	//�ʒu�X�V
	m_pos += m_move;
	SetPosition(m_pos);
	SetCol(m_col);
	bool bFadeSwitch = false;

	//�̗͂��Ȃ��Ȃ�����
	if (m_nLife <= 0)
	{
		CScore* pScore = NULL;
		pScore = CGame::GetScore();
		int nScore = pScore->GetScore();
		m_bBulletChange = false;
		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			PLAYER_EXPLOSION_SIZE, PLAYER_EXPLOSION_SIZE,
			CExplosion::TYPE_PLAYER_DEATH);
		//CCrient_ranking::SetRanking(nScore);
		Uninit();

		//�t�F�[�h������ă��U���g��ʂɂ���
		bFadeSwitch = true;
		CFade::SetFade(CManager::MODE_GAMEOVER);
		CFade::SetFadeSwitch(bFadeSwitch);
	}
	else
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (PLAYER_SIZE / 2), m_pos.y - (PLAYER_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (PLAYER_SIZE / 2), m_pos.y - (PLAYER_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (PLAYER_SIZE / 2), m_pos.y + (PLAYER_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (PLAYER_SIZE / 2), m_pos.y + (PLAYER_SIZE / 2), 0.0f);
		//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;
		//pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
		m_pVtxBuff->Unlock();
	}

}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//�_���[�W���󂯂��Ƃ�
//=============================================================================
void CPlayer::SetLife(int nLife)
{
	VERTEX_2D* pVtx;
	if (m_nInvincible <= 0)
	{
		m_nLife -= nLife;
		m_State = PLAYERSTATE_DAMAGE;
		m_nInvincible = 100;
	}
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�
	//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// �g���Ă���e��ς���
//=============================================================================
void CPlayer::SetBulletChange(bool bBulletChange)
{
	m_bBulletChange = bBulletChange;
}

//=============================================================================
// �g���Ă���Minion��ς���
//=============================================================================
void CPlayer::SetMinion(bool bUseMinion)
{
	m_bUseMinion = bUseMinion;
}