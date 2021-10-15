#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PARTS (15) // ���f���̃p�[�c�̍ő吔
#define MAX_MATERIAL (50)

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CReticle;

typedef enum
{
	CHARACTERTYPE_PLAYER = 0,
	CHARACTERTYPE_ENEMY,
	CHARACTERTYPE_MAX
}CharacterType;

//=============================================================================
// �L�����N�^�[�N���X
//=============================================================================
class CCharacter :public CScene
{
public:
	CCharacter(int nPriority);//�R���X�g���N�^
	~CCharacter();//�f�X�g���N�^

	virtual HRESULT Init(void);//����������
	virtual void Uninit(void);//�I������
	virtual void Update(void);//�X�V����
	virtual void Draw(void);//�`�揈��

	HRESULT LoadInitialPosition(char* cFileName);
	void LoadMotion(char* FileName);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetModelPartPos(int nNumPart, D3DXVECTOR3 pos) { m_apModel[nNumPart]->Setpos(pos); }
	void SetModelPartRot(int nNumPart, D3DXVECTOR3 rot) { m_apModel[nNumPart]->Setrot(rot); }
	void SetModelPartSize(int nNumPart, D3DXVECTOR3 size) { m_apModel[nNumPart]->Setsize(size); }
	void SetModelPartsNum(int nPartNum) { m_nPartsNum = nPartNum; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetType(CharacterType Type) { m_Type = Type; }

	//�󂯓n������
	D3DXVECTOR3 GetPos(void) { return m_pos; }//�ꏊ
	D3DXVECTOR3 GetRot(void) { return m_rot; }//�p�x
	D3DXVECTOR3 GetSize(void) { return m_size / 2; }//�p�x
	D3DXVECTOR3 GetModelPartPos(int nNumPart) { return m_apModel[nNumPart]->GetPos(); }
	D3DXVECTOR3 GetModelPartRot(int nNumPart) { return m_apModel[nNumPart]->GetRot(); }
	D3DXVECTOR3 GetModelPartSize(int nNumPart) { return m_apModel[nNumPart]->GetSize(); }
	CharacterType GetType(void) { return m_Type; }
	CMotion* GetMotion(void) { return m_pMotion; }
	CModel* GetModelParts(int nNumPart) { return m_apModel[nNumPart]; }
	CCharacter* GetCharacter(void) { return this; }
	int GetLife(void) { return m_nLife; }
private:
	char* m_apFileName[MAX_PARTS];	  // �t�@�C���̖��O
	char* m_apTextureFileName[MAX_PARTS]; //�e�N�X�`���̃t�@�C���̖��O

	int m_nldxModelNum[MAX_PARTS];			 // ���f���i���o�[
	int m_nldxModelParent[MAX_PARTS];			 // ���f���̐e�q�֌W

	D3DXVECTOR3 m_Beginpos[MAX_PARTS];
	D3DXVECTOR3 m_Beginrot[MAX_PARTS];

	int m_nPartsNum;

	D3DXVECTOR3 m_pos;					// �ꏊ
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;
	CharacterType m_Type;
	CMotion* m_pMotion;					// ���[�V�����N���X�̃|�C���^
	CModel* m_apModel[MAX_PARTS]; // ���f���N���X�̃|�C���^

	int m_nLife;
};

#endif