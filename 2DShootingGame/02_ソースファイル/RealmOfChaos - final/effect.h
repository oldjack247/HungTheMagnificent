#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BOSS_EFFECT_SIZE 10.0f						//�{�X�̃G�t�F�N�g�̃T�C�Y
#define ENEMY_EFFECT_SIZE 80.0f						//�G�̃G�t�F�N�g�̃T�C�Y
#define BULLET_SPAWN_SIZE 40.0f
#define BULLET_DEATH_SIZE 150.0f
#define BULLET_EFFECT_SIZE_X 15.0f
#define BULLET_EFFECT_SIZE_Y 20.0f
#define MAX_EFFECT 150
#define FADE_SIZE 1.5f
#define FADE_COL 0.02f
#define FADE_COUNT 5

//=============================================================================
//�N���X
//=============================================================================
class CEffect : public CScene2d
{
public:
	CEffect(int nPriority = PRIORITYTYPE_EFFECT);
	~CEffect();
	typedef enum
	{
		TYPE_2FBOSS = 0,
		TYPE_ENEMY2_DEATH,
		TYPE_BULLET_SPAWN,
		TYPE_BULLET_DEATH,
		TYPE_BULLET_EFFECT,
		TYPE_MAX
	}EFFECTTYPE;

	static HRESULT Load(void);
	static void Unload(void);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EFFECTTYPE type);					//��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float size_x, float size_y, EFFECTTYPE type);							//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	int m_nCounterAnim;								//�J�E���^�[
	int m_nPatternAnim;								//�p�^�[��NO.
	EFFECTTYPE m_type;								//���
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_move;								//�ړ���
	D3DXCOLOR m_col;								//�J���[
	float m_size_x;									//x���W�̃T�C�Y
	float m_size_y;									//y���W�̃T�C�Y
	int m_nEffectFade;								//���ŃJ�E���g
};
#endif 