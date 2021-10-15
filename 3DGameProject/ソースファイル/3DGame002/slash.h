#ifndef _SLASH_H_
#define _SLASH_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define SLASH_SPEED (5.0f) // �a���̃X�s�[�h
#define NEXT_SLASH_COUNT (5) // �a���̌�ɏo�Ă���J�E���g
#define NEXT_SLASH_LIFE (60) // �a���̃��C�t
#define SLASH_LIFE (120) // �a���̗̑�
#define SLASH_SIZE (D3DXVECTOR3(10.0f, 10.0f, 0.0f)) // �a���̑傫��
#define SLASH_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) // �a���̐F

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "particle.h"

//=============================================================================
// �a���G�t�F�N�g�N���X
//=============================================================================
class CSlash : public CParticle
{
public:
	typedef enum
	{
		TYPE_SLASH_1 = 0,
		TYPE_SLASH_2,
		TYPE_MAX,
	}TYPE;

	CSlash(int nPriority = OBJTYPE_PARTICLE);
	~CSlash();

	static CSlash* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 moveangle, D3DXCOLOR col, int Life, TYPE type);

	HRESULT Init(TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetType(TYPE type) { m_Type = type; }
private:
	D3DXVECTOR3 m_MoveAngle;
	int m_SlashCount;
	TYPE m_Type;
};
#endif