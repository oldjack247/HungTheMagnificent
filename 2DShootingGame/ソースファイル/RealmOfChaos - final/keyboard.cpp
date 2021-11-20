//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "keyboard.h"
#include "input.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
BYTE CInputKeyboard::m_aKeyState[NUM_KEY_MAX] = {};
BYTE CInputKeyboard::m_aKeyStateRelease[NUM_KEY_MAX] = {};
BYTE CInputKeyboard::m_aKeyStateTrigger[NUM_KEY_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�(�t�H�A�O���E���h&��r�����[�h)
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND || DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�L�[�{�[�h����ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
			//�L�[�v���X�ۑ�
			/*m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyState[nCntKey] != aKeyState[nCntKey];*/
		}
	}
	else
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
