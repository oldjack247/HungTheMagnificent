#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
//�N���X
//=============================================================================
class CScene2d : public CScene
{//�h���N���X
public:
	//======================================================
	//�񋓌^��`
	//======================================================
	typedef enum
	{
		BG_MOVE = 0,
		BG_INPUT,
		DIRECT_MAX,
	}BGOPRETION;

	CScene2d(int nPriority = 0);									//�R���X�g���N�^
	~CScene2d();													//�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);		//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	void SetPosition(D3DXVECTOR3 pos);								//�ʒu�̃Z�b�g
	D3DXVECTOR3 GetPosition(void);									//�ʒu�̏��擾
	void SetCol(D3DXCOLOR col);										//�F�̃Z�b�g
	D3DXCOLOR GetCol(void);											//�F�̏��擾
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					//�e�N�X�`���̃Z�b�g
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								//�o�b�t�@
	void MoveBg(D3DXVECTOR2 move, BGOPRETION bg);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;								//�e�N�X�`��
	D3DXVECTOR2        m_MoveBg;								// �w�i�̈ړ��ʂ�ۑ�
	D3DXVECTOR3		   m_pos;									//�ʒu
	D3DXCOLOR		   m_col;									//�F							
};
#endif