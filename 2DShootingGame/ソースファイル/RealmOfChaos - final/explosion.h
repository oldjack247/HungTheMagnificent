#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define EXPLOSION_SIZE 50.0f
#define PLAYER_EXPLOSION_SIZE 100.0f
#define MAX_EXPLOSION 68								//�ő吔

//=============================================================================
//�N���X
//=============================================================================
class CExplosion : public CScene2d
{
public:
	CExplosion(int nPriority = PRIORITYTYPE_EXPLOSION);	//�R���X�g���N�^
	~CExplosion();										//�f�X�g���N�^
	typedef enum
	{//�����̎��
		TYPE_SIMPLE = 0,								//���ʂ̔���				
		TYPE_ENEMY2_DEATH,								//�A�C�e�����h���b�v���邨�΂��̔���
		TYPE_PLAYER_DEATH,
		TYPE_MAX
	}EXPLOSIONTYPE;

	static HRESULT Load(void);							//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);							//�e�N�X�`���̔j��
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EXPLOSIONTYPE type); //��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EXPLOSIONTYPE type); //����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	void SetAnimation(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		//�e�N�X�`��
	int m_nCounterAnim;									//�J�E���^�[
	int m_nPatternAnim;									//�p�^�[��NO.
	EXPLOSIONTYPE m_type;								//�����̎��
	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_move;									//�ړ���
	D3DXCOLOR m_col;									//�F
	float m_size_x;										//X���W�̃T�C�Y
	float m_size_y;										//Y���W�̃T�C�Y
};
#endif 