#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_RATE 0.05f					//����

//=============================================================================
//�N���X
//=============================================================================
class CFade
{
public:
	typedef enum
	{//�t�F�[�h�̏��
		FADE_NONE,										//�ʏ�
		FADE_IN,										//�t�F�[�h�C��
		FADE_OUT,										//�t�F�[�h�A�E�g
		FADE_MAX										//�ő吔

	}FADE;

	CFade();											//�R���X�g���N�^
	~CFade();											//�f�X�g���N�^
	static CFade* Create(D3DXVECTOR3 pos, float size_x, float size_y, CManager::MODE modenext);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y, CManager::MODE modenext);	//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static void SetFade(CManager::MODE modenext);		//�t�F�[�h�̃Z�b�g
	static FADE GetFade(void) { return m_Fade; }
	static void SetFadeSwitch(bool bFadeSwitch);		//�t�F�[�h��؂�ւ�
private:
	static FADE m_Fade;									//�t�F�[�h�̏����������ϐ�
	static CManager::MODE m_ModeNext;					//���[�h�̏����������ϐ�
	static D3DXCOLOR m_col;								//�J���[
	static bool m_bFadeSwitch;							//�t�F�[�h���s�����ǂ���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//�o�b�t�@
};
#endif