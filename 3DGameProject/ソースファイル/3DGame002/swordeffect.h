#ifndef _SWORDEFFECT_H_
#define _SWORDEFFECT_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define SWORD_EFFECT_NUM (10)									// ���̃G�t�F�N�g�̏o����
#define SWORD_EFFECT_LIFE (120)									// ���̃G�t�F�N�g�̃��C�t
#define SWORD_EFFECT_SIZE (D3DXVECTOR3(2.0f, 2.0f, 0.0f))		// ���̃G�t�F�N�g�̑傫��
#define SWORD_EFFECT_COLOR (D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))	// ���̃G�t�F�N�g�̐F
#define SWORD_EFFECT_ALPHA_SUBTRACT (0.01f)					// �����x�����炷��
#define SWORD_EFFECT_SPEED (5.0f)								// �����x
#define SWORD_EFFECT_CREATE_TIME (10)							// �������鎞��

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "particle.h"

//=============================================================================
// �a���G�t�F�N�g�N���X
//=============================================================================
class CSwordeffect : public CParticle
{
public:
	CSwordeffect(int nPriority = OBJTYPE_PARTICLE);
	~CSwordeffect();

	static CSwordeffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 moveangle, D3DXCOLOR col, int Life);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_MoveAngle;
};
#endif