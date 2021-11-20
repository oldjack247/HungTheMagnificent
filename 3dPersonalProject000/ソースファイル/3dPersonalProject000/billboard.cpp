//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================	
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "billboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pBuffMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 0;
	m_fTexX1 = 0.0f;
	m_fTexX2 = 1.0f;
	m_fTexY1 = 0.0f;
	m_fTexY2 = 1.0f;
	m_Animation = false;
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_nTime = 0;
	m_nCountAnimChange = 0;
	m_nPatternAnimChange = 0;
	m_nTimeChange = 0;
	m_bAdditiveSynthesis = false;
	m_bUseZbuf = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBillboard::Init(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,														//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pBuffMat,														//���_�o�b�t�@�ւ̃|�C���^
		NULL)))																//NULL�ɐݒ�
	{
		return E_FAIL;
	}

	//���_����ݒ�
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pBuffMat->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / 2), (m_size.y / 2), (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3((+m_size.x / 2), (m_size.y / 2), (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / 2), (-m_size.y / 2), (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3((+m_size.x / 2), (-m_size.y / 2), (m_size.z / 2));

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	if (m_Animation == true)
	{
		m_nCountAnimChange++;

		if (m_nCountAnim % m_nCountAnimChange == 0)
		{
			m_nCountAnimChange = 0;
			m_nPatternAnimChange++;
			if (m_nPatternAnim % m_nPatternAnimChange == 0)
			{
				m_nPatternAnimChange = 0;
			}
		}

		// ���_����ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnimChange) * m_fTexX1, (float)(1.0f / m_nPatternAnim) * m_fTexY1);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnimChange) * m_fTexX2, (float)(1.0f / m_nPatternAnim) * m_fTexY1);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnimChange) * m_fTexX1, (float)(1.0f / m_nPatternAnim) * m_fTexY2);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnimChange) * m_fTexX2, (float)(1.0f / m_nPatternAnim) * m_fTexY2);

		m_nTimeChange = 0;
	}

	else
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_fTexX1, m_fTexY1);
		pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY1);
		pVtx[2].tex = D3DXVECTOR2(m_fTexX1, m_fTexY2);
		pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pBuffMat->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBillboard::Uninit(void)
{
	// �j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBillboard::Update(void)
{
	//���_����ݒ�
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pBuffMat->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / 2), (m_size.y / 2), (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3((+m_size.x / 2), (m_size.y / 2), (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / 2), (-m_size.y / 2), (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3((+m_size.x / 2), (-m_size.y / 2), (m_size.z / 2));

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �A�j���[�V������������Ƃ�
	if (m_Animation == true)
	{
		// �ݒ肵���^�C���Ɖ��Z�����^�C�����ꏏ�Ȃ�
		if (m_nTime == m_nTimeChange)
		{
			// ���̕����̉��Z
			m_nCountAnimChange++;

			// ���̕������Ɖ��Z���������ꏏ�Ȃ�
			if (m_nCountAnimChange % m_nCountAnim == 0)
			{
				m_nCountAnimChange = 0;

				// �c�̕����̉��Z
				m_nPatternAnimChange++;

				// �c�̕������Ɖ��Z���������ꏏ�Ȃ�
				if (m_nPatternAnimChange % m_nPatternAnim == 0)
				{
					m_nPatternAnimChange = 0;
				}
			}

			// ���_����ݒ�
			pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * m_nCountAnimChange, (float)(1.0f / m_nPatternAnim) * m_nPatternAnimChange);
			pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * (m_nCountAnimChange + 1), (float)(1.0f / m_nPatternAnim) * m_nPatternAnimChange);
			pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * m_nCountAnimChange, (float)(1.0f / m_nPatternAnim) * (m_nPatternAnimChange + 1));
			pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * (m_nCountAnimChange + 1), (float)(1.0f / m_nPatternAnim) * (m_nPatternAnimChange + 1));

			m_nTimeChange = 0;
		}
		// ���Ԃ̉��Z
		m_nTimeChange++;
	}
	else
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_fTexX1, m_fTexY1);
		pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY1);
		pVtx[2].tex = D3DXVECTOR2(m_fTexX1, m_fTexY2);
		pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pBuffMat->Unlock();


	if (m_nLife > 0 && m_col > 0.0f)
	{
		m_nLife--;
	}
	else
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �e�N�X�`����]������X�V����
//=============================================================================
void CBillboard::Update(float fangle)
{
	//���_����ݒ�
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pBuffMat->Lock(0, 0, (void**)&pVtx, 0);

	//�Εӂ̌v�Z
	float fHypotenuse = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y);

	//�p�x
	float frot = atan2f(m_size.y, m_size.x);


	float cos1 = cosf(frot + fangle) * fHypotenuse; //x��+
	float cos2 = cosf(frot - fangle) * fHypotenuse; //x��-
	float sin1 = sinf(frot + fangle) * fHypotenuse; //y��+
	float sin2 = sinf(frot - fangle) * fHypotenuse; //y��-

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-cos1, -sin1, (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(-cos2, +sin2, (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(+cos2, -sin2, (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+cos1, +sin1, (m_size.z / 2));


	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �A�j���[�V������������Ƃ�
	if (m_Animation == true)
	{
		// �ݒ肵���^�C���Ɖ��Z�����^�C�����ꏏ�Ȃ�
		if (m_nTime == m_nTimeChange)
		{
			// ���̕����̉��Z
			m_nCountAnimChange++;

			// ���̕������Ɖ��Z���������ꏏ�Ȃ�
			if (m_nCountAnimChange % m_nCountAnim == 0)
			{
				m_nCountAnimChange = 0;

				// �c�̕����̉��Z
				m_nPatternAnimChange++;

				// �c�̕������Ɖ��Z���������ꏏ�Ȃ�
				if (m_nPatternAnimChange % m_nPatternAnim == 0)
				{
					m_nPatternAnimChange = 0;
				}
			}

			// ���_����ݒ�
			pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * m_nCountAnimChange, (float)(1.0f / m_nPatternAnim) * m_nPatternAnimChange);
			pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * (m_nCountAnimChange + 1), (float)(1.0f / m_nPatternAnim) * m_nPatternAnimChange);
			pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * m_nCountAnimChange, (float)(1.0f / m_nPatternAnim) * (m_nPatternAnimChange + 1));
			pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nCountAnim) * (m_nCountAnimChange + 1), (float)(1.0f / m_nPatternAnim) * (m_nPatternAnimChange + 1));

			m_nTimeChange = 0;
		}
		// ���Ԃ̉��Z
		m_nTimeChange++;
	}
	else
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_fTexX1, m_fTexY1);
		pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY1);
		pVtx[2].tex = D3DXVECTOR2(m_fTexX1, m_fTexY2);
		pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pBuffMat->Unlock();


	if (m_nLife > 0 && m_col > 0.0f)
	{
		m_nLife--;
	}
	else
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBillboard::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; // �s��v�Z�p�̃}�g���N�X

	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�o�b�t�@���g���Ȃ�
	if (m_bUseZbuf == true)
	{
		// Z�o�b�t�@�𖳌���
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	// ���Z����
	if (m_bAdditiveSynthesis == true)
	{
		// ���Z��������
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// �A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	// �A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	// �A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_rot == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		// ��]�̋t�s��
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;

		// �������f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	else
	{
		// �������f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}


	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pBuffMat, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �Z�b�g�e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �Z�b�g�e�N�X�`��
	pDevice->SetTexture(0, NULL);

	// �A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���Z������߂�
	if (m_bAdditiveSynthesis == true)
	{
		// ���Z������߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// �t���O��false�ɖ߂�
		m_bAdditiveSynthesis = false;
	}

	// Z�o�b�t�@���g���Ȃ�
	if (m_bUseZbuf == true)
	{
		// Z�o�b�t�@��L����
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		m_bUseZbuf = false;
	}

	//���C�g�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// �e�N�X�`���󂯓n��
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//���
	m_pTexture = pTexture;
}