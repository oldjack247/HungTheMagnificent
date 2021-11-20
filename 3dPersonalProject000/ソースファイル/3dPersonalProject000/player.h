#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"5

//=============================================================================
// �}�N����`
//=============================================================================
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt")	// ���[�V�����̃e�L�X�g
#define PLAYER_LIFE (50)											// �v���C���[�̃��C�t
#define PLAYER_ROT_SPEED (0.1f)										// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_SP_MAX (20)											// �v���C���[��SP
#define PLAYER_DEFAULT_POS (D3DXVECTOR3(0.0f, 32.0f, 0.0f))			// ���W
#define PLAYER_DEFAULT_ROT (D3DXVECTOR3(0.0f, 1.5f, 0.0f))			// ��]
#define PLAYER_DEFAULT_SIZE (D3DXVECTOR3(150.0f, 150.0f, 150.0f))	// �傫��
#define PLAYER_MOVE_SPEED (4.0f)									// �������x
#define PLAYER_ATTACK_MOVE_SPEED (0.5f)								// �U���������̑��x
#define PLAYER_DAMAGE_TIME (120.0f)									// �v���C���[���_���[�W���󂯂鎞��
#define PLAYER_MOVE_MAP_LIMIT (3000.0f)								// �v���C���[�̈ړ��ł���͈�
#define SWORD_COLISION_SIZE (D3DXVECTOR3(5.0f, 5.0f, 5.0f))		// ���̓����蔻��̑傫��
#define MOTION_SLASH_FRAME (75.0f)									// �a�郂�[�V�����̃t���[��
#define MOTION_SLASH_FRAME_COLLISION_START (8.0f)					// �a�郂�[�V�����̃G�t�F�N�g���o��܂ł̃t���[��
#define MOTION_MAGICCIRCLE_FLAME (380.0f)							// ���@�w���o�����[�V�����̃t���[��
#define MOTION_MAGICCIRCLE_CREATE_START (70.0f)						// ���@�w���o���܂ł̃t���[��
#define SUBTRACT_FLAME (1.0f)										// ���炷�t���[���̗�
#define PLAYER_INVINCIBLE_TIME (150)								// ���G����

// �U�����[�V�����̏��
#define PLAYER_STAND_ATTACK_KEY_000		(2)					// 1�i�ڂ̍U�����L���ȃL�[
#define PLAYER_NEXT_ATTACK_KEY_000		(3)					// ���̍U�����\�ȃL�[
#define PLAYER_STAND_ATTACK_KEY_001		(2)					// 2�i�ڂ̍U�����L���ȃL�[
#define PLAYER_NEXT_ATTACK_KEY_001		(2)					// ���̍U�����\�ȃL�[
#define PLAYER_STAND_ATTACK_KEY_002		(2)					// 3�i�ڂ̍U�����\�ȃL�[
#define PLAYER_NEXT_ATTACK_KEY_002		(3)					// ���̍U���̔h���L�[

// ������[�V�����̏��
#define DODGE_RANGE						(6.5f)			// �v���C���[�̉���
#define MOTION_DODGE_FRAME				(40.0f)			// �������
#define MOTION_DODGE_END_FRAME			(8.0f)			// ����̉�������

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
		PLAYERMOTION_ATTACK000,
		PLAYERMOTION_DODGE,
	}PLAYERMOTION;

	typedef enum
	{
		PLAYERSTATE_NOMAL = 0,
		PLAYERSTATE_ATTACK,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_DODGE
	}PLAYERSTATE;

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//�R���X�g���N�^
	~CPlayer();//�f�X�g���N�^

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);// ��������

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);	// �e��ݒ�

	void Keyboard(void);							// �}�E�X�ƃL�[�{�[�h����
	void GamePad(void);								// �Q�[���p�b�h����
	void UpdateRot(void);							// �p�x�̍X�V����
	void Attack(D3DXVECTOR3 Distance);				// �U���̏���
	void Attack2(D3DXVECTOR3 Distance);				// �U��2�̏���
	void Attack3(D3DXVECTOR3 Distance);				// �U��32�̏���
	void Dodge(void);								// ����̏���
	void Swordeffect(D3DXVECTOR3 Distance);			// ���̃G�t�F�N�g
	D3DXVECTOR3 EnemyCollision(D3DXVECTOR3 pos);	// �G�Ƃ̔���
	bool HitDamage(int nDamage);					// �_���[�W����
private:
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXVECTOR3 m_rotDest;				// ��](�ڕW�l)
	float m_fMotionTime;				// ����ł��Ȃ�����
	float m_fDamageTime;				// �_���[�W���󂯂鎞��
	int m_nSwordEffectTime;				// ���̃G�t�F�N�g�̏o������
	bool m_bDodge;						// ����̃t���O
	int m_nDodgeCounter;				// ����̃J�E���^�[
	PLAYERSTATE m_Playerstate;			// �v���C���[�̏��
};

#endif