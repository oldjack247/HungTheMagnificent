#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "mode.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DEATH_ENEMY_NUM (10) // �G�̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;

//=============================================================================
// �Q�[���N���X
//=============================================================================
class CGame :public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* GetPlayer(void);
	static void SubtractEnemy(void) {
		m_nEnemyNum--; m_nEnemyDeathTotal++;
	}

private:
	static CPlayer* m_pPlayer;				// �v���C���[
	static int m_nEnemyNum;					// �G�̐�
	static int m_nEnemyDeathTotal;			// �G�|��������
	bool m_bEnemyCreate;					// �G�𐶐����邩�ǂ���
	int m_nEnemyCreateTime;					// �G�𐶐����鎞��
	int m_nDisplace;						// ���������炷����
	int m_nEnemyDeathTotalOld;				// 1�t���[���O�̓G�̑���
};
#endif