#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"

//=============================================================================
//�N���X
//=============================================================================
class CInput
{//��{�N���X
public:
	CInput();												//�R���X�g���N�^
	virtual ~CInput() = 0;									//�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void Uninit(void);								//�I������
	virtual void Update(void);								//�X�V����
	LPDIRECTINPUT8 GetInput(void) { return m_pInput; }		//���擾�p
protected:
	static LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;							//Directinput�I�u�W�F�N�g�ւ̃|�C���^
private:

};
#endif

