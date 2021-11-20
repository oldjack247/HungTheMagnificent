#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// Scene3d�N���X
//=============================================================================
class CScene3d :public CScene
{
public:
	CScene3d(int nPriority);//�C���N�������g
	~CScene3d();//�f�N�������g
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);		//�`�揈��

	//�e��ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu
	void SetSize(D3DXVECTOR3 size) { m_size = size; }			//�T�C�Y	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`��
	void BindMesh(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	LPD3DXMESH				m_pMesh;
	LPD3DXBUFFER			m_pBuffMat;
	DWORD					m_nNumMat;
	D3DXMATRIX			    m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	int m_nType;
};
#endif //_SCENE3D_H_