#ifndef _FIRE_H_
#define _FIRE_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define FIRE_SPEED_ADD_SUBTRACT_Z (0.06f)		// Z�̈ړ��ʂ̉��Z�ƌ��Z�p
#define FIRE_SPEED_ADD_Y (0.05f)				// Y�̉��Z�p
#define FIRE_SUBTRACT_COLOR_RED_GREEN (0.03f)	// �ԂƗ΂̉������
#define FIRE_SUBTRACT_COLOR_ALPHA (0.003f)		// �����x�̉������

#define FIR_SIZE (D3DXVECTOR3(50.0f, 50.0f, 0.0f))			// �T�C�Y
#define FIRE_COLOR (D3DXCOLOR(0.6f, 0.9f, 1.0f, 1.0f))		// �F
#define FIRE_LIFE (60)										// ���C�t
#define FIRE_MOVE_Y (1.5f)									// ���C�t
#define FIRE_MOVE_Z (2.2f)									// ���C�t
#define FIRE_CREATE_ANGLE_MAX (360)							// ��������p�x�̍ő�l

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "particle.h"

//=============================================================================
// �t�@�C�A�N���X
//=============================================================================
class CFire : public CParticle
{
public:
	CFire(int nPriority = OBJTYPE_PARTICLE);
	~CFire();

	static CFire* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 move, D3DXCOLOR col, int Life);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif