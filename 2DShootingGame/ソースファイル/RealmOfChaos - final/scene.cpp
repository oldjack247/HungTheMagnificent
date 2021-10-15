//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "main.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
int CScene::m_nNumAll = 0;
CScene* CScene::m_apScene[PRIORITYTYPE_MAX][MAX_SCENE] = {};

//=============================================================================
//�l�̃N���A
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nPriority = nPriority;
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		if (m_apScene[m_nPriority][nCount] == NULL)
		{
			m_apScene[m_nPriority][nCount] = this;
			m_nID = nCount;
			m_nNumAll++;
			break;
		}
	}
	m_nType = OBJTYPE_NONE;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::Draw(void)
{
}

//=============================================================================
//�S�čX�V
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nPriority][nCount] != NULL)
			{
				m_apScene[nPriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
//�S�ĕ`��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nPriority][nCount] != NULL)
			{
				m_apScene[nPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
//�S�ĊJ��
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITYTYPE_MAX; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nPriority][nCount] != NULL)
			{
				m_apScene[nPriority][nCount]->Uninit();
				delete m_apScene[nPriority][nCount];
				m_apScene[nPriority][nCount] = NULL;
			}
		}
	}
}

//=============================================================================
//����̃I�u�W�F�N�g�̂݊J��
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID;
		int nPriority;
		nID = m_nID;
		nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//=============================================================================
// �I�u�W�F�N�g�^�C�v�̃Z�b�g
//=============================================================================
void CScene::SetObjType(OBJTYPE type)
{
	m_nType = type;
}

//=============================================================================
// �V�[���̏��擾
//=============================================================================
CScene* CScene::GetScene(int nPriority, int nNum)
{
	return m_apScene[nPriority][nNum];
}
