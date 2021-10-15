#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NUMBER ("data/TEXTURE/number.png")						// �i���o�[�̃e�N�X�`��
#define MAX_ENEMY_NUM (50)												// �G�̍ő吔
#define MAX_NUMBER_CREATE (2)											// �i���o�[�̐������鐔
#define ENEMYREMAINDER_POS (D3DXVECTOR3(1000.0f, 100.0f, 0.0f))			// ���W
#define ENEMYREMAINDER_SIZE (D3DXVECTOR3(422.5f, 65.5f, 0.0f))			// �T�C�Y
#define ENEMYREMAINDER_POS_DISTANCE (D3DXVECTOR3(35.0f, 0.0f, 0.0f))	// ��������
#define ENEMYREMAINDER_NUM_SIZE (D3DXVECTOR3(70.0f, 95.5f, 0.0f))		// �����̃T�C�Y
#define TWO_DIGITS_SPOT (0)												// �񌅖�
#define ONE_DIGITS_SPOT (1)												// �ꌅ��
#define ENEMYREMAINDER_POS_DISPLACE (D3DXVECTOR3(3.0f, 0.0f, 0.0f))		// ���W�����炷��
#define ENEMYREMAINDER_SIZE_DISPLACE (D3DXVECTOR3(6.0f, 6.0f, 0.0f))	// �T�C�Y�����炷��
#define DISPLACE_TIME (5)												// ���炷����

//=============================================================================
//	�i���o�[�N���X
//=============================================================================
class CNumber : public CScene
{
public:
	CNumber(int nPriority = OBJTYPE_UI);
	~CNumber();

	static CNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif // !_NUMBER_H_