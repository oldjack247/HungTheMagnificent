//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_MoveBg = D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CScene2d::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	VERTEX_2D* pVtx;

	m_pos = pos;

	//���_�o�b�t�@����
	pRenderer->GetDevice()->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//(�Œ�)
		FVF_VERTEX_2D,//(�Œ�)
		D3DPOOL_MANAGED,//(�Œ�)
		&m_pVtxBuff,//�ϐ������ς��ƕύX���K�v
		NULL);//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

	//���_���W�̐ݒ�(�E���)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (size_x / 2), m_pos.y - (size_y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (size_x / 2), m_pos.y - (size_y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (size_x / 2), m_pos.y + (size_y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (size_x / 2), m_pos.y + (size_y / 2), 0.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CScene2d::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CScene2d::Update(void)
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void CScene2d::Draw(void)
{
	CRenderer* pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	if (pRenderer != NULL)
	{
		//���_�o�b�t�@���f�o�C�X�̃X�g���[���Ƀo�C���h
		pRenderer->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pRenderer->GetDevice()->SetTexture(0, m_pTexture);
		//�|���S���̕`��
		pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
//pos�̃Z�b�g
//=============================================================================
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//�ʒu�擾�p
//=============================================================================
D3DXVECTOR3 CScene2d::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
//�F�̃Z�b�g
//=============================================================================
void CScene2d::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �F�̎擾�p
//=============================================================================
D3DXCOLOR CScene2d::GetCol(void)
{
	return m_col;
}

//=============================================================================
// �e�N�X�`���̃Z�b�g
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2d::MoveBg(D3DXVECTOR2 move, CScene2d::BGOPRETION bg)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (bg)
	{
	case BG_MOVE:

		m_MoveBg += move;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f) + m_MoveBg;
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f) + m_MoveBg;
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f) + m_MoveBg;
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f) + m_MoveBg;

		break;

	case BG_INPUT:

		break;

	default:
		break;
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
