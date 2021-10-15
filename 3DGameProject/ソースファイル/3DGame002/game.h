#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "mode.h"
#include "number.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DEATH_ENEMY_NUM (99) // �G�̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CNumber;

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

	static int GetEnemyDeathTotal(void) { return m_nEnemyDeathTotal; }
private:
	static CPlayer* m_pPlayer;				// �v���C���[
	static int m_nEnemyNum;					// �G�̐�
	static int m_nEnemyDeathTotal;			// �G�|��������
	CNumber* m_apNumber[MAX_NUMBER_CREATE]; // �i���o�[�̃|�C���^
	bool m_bNumberScaling;			// ������傫�����邩�ǂ���
	bool m_bEnemyCreate;					// �G�𐶐����邩�ǂ���
	int m_nEnemyCreateTime;					// �G�𐶐����鎞��
	int m_nDisplace;						// ���������炷����
	int m_nEnemyDeathTotalOld;				// 1�t���[���O�̓G�̑���
};
#endif