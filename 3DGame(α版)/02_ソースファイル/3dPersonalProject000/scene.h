#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_DEBUG,
		OBJTYPE_SKYBOX,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_PARTICLE,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_NONE);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }

	//�������z�֐�
	virtual HRESULT Init(void) = 0;	//����������
	virtual void Uninit(void) = 0;	//�I������
	virtual void Update(void) = 0;	//�X�V����
	virtual void Draw(void) = 0;		//�`�揈��

	static void UpdateAll(void);	//�X�V�܂Ƃ�
	static void DrawAll(void);		//�`��܂Ƃ�
	static void ReleaseAll(void);	//�I���܂Ƃ�

	static void DesignationReleaseAll(OBJTYPE type);
	static void SetbUpdate(bool bUpdate, OBJTYPE type);

	void ConnectionList(void); // �f�[�^�̂Ȃ��Ȃ���

	static bool GetbUpdate(OBJTYPE type) { return m_bUpdate[type]; }
	static CScene* GetSceneTop(int nPriority) { return m_pTop[nPriority]; } // �V�[���̃f�[�^��Ԃ�
	CScene* GetSceneNext(void) { return m_pNext; } // �V�[���̃l�N�X�g�̃f�[�^��Ԃ�

protected:
	void Release(void);

private:
	OBJTYPE m_objType;					// �I�u�W�F�N�g�̎��
	static CScene* m_pTop[OBJTYPE_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene* m_pCur[OBJTYPE_MAX];	// ���݂̃I�u�W�F�N�g�ւ̃|�C���^
	CScene* m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene* m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nObj;							// �I�u�W�F�N�g�̃i���o�[
	bool m_bDeath;						// ���S�t���O
	static bool m_bUpdate[OBJTYPE_MAX]; // �X�V���邩�ǂ���
	static bool m_bDraw[OBJTYPE_MAX];	// �`�悷�邩�ǂ���
};

#endif // !_RENDERER_H_