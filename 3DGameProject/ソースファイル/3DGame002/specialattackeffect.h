#ifndef _SPESIALATTACKEFFECT_H_
#define _SPESIALATTACKEFFECT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"particle.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SPECIALATTACKEFFECT_COUNTANIM (10)	// �e�N�X�`���̉��̕���
#define SPECIALATTACKEFFECT_PATTERNANIM (1) // �e�N�X�`���̏c�̕���
#define SPECIALATTACKEFFECT_TIMEANIM (4)	// �A�j���[�V�����̎���

#define SPECIALATTACKEFFECT_SIZE (D3DXVECTOR3(300.0f, 300.0f, 0.0f))	// �T�C�Y
#define SPECIALATTACKEFFECT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// �F

//=============================================================================
// �X�y�V�����A�^�b�N�G�t�F�N�g�N���X
//=============================================================================
class CSpecialattackeffect : public CParticle
{
public:
	CSpecialattackeffect();
	~CSpecialattackeffect();

	static CSpecialattackeffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int Life);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif