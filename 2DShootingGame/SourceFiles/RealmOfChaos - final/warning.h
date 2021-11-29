#ifndef _WARNING_H_
#define _WARNING_H_

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
//�}�N����`
//=============================================================================
#define BOSS_WARNING_SIZE_X 875
#define BOSS_WARNING_SIZE_Y 225

//=============================================================================
//�N���X
//=============================================================================
class CWarning : public CScene2d
{
public:
	typedef enum
	{//�^�C�g���e�N�X�`���̎��
		WARNINGTYPE_NONE = 0,
		WARNINGTYPE_BOSS1,
		WARNINGTYPE_BOSS2,
		WARNINGTYPE_MAX
	}WARNINGTYPE;

	CWarning(int nPriority = PRIORITYTYPE_WARNING);					//�R���X�g���N�^
	~CWarning();												//�f�X�g���N�^
	static HRESULT Load(void);									//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);									//�e�N�X�`���̔j��
	static CWarning* Create(D3DXVECTOR3 pos, float size_x, float size_y, WARNINGTYPE m_type);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y, WARNINGTYPE m_type);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[WARNINGTYPE_MAX];		//�e�N�X�`��
	WARNINGTYPE m_type;											//�^�C�g��
	CScene2d* m_apScene2D[WARNINGTYPE_MAX];						//Scene2D�̃|�C���^										
	D3DXVECTOR3 m_pos;											//�ʒu
	D3DXCOLOR m_col;											//�F
	CSound* m_pSound;											//���̃|�C���^
	float m_size_x;												//x���W�̃T�C�Y
	float m_size_y;												//y���W�̃T�C�Y
	int nStopCount;
};
#endif
