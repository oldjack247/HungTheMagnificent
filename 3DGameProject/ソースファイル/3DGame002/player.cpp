//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "motion.h"
#include "collision.h"
#include "sound.h"
#include "camera.h"
#include "slash.h"
#include "debugcollision.h"
#include "swordeffect.h"
#include "hiteffect.h"
#include "specialattackeffect.h"
#include "magiccircle.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMotionTime = 0.0f;
	m_fDamageTime = 0.0f;
	m_fSpGauge = 0.0f;
	m_nSwordEffectTime = 0;
	m_Playerstate = PLAYERSTATE_NOMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ��������
//=============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPlayer* pPlayer;
	pPlayer = new CPlayer;
	pPlayer->SetPlayer(pos, rot, size);
	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	SetObjType(OBJTYPE_PLAYER);
	SetType(CHARACTERTYPE_PLAYER);
	LoadInitialPosition(MOTION_PLAYER_TEXT);
	CCharacter::Init();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();

	// �����[�X
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPlayer::Update(void)
{
	CCharacter::Update();

	D3DXVECTOR3 pos = GetPos();

	// ���[�V�����̎��Ԃ�0�ȉ���������
	if (m_fMotionTime <= 0.0f)
	{
		m_Playerstate = PLAYERSTATE_NOMAL;
	}

	// ���̐�Ǝ�����̈ʒu�̋���
	D3DXVECTOR3 Top = D3DXVECTOR3(GetModelParts(12)->GetMtxWorld()._41, GetModelParts(12)->GetMtxWorld()._42, GetModelParts(12)->GetMtxWorld()._43);
	D3DXVECTOR3 Bottom = D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41, GetModelParts(11)->GetMtxWorld()._42, GetModelParts(11)->GetMtxWorld()._43);
	D3DXVECTOR3 Distance = D3DXVECTOR3(Top.x - Bottom.x, Top.y - Bottom.y, Top.z - Bottom.z);

	// ����ł��Ȃ��Ȃ�
	if (GetLife() > 0)
	{
		switch (m_Playerstate)
		{
		case PLAYERSTATE_NOMAL:
			//�Q�[���p�b�h����
			GamePad();
			break;

		case PLAYERSTATE_ATTACK:
			//�U���̏���
			Attack(Distance);
			break;

		case PLAYERSTATE_MAGIC:
			//���@�̏���
			Magic();
			break;

		default:
			break;
		}

		// ���̃G�t�F�N�g�̏���
		Swordeffect(Distance);
	}

	// ���[�V�����̎��Ԃ����炵�Ă���
	m_fMotionTime -= SUBTRACT_FLAME;

	// �_���[�W���󂯂鎞�Ԃ����Z����
	m_fDamageTime--;

	// SP�Q�[�W���ő�l�𒴂��Ȃ��悤�ɂ���
	if (m_fSpGauge >= PLAYER_SP_MAX)
	{
		m_fSpGauge = PLAYER_SP_MAX;
	}

	// �ړ��ʂ����Z
	pos += m_move;

	//// �G�Ƃ̓����蔻��
	//pos = EnemyCollision(pos);

	// �}�b�v����
	if (pos.x - GetSize().x < -PLAYER_MOVE_MAP_LIMIT)
	{
		pos.x = -PLAYER_MOVE_MAP_LIMIT + GetSize().x;
	}
	if (pos.x + GetSize().x > PLAYER_MOVE_MAP_LIMIT)
	{
		pos.x = PLAYER_MOVE_MAP_LIMIT - GetSize().x;
	}
	if (pos.z - GetSize().z < -PLAYER_MOVE_MAP_LIMIT)
	{
		pos.z = -PLAYER_MOVE_MAP_LIMIT + GetSize().z;
	}
	if (pos.z + GetSize().z > PLAYER_MOVE_MAP_LIMIT)
	{
		pos.z = PLAYER_MOVE_MAP_LIMIT - GetSize().z;
	}

	// ���W�̃Z�b�g
	SetPos(pos);

#ifdef _DEBUG
	// �����蔻��̉���
	CDebugCollision::Create(GetPos() + GetMotion()->GetPos(0), GetSize(), CDebugCollision::TYPE_SQUARE);

	//CDebugCollision::Create(GetPos(), D3DXVECTOR3(GetSize().y, GetSize().y, GetSize().y), CDebugCollision::TYPE_SPHERE);
