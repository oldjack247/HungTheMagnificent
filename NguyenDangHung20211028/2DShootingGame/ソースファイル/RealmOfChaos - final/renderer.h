#ifndef _RENDERER_H_
#define _RENDERER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_RENDERER 3

//=============================================================================
//�N���X
//=============================================================================
class CRenderer
{//��{�N���X
public:
	CRenderer();								//�R���X�g���N�^
	~CRenderer();								//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);		//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void);			//�擾����
	static void ResumeGame(void) { m_bPause = false; }
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXFONT m_pFont;
	static bool	m_bPause;
};
#endif