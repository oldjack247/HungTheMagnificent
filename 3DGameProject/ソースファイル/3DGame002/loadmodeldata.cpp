//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "loadmodeldata.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ�
//=============================================================================
LPD3DXMESH CLoadmodeldata::m_pMesh[MODELDATA_MAX][MAX_PARTS] = {};
LPD3DXBUFFER CLoadmodeldata::m_pBuffMat[MODELDATA_MAX][MAX_PARTS] = {};
DWORD CLoadmodeldata::m_nNumMat[MODELDATA_MAX][MAX_PARTS] = {};
char CLoadmodeldata::cModelFileName[MODELDATA_MAX][MAX_PARTS][MAX_TEXT] = {};
int CLoadmodeldata::m_nNumParts[MODELDATA_MAX] = {};
int CLoadmodeldata::m_nModelNum = 0;
LPDIRECT3DTEXTURE9 CLoadmodeldata::m_pTexture[MODELDATA_MAX][MAX_PARTS][MAX_MATERIAL] = {};

//=============================================================================
// [LoadModel] ���f���̓ǂݍ���
// FileName : �ǂݍ��ރt�@�C���̖��O
// type		: �L�����N�^�[�̃^�C�v
//=============================================================================
HRESULT CLoadmodeldata::LoadModelData(char* cFileName, int nType)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �t�@�C���|�C���g
	FILE* pFile;

	// �ϐ��錾
	int  nCntPart = 0;		// �ǂݍ��񂾃J�E���g
	char cReedText[MAX_TEXT];	// �����Ƃ��ēǂݎ��p
	char cHeadText[MAX_TEXT];	// �����̔��ʗp
	char cDie[MAX_TEXT];		// �g��Ȃ�����

	// �t�@�C�����J��
	pFile = fopen(cFileName, "r");

	// �J������
	if (pFile != NULL)
	{
		// SCRIPT�̕�����������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			// �e�L�X�g����cReedText���������󂯎��
			fgets(cReedText, sizeof(cReedText), pFile);

			// cReedText��cHeadText�Ɋi�[
			sscanf(cReedText, "%s", &cHeadText);
		}

		// cHeadText��SCRIPT�̎�
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// cHeadText��END_SCRIPT�ɂȂ�܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReedText, sizeof(cReedText), pFile);
				sscanf(cReedText, "%s", &cHeadText);

				// cHeadText��MODELNAMESET�̎�
				if (strcmp(cHeadText, "MODELNAMESET") == 0)
				{
					// cHeadText��END_MODELNAMESET�ɂȂ�܂�
					while (strcmp(cHeadText, "END_MODELNAMESET") != 0)
					{
						fgets(cReedText, sizeof(cReedText), pFile);
						sscanf(cReedText, "%s", &cHeadText);

						// cHeadText�����s�̎�
						if (strcmp(cHeadText, "\n") == 0)
						{
						}
						// cHeadText��MODELNUM�̎�
						else if (strcmp(cHeadText, "MODELNUM") == 0)
						{
							// �e�L�X�g��INDEX�̒l��m_nIndex�Ɋi�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nModelNum);
						}
						// cHeadText��PARTNUM�̎�
						else if (strcmp(cHeadText, "PARTSNUM") == 0)
						{
							// �e�L�X�g��INDEX�̒l��m_nNumParts�Ɋi�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nNumParts[m_nModelNum]);
						}
						// cHeadText��MODEL_FILENAME�̎�
						else if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
						{
							// �e�L�X�g��INDEX�̒l��m_nIndex�Ɋi�[
							sscanf(cReedText, "%s %s %s", &cDie, &cDie, &cModelFileName[m_nModelNum][nCntPart]);
							// �J�E���g���Z
							nCntPart++;
						}
					}
				}
				nCntPart = 0;
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

	for (int nType = 0; nType < MODELDATA_MAX; nType++)
	{
		// ���f���̓ǂݍ���
		for (int nCount = 0; nCount < m_nNumParts[nType]; nCount++)
		{
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(cModelFileName[nType][nCount],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_pBuffMat[nType][nCount],
				NULL,
				&m_nNumMat[nType][nCount],
				&m_pMesh[nType][nCount]
			);
		}

		// �e�N�X�`���̃��[�h
		LoadTexture(nType);
	}


	return S_OK;
}

//=============================================================================
// [LoadTexture] �e�N�X�`���̓ǂݍ���
// type		: �L�����N�^�[�̃^�C�v
//=============================================================================
HRESULT CLoadmodeldata::LoadTexture(int nType)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < m_nNumParts[nType]; nCount++)
	{
		// �}�e���A���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nType][nCount]->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nType][nCount]; nCntMat++)
		{
			// �g�p���Ă���e�N�X�`��������Γǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_pTexture[nType][nCount][nCntMat])))
				{
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}