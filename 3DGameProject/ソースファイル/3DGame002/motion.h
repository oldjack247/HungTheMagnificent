#ifndef _MOTION_H_
#define _MOTION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PARTS (15)			  // ���f���p�[�c�̍ő吔
#define MOTION_MAX (20)			  // �L�[�ő吔
#define MOTION_ANIMATION_NUM (60) // �A�j���[�V������
#define MOTION_KEYSET_MAX (60)	  // �L�[�Z�b�g�ő吔
#define MOTION_KEY_MAX (60)		  // �L�[�ő吔

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct {
	int m_nIndex;			 // ���f���i���o�[
	int m_nParents;			 // ���f���̐e�q�֌W
	D3DXVECTOR3 m_pos;		 // �ʒu
	D3DXVECTOR3 m_posOrigin; // �n�܂�̈ʒu
	D3DXVECTOR3 m_rot;		 // �p�x
}MODELPARENT;

// �A�j���[�V�����L�[�Z�b�g���
typedef struct
{
	D3DXVECTOR3 m_pos[MAX_PARTS];
	D3DXVECTOR3 m_rot[MAX_PARTS];
	int m_nFrame; // 1���[�V�����̃L�[�t���[����
}KEY_INFO;

// �A�j���[�V�������
typedef struct
{
	bool m_nLoop;						   // ���[�v���邩
	int m_nNumKey;						   // ���[�V�����̃L�[��
	KEY_INFO m_KeyInfo[MOTION_KEYSET_MAX]; // �A�j���[�V�����Ɋ܂ރL�[�Z�b�g���
}ANIMATION;

//=============================================================================
// ���[�V�����N���X
//=============================================================================
class CMotion
{
public:
	typedef enum
	{
		TYPE_PLAYER,   // �v���C���[
		TYPE_ENEMY,	   // �G
		TYPE_MAX	   // �ő�l
	}MOTIONTYPE;

	CMotion();
	~CMotion();

	static CMotion* Create(CCharacter* pCharacter, CharacterType Type);

	void Uninit(void);
	void LoadMotion(const char* cText);
	void UpdateMotion(void);

	void SetMotion(int nMotionstate) { m_nMotionState = nMotionstate; }
	void SetType(CharacterType Type) { m_Type = Type; }
	void SetCharacter(CCharacter* pCharacter) { m_pCharacter = pCharacter; }

	void SetPos(int nCount, D3DXVECTOR3 pos) { m_modelParent[nCount].m_pos = pos; }
	void SetRot(int nCount, D3DXVECTOR3 rot) { m_modelParent[nCount].m_rot = rot; }

	int GetMotionState(void) { return m_nMotionState; }
	int GetIndex(int nCount) { return m_modelParent[nCount].m_nIndex; }
	int GetParents(int nCount) { return m_modelParent[nCount].m_nParents; }
	D3DXVECTOR3 GetPos(int nCount) { return m_modelParent[nCount].m_pos; }
	D3DXVECTOR3 GetRot(int nCount) { return m_modelParent[nCount].m_rot; }
private:
	MODELPARENT m_modelParent[MAX_PARTS]; // ���f���̃p�[�c���Ƃ̏��
	ANIMATION m_motion[TYPE_MAX][MOTION_MAX];		  // ���[�V�������Ƃ̏��

	int m_nMotionState;	  // ���[�V�����̍\����
	int m_nMotionOldState; // 1F�O�̃��[�V�����̍\����

	CharacterType m_Type;

	CCharacter* m_pCharacter; // �L�����N�^�[�̃C���X�^���X

	int m_nFreme;  // �t���[����
	int m_nCntKey; // �L�[��

	D3DXVECTOR3 m_NumPos[MAX_PARTS];		// pos�̍���
	D3DXVECTOR3 m_NumRot[MAX_PARTS];		// rot�̍���
	D3DXVECTOR3 m_NumRotDest[MAX_PARTS];	// rot�̍���

	bool m_AngleModifying; // �p�x�̏C����������
};

#endif