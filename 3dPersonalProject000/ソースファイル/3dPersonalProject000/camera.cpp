//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "game.h"
#include "mouse.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_fDistance = 0;
	m_fTheta = 1.0f;
	m_fPhi = 1.7f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ����������
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_fDistance = sqrtf(powf(m_posV.x - m_posR.x, 2) + powf(m_posV.z - m_posR.z, 2));
	m_fTheta = 1.0f;
	m_fPhi = 0.0f;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	GamePad();

	//=============================================================================
	//�J�����`��
	//=============================================================================
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &m_posV, &m_posR, &m_vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10, 10000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//=============================================================================
// �Q�[���p�b�h����
//=============================================================================
void CCamera::GamePad(void)
{
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick = {};
	CInputJoystick* pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	//--------------------------
	//�ړ�
	//--------------------------		
	// �E�X�e�B�b�N�����ɓ|��
	if (pStick.lZ < 500)
	{
		m_fPhi -= CAMERA_MOVE_LEFT_RIGHT;
	}
	// �E�X�e�B�b�N���E�ɓ|��
	if (pStick.lZ > -500)
	{
		m_fPhi += CAMERA_MOVE_LEFT_RIGHT;
	}
	// �E�X�e�B�b�N����ɓ|��
	if (pStick.lRz < 500)
	{
		m_fTheta -= CAMERA_MOVE_UP_DOWN;
	}
	// �E�X�e�B�b�N�����ɓ|��
	if (pStick.lRz > -500)
	{
		m_fTheta += CAMERA_MOVE_UP_DOWN;
	}

	// �J�����̈ړ�����
	CameraMovement();

	if (CGame::GetPlayer() != NULL)
	{
		//�����_
		m_posR = CGame::GetPlayer()->GetPos();
	}

	//���_	
	m_fDistance = CAMERA_VIEW_DISTANCE;	//����
	m_posV.x = m_fDistance * (sinf(m_fTheta) * cosf(m_fPhi)) + m_posR.x;
	m_posV.y = m_fDistance * cosf(m_fTheta) + m_posR.y;
	m_posV.z = m_fDistance * (sinf(m_fTheta) * sinf(m_fPhi)) + m_posR.z;
}

//=============================================================================
// �J�����̈ړ�����
//=============================================================================
void CCamera::CameraMovement(void)
{
	// ���E�͈̔͂𒴂��Ȃ��悤�ɂ���
	if (m_fPhi >= D3DXToRadian(360.0f))
	{
		m_fPhi = 0.0f;
	}
	else if (m_fPhi <= D3DXToRadian(-360.0f))
	{
		m_fPhi = 0.0f;
	}

	// �㉺�͈̔͂̐���
	if (m_fTheta >= CAMERA_LIMIT_DOWN)
	{
		m_fTheta = CAMERA_LIMIT_DOWN;
	}
	else if (m_fTheta <= CAMERA_LIMIT_UP)
	{
		m_fTheta = CAMERA_LIMIT_UP;
	}

}

//=============================================================================
// �J�����̊p�x���󂯎�鏈��
//=============================================================================
float CCamera::GetAngle(void)
{
	// �Ԃ��p�x
	float fReturnAngle = 0.0f;

	// �p�x�����߂�(�J�����̈ʒu����A�����_���������̊p�x)
	fReturnAngle = atan2f((m_posR.x - m_posV.x), (m_posR.z - m_posV.z));

	return fReturnAngle;
}