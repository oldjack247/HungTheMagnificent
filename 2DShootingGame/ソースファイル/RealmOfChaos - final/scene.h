#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_SCENE 1280									//�V�[���̍ő吔

//=============================================================================
//�N���X
//=============================================================================
class CScene
{//��{�N���X
public:
	typedef enum
	{//�`��D�揇��
		PRIORITYTYPE_BG = 0,							//BG
		PRIORITYTYPE_EFFECT,							//�G�t�F�N�g
		PRIORITYTYPE_ENEMY,								//�G
		PRIORITYTYPE_PLAYER,							//�v���C���[
		PRIORITYTYPE_BULLET,							//�e
		PRIORITYTYPE_EXPLOSION,							//����
		PRIORITYTYPE_UI,								//UI
		PRIORITYTYPE_WARNING,							//Warning
		PRIORITYTYPE_GAMECLEAR,
		PRIORITYTYPE_MINION,
		PRIORITYTYPE_MAX								//�ő吔
	}PRIORITYTYPE;

	typedef enum
	{
		OBJTYPE_NONE = 0,								//�ʏ�
		OBJTYPE_PLAYER,									//�v���C���[
		OBJTYPE_ENEMY,									//�G
		OBJTYPE_BULLET,									//�e				
		OBJTYPE_ITEM,									//�A�C�e��
		OBJTYPE_BG,										//BG
		OBJTYPE_LIFE,
		OBJTYPE_MINION,
		OBJTYPE_MAX										//�ő吔
	}OBJTYPE;

	CScene(int nPriority = 0);							//�R���X�g���N�^
	virtual ~CScene();									//�f�X�g���N�^
	virtual HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y) = 0;	//����������
	virtual void Uninit(void) = 0;						//�I������
	virtual void Update(void) = 0;						//�X�V����
	virtual void Draw(void) = 0;						//�`�揈��
	static void UpdateAll(void);						//�S�����X�V
	static void DrawAll(void);							//�S����`��
	static void ReleaseAll(void);						//�S���������[�X
	OBJTYPE GetObjType(void) { return m_nType; }		//�I�u�W�F�N�g�^�C�v�̎擾�֐�
	void SetObjType(OBJTYPE type);						//�I�u�W�F�N�g�^�C�v�̃Z�b�g�֐�
	static CScene* GetScene(int nPriority, int nNum);
	int GetPriority(void) { return m_nPriority; }
	void Release(void);									//�I�u�W�F�N�g�������[�X

private:
	static CScene* m_apScene[PRIORITYTYPE_MAX][MAX_SCENE];	//�V�[���̃|�C���^
	static int m_nNumAll;								//�S�ẴV�[��
	int m_nID;											//�����Ǘ�����
	int m_nPriority;									//�D�揇��
	OBJTYPE m_nType;									//�I�u�W�F�N�g�̎��
};
#endif