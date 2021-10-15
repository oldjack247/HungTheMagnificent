//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "loadmodeldata.h"

//=============================================================================
// �L�����N�^�[�N���X�̃R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(int nPriority) : CScene(nPriority)
{
	// ���f���p�[�c�̏�����
	memset(m_apFileName, 0, sizeof(m_apFileName));
	memset(m_apTextureFileName, 0, sizeof(m_apTextureFileName));
	memset(m_apModel, 0, sizeof(m_apModel));
	memset(m_nldxModelParent, 0, sizeof(m_nldxModelParent));
	memset(m_Beginpos, 0, sizeof(m_Beginpos));
	memset(m_Beginrot, 0, sizeof(m_Beginrot));

	m_nPartsNum = 0;

	m_pMotion = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Type = CHARACTERTYPE_PLAYER;
}

//=============================================================================
// �L�����N�^�[�N���X�̃f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// �L�����N�^�[�N���X�̏���������
//=============================================================================
HRESULT CCharacter::Init(void)
{
	for (int nCount = 0; nCount < CLoadmodeldata::GetNumParts(m_Type); nCount++)
	{
		// ���f���̐���
		m_apModel[nCount] = CModel::Create();

		if (nCount != 0)
		{
			m_apModel[nCount]->SetParent(m_apModel[m_nldxModelParent[nCount]]);
		}

		// ���f���̃o�C���h
		m_apModel[nCount]->BindModel(CLoadmodeldata::GetMesh(m_Type, nCount), CLoadmodeldata::GetBuffMat(m_Type, nCount), CLoadmodeldata::GetNumMat(m_Type, nCount));

		for (int nCntMat = 0; nCntMat < (int)CLoadmodeldata::GetNumMat(m_Type, nCount); nCntMat++)
		{
			// �e�N�X�`���̃o�C���h
			m_apModel[nCount]->BindTexture(CLoadmodeldata::GetTextureData(m_Type, nCount), nCntMat);
		}

		m_apModel[nCount]->Setpos(m_Beginpos[nCount]);
		m_apModel[nCount]->Setrot(m_Beginrot[nCount]);

		m_apModel[nCount]->Init();
	}
	return E_NOTIMPL;
}

