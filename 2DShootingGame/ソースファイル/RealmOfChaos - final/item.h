#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define ITEM_SIZE 90.0f
#define MAX_ITEM 56
#define ITEM_LIFE 1

//=============================================================================
//�N���X
//=============================================================================
class CItem : public CScene2d
{
public:

	typedef enum
	{
		TYPE_ITEM_HP = 0,
		TYPE_ITEM_BULLET,
		TYPE_ITEM_MINION,
		TYPE_MAX
	}ITEMTYPE;

	CItem();
	~CItem();
	static HRESULT Load(void);											//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);											//�e�N�X�`���̔j��
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, ITEMTYPE Type);	//��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, ITEMTYPE Type);	//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��
	void SetLife(int nLife);											//�̗͂̃Z�b�g
	bool HitCcollision(D3DXVECTOR3 Pos, float size_x, float size_y);	//�����蔻��
private:
	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_move;													//�ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	int m_nLife;														//�̗�
	ITEMTYPE m_type;
	int m_nCounterAnim;													//�J�E���^�[
	int m_nPatternAnim;													//�p�^�[��NO.
	bool m_bHit;														//�����������ǂ���
};
#endif
