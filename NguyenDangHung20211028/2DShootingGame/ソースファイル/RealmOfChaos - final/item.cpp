//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "item.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "life.h"
#include "game.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture[TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_type = TYPE_ITEM_HP;

	m_bHit = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
//�e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CItem::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = NULL;
	if (pRenderer == NULL)
	{
		pRenderer = CManager::GetRenderer();
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/item/item002.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_ITEM_HP]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/item/item000.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_ITEM_BULLET]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pRenderer->GetDevice(),
		"data/TEXTURE/item/item001.png",//�t�@�C���̖��O
		&m_pTexture[TYPE_ITEM_MINION]);

	return E_NOTIMPL;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CItem::Unload(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̊J��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}


//=============================================================================
//��������
//=============================================================================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, ITEMTYPE type)
{
	CItem* pItem = NULL;
	if (pItem == NULL)
	{
		pItem = new CItem;
		if (pItem != NULL)
		{
			pItem->Init(pos, move, size_x, size_y, type);
		}
	}
	return pItem;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, ITEMTYPE type)
{

	CScene2d::Init(pos, size_x, size_y);

	BindTexture(m_pTexture[type]);
	m_pos = pos;
	m_move = move;
	m_type = type;
	m_nLife = ITEM_LIFE;

	SetObjType(OBJTYPE_ITEM);
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CItem::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CItem::Update(void)
{
	VERTEX_2D* pVtx;
	m_nCounterAnim++;

	if (m_type == TYPE_ITEM_BULLET)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.11f + 0.11f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.11f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.11f + 0.11f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.11f, 1.0f);
		if (m_nCounterAnim >= 5)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 9)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();

		for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_SCENE; nCount++)
			{
				CScene* pScene = GetScene(nPriority, nCount);
				if (pScene != NULL)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;
					OBJTYPE objType;

					m_move.y = 2.0f;
					objType = pScene->GetObjType();
					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							m_bHit = true;
							CPlayer::SetBulletChange(m_bHit);
							m_nLife = 0;
						}
					}

					if (m_pos.y >= 500)
					{
						//�������~�߂�
						m_move.y = 0.0f;
					}
				}
			}
		}
	}

	if (m_type == TYPE_ITEM_HP)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.047f + 0.047f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.047f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.047f + 0.047f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.047f, 1.0f);
		if (m_nCounterAnim >= 5)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 9)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();

		for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_SCENE; nCount++)
			{
				CScene* pScene = GetScene(nPriority, nCount);
				if (pScene != NULL)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;
					OBJTYPE objType;

					m_move.y = 2.0f;
					objType = pScene->GetObjType();
					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							m_bHit = true;
							CGame::SetPlayerLife(+1);
							m_nLife = 0;
						}
					}

					if (m_pos.y >= 500)
					{
						//�������~�߂�
						m_move.y = 0.0f;
					}
				}
			}
		}
	}


	if (m_type == TYPE_ITEM_MINION)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f + 0.25f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.25f, 1.0f);
		if (m_nCounterAnim >= 5)
		{//��莞�Ԍo�߂���
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim >= 4)
			{//�p�^�[�����𒴂���
				m_nPatternAnim = 0;
			}
		}
		m_pVtxBuff->Unlock();

		for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_SCENE; nCount++)
			{
				CScene* pScene = GetScene(nPriority, nCount);
				if (pScene != NULL)
				{
					CPlayer* pPlayer = (CPlayer*)pScene;
					OBJTYPE objType;

					m_move.y = 2.0f;
					objType = pScene->GetObjType();
					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�����蔻��
						if (HitCcollision(pPlayer->GetPosition(), PLAYER_SIZE, PLAYER_SIZE))
						{
							m_bHit = true;
							CPlayer::SetMinion(m_bHit);
							m_nLife = 0;
						}
					}

					if (m_pos.y >= 500)
					{
						//�������~�߂�
						m_move.y = 0.0f;
					}
				}
			}
		}
	}

	//�ʒu�X�V
	m_pos += m_move;
	//�ʒu���Z�b�g
	SetPosition(m_pos);

	if (m_nLife <= 0)
	{
		Uninit();
	}
	else
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�

		//���_���W�̐ݒ�(�E���)
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - (ITEM_SIZE / 2), m_pos.y - (ITEM_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (ITEM_SIZE / 2), m_pos.y - (ITEM_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (ITEM_SIZE / 2), m_pos.y + (ITEM_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (ITEM_SIZE / 2), m_pos.y + (ITEM_SIZE / 2), 0.0f);

		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CItem::SetLife(int nLife)
{
	m_nLife -= nLife;
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CItem::HitCcollision(D3DXVECTOR3 Pos, float size_x, float size_y)
{
	bool bHit = false;
	D3DXVECTOR3 pos;
	pos = GetPosition();
	if (pos.x <= Pos.x + (size_x / 2) &&
		pos.x >= Pos.x - (size_x / 2) &&
		pos.y <= Pos.y + (size_y / 2) &&
		pos.y >= Pos.y - (size_y / 2))//�����蔻��
	{
		bHit = true;
	}
	return bHit;
}
