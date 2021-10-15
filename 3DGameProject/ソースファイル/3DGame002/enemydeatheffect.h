#ifndef _ENEMYDEATHEFFECT_H_
#define _ENEMYDEATHEFFECT_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMYDEATHEFFEC_DEFAULT_SIZE (D3DXVECTOR3(80.0f, 80.0f, 0.0f))		// �G�����񂾃G�t�F�N�g�̂̏����T�C�Y
#define ENEMYDEATHEFFEC_DEFAULT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// �G�����񂾃G�t�F�N�g�̂̏����J���[
#define ENEMYDEATHEFFEC_DEFAULT_SPEED (1.5f)								// �G�����񂾃G�t�F�N�g�̂̏����X�s�[�h
#define ENEMYDEATHEFFEC_SUBTRACT_COLOR_ALPHA (0.01f)						// �����x�̉������
#define ENEMYDEATHEFFEC_COUNTANIM (13)	// �e�N�X�`���̉��̕���
#define ENEMYDEATHEFFEC_PATTERNANIM (1) // �e�N�X�`���̏c�̕���
#define ENEMYDEATHEFFEC_TIMEANIM (4)	// �A�j���[�V�����̎���
#define ENEMYDEATHEFFEC_CREATE_NUM (6)	// ��鐔

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "particle.h"

//=============================================================================
// �t�@�C�A�N���X
//=============================================================================
class CEnemydeatheffect : public CParticle
{
public:
	CEnemydeatheffect(int nPriority = OBJTYPE_PARTICLE);
	~CEnemydeatheffect();

	static CEnemydeatheffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 move, D3DXCOLOR col, int Life);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif