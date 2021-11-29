//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bg.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_BG] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
//�e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CBg::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	if (pRenderer == NULL)
	{
		pRenderer = CManager::GetRenderer();
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/Texture/BG/bg102.png", &m_pTexture[CBg::BG_SPACE_1]);

	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/Texture/BG/bg101.png", &m_pTexture[CBg::BG_SPACE_2]);

	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/Texture/BG/bg102.png", &m_pTexture[CBg::BG_SPACE_3]);

	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/Texture/BG/bg102.png", &m_pTexture[CBg::BG_SUN]);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//��������
//=============================================================================
CBg* CBg::Create(D3DXVECTOR3 pos, int nPriority, BG_MOVETYPE MoveType)
{
	//�ϐ��錾
	CBg* pBg;

	//����������
	pBg = new CBg(nPriority);

	//����������
	pBg->Init(pos, SCREEN_WIDTH, SCREEN_HEIGHT);

	pBg->SetObjType(OBJTYPE_BG);

	pBg->SetBgType(MoveType);

	return pBg;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//�|���S���̐���
		m_apScene2D[nCnt] = new CScene2d(PRIORITYTYPE_BG());
		m_apScene2D[nCnt]->Init(pos, size_x, size_y);
		m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
		m_apScene2D[nCnt]->SetObjType(OBJTYPE_BG);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CBg::Update(void)
{
	VERTEX_2D* pVtx;

	switch (m_BgType)
	{
	case BG_MOVE:
		//���ꂽ�������A�����A����
		m_apScene2D[CBg::BG_SPACE_1]->MoveBg(D3DXVECTOR2(0.0f, -0.005f), CScene2d::BG_MOVE);
		m_apScene2D[CBg::BG_SPACE_2]->MoveBg(D3DXVECTOR2(0.0f, -0.003f), CScene2d::BG_MOVE);
		m_apScene2D[CBg::BG_SPACE_3]->MoveBg(D3DXVECTOR2(0.0f, -0.001f), CScene2d::BG_MOVE);

		break;
	default:

		break;
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CBg::Draw(void)
{
}
