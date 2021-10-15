//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "motion.h"
#include "loadmodeldata.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	// ���f���p�[�c�̏�����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_modelParent[nCount].m_nIndex = 0;
		m_modelParent[nCount].m_nParents = 0;
		m_modelParent[nCount].m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���[�V�����̏�����
	for (int m_Type = 0; m_Type < TYPE_MAX; m_Type++)
	{
		for (int nCountMotion = 0; nCountMotion < MOTION_MAX; nCountMotion++)
		{
			m_motion[m_Type][nCountMotion].m_nLoop = false;
			m_motion[m_Type][nCountMotion].m_nNumKey = 0;

			for (int nCountKey = 0; nCountKey < MOTION_KEYSET_MAX; nCountKey++)
			{
				m_motion[m_Type][nCountMotion].m_KeyInfo[nCountKey].m_nFrame = 0;
				for (int nCountParts = 0; nCountParts < MAX_PARTS; nCountParts++)
				{
					m_motion[m_Type][nCountMotion].m_KeyInfo[nCountKey].m_pos[nCountParts] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_motion[m_Type][nCountMotion].m_KeyInfo[nCountKey].m_rot[nCountParts] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}

	// ���[�V�����̏�Ԃ�MOTION_IDLE��
	m_nMotionState = 0;
	m_nMotionOldState = 0;

	// �t���[�����ƃL�[���̏�����
	m_nFreme = 0;
	m_nCntKey = 1;

	// 
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_NumPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRot[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRotDest[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_AngleModifying = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// ���[�V�����N���X�̃C���X�^���X����
//=============================================================================
CMotion* CMotion::Create(CCharacter* pCharacter, CharacterType Type)
{
	CMotion* pMotion;
	pMotion = new CMotion;
	pMotion->SetCharacter(pCharacter);
	pMotion->SetType(Type);

	return pMotion;
}

//=============================================================================
// ���[�V�����N���X�̏I������
//=============================================================================
void CMotion::Uninit(void)
{
	// ���f���p�[�c�̏�����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_modelParent[nCount].m_nIndex = 0;
		m_modelParent[nCount].m_nParents = 0;
		m_modelParent[nCount].m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���[�V�����̏�����
	for (int m_Type = 0; m_Type < TYPE_MAX; m_Type++)
	{
		for (int nCountMotion = 0; nCountMotion < MOTION_MAX; nCountMotion++)
		{
			m_motion[m_Type][nCountMotion].m_nLoop = false;
			m_motion[m_Type][nCountMotion].m_nNumKey = 0;

			for (int nCountKey = 0; nCountKey < MOTION_KEYSET_MAX; nCountKey++)
			{
				m_motion[m_Type][nCountMotion].m_KeyInfo[nCountKey].m_nFrame = 0;
				for (int nCountParts = 0; nCountParts < MAX_PARTS; nCountParts++)
				{
					m_motion[m_Type][nCountMotion].m_KeyInfo[nCountKey].m_pos[nCountParts] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_motion[m_Type][nCountMotion].m_KeyInfo[nCountKey].m_rot[nCountParts] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}

	// ���[�V�����̏�Ԃ�MOTION_IDLE��
	m_nMotionState = 0;
	m_nMotionOldState = 0;

	// �t���[�����ƃL�[���̏�����
	m_nFreme = 0;
	m_nCntKey = 1;

	// 
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_NumPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRot[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRotDest[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// ���[�V�����N���X�̃��[�V�����̓ǂݍ���
//=============================================================================
void CMotion::LoadMotion(const char* cText)
{
	// �t�@�C���|�C���g
	FILE* pFile;

	// �ϐ��錾
	int  nCntLoad = 0;		// �ǂݍ��񂾃J�E���g
	int	 nCntKey = 0;		// �L�[�̐��̃J�E���g
	int	 nCntMotion = 0;	// ���[�V�����̐��̃J�E���g
	char cReedText[MAX_TEXT];	// �����Ƃ��ēǂݎ��p
	char cHeadText[MAX_TEXT];	// �����̔��ʗp
	char cDie[MAX_TEXT];		// �g��Ȃ�����

	// �t�@�C�����J��
	pFile = fopen(cText, "r");

	// �J��������
	if (pFile != NULL)
	{
		// SCRIPT�̕�����������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			// �e�L�X�g����cReedText��������ǂݍ���
			fgets(cReedText, sizeof(cReedText), pFile);
			// �ǂݍ��񂾕�������cHeadText�Ɋi�[
			sscanf(cReedText, "%s", &cHeadText);
		}

		// cHeadText��SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT�̕�����������܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				// �e�L�X�g����cReedText��������ǂݍ���
				fgets(cReedText, sizeof(cReedText), pFile);
				// �ǂݍ��񂾕�������cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);

				// cHeadText��MOTIONSET��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// END_MOTIONSET�̕�����������܂�
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						// �e�L�X�g����cReedText��������ǂݍ���
						fgets(cReedText, sizeof(cReedText), pFile);
						// �ǂݍ��񂾕�������cHeadText�Ɋi�[
						sscanf(cReedText, "%s", &cHeadText);

						// cHeadText��MOTIONSET��������
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							// m_nLoop�Ƀ��[�v�����邩�i�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, (int*)&m_motion[m_Type][nCntMotion].m_nLoop);
						}

						// cHeadText��NUM_KEY��������
						if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							// m_nNumKey�ɃL�[�̐����i�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[m_Type][nCntMotion].m_nNumKey);
						}

						// cHeadText��KEYSET��������
						if (strcmp(cHeadText, "KEYSET") == 0)
						{
							// END_KEYSET�̕�����������܂�
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								// �e�L�X�g����cReedText��������ǂݍ���
								fgets(cReedText, sizeof(cReedText), pFile);
								// �ǂݍ��񂾕�������cHeadText�Ɋi�[
								sscanf(cReedText, "%s", &cHeadText);

								// cHeadText��FRAME��������
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									// m_nFrame�Ƀt���[�������i�[
									sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_nFrame);
								}
								// cHeadText��KEY��������
								if (strcmp(cHeadText, "KEY") == 0)
								{
									// END_KEY�̕�����������܂�
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										// �e�L�X�g����cReedText��������ǂݍ���
										fgets(cReedText, sizeof(cReedText), pFile);
										// �ǂݍ��񂾕�������cHeadText�Ɋi�[
										sscanf(cReedText, "%s", &cHeadText);

										// cHeadText��POS��������
										if (strcmp(cHeadText, "POS") == 0)
										{
											// m_pos�ɍ��W���i�[
											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
												&m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].x,
												&m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].y,
												&m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].z);
										}
										// cHeadText��ROT��������
										if (strcmp(cHeadText, "ROT") == 0)
										{
											// m_rot�ɉ�]���i�[
											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
												&m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].x,
												&m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].y,
												&m_motion[m_Type][nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].z);
										}
									}
									// �J�E���g�̉��Z
									nCntLoad++;
								}
							}
							// �ǂݍ��񂾃J�E���g�̏�����
							nCntLoad = 0;
							// �J�E���g�̉��Z
							nCntKey++;
						}
					}
					// �L�[�̐��̏�����
					nCntKey = 0;
					// �J�E���g�̉��Z
					nCntMotion++;
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
	}
}



//=============================================================================
// ���[�V�����N���X�̍X�V����
//=============================================================================
void CMotion::UpdateMotion(void)
{
	// ���[�V������1F�O�̃��[�V�����ƈ������
	if (m_nMotionOldState != m_nMotionState) {
		m_nFreme = 0;
		m_nCntKey = 0;
	}
	for (int nCntParts = 0; nCntParts < CLoadmodeldata::GetNumParts(m_Type); nCntParts++)
	{
		//�t���[���J�n���ɁA�ύX��̉�]�̒l��ʒu�̒l�Ȃǂ�ݒ�
		if (m_nFreme == 0)
		{
			m_NumPos[nCntParts] = ((m_motion[m_Type][m_nMotionState].m_KeyInfo[m_nCntKey].m_pos[nCntParts] -
				(m_modelParent[nCntParts].m_pos - m_modelParent[nCntParts].m_posOrigin))
				/ float(m_motion[m_Type][m_nMotionState].m_KeyInfo[m_nCntKey].m_nFrame));

			m_NumRotDest[nCntParts] =
				m_motion[m_Type][m_nMotionState].m_KeyInfo[m_nCntKey].m_rot[nCntParts] - m_modelParent[nCntParts].m_rot;

			// �v�Z������]�̒l���Ԃ����ł���
			if (m_NumRotDest[nCntParts].x > D3DX_PI)
			{
				m_NumRotDest[nCntParts].x -= D3DX_PI * 2;
			}
			if (m_NumRotDest[nCntParts].x < -D3DX_PI)
			{
				m_NumRotDest[nCntParts].x += D3DX_PI * 2;
			}

			if (m_NumRotDest[nCntParts].y > D3DX_PI)
			{
				m_NumRotDest[nCntParts].y -= D3DX_PI * 2;
			}
			if (m_NumRotDest[nCntParts].y < -D3DX_PI)
			{
				m_NumRotDest[nCntParts].y += D3DX_PI * 2;
			}

			if (m_NumRotDest[nCntParts].z > D3DX_PI)
			{
				m_NumRotDest[nCntParts].z -= D3DX_PI * 2;
			}
			if (m_NumRotDest[nCntParts].z < -D3DX_PI)
			{
				m_NumRotDest[nCntParts].z += D3DX_PI * 2;
			}

			m_NumRot[nCntParts] = (m_NumRotDest[nCntParts] / float(m_motion[m_Type][m_nMotionState].m_KeyInfo[m_nCntKey].m_nFrame));
		}

		// �ύX��̉�]�̒l��ʒu�̒l�����Z
		m_modelParent[nCntParts].m_pos += m_NumPos[nCntParts];
		m_modelParent[nCntParts].m_rot += m_NumRot[nCntParts];
	}

	// ���݂̃��[�V�����̋L�^
	m_nMotionOldState = m_nMotionState;

	// ���[�v����Ƃ�
	if (m_nFreme >= m_motion[m_Type][m_nMotionState].m_KeyInfo[m_nCntKey].m_nFrame && m_motion[m_Type][m_nMotionState].m_nLoop == 1)
	{
		m_nFreme = 0;
		m_nCntKey++;
		m_AngleModifying = false;

		// �L�[���L�^����Ă���L�[���傫���Ȃ�����
		if (m_nCntKey >= m_motion[m_Type][m_nMotionState].m_nNumKey)
		{
			m_nCntKey = 0;
		}

	}
	// ���[�v���Ȃ��Ƃ�
	else if (m_nFreme >= m_motion[m_Type][m_nMotionState].m_KeyInfo[m_nCntKey].m_nFrame && m_motion[m_Type][m_nMotionState].m_nLoop == 0)
	{
		m_nFreme = 0;
		m_nCntKey++;
		m_AngleModifying = false;

		// �L�[���L�^����Ă���L�[���傫���Ȃ�����
		if (m_nCntKey >= m_motion[m_Type][m_nMotionState].m_nNumKey)
		{
			for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
			{
				m_NumPos[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_NumRot[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			m_nCntKey = m_motion[m_Type][m_nMotionState].m_nNumKey;
			m_nMotionState = 0;
		}
	}
	else
	{
		m_nFreme++;
	}
}