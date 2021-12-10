//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "enemy.h"
#include "fire.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "map.h"
#include "skybox.h"
#include "magiccircle.h"


//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer* CGame::m_pPlayer = NULL;
int CGame::m_nEnemyNum = 0;
int CGame::m_nEnemyDeathTotal = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_bEnemyCreate = true;
	m_nEnemyCreateTime = ENEMY_CREATE_TIME;
	m_nDisplace = 0;
	m_nEnemyDeathTotalOld = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//rand�̏�����
	srand((unsigned)time(NULL));

	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	//�J����
	CManager::CreateCamera();

	//���C�g
	CManager::CreateLight();
	m_pPlayer = CPlayer::Create(PLAYER_DEFAULT_POS, PLAYER_DEFAULT_ROT, PLAYER_DEFAULT_SIZE);
	CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));

	// HP��UI
	//CUi::Create(PLAYER_HP_POS, PLAYER_HP_SIZE, CUi::TYPE_HP);
	CUi::Create(PLAYER_HP_GAUGE, PLAYER_HP_GAUGE_SIZE, CUi::TYPE_HPSPBACK);
	CUi::Create(PLAYER_HP_GAUGE, PLAYER_HP_GAUGE_SIZE, CUi::TYPE_PLAYER_LIFE);
	CUi::Create(PLAYER_HP_GAUGE, PLAYER_HP_GAUGE_SIZE, CUi::TYPE_HPFRAME);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);

	m_pPlayer = NULL;
	m_nEnemyNum = 0;
	m_nEnemyDeathTotal = 0;

	m_bEnemyCreate = false;
	m_nEnemyCreateTime = 0;

}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		// ��������t���O�������Ă���Ȃ�
		if (m_bEnemyCreate == true)
		{
			// �G�𐶐����鎞�Ԃ̉��Z
			m_nEnemyCreateTime++;
			if (m_nEnemyCreateTime >= ENEMY_CREATE_TIME)
			{
				// ��������p�x
				float fCreateAngle = D3DXToRadian((rand() % ENEMY_CREATE_ANGLE));
				float fDivide = (float)(rand() % 3 + 1);

				// �G�𐶐�����Ƃ��̖��@�w�̐���
				CMagiccercle::Create(D3DXVECTOR3((ENEMY_CREATE_DISTANCE.x / fDivide) * sinf(fCreateAngle), 0.0f, (ENEMY_CREATE_DISTANCE.z / fDivide) * cosf(fCreateAngle)),
					MAGICCERCLE_DEFAULT_ROT, MAGICCERCLE_ENEMY_DEFAULT_SIZE, MAGICCERCLE_DEFAULT_COLOR,
					MAGICCERCLE_ENEMY_COUNTANIM * MAGICCERCLE_ENEMY_PATTERNANIM * MAGICCERCLE_ENEMY_TIMEANIM, CMagiccercle::MAGICCIRCLETYPE_ENEMY);

				// �G�̐��̉��Z
				m_nEnemyNum++;
				m_nEnemyCreateTime = 0;

				// �G�̑�������������
				if (m_nEnemyNum >= ENEMY_CREATE_NUM)
				{
					m_bEnemyCreate = false;
				}
			}
		}
	}

	// �G�̐���0�ɂȂ�����
	if (m_nEnemyNum == 0)
	{
		m_bEnemyCreate = true;
	}

	// �|���������������Ȃ�
	if (m_nEnemyDeathTotal >= MAX_DEATH_ENEMY_NUM)
	{
		if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
		{
			//�T�E���h�̒�~
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);

			//�t�F�[�h�̐���
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}