#endif
}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
//�Q�[���p�b�h����
//=============================================================================
void CPlayer::GamePad(void)
{
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick = {};
	CInputJoystick* pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	if (pJoystickDevice != NULL)
	{
		//�ʏ탂�[�V����
		GetMotion()->SetMotion(PLAYERMOTION_IDLE);

		//--------------------------
		//�ړ�
		//--------------------------
		// �X�e�B�b�N�̓��͂���������
		if (pStick.lY != 0 || pStick.lX != 0)
		{
			// �X�e�B�b�N�̊p�x�����߂�
			float fAngle = atan2(pStick.lX * -1.0f, pStick.lY);

			// �X�e�B�b�N�̊p�x����ړ�������������߂�
			m_move.x = -sinf(CManager::GetCamera()->GetAngle() + fAngle) * PLAYER_MOVE_SPEED;
			m_move.z = -cosf(CManager::GetCamera()->GetAngle() + fAngle) * PLAYER_MOVE_SPEED;

			// �L�����̌�����ς���
			rot.y = CManager::GetCamera()->GetAngle() + fAngle;

			// ���郂�[�V����
			GetMotion()->SetMotion(PLAYERMOTION_RUN);
		}
		else
		{
			// ���삪�Ȃ��Ƃ��͒l��0��
			m_move.x = 0.0f;
			m_move.z = 0.0f;
		}

		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2;
		}
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}

		// X�{�^������������
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_X))
		{
			// �a�郂�[�V����
			GetMotion()->SetMotion(PLAYERMOTION_SLASH);
			m_Playerstate = PLAYERSTATE_ATTACK;
			m_fMotionTime = MOTION_SLASH_FLAME;

			//�T�E���h�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASH);
		}

		// �Q�[�W���ő�ɂȂ�����
		if (m_fSpGauge == PLAYER_SP_MAX)
		{
			// Y�{�^������������
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_Y))
			{
				// ���@���o�����[�V����
				GetMotion()->SetMotion(PLAYERMOTION_MAGIC);
				m_Playerstate = PLAYERSTATE_MAGIC;
				m_fMotionTime = MOTION_MAGICCIRCLE_FLAME;

				// �K�E�Z�̃G�t�F�N�g�̐���
				CSpecialattackeffect::Create(GetPos(), SPECIALATTACKEFFECT_SIZE,
					SPECIALATTACKEFFECT_COLOR, SPECIALATTACKEFFECT_COUNTANIM * SPECIALATTACKEFFECT_PATTERNANIM * SPECIALATTACKEFFECT_TIMEANIM);

				// �Q�[�W�̗ʂƈړ��ʂ�0��
				m_fSpGauge = 0.0f;
				m_move.x = 0.0f;
				m_move.z = 0.0f;

				CScene::SetbUpdate(true, CScene::OBJTYPE_ENEMY);

				//�T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_MAGICCIRCLE);
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_MAGIC);
			}
		}
	}

	// ��]�̃Z�b�g
	SetRot(rot);
}

//=============================================================================
// �U������
//=============================================================================
void CPlayer::Attack(D3DXVECTOR3 Distance)
{
	D3DXVECTOR3 GetDistance = Distance / SWORD_EFFECT_NUM;

	// �����Ă�����ɓ�����
	m_move.x = -sinf(GetRot().y) * PLAYER_ATTACK_MOVE_SPEED;
	m_move.z = -cosf(GetRot().y) * PLAYER_ATTACK_MOVE_SPEED;

	// ����ł��Ȃ�����
	if (m_fMotionTime > 0.0f)
	{
		if (m_fMotionTime < MOTION_SLASH_FLAME - MOTION_SLASH_FLAME_COLLISION_START && m_fMotionTime > 10.0f)
		{
			//// �ړ��̊p�x�����߂�
			//D3DXVECTOR3 moveAngle = D3DXVECTOR3(sinf(GetRot().y) * -1, 0.0f, cosf(GetRot().y) * -1);
			//
			//CSlash::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			//	GetModelParts(11)->GetMtxWorld()._42,
			//	GetModelParts(11)->GetMtxWorld()._43) + Distance,
			//	SLASH_SIZE, moveAngle,
			//	SLASH_COLOR, SLASH_LIFE, CSlash::TYPE_SLASH_1);

			// �G�ւ̓����蔻��
			CScene* pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
			do
			{
				if (pScene != NULL)
				{
					OBJTYPE objType = pScene->GetObjType();
					if (objType == OBJTYPE_ENEMY)
					{
						// �����������ǂ����Ɠ��������ꏊ
						bool bHit = false;
						D3DXVECTOR3 Hitpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						// ���̓����蔻�蕪��
						for (int nCount = 0; nCount < SWORD_EFFECT_NUM; nCount++)
						{
#ifdef _DEBUG
							// �����蔻��̉���
							CDebugCollision::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
								GetModelParts(11)->GetMtxWorld()._42,
								GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
								SWORD_COLISION_SIZE, CDebugCollision::TYPE_SQUARE);
#endif
							// �����蔻��
							if (CCollision::RectangleCollision3D(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
								GetModelParts(11)->GetMtxWorld()._42,
								GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
								SWORD_COLISION_SIZE, ((CEnemy*)pScene)->GetPos(), ((CEnemy*)pScene)->GetSize()) == true)
							{
								// �G�ւ̃_���[�W(�G���œ����������Ԃ�)
								bHit = ((CEnemy*)pScene)->HitDamage(5, CEnemy::DAMAGESTATE_SLASH);
								Hitpos = GetDistance * (float)nCount;
								break;
							}
						}

						// �G�ɓ��������Ȃ�
						if (bHit == true)
						{
							// �ΉԂ��o��
							CHiteffect::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
								GetModelParts(11)->GetMtxWorld()._42,
								GetModelParts(11)->GetMtxWorld()._43) + Hitpos, HITEFFECT_PLAYER_SIZE, HITEFFECT_PLAYER_COLOR,
								HITEFFECT_PLAYER_COUNTANIM * HITEFFECT_PLAYER_PATTERNANIM * HITEFFECT_PLAYER_TIMEANIM, CHiteffect::HITEFFECTTYPE_PLAYER);

							// sp�̃Q�[�W�����Z����
							m_fSpGauge++;
						}
					}
					pScene = pScene->GetSceneNext();
				}
			} while (pScene != NULL);
		}
	}
}

//=============================================================================
// ���̃G�t�F�N�g�̏���
//=============================================================================
void CPlayer::Swordeffect(D3DXVECTOR3 Distance)
{
	D3DXVECTOR3 GetDistance = (float)(rand() % SWORD_EFFECT_NUM) * (Distance / SWORD_EFFECT_NUM);

	m_nSwordEffectTime++;
	if (m_nSwordEffectTime >= SWORD_EFFECT_CREATE_TIME)
	{
		// ���̃G�t�F�N�g
		CSwordeffect::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			GetModelParts(11)->GetMtxWorld()._42,
			GetModelParts(11)->GetMtxWorld()._43) + GetDistance,
			SWORD_EFFECT_SIZE, D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			SWORD_EFFECT_COLOR, SWORD_EFFECT_LIFE);
		m_nSwordEffectTime = 0;
	}
}

//=============================================================================
// ���@�̏���
//=============================================================================
void CPlayer::Magic(void)
{
	if (m_fMotionTime == MOTION_MAGICCIRCLE_FLAME - MOTION_MAGICCIRCLE_CREATE_START)
	{
		// ���@�w�̐���
		CMagiccercle::Create(D3DXVECTOR3(GetPos().x, 0.0f, GetPos().z),
			MAGICCERCLE_DEFAULT_ROT, MAGICCERCLE_DEFAULT_SIZE, MAGICCERCLE_DEFAULT_COLOR, (int)m_fMotionTime, CMagiccercle::MAGICCIRCLETYPE_PLAYER);
	}
}

//=============================================================================
// �G�Ƃ̓����蔻��
//=============================================================================
D3DXVECTOR3 CPlayer::EnemyCollision(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Hitpos = pos;
	CScene* pScene = GetSceneTop(OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				if (((CEnemy*)pScene)->GetEnemyState() != CEnemy::ENEMYSTATE_DEATH)
				{
					// �����蔻��
					if (CCollision::SphereCollision(Hitpos, GetSize().x / 2.0f, ((CEnemy*)pScene)->GetPos(), ((CEnemy*)pScene)->GetSize().x / 2.0f) == true)
					{
						// ����������1�t���[���O�̍��W������
						Hitpos = GetPos();
					}
				}
			}
			// ���̃|�C���^�̎󂯎��
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

	return Hitpos;
}

//=============================================================================
// �����ݒ�
//=============================================================================
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	SetObjType(OBJTYPE_PLAYER); //�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(size);
	SetLife(PLAYER_LIFE);
}

//=============================================================================
//�v���C���[���_���[�W���󂯂���
//=============================================================================
bool CPlayer::HitDamage(int nDamage)
{
	// �����������ǂ���
	bool bHit = false;

	// �_���[�W���󂯂鎞�Ԃ�0�ȉ��̎�
	if (m_fDamageTime <= 0)
	{
		m_fDamageTime = PLAYER_DAMAGE_TIME;

		// ���C�t�����炷
		int nLife = GetLife();
		nLife -= nDamage;
		SetLife(nLife);

		//�T�E���h�̍Đ�
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);

		// ���C�t��0�ȉ��̎�
		if (nLife <= 0)
		{
			// �t�F�[�h�̐���
			CManager::GetFade()->SetFade(CManager::MODE_GAMEOVER);
		}

		// ���������t���O��Ԃ�
		bHit = true;
	}

	return bHit;
}