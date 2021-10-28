#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include <windows.h>
#include "main.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CBullet;
class CSound;
class CBg;
class CEnemy;
class CGame;
class CTitle;
class CTutorial;
class CResult;
class CFade;
class CInputController;
class CGameClear;
class CGameOver;

//=============================================================================
//�N���X
//=============================================================================
class CManager
{
public:
	typedef enum
	{//���[�h�̎��
		MODE_TITLE = 0,												//�^�C�g��
		MODE_TUTORIAL,												//�`���[�g���A��
		MODE_GAME,													//�Q�[��
		MODE_RESULT,												//���U���g
		MODE_GAMECLEAR,
		MODE_GAMEOVER,
		MODE_MAX
	}MODE;

	CManager();														//�R���X�g���N�^
	~CManager();													//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	static CRenderer* GetRenderer(void);							//�����_���[�̏��擾��
	static CInputKeyboard* GetInputKeyboard(void);					//�L�[�{�[�h�̏��擾��
	static CSound* GetSound(void);									//�T�E���h�̏��擾��
	static void SetMode(MODE mode);									//
	static MODE GetMode(void) { return m_mode; };
	static CFade* GetFade(void) { return m_pFade; };				//�t�F�[�h�̏��擾
	static CInputController* GetController(void);					//�R���g���[���[�̏��擾��
private:
	static MODE m_mode;												//���[�h�̏����������ϐ�
	static D3DXVECTOR3 m_pos;										//�ʒu
	static CInputKeyboard* m_pInputKeyboard;						//�L�[�{�[�h�̃|�C���^
	static CRenderer* m_pRenderer;									//�����_���[��7�|�C���^
	static CSound* m_pSound;										//�T�E���h�̃|�C���^
	static CBg* m_pBg;												//BG�̃|�C���^
	static CGame* m_pGame;											//�Q�[���̃|�C���^
	static CTitle* m_pTitle;										//�^�C�g���̃|�C���^
	static CTutorial* m_pTutorial;
	static CGameClear* m_pGameClear;
	static CGameOver* m_pGameOver;
	static CResult* m_pResult;										//���U���g�̃|�C���^
	static CFade* m_pFade;											//�t�F�[�h�̃|�C���^
	static CInputController* m_pInputController;					//�R���g���[���[�̃|�C���^
};
#endif