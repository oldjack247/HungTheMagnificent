#ifndef _MAGICCIRCLE_H_
#define _MAGICCIRCLE_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define MAGICCERCLE_DEFAULT_SIZE (D3DXVECTOR3(200.0f, 200.0f, 0.0f))			// ���@�w�̏����T�C�Y
#define MAGICCERCLE_DEFAULT_ROT (D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f))	// ���@�w�̏����p�x
#define MAGICCERCLE_DEFAULT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			// ���@�w�̏����F
#define MAGICCERCLE_FLAMECREATE_NUM (6)											// ���@�w�̉��̐������鐔
#define MAGICCERCLE_ENEMY_DEFAULT_SIZE (D3DXVECTOR3(200.0f, 200.0f, 0.0f))		// ���@�w�̏����T�C�Y

#define MAGICCERCLE_ENEMY_COUNTANIM (11)	// �e�N�X�`���̉��̕���
#define MAGICCERCLE_ENEMY_PATTERNANIM (1)	// �e�N�X�`���̏c�̕���
#define MAGICCERCLE_ENEMY_TIMEANIM (4)		// �A�j���[�V�����̎���
#define MAGICCERCLE_ENEMY_CREATE_TIME (12)	// �G���o������

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "particle.h"

//=============================================================================
// �t�@�C�A�N���X
//=============================================================================
class CMagiccercle : public CParticle
{
public:
	typedef enum
	{
		MAGICCIRCLETYPE_PLAYER = 0,
		MAGICCIRCLETYPE_ENEMY,
	}MAGICCIRCLETYPE;

	CMagiccercle(int nPriority = OBJTYPE_PARTICLE);
	~CMagiccercle();

	static CMagiccercle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int Life, MAGICCIRCLETYPE type);

	HRESULT Init(MAGICCIRCLETYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif