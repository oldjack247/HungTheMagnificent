#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt")	// ���[�V�����̃e�L�X�g
#define PLAYER_LIFE (50)											// �v���C���[�̃��C�t
#define PLAYER_SP_MAX (20)											// �v���C���[��SP
#define PLAYER_DEFAULT_POS (D3DXVECTOR3(0.0f, 43.0f, 0.0f))			// ���W
#define PLAYER_DEFAULT_ROT (D3DXVECTOR3(0.0f, 1.5f, 0.0f))			// ��]
#define PLAYER_DEFAULT_SIZE (D3DXVECTOR3(50.0f, 80.0f, 50.0f))		// �傫��
#define PLAYER_MOVE_SPEED (2.0f)									// �������x
#define PLAYER_ATTACK_MOVE_SPEED (1.0f)								// �U���������̑��x
#define PLAYER_DAMAGE_TIME (120.0f)									// �v���C���[���_���[�W���󂯂鎞��
#define PLAYER_MOVE_MAP_LIMIT (800.0f)								// �v���C���[�̈ړ��ł���͈�
#define SWORD_COLISION_SIZE (D3DXVECTOR3(10.0f, 10.0f, 10.0f))			// ���̓����蔻��̑傫��
#define MOTION_SLASH_FLAME (26.0f)									// �a�郂�[�V�����̃t���[��
#define MOTION_SLASH_FLAME_COLLISION_START (8.0f)					// �a�郂�[�V�����̃G�t�F�N�g���o��܂ł̃t���[��
#define MOTION_MAGICCIRCLE_FLAME (380.0f)							// ���@�w���o�����[�V�����̃t���[��
#define MOTION_MAGICCIRCLE_CREATE_START (70.0f)						// ���@�w���o���܂ł̃t���[��
#define SUBTRACT_FLAME (1.0f)			// ���炷�t���[���̗�

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;
class CReticle;
class CEnemy;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer :public CCharacter
{
public:

	typedef enum
	{
		PLAYERMOTION_IDLE = 0,
		PLAYERMOTION_RUN,
		PLAYERMOTION_SLASH,
		PLAYERMOTION_MAGIC,
	}PLAYERMOTION;

	typedef enum
	{
		PLAYERSTATE_NOMAL = 0,
		PLAYERSTATE_ATTACK,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_MAGIC,
	}PLAYERSTATE;

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//�R���X�g���N�^
	~CPlayer();//�f�X�g���N�^

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);// ��������

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);	// �e��ݒ�

	void GamePad(void);								// �Q�[���p�b�h����
	void Attack(D3DXVECTOR3 Distance);				// �U���̏���
	void Swordeffect(D3DXVECTOR3 Distance);			// ���̃G�t�F�N�g
	void Magic(void);								// ���@�̏���
	D3DXVECTOR3 EnemyCollision(D3DXVECTOR3 pos);	// �G�Ƃ̔���
	bool HitDamage(int nDamage);					// �_���[�W����

	float GetSpGauge(void) { return m_fSpGauge; }	// sp�Q�[�W�̗ʂ�Ԃ�
private:
	D3DXVECTOR3 m_move;					// �ړ���
	float m_fMotionTime;				// ����ł��Ȃ�����
	float m_fDamageTime;				// �_���[�W���󂯂鎞��
	float m_fSpGauge;					// �K�E�Z���o�����߂̃Q�[�W�̗�
	int m_nSwordEffectTime;				// ���̃G�t�F�N�g�̏o������
	PLAYERSTATE m_Playerstate;			// �v���C���[�̏��
};

#endif