//=============================================================================
// �L�����N�^�[�N���X�̏I������
//=============================================================================
void CCharacter::Uninit(void)
{
	// ���f���p�[�c�̏�����
	memset(m_apFileName, 0, sizeof(m_apFileName));
	memset(m_apTextureFileName, 0, sizeof(m_apTextureFileName));
	memset(m_apModel, 0, sizeof(m_apModel));

	m_pMotion = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �L�����N�^�[�N���X�̃��[�V�����̓ǂݍ���
//=============================================================================
HRESULT CCharacter::LoadInitialPosition(char* cFileName)
{
	// �t�@�C���|�C���g
	FILE* pFile;

	// �ϐ��錾
	int  nCntLoad = 0;	 // �ǂݍ��񂾃J�E���g
	char cReedText[MAX_TEXT]; // �����Ƃ��ēǂݎ��p
	char cHeadText[MAX_TEXT]; // �����̔��ʗp
	char cDie[MAX_TEXT];		 // �g��Ȃ�����
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �t�@�C�����J��
	pFile = fopen(cFileName, "r");

	// �J������
	if (pFile != NULL)
	{
		// CHARACTERSET�̕�����������܂�
		while (strcmp(cHeadText, "CHARACTERSET") != 0)
		{
			// �e�L�X�g����cReedText���������󂯎��
			fgets(cReedText, sizeof(cReedText), pFile);
			// cReedText��cHeadText�Ɋi�[
			sscanf(cReedText, "%s", &cHeadText);
		}

		// cHeadText��CHARACTERSET�̎�
		if (strcmp(cHeadText, "CHARACTERSET") == 0)
		{
			// cHeadText��END_CHARACTERSET�ɂȂ�܂�
			while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
			{
				// �e�L�X�g����cReedText���������󂯎��
				fgets(cReedText, sizeof(cReedText), pFile);
				// cReedText��cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);

				// cHeadText�����s�̎�
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				// cHeadText��PARTSSET�̎�
				else if (strcmp(cHeadText, "PARTSSET") == 0)
				{
					// cHeadText��END_PARTSSET�ɂȂ�܂�
					while (strcmp(cHeadText, "END_PARTSSET") != 0)
					{
						// �e�L�X�g����cReedText���������󂯎��
						fgets(cReedText, sizeof(cReedText), pFile);
						// cReedText��cHeadText�Ɋi�[
						sscanf(cReedText, "%s", &cHeadText);

						// cHeadText��INDEX�ɂȂ�܂�
						if (strcmp(cHeadText, "INDEX") == 0)
						{
							// �e�L�X�g��INDEX�̒l��m_nIndex�Ɋi�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nldxModelNum[nCntLoad]);
						}

						// cHeadText��PARENT�ɂȂ�܂�
						if (strcmp(cHeadText, "PARENT") == 0)
						{
							// �e�L�X�g��PARENT�̒l��m_nParents�Ɋi�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nldxModelParent[nCntLoad]);
						}

						// cHeadText��POS�ɂȂ�܂�
						if (strcmp(cHeadText, "POS") == 0)
						{
							// �e�L�X�g��pos�̒l��m_Beginpos�Ɋi�[
							sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
								&pos.x,
								&pos.y,
								&pos.z);

							// pos�̒l��m_Beginpos�ɑ��
							m_Beginpos[nCntLoad] = pos;
						}

						// cHeadText��ROT�ɂȂ�܂�
						if (strcmp(cHeadText, "ROT") == 0)
						{
							// �e�L�X�g��rot�̒l��m_Beginrot�Ɋi�[
							sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
								&rot.x,
								&rot.y,
								&rot.z);

							// rot�̒l��m_Beginrot�ɑ��
							m_Beginrot[nCntLoad] = rot;
						}
					}
					// �J�E���g���Z
					nCntLoad++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}

	// �J���Ȃ�������
	else
	{
		printf("�J����܂���ł���\n");
	}

	LoadMotion(cFileName);

	return E_NOTIMPL;
}

//=============================================================================
// �L�����N�^�[�N���X�̃��[�V�����̓ǂݍ��ݏ���
//=============================================================================
void CCharacter::LoadMotion(char* FileName)
{
	m_pMotion = CMotion::Create(this, m_Type);

	if (m_pMotion != NULL)
	{
		m_pMotion->LoadMotion(FileName);
		for (int nCount = 0; nCount < CLoadmodeldata::GetNumParts(m_Type); nCount++)
		{
			m_pMotion->SetPos(nCount, m_Beginpos[nCount]);
			m_pMotion->SetRot(nCount, m_Beginrot[nCount]);
		}
	}
}


//=============================================================================
// �L�����N�^�[�N���X�̍X�V����
//=============================================================================
void CCharacter::Update(void)
{
	if (m_pMotion != NULL)
	{
		m_pMotion->UpdateMotion();
	}
}

//=============================================================================
// �L�����N�^�[�N���X�̕`�揈��
//=============================================================================
void CCharacter::Draw(void)
{
	for (int nCount = 0; nCount < CLoadmodeldata::GetNumParts(m_Type); nCount++)
	{
		if (m_pMotion != NULL)
		{
			if (nCount != 0)
			{
				m_apModel[nCount]->SetModel(m_Beginpos[nCount], m_pMotion->GetRot(nCount), m_size);
			}
			else
			{
				m_apModel[nCount]->SetModel(m_pos + m_pMotion->GetPos(nCount), m_rot + m_pMotion->GetRot(nCount), m_size);
			}
		}
		else
		{
			m_apModel[nCount]->SetModel(m_pos, m_rot, m_size);
		}

		// ���f���N���X�̕`�揈��
		m_apModel[nCount]->Draw();
	}
}