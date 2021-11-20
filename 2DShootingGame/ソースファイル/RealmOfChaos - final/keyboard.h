#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//=============================================================================
//�N���X
//=============================================================================
class CInputKeyboard :public CInput
{//�h���N���X
public:
	CInputKeyboard();								//�R���X�g���N�^	
	~CInputKeyboard();								//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	bool GetKeyboardPress(int nKey);				//���������Ă���Ƃ�
	bool GetKeyboardTrigger(int nKey);				//�������Ƃ�
	bool GetKeyboardRelease(int nKey);				//�������Ƃ�
private:
	static BYTE m_aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̏����̓��[�N
	static BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�L�[�{�[�h�̃����[�X���
	static BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};
#endif