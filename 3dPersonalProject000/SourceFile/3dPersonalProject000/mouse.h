#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "input.h"

//================================================
// �}�E�X�̃N���X
//================================================
class CInputMouse : public CInput
{
public:
    typedef struct _MSTATE {
        RECT    moveRect;     // ��ʏ�œ�����͈�
        int     x;            // X���W
        int     y;            // Y���W
        bool    lButton;      // ���{�^��
        bool    rButton;      // �E�{�^��
        bool    cButton;      // �^�񒆃{�^��
        int     moveAdd;      // �ړ���
        RECT    imgRect;      // �}�E�X�p�摜��`
        int     imgWidth;     // �}�E�X�摜��
        int     imgHeight;    // �}�E�X�摜����
    } MSTATE;

    CInputMouse();
    ~CInputMouse();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit(void);
    void Update(void);

    static MSTATE* GetMouse(void);
    bool GetMouseTriggerLeft(void);
    bool GetMouseTriggerRight(void);
    bool GetMousePressLeft(void);
    bool GetMousePressRight(void);

private:
    static LPDIRECTINPUTDEVICE8 m_pMDevice;
    DIMOUSESTATE2 m_dIMouseState;
    static CInputMouse::MSTATE m_MState;
};

#endif