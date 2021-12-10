//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3d::CScene3d(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pTexture = NULL;
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_nNumMat = 0;
	D3DXMatrixIdentity(&m_mtxWorld);

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3d::~CScene3d()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3d::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3d::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3d::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat = nullptr;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixScaling(&mtxSize, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxSize);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pBuffMat != NULL)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾����
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	pDevice->SetTexture(0, m_pTexture);

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_pMesh != NULL)
		{
			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	pDevice->SetTexture(0, NULL);
}

//================================================================================
// �e��ݒ�
//================================================================================

//=============================================================================
// �e�N�X�`��
//=============================================================================
void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene3d::BindMesh(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat)
{
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
}
