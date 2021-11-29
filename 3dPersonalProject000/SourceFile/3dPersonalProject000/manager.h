#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CInputMouse;
class CCamera;
class CLight;
class CFade;
class CPlayer;
class CModel;
class CMode;
class CSound;

//=============================================================================
// �}�l�[�W���[�N���X
//=============================================================================
class CManager
{
public:
	//��ʑJ�ڂ̗񋓌^
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,		//�^�C�g��
		MODE_GAME,		//�Q�[��
		MODE_TUTORIAL,	//�`���[�g���A��
		MODE_RESULT,	//���U���g
		MODE_GAMEOVER, //�Q�[���I�[�o�[
		MODE_MAX
	}MODE;

	CManager();													//�C���N�������g
	~CManager();												//�f�N�������g
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��

	void LoadAll(void);											//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
	void UnloadAll(void);										//�e�N�X�`���̔j���܂Ƃ�

	static void SetMode(MODE mode);								//���[�h�̐ݒ�

	static void CreateCamera(void);
	static void CreateLight(void);
	static void CreateFade(void);

	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }

	static CRenderer* GetRenderer(void) { return m_pRenderer; }					//�����_���[
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }	//�L�[�{�[�h
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }			//�}�E�X
	static CInputJoystick* GetInputJoystick(void) { return m_pInputJoystick; }	//�Q�[���p�b�h
	static CCamera* GetCamera(void) { return m_pCamera; }						//�J����
	static CLight* GetLight(void) { return m_pLight; }							//���C�g
	static CFade* GetFade(void) { return m_pFade; }								//�t�F�[�h
	static MODE GetMode(void) { return m_mode; }								//���[�h
	static CSound* GetSound(void) { return m_pSound; }							//�T�E���h

private:
	static CRenderer* m_pRenderer;				//�����_���[
	static CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h
	static CInputMouse* m_pInputMouse;			//�}�E�X
	static CInputJoystick* m_pInputJoystick;	//�Q�[���p�b�h
	static CCamera* m_pCamera;					//�J����
	static CLight* m_pLight;					//���C�g
	static CFade* m_pFade;						//�t�F�[�h
	static CSound* m_pSound;					//�T�E���h
	static CMode* m_pMode;						//���[�h�̃|�C���^
	static MODE m_mode;							//���݂̃��[�h
	int m_nCountFPS;							// FPS�̒l
};

#endif // !_MANAGER_H_
