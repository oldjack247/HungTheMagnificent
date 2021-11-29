#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_RATE (0.05f) // �t�F�[�h�̑��x

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CFade :public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade(int nPriority = OBJTYPE_FADE);	//�R���X�g���N�^
	~CFade();								//�f�X�g���N�^

	static CFade* Create(void);				// �N���G�C�g

	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������	
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

	void FadeIn(void);						// �t�F�[�h�C��
	void FadeOut(void);						// �t�F�[�h�A�E�g

	void SetFade(CManager::MODE mode);	// �t�F�[�h�̐ݒ�
	FADE GetFadeState(void) { return m_fade; }						// �t�F�[�h�̏�Ԃ̃Q�b�g
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR				m_color;		// �F
	CManager::MODE			m_modeNext;		// ���̉��(���[�h)
	FADE					m_fade;			// �t�F�[�h���
};
#endif // !_FADE_H_
