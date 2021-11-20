#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//�}�N����`
//=============================================================================
#define COUNT_WAIT_FINISH_GAME (30)

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CPlayer;
class CEnemy;
class CBg;
class CScore;
class CLife;
class CEffect;
class CSound;
class CItem;
class CWarning;
class CBulletEffect;
class CMinion;

//=============================================================================
//�N���X
//=============================================================================
class CGame : public CScene
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,										//�������Ă��Ȃ����
		GAMESTATE_NORMAL,										//�ʏ���
		GAMESTATE_END,											//�Q�[���I�����
		GAMESTATE_MAX
	}GAMESTATE;

	CGame();													//�R���X�g���N�^
	~CGame();													//�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��
	void SetGameState(GAMESTATE state);							//�Z�b�g
	GAMESTATE GetGameState(void) { return m_gamestate; };		//�Q�[����Ԃ̏��擾
	static CEnemy* GetEnemy(void);								//�G�̏��擾�p
	static void SetScore(int nScore);							//�X�R�A�̃Z�b�g
	static CScore* GetScore(void) { return m_pScore; }			//�X�R�A�擾�p
	static void SetPlayerLife(int nLife);						//���C�t�̃Z�b�g
	static void Set1FBossSpawn(bool bSpawn);					//�X�|�[��������
	static void Set2FEnemySpawn(bool b2Spawn);					//�X�|�[��������
	static void Set3FEnemySpawn(bool b2Spawn);					//�X�|�[��������
private:
	D3DXVECTOR3 m_pos;											//�ʒu
	GAMESTATE m_gamestate;										//�Q�[����� 
	int m_nCounterGameState;									//�Q�[����ԃJ�E���g
	int n1FEnemySpawnTime;										//1F�̓G�𐶐����鎞��
	int n2FEnemySpawnTime;										//2F�̓G�𐶐����鎞��
	int n3FEnemySpawnTime;										//3F�̓G�𐶐����鎞��
	static CPlayer* m_pPlayer;									//�v���C���[�̃|�C���^
	static CEnemy* m_pEnemy;									//�G�̃|�C���^
	static CBg* m_pBg;											//BG�̃|�C���^											
	static CScore* m_pScore;									//�X�R�A�̃|�C���^
	static CLife* m_pLife;										//���C�t�o�[�̃|�C���^
	static CEffect* m_pEffect;									//�G�t�F�N�g�̃|�C���^
	static CItem* m_pItem;										//�A�C�e���̃|�C���^
	static CWarning* m_pWarning;								//Warning					
	static CMinion* m_pMinion;
	CSound* m_pSound;											//�T�E���h�̃|�C���^
	static bool m_b1FBossSpawn;									//1F�̃{�X���X�|�[�����邩�ǂ���
	static bool m_b2FEnemySpawn;								//2F�̃{�X���X�|�[�����邩�ǂ���
	bool b2FBossAwakening;										//2F�̃{�X���o���������ǂ���	
	static bool m_b3FEnemySpawn;								//3F�̃{�X���X�|�[�����邩�ǂ���										
};
#endif