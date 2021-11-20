//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "enemy.h"
#include "motion.h"
#include "model.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include "sound.h"
#include "collision.h"
#include "debugcollision.h"
#include "enemydeatheffect.h"
#include "hiteffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) :CCharacter(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDamageTime = 0.0f;
	m_fMotionTime = 0.0f;
	m_fAttackTime = 0.0f;
	m_bAttack = false;
	m_EnemyState = ENEMYSTATE_NOMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ��������
//=============================================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState)
{
	CEnemy* pEnemy;
	pEnemy = new CEnemy;
	pEnemy->SetEnemy(pos, rot, size, EnemyState);
	pEnemy->Init();
	return pEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	SetObjType(OBJTYPE_ENEMY);
	SetType(CHARACTERTYPE_ENEMY);
	LoadInitialPosition(MOTION_ENEMY_TEXT);
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CCharacter::Uninit();

	// �����[�X
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	CCharacter::Update();

	if (CGame::GetPlayer != NULL)
	{
		//�v���C���[�̏ꏊ�̎擾
		D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		// �v���C���[�Ƃ̋���
		float fDistance = sqrtf(
			powf(PlayerPos.x - pos.x, 2.0f) +
			powf(PlayerPos.z - pos.z, 2.0f));

		// ����ł��Ȃ��Ƃ�
		if (m_EnemyState != ENEMYSTATE_DEATH)
		{
			//�����̌v�Z
			float angle = (float)atan2(PlayerPos.x - pos.x, PlayerPos.z - pos.z);
			rot.y = angle - D3DXToRadian(180.0f);
		}

		// �G�̏��
		switch (m_EnemyState)
		{
		case ENEMYSTATE_NOMAL:
			// �v���C���[�ƓG�̋������߂�������
			if (fDistance <= ENEMY_DISTANCE_PLAYER)
			{
				Attack();
			}
			else
			{
				//�����Ă��������rot
				m_move.x = -sinf(rot.y) * ENEMY_MOVE_SPEED;
				m_move.z = -cosf(rot.y) * ENEMY_MOVE_SPEED;

				// �`�F�C�X���͑��郂�[�V����
				GetMotion()->SetMotion(ENEMYMOTION_RUN);
			}
			break;

		case ENEMYSTATE_DAMAGE:
			// �`�F�C�X���͑��郂�[�V����
			GetMotion()->SetMotion(ENEMYMOTION_DAMAGE);

			//�����Ă��������rot
			m_move.x = sinf(rot.y) * ENEMY_DAMAGE_MOVE_SPEED;
			m_move.z = cosf(rot.y) * ENEMY_DAMAGE_MOVE_SPEED;

			// ���[�V�����̎��Ԃ̌��Z
			m_fMotionTime--;
			if (m_fMotionTime <= 0.0f)
			{
				m_EnemyState = ENEMYSTATE_NOMAL;
			}
			break;

		case ENEMYSTATE_DEATH:
			// ���[�V�����̎��Ԃ̌��Z
			m_fMotionTime--;
			if (m_fMotionTime <= 50.0f)
			{
				float fAngle = D3DXToRadian(360.0f / ENEMYDEATHEFFEC_CREATE_NUM);
				for (int nCount = 0; nCount < ENEMYDEATHEFFEC_CREATE_NUM; nCount++)
				{
					CEnemydeatheffect::Create(pos, ENEMYDEATHEFFEC_DEFAULT_SIZE,
						D3DXVECTOR3(sinf(fAngle * nCount), 0.0f, cosf(fAngle * nCount)) * ENEMYDEATHEFFEC_DEFAULT_SPEED,
						ENEMYDEATHEFFEC_DEFAULT_COLOR,
						ENEMYDEATHEFFEC_COUNTANIM * ENEMYDEATHEFFEC_PATTERNANIM * ENEMYDEATHEFFEC_TIMEANIM);
				}

				for (int nCount = 0; nCount < ENEMYDEATHEFFEC_CREATE_NUM; nCount++)
				{
					CEnemydeatheffect::Create(pos, ENEMYDEATHEFFEC_DEFAULT_SIZE,
						D3DXVECTOR3(sinf(fAngle * nCount), 1.0f, cosf(fAngle * nCount)) * (ENEMYDEATHEFFEC_DEFAULT_SPEED / 2.0f),
						ENEMYDEATHEFFEC_DEFAULT_COLOR,
						ENEMYDEATHEFFEC_COUNTANIM * ENEMYDEATHEFFEC_PATTERNANIM * ENEMYDEATHEFFEC_TIMEANIM);
				}

				CEnemydeatheffect::Create(pos, ENEMYDEATHEFFEC_DEFAULT_SIZE,
					D3DXVECTOR3(0.0f, 1.0f, 0.0f) * ENEMYDEATHEFFEC_DEFAULT_SPEED,
					ENEMYDEATHEFFEC_DEFAULT_COLOR,
					ENEMYDEATHEFFEC_COUNTANIM * ENEMYDEATHEFFEC_PATTERNANIM * ENEMYDEATHEFFEC_TIMEANIM);

				// �I������
				Uninit();
				return;
			}
			if (m_fMotionTime >= 131.0f)
			{
				//�����Ă��������rot
				m_move.x = -sinf(rot.y) * ENEMY_DAMAGE_MOVE_SPEED;
				m_move.z = -cosf(rot.y) * ENEMY_DAMAGE_MOVE_SPEED;
			}
			else
			{
				m_move.x = 0.0f;
				m_move.z = 0.0f;
			}

			break;

		default:
			break;
		}

		// �G���m�̔���
		EnemyCollision();

		// �ړ��ʂ̉��Z
		pos += m_move;

		// �v���C���[�Ƃ̔���
		pos = PlayerCollision(pos);

		SetPos(pos);
		SetRot(rot);

	}
	// �_���[�W���󂯂鎞�Ԃ����炷
	m_fDamageTime--;

#ifdef _DEBUG
	// �����蔻��̉���
	CDebugCollision::Create(GetPos() + GetMotion()->GetPos(0), GetSize(), CDebugCollision::TYPE_SQUARE);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
// �q�b�g����
//=============================================================================
bool CEnemy::HitDamage(int nDamage, DAMAGESTATE DamageState)
{
	bool bHit = false;
	if (m_EnemyState == ENEMYSTATE_NOMAL || m_EnemyState == ENEMYSTATE_DAMAGE)
	{
		// �_���[�W���󂯂鎞�Ԃ�0�ȉ���������
		if (m_fDamageTime <= 0.0f)
		{
			// �_���[�W�̎�ނɂ���ă_���[�W���󂯂鎞�Ԃ�ς���
			switch (DamageState)
			{
			case DAMAGESTATE_SLASH:
				m_fDamageTime = ENEMY_DAMAGE_SRASH_TIME;
				break;

			//case DAMAGESTATE_MAGICCIRCLE:
			//	m_fDamageTime = ENEMY_DAMAGE_MAGICCIRCLE_TIME;
			//	break;

			default:
				break;
			}

			// ���C�t�����炷
			int nLife = GetLife();
			nLife -= nDamage;
			SetLife(nLife);

			// ��Ԃ��_���[�W���󂯂���Ԃɂ���
			m_EnemyState = ENEMYSTATE_DAMAGE;
			m_fMotionTime = ENEMY_DAMAGE_MOTION_TIME;

			//�T�E���h�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ENEMY_DAMAGE);

			if (nLife <= 0)
			{
				//�T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ZOMBIE_DEATH);
				CGame::SubtractEnemy();

				// ���񂾂Ƃ��̃��[�V�����Ǝ��ԁA���
				GetMotion()->SetMotion(ENEMYMOTION_DEATH);
				m_fMotionTime = ENEMY_DEATH_MOTION_TIME;
				m_EnemyState = ENEMYSTATE_DEATH;
			}
			else
			{
				//�T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ZOMBIE_DAMAGE);
			}

			// �����������Ƃ�Ԃ�
			bHit = true;
		}
	}

	return bHit;
}

//=============================================================================
// �G���m�̓����蔻��̏���
//=============================================================================
void CEnemy::EnemyCollision(void)
{
	// ����ł��Ȃ��Ƃ��ƃ_���[�W���󂯂ĂȂ��Ƃ�
	if (m_EnemyState != ENEMYSTATE_DEATH || m_EnemyState != ENEMYSTATE_DAMAGE)
	{
		CScene* pScene = GetSceneTop(OBJTYPE_ENEMY);
		do
		{
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					if (GetPos() != ((CEnemy*)pScene)->GetPos())
					{
						if (((CEnemy*)pScene)->GetEnemyState() != ENEMYSTATE_DEATH)
						{
							// �����蔻��
							if (CCollision::SphereCollision(GetPos(), GetSize().x / 2.0f, ((CEnemy*)pScene)->GetPos(), ((CEnemy*)pScene)->GetSize().x / 2.0f) == true)
							{
								float frot = atan2f(GetPos().x - ((CEnemy*)pScene)->GetPos().x, GetPos().z - ((CEnemy*)pScene)->GetPos().z);
								m_move.x -= sinf(frot + D3DX_PI);
								m_move.z -= cosf(frot + D3DX_PI);
							}
						}
					}
				}
				// ���̃|�C���^�̎󂯎��
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
	}
}

//=============================================================================
// �v���C���[�Ƃ̓����蔻��̏���
//=============================================================================
D3DXVECTOR3 CEnemy::PlayerCollision(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Getpos = pos;

	// ����ł��Ȃ��Ƃ�
	if (m_EnemyState != ENEMYSTATE_DEATH)
	{
		CScene* pScene = GetSceneTop(OBJTYPE_PLAYER);
		do
		{
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					// �����蔻��
					if (CCollision::SphereCollision(GetPos(), GetSize().x / 2.0f, ((CPlayer*)pScene)->GetPos(), ((CPlayer*)pScene)->GetSize().x / 2.0f) == true)
					{
						if (m_EnemyState == ENEMYSTATE_NOMAL)
						{
							Getpos = GetPos();
						}
					}
				}
				// ���̃|�C���^�̎󂯎��
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
	}
	return Getpos;
}

//=============================================================================
// �U���̏���
//=============================================================================
void CEnemy::Attack(void)
{
	// �U�����Ă��Ȃ��Ƃ�
	if (m_bAttack == false)
	{
		// �U�����鎞�Ԃ̉��Z
		m_fAttackTime++;

		// �U�����鎞�Ԃ���������
		if (m_fAttackTime >= ENEMY_ATTACK_UNTIL_TIME)
		{
			// �U���̃t���O����
			m_bAttack = true;

			// �U�����[�V����
			GetMotion()->SetMotion(ENEMYMOTION_ATTACK);
			m_fMotionTime = ENEMY_ATTACK_MOTION_TIME;
		}
	}
	else
	{
#ifdef _DEBUG
		// �����蔻��̉���
		CDebugCollision::Create(D3DXVECTOR3(GetModelParts(15)->GetMtxWorld()._41,
			GetModelParts(15)->GetMtxWorld()._42,
			GetModelParts(15)->GetMtxWorld()._43),
			D3DXVECTOR3(50.0f, 50.0f, 50.0f), CDebugCollision::TYPE_SQUARE);
#endif
		// �v���C���[�ւ̓����蔻��
		CScene* pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
		do
		{
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					// �����������ǂ����Ɠ��������ꏊ
					bool bHit = false;
					D3DXVECTOR3 Hitpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					// �����蔻��
					if (CCollision::RectangleCollision3D(D3DXVECTOR3(GetModelParts(15)->GetMtxWorld()._41,
						GetModelParts(15)->GetMtxWorld()._42,
						GetModelParts(15)->GetMtxWorld()._43),
						SWORD_COLISION_SIZE, ((CPlayer*)pScene)->GetPos(), ((CPlayer*)pScene)->GetSize()) == true)
					{
						// �G�ւ̃_���[�W(�G���œ����������Ԃ�)
						bHit = ((CPlayer*)pScene)->HitDamage(5);
					}

					// �G�ɓ��������Ȃ�
					if (bHit == true)
					{
						// �ΉԂ��o��
						CHiteffect::Create(D3DXVECTOR3(GetModelParts(15)->GetMtxWorld()._41,
							GetModelParts(15)->GetMtxWorld()._42,
							GetModelParts(15)->GetMtxWorld()._43) + Hitpos, HITEFFECT_ENEMY_SIZE, HITEFFECT_ENEMY_COLOR,
							HITEFFECT_ENEMY_COUNTANIM * HITEFFECT_ENEMY_PATTERNANIM * HITEFFECT_ENEMY_TIMEANIM, CHiteffect::HITEFFECTTYPE_ENEMY);
					}

				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

		// ���[�V�����̎��Ԃ̌��Z
		m_fMotionTime--;
		if (m_fMotionTime <= 0.0f)
		{
			m_bAttack = false;
			m_fAttackTime = 0.0f;
			m_fMotionTime = 0.0f;
		}
	}
}

//=============================================================================
// �e��ݒ�
//=============================================================================
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState)
{
	SetObjType(OBJTYPE_ENEMY); //�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(size);
	m_EnemyState = EnemyState;
	SetLife(ENEMY_LIFE);
}