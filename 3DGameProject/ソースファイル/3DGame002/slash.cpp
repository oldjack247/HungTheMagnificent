#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "particle.h"
#include "slash.h"
#include "collision.h"
#include "enemy.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSlash::CSlash(int nPriority) : CParticle(nPriority)
{
	m_SlashCount = NEXT_SLASH_COUNT;
	m_MoveAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSlash::~CSlash()
{
}

//=============================================================================
// ��������
//=============================================================================
CSlash* CSlash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 moveangle, D3DXCOLOR col, int Life, TYPE type)
{
	// CSlash�|�C���^
	CSlash* pSlash = NULL;

	// �������m��
	pSlash = new CSlash;

	// �ʒu���W�ݒ�
	pSlash->SetPos(pos);

	// �T�C�Y�ݒ�
	pSlash->SetSize(size);

	// �J���[�ݒ�
	pSlash->SetColor(col);

	// �J���[�ݒ�
	pSlash->SetLife(Life);

	pSlash->m_MoveAngle = moveangle;

	// ������
	pSlash->Init(type);

	// �|�C���^��Ԃ�
	return pSlash;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSlash::Init(TYPE type)
{
	switch (type)
	{
	case TYPE_SLASH_1:
		// ������
		CParticle::Init(TEX_TYPE_1);
		break;

	case TYPE_SLASH_2:
		// ������
		CParticle::Init(TEX_TYPE_2);
		break;

	default:
		break;
	}

	SetType(type);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CSlash::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CSlash::Update(void)
{
	// �X�V
	CParticle::Update();

	D3DXVECTOR3 pos = GetPos();
	D3DXCOLOR col = GetColor();
	//switch (m_Type)
	//{
	//case TYPE_SLASH_1:
	//	m_SlashCount++;
	//	pos += m_MoveAngle * SLASH_SPEED;
	//
	//	if (m_SlashCount > NEXT_SLASH_COUNT)
	//	{
	//		CSlash::Create(GetPos(), GetSize(), -m_MoveAngle + D3DXVECTOR3(sinf(24.0f), 0.0f, cosf(24.0f)),
	//			GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
	//
	//		//CSlash::Create(GetPos(), GetSize(), D3DXVECTOR3((-GetMove().x) + sinf((24.0f)), 0.0f, (-GetMove().z) + cosf((24.0f))),
	//		//	GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
	//
	//		//CSlash::Create(GetPos(), GetSize(), D3DXVECTOR3((-GetMove().x) , 0.0f, (-GetMove().z)),
	//		//	GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
	//
	//		//CSlash::Create(GetPos(), GetSize(), D3DXVECTOR3((-GetMove().x) - sinf(-(24.0f)), 0.0f, (-GetMove().z) - cosf(-(24.0f))),
	//		//	GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
	//
	//		CSlash::Create(GetPos(), GetSize(), -m_MoveAngle - D3DXVECTOR3(sinf(24.0f), 0.0f, cosf(24.0f)),
	//			GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
	//
	//		m_SlashCount = 0;
	//	}
	//	break;
	//
	//case TYPE_SLASH_2:
	//	pos += m_MoveAngle * SLASH_SPEED;
	//	break;
	//default:
	//	break;
	//}

	//// �p�x�̌v�Z�����Ă��Ȃ��Ƃ�
	//if (m_bCalculate == false)
	//{
	//	// m_fSlashFlame��19.0f�ȏゾ������
	//	if (m_fSlashFlame > 19.0f)
	//	{
	//		// m_fSlashFlame��19.0f�̍�
	//		float fFlame = m_fSlashFlame - 19.0f;
	//		m_bCalculate = true;
	//
	//		//���̕������񂵂Ċp�x�����炷
	//		for (int nCount = 0; nCount < (int)fFlame; nCount++)
	//		{
	//			m_fSlashAngleLimit -= 6.0f;
	//		}
	//	}
	//	else if (m_fSlashFlame < 19.0f)
	//	{
	//		m_bCalculate = true;
	//
	//		//���̕������񂵂Ċp�x�𑝂₷
	//		for (int nCount = 19; (int)m_fSlashFlame < nCount; nCount--)
	//		{
	//			m_fSlashAngleLimit -= 6.0f;
	//		}
	//	}
	//}

	switch (m_Type)
	{
	case TYPE_SLASH_1:
		m_SlashCount++;
		pos += m_MoveAngle * SLASH_SPEED;

		if (m_SlashCount > NEXT_SLASH_COUNT)
		{
			CSlash::Create(GetPos(), GetSize(),
				-m_MoveAngle,
				GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
		}


		//if (m_SlashCount > NEXT_SLASH_COUNT)
		//{
		//	for (int nCount = 0; nCount < NEXT_SLASH_NUM; nCount++)
		//	{
		//		fSlashAngle = m_fSlashAngleLimit - ((m_fSlashAngleLimit * 2) / (NEXT_SLASH_NUM - 1)) * nCount;
		//		if (fSlashAngle > 0.0f)
		//		{
		//			CSlash::Create(GetPos(), GetSize(),
		//				D3DXVECTOR3(sinf(D3DXToRadian(fSlashAngle + m_MoveAngle.y)), 0.0f, cosf(D3DXToRadian(fSlashAngle + m_MoveAngle.y))),
		//				GetColor(), NEXT_SLASH_LIFE, m_fSlashFlame, CSlash::TYPE_SLASH_2);
		//		}
		//		if (fSlashAngle == 0.0f)
		//		{
		//			CSlash::Create(GetPos(), GetSize(),
		//				-m_MoveAngle,
		//				GetColor(), NEXT_SLASH_LIFE, m_fSlashFlame, CSlash::TYPE_SLASH_2);
		//		}
		//		else if (fSlashAngle < 0.0f)
		//		{
		//			CSlash::Create(GetPos(), GetSize(),
		//				D3DXVECTOR3(sinf(D3DXToRadian(fSlashAngle + m_MoveAngle.y)), 0.0f, cosf(D3DXToRadian(fSlashAngle + m_MoveAngle.y))),
		//				GetColor(), NEXT_SLASH_LIFE, m_fSlashFlame, CSlash::TYPE_SLASH_2);
		//		}
		//	}
		//
		//	//CSlash::Create(GetPos(), GetSize(), D3DXVECTOR3((-GetMove().x) + sinf((24.0f)), 0.0f, (-GetMove().z) + cosf((24.0f))),
		//	//	GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
		//	//
		//	//CSlash::Create(GetPos(), GetSize(), D3DXVECTOR3((-GetMove().x) , 0.0f, (-GetMove().z)),
		//	//	GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
		//	//
		//	//CSlash::Create(GetPos(), GetSize(), D3DXVECTOR3((-GetMove().x) - sinf(-(24.0f)), 0.0f, (-GetMove().z) - cosf(-(24.0f))),
		//	//	GetColor(), NEXT_SLASH_LIFE, CSlash::TYPE_SLASH_2);
		//	//
		//	//CSlash::Create(GetPos() - D3DXVECTOR3(sinf(-24.0f) * fDistance, 0.0f, cosf(-24.0f) * fDistance), GetSize(), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		//	//	GetColor(), NEXT_SLASH_LIFE, m_fSlashFlame, CSlash::TYPE_SLASH_2);
		//
		//	m_SlashCount = 0;
		//}
		break;

	case TYPE_SLASH_2:
		col.a -= 0.05f;
		SetColor(col);
		break;

	default:
		break;
	}

	// �G�ւ̓����蔻��
	CScene* pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// �����蔻��
				if (CCollision::RectangleCollision3D(GetPos(), GetSize(),
					((CEnemy*)pScene)->GetPos(), ((CEnemy*)pScene)->GetSize()) == true)
				{
					// �e������
					Uninit();
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

	SetPos(pos);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSlash::Draw(void)
{
	// �`��
	CParticle::Draw();
}