#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// �O���ϐ�
//=============================================================================
extern LPDIRECTINPUT8		pDInput;
extern LPDIRECTINPUTDEVICE8	pDIKeyboard;
extern BYTE					diKeyState[256];
extern LPDIRECTINPUTDEVICE8	pDIJoypad;
extern DWORD				diJoyState;
extern LPDIRECTINPUTDEVICE8	pDIMouse;
extern DIMOUSESTATE			diMouseState;

//*****************************************************************************
// Joypad�p�ݒ�l
//*****************************************************************************
#define DEADZONE		(2500)			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		(10000)			// �L���͈͂̍ő�l
#define RANGE_MIN		(-10000)			// �L���͈͂̍ŏ��l
#define	MAX_CONTROLLER	(4)				//�Ȃ��R���g���[���[�̍ő吔 

//=============================================================================
//�}�N����`
//=============================================================================
#define UP     (0)	    //�\���L�[��
#define DOWN   (18000)	//�\���L�[��
#define LEFT   (27000)	//�\���L�[��
#define RIGHT  (9000)	//�\���L�[�E

#define CROSSZONE (4500)        //�\���L�[�̋��e�͈�

//=============================================================================
//�N���X
//=============================================================================
class CInputController :public CInput
{//�h���N���X
public:
	typedef struct
	{
		LPDIRECTINPUTDEVICE8 pDIJoypad;				// �R���g���[���[�f�o�C�X
		DIJOYSTATE2 State;							//�R���g���[���[�̃v���X���
		DIJOYSTATE2 Trigger;						//�R���g���[���[�̃g���K�[���
		DIJOYSTATE2 Release;						//�R���g���[���[�̃v���X���
	}CONTROLLER;

	typedef enum
	{
		BUTTON_X = 0,					//X
		BUTTON_Y,						//Y
		BUTTON_A,						//X
		BUTTON_B,						//Y
		BUTTON_L1,						//LB
		BUTTON_R1,						//RB
		BUTTON_L2,						//BACK
		BUTTON_R2,						//START
		BUTTON_L3,						//L��������
		BUTTON_R3,						//R��������
		BUTTON_BACK,					//BACK
		BUTTON_START,					//START
		BUTTON_UP,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_M,
		MAX_BUTTON
	}BUTTON;//�{�^���̐�

	CInputController();									//�R���X�g���N�^				
	~CInputController();								//�f�X�g���N�^
	HRESULT CreateJoypad(LPCDIDEVICEINSTANCE lpddi);	//��������
	HRESULT InitJoypad(HINSTANCE hInstance, HWND hWnd);//����������
	void UpdateJoypad(void);							//�X�V����
	void ReleaseDInput(void);							//�����[�X����
	bool GetJoypadPress(int nButton);					//�����Ă���Ƃ�
	bool GetJoypadTrigger(int nButton);					//�������Ƃ�
	bool GetJoypadRelease(int nButton);					//�������Ƃ�
	DIJOYSTATE2 GetController(void);					//�R���g���[���[�̏��擾�֐�
private:
	LPDIRECTINPUT8			m_pDInput;					// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	m_pDIJoypad;				// �R���g���[���[�f�o�C�X
	static DIJOYSTATE2 m_ControllerState;				//�R���g���[���[�̃v���X���
	static DIJOYSTATE2 m_ControllerStateTrigger;		//�R���g���[���[�̃g���K�[���
	CONTROLLER m_Controller[MAX_CONTROLLER];
};
#endif
