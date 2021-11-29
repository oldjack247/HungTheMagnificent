#ifndef _DEBUGCOLLISION_H_
#define _DEBUGCOLLISION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene3d.h"

//=============================================================================
// �f�o�b�N�R���W�����N���X
//=============================================================================
class CDebugCollision : public CScene3d
{
public:

	// �f�o�b�N�̎��
	typedef enum
	{
		TYPE_SPHERE = 0,	    // ����
		TYPE_SQUARE,	        // �l�p
		TYPE_MAX			    // ��ނ̍ő吔
	}TYPE;

	CDebugCollision();
	~CDebugCollision();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CDebugCollision* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[TYPE_MAX];
	static LPD3DXMESH				m_pMesh[TYPE_MAX];
	static LPD3DXBUFFER				m_pBuffMat[TYPE_MAX];
	static DWORD					m_nNumMat[TYPE_MAX];

	int m_nLife;    // ����
	TYPE m_type;    // ���

};

#endif