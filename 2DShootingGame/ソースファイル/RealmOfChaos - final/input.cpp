//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "input.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUTDEVICE8 CInput::m_pDevice = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{

	//DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

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
// �I������
//=============================================================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CInput::Update(void)
{
}
