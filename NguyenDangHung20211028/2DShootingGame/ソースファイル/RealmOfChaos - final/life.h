#ifndef _LIFE_H_
#define _LIFE_H_

//=============================================================================
//�}�N����`
//=============================================================================
#define HP_SIZE_X 10						//X���̑傫��
#define HP_SIZE_Y 5							//Y���̑傫��
#define	NUM_HP 50							//��

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
//�N���X
//=============================================================================
class CLife : public CScene
{
public:
	CLife(int nPriority = PRIORITYTYPE_UI);								//�R���X�g���N�^
	~CLife();															//�f�X�g���N�^
	static HRESULT Load(void);											//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);											//�e�N�X�`���̔j��
	static CLife* Create(D3DXVECTOR3 pos, float size_x, float size_y);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);			//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2d* m_apScene2D[MAX_LIFE];									//Scene2D�̃|�C���^
};
#endif
