#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CAMERA_VIEW_DISTANCE (200.0f)				// �J�����̋���
#define CAMERA_MOVE_LEFT_RIGHT (D3DXToRadian(2.0f))	// �J�����̍��E�̈ړ���
#define CAMERA_MOVE_UP_DOWN (D3DXToRadian(1.5f))	// �J�����̏㉺�̈ړ���
#define CAMERA_LIMIT_UP (0.5f)						// �J�����̏�̏��
#define CAMERA_LIMIT_DOWN (1.5f)					// �J�����̉��̏��

//=============================================================================
// �J�����N���X
//=============================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();		//�f�X�g���N�^
	void Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����

	void GamePad(void);		// �Q�[���p�b�h����
	void CameraMovement(void); // �J�����̈ړ�����
	D3DXVECTOR3 GetPosR(void) { return m_posR; }		// �p�x�̎󂯎�菈��
	D3DXVECTOR3 GetPosV(void) { return m_posV; }		// ���W�̎󂯎�菈��
	float GetPhi(void) { return m_fPhi; }
	float GetAngle(void); // �J�����̊p�x���󂯎�鏈��
private:
	D3DXVECTOR3 m_posV;		//�ʒu
	D3DXVECTOR3 m_posR;		//�p�x
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_posVDest;		//�ʒu
	D3DXVECTOR3 m_posRDest;		//�p�x

	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	float m_fDistance;		// ����
	float m_fTheta;			// �J�����̉�
	float m_fPhi;			// �J�����̏c
};

#endif