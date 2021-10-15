#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET_SIZE 50.0f				//��{�I�Ȓe�̃T�C�Y
#define PLAYER_BULLET_SIZE 25.0f		//�v���C���[�̒e�̃T�C�Y
#define PLAYER_BULLET_2_SIZE 20.0f
#define PLAYER_BULLET_3_SIZE 25.0f
#define BOSS2_BULLET_SIZE 150.0f		//2�t���A�ڂ̃{�X�̃T�C�Y7
#define ENEMY_BULLET_SIZE 50.0f
#define MAX_BULLET 256					//�e�̍ő吔
#define ANGLE 0.05f
#define ANGLE2 0.05f
#define RADIUS 100

//=============================================================================
//�O���錾
//=============================================================================
class CSound;

//=============================================================================
//�N���X
//=============================================================================
class CBullet : public CScene2d
{
public:
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
		BULLETTYPE_PLAYER_2,
		BULLETTYPE_PLAYER_3,
		BULLETTYPE_ENEMY,
		BULLETTYPE_1FBOSS,
		BULLETTYPE_2FBOSS,		//�{�X�̒e
		BULLETTYPE_2FBOSS2,		//�{�X�̒e����������̑S�����e
		BULLETTYPE_2FBOSS3,
		BULLETTYPE_MAX
	}BULLETTYPE;
	CBullet(int nPriority = PRIORITYTYPE_BULLET);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, int nLife, BULLETTYPE type);				//��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size_x, float size_y, int nLife, BULLETTYPE type);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	bool HitCcollision(D3DXVECTOR3 Pos, float size_x, float size_y);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTexture[BULLETTYPE_MAX];
	int m_nLife;				//�e�̗̑�
	int m_nCounterAnim;			//�J�E���^�[
	int m_nPatternAnim;			//�p�^�[��NO.
	BULLETTYPE m_type;			//�e�̎��
	float m_r;					//���a
	float m_fAngle;				//�p�x
	float m_fAngle2;			//�p�x
	CSound* m_pSound;
};
#endif 
