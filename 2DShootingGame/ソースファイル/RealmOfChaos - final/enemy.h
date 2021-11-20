#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define ENEMY_SIZE 100.0f					//�ʏ�̓G�̃T�C�Y
#define ENEMY_GHOST_SIZE 300.0f				
#define MAX_ENEMY 256						//�G�̍ő吔
#define ENEMY_2FGHOST_AVATAR_SIZE 100.0f	//�������̕��g
#define ENEMY_1FBOSS_SIZE 400.0f			//1�t���A�ڂ̃{�X�̃T�C�Y
#define ENEMY_2FBOSS_SIZE 300.0f			//2�t���A�ڂ̃{�X�̃T�C�Y
#define ENEMY_3FBOSS_SIZE 400.0f			//3�t���A�ڂ̃{�X�̃T�C�Y
#define ENEMY_BOSS_FOG   300.0f
#define BOSS_AVATAR_SIZE 120.0f
#define ENEMY_NOMAL_LIFE 2					//�ʏ�̓G�̃��C�t
#define ENEMY_3F_LIFE 5						//�ʏ�̓G�̃��C�t
#define ENEMY_1FBOSS_LIFE 80				//1�t���A�ڂ̃{�X�̃��C�t
#define ENEMY_2FBOSS_LIFE 20000				//�o������O�̓G�̃��C�t
#define ENEMY_2FBOSS_AWAKENING_LIFE 300		//�o���������Ƃ̃��C�t
#define ENEMY_3FBOSS_LIFE 500				//1�t���A�ڂ̃{�X�̃��C�t
#define COUNT_BOSS_AVATAR 20				//�o�����鐔
#define NOMAL_ENEMY_SCORE 300				//���ʂ̓G�̃X�R�A
#define FIRST_BOSS_SCORE 2000				//1F�̃{�X�̃X�R�A
#define SECOND_BOSS_SCORE 3000				//2F�̃{�X�̃X�R�A
#define THIRD_BOSS_SCORE 4000				//3F�̃{�X�̃X�R�A

//=============================================================================
//�O���錾
//=============================================================================
class CSound;
class CGameClear;

//=============================================================================
//�N���X
//=============================================================================
class CEnemy : public CScene2d
{
public:
	CEnemy(int nPriority = PRIORITYTYPE_ENEMY);
	~CEnemy();
	typedef enum
	{//�G�̎��
		TYPE_ENEMY_HARPY,					//�G
		TYPE_ENEMY_BOSS_FOG,				//
		TYPE_ENEMY_GHOST,					//���΂�
		TYPE_ENEMY_1FBOSS,					//�{�X
		TYPE_ENEMY_2FGHOST,					//2F�̂��΂�
		TYPE_ENEMY_2FBAT,					//��
		TYPE_ENEMY_2FGHOST_AVATAR,			//���Ȃ���|�����炻������o�Ă�����
		TYPE_ENEMY_2FBOSS,					//�{�X
		TYPE_ENEMY_2FBOSS_AVATAR,			//�{�X����łĂ��鏬�����{�X
		TYPE_ENEMY_3FBOSS,
		TYPE_ENEMY_3FGHOST,
		TYPE_ENEMY_3FDEMON,
		TYPE_ENEMY_MAX
	}TYPEENEMY;

	typedef enum
	{//�s���̎��
		ACTION_MOVE_NONE = 0,				//�ʏ���
		ACTION_MOVE_LEFT,					//���Ɉړ����Ă���Ƃ�
		ACTION_MOVE_RIGHT,					//�E�Ɉړ����Ă���Ƃ�
		ACTION_MOVE_BACK,					//�߂�G
		ACTION_ENEMY2_DROP_ITEM,			//���΂�����������Ƃ�
		ACTION_CIRCLE_RIGHT,				//�E��]
		ACTION_CIRCLE_LEFT,					//����]
		ACTION_2FBOSS_AWAKENING,			//2F�{�X�̊o�������Ƃ�
		ACTION_MAX
	}ENEMY_ACTION_PATTERN;

	static HRESULT Load(void);										//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);										//�e�N�X�`���̔j��
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, int nLife, TYPEENEMY Type, ENEMY_ACTION_PATTERN MoveType);				//��������			
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, int nLife, TYPEENEMY Type, ENEMY_ACTION_PATTERN MoveType);				//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	void SetLife(int nLife);										//�_���[�W����
	int GetLife(void);												//�̗͎擾
	int GetRandNum(int min, int max);								//�����_������
	bool HitCcollision(D3DXVECTOR3 Pos, float size_x, float size_y);//�����蔻��
	static void Set2FBossAwakening(bool b2FBossAwakening);			//�Z�b�g			
private:
	D3DXVECTOR3 m_move;												//�ړ���
	D3DXVECTOR3 m_pos;												//�ʒu
	static D3DXVECTOR3 m_2FBossPos;									//2�t���A�ڂ̈ʒu
	D3DXCOLOR m_col;												//�F
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_ENEMY_MAX];			//�e�N�X�`��
	int m_nLife;													//�̗�
	int m_nCntEnemy;												//�J�E���^
	int m_nCnt2FBoss;												//�{�X���e�����^�C�~���O
	int nCnt2FBossChange;											//�o���G�t�F�N�g���o������
	int m_nCounterAnim;												//�J�E���^�[
	int m_nPatternAnim;												//�p�^�[��NO.
	static int nCnt2FBossAvatar;									//���g��|������
	float m_fAngle;													//�p�x
	TYPEENEMY m_type;												//�G�̎��
	ENEMY_ACTION_PATTERN m_movetype;								//�����̎��
	bool m_b1FBossInvisible;										//�������ǂ���											
	bool m_b2FBossBullet;											//�{�X�����g���o�����ǂ���
	bool m_b2FBossAttack;											//�o���������Ƃ̍U��
	static bool m_b2FBossAwakening;									//�o���������ǂ���
	static CGameClear* m_pGameClear;									//GameClear
	CSound* m_pSound;												//�T�E���h�̃|�C���^
};
#endif