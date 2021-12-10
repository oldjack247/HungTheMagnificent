#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �r���{�[�h�N���X
//=============================================================================
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority);
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Update(float fangle);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetAnimation(int nCountAnim, int nPatternAnim, int nTime) {
		m_nCountAnim = nCountAnim; m_nPatternAnim = nPatternAnim;
		m_nTime = nTime; m_Animation = true;
	}
	void SetAdditiveSynthesis(void) { m_bAdditiveSynthesis = true; }
	void SetZbuffer(void) { m_bUseZbuf = true; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXCOLOR GetColor(void) { return m_col; }
	int GetLife() { return m_nLife; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pBuffMat;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	int m_nLife;

	float                              m_fTexX1;      //�e�N�X�`��X���W
	float                              m_fTexX2;      //�e�N�X�`��X2���W
	float                              m_fTexY1;      //�e�N�X�`��Y���W
	float                              m_fTexY2;      //�e�N�X�`��Y���W
	D3DXMATRIX m_mtxWorld;					// �}�g���b�N�X

	bool m_Animation;	// �A�j���[�V�������邩
	int m_nCountAnim;	// ���̕���
	int m_nPatternAnim;	// �c�̕���
	int m_nTime;		// �A�j���[�V�����ɂ����鎞��

	int m_nCountAnimChange;		// ���̕����̌v�Z
	int m_nPatternAnimChange;	// �c�̕����̌v�Z
	int m_nTimeChange;			// �A�j���[�V�����ɂ����鎞�Ԃ̌v�Z

	bool m_bAdditiveSynthesis;	// ���Z�������邩
	bool m_bUseZbuf;			// Z�o�b�t�@���g����
};
#endif