#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �|�[�Y�N���X��`
//*****************************************************************************
class CPause
{
public:
	// �����o�֐�
	CPause();									// �R���X�g���N�^
	~CPause();									// �f�X�g���N�^

	typedef enum
	{
		PAUSE_RETURN = 0,
		PAUSE_RETRY,
		PAUSE_TITLE,
		PAUSE_END,
		PAUSE_MAX
	}PAUSE;

	HRESULT Init(void);								// ����������
	static void Uninit(void);								// �I������
	static void Update(void);								// �X�V����
	static void Draw(void);								// �`�揈��
	static CPause* Create(void);					// �C���X�^���X����
	static HRESULT Load(void);
	static void Unload(void);
private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	static int m_nSelect;
};

#endif