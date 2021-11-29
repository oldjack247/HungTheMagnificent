#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt")	// ���[�V�����̃e�L�X�g

#define ENEMY_SIZE (D3DXVECTOR3(100.0f,250.0f,100.0f))					// �����蔻��T�C�Y
#define ENEMY_LIFE (20)												// �̗�
#define ENEMY_MOVE_SPEED (1.0f)										// �ړ���
#define ENEMY_DAMAGE_MOVE_SPEED (2.0f)								// �_���[�W���󂯂����̈ړ���
#define ENEMY_DISTANCE_PLAYER (100.0f)								// �v���C���[�Ƃ̋���
#define ENEMY_CREATE_NUM (2)										// �G�𐶐����鐔
#define ENEMY_CREATE_ANGLE (360)									// �G�𐶐�����p�x
#define ENEMY_CREATE_DISTANCE (D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))	// �G�𐶐����鋗��
#define ENEMY_CREATE_TIME (20)										// �G�𐶐����鎞��
#define ENEMY_DAMAGE_SRASH_TIME (10.0f)								// �a���ł̃_���[�W���󂯂鎞��
#define ENEMY_DAMAGE_MOTION_TIME (20.0f)							// �_���[�W���[�V�����̎���
#define ENEMY_ATTACK_MOTION_TIME (103.0f)							// �U�����郂�[�V�����̎���
#define ENEMY_ATTACK_UNTIL_TIME (20.0f)								// �U������܂ł̎���
#define ENEMY_ATTACK_COLISION_SIZE (D3DXVECTOR3(5.0f, 5.0f, 5.0f))	// ���̓����蔻��̑傫��
#define ENEMY_DEATH_MOTION_TIME (132.0f)							// ���̓����蔻��̑傫��

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy :public CCharacter
{
public:
	typedef enum
	{
		ENEMYSTATE_NOMAL = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_DEATH,
	}ENEMYSTATE;

	// ���[�V�����̏��
	typedef enum
	{
		ENEMYMOTION_IDLE = 0,
		ENEMYMOTION_RUN,
		ENEMYMOTION_DAMAGE,
		ENEMYMOTION_ATTACK,
		ENEMYMOTION_DEATH,
	}ENEMYMOTION;

	// �󂯂��_���[�W�̎��
	typedef enum
	{
		DAMAGESTATE_SLASH = 0,
		DAMAGESTATE_MAGICCIRCLE,
	}DAMAGESTATE;

	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);	// �R���X�g���N�^
	~CEnemy();										// �f�X�g���N�^

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);	// ��������

	HRESULT Init(void);										// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	bool HitDamage(int nDamage, DAMAGESTATE DamageState);	// �_���[�W���󂯂����̏���
	void EnemyCollision(void);								// �G���m�̓����蔻��
	void Attack(void);										// �U���̏���
	D3DXVECTOR3 PlayerCollision(D3DXVECTOR3 pos);			// �v���C���[�Ƃ̓����蔻��

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);	// �Z�b�g

	ENEMYSTATE GetEnemyState(void) { return m_EnemyState; } // �G�̏�Ԃ̎擾
private:
	D3DXVECTOR3 m_move;			// �ړ���
	float m_fDamageTime;		// �_���[�W���󂯂鎞��
	float m_fMotionTime;		// ���[�V�����̎���
	float m_fAttackTime;		// �U�����鎞��
	bool m_bAttack;				// �U���������ǂ���
	ENEMYSTATE m_EnemyState;	// �G�̏��
};

#endif