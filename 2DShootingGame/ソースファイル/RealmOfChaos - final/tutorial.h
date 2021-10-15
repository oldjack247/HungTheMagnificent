#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "scene2d.h"
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSound;

//=============================================================================
//�N���X
//=============================================================================
class CTutorial : public CScene
{
public:
	CTutorial(int nPriority = 0);												//�R���X�g���N�^
	~CTutorial();																//�f�X�g���N�^
	static HRESULT Load(void);												//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);												//�e�N�X�`���̔j��
	static CTutorial* Create(D3DXVECTOR3 pos, float size_x, float size_y);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);				//����������
	void Uninit(void);														//�I������
	void Update(void);														//�X�V����
	void Draw(void);														//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2d* m_apScene2D;													//Scene2D�̃|�C���^
	CSound* m_pSound;														//�T�E���h�̃|�C���^
};
#endif