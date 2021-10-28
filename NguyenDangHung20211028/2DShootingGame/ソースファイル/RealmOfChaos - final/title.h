#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "scene2d.h"
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSound;

//=============================================================================
//�N���X
//=============================================================================
class CTitle : public CScene
{
public:
	typedef enum
	{//�^�C�g���e�N�X�`���̎��
		TITLETYPE_BG = 0,										//�w�i
		TITLETYPE_NAME,											//�Q�[���̖��O
		TITLETYPE_START,										//�X�^�[�g�{�^��
		TITLETYPE_MAX
	}TITLETYPE;

	CTitle(int nPriority = PRIORITYTYPE_BG);					//�R���X�g���N�^
	~CTitle();													//�f�X�g���N�^
	static HRESULT Load(void);									//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);									//�e�N�X�`���̔j��
	static CTitle* Create(D3DXVECTOR3 pos, float size_x, float size_y);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TITLETYPE_MAX];		//�e�N�X�`��
	TITLETYPE m_titletype;										//�^�C�g��
	CScene2d* m_apScene2D[TITLETYPE_MAX];						//Scene2D�̃|�C���^										
	D3DXVECTOR3 m_pos;											//�ʒu
	D3DXCOLOR m_col;											//�F
	CSound* m_pSound;											//���̃|�C���^
};
#endif
