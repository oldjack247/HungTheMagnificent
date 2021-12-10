#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define PLAYER_SIZE 80.0f
#define MAX_LIFE 6
#define MINION_USE_LIMITE 3

//=============================================================================
//�O���錾
//=============================================================================
class CSound;
class CGameClear;

//=============================================================================
//�N���X
//=============================================================================
class CPlayer : public CScene2d
{
public:
	typedef enum
	{//�v���C���[�̏��
		PLAYERSTATE_NORMAL = 0,								//�ʏ���
		PLAYERSTATE_DAMAGE,									//�_���[�W���󂯂��Ƃ�
		PLAYERSTATE_DEATH,									//���ꂽ�Ƃ�
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CPlayer(int nPriority = PRIORITYTYPE_PLAYER);			//�R���X�g���N�^
	~CPlayer();												//�f�X�g���N�^
	static HRESULT Load(void);								//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);								//�e�N�X�`���̔j��
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float size_x, float size_y);		//��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col, float size_x, float size_y);	//����������
	void Uninit(void);										//�I������
	void Update(void);										//�X�V����
	void Draw(void);										//�`�揈��
	void SetLife(int nLife);								//�̗͂̃Z�b�g�֐�
	static int GetLife(void) { return m_nLife; };			//�̗͂̏��擾�֐�
	static D3DXVECTOR3 GetPos(void) { return m_pos; };		//�ʒu�̎擾�֐�
	static void SetBulletChange(bool bBulletChange);
	static bool GetBulletChange(void) { return m_bBulletChange; };							//�e�L�X�g�t�@�C���ɏ������ފ֐�
	static void SetMinion(bool bUseMinion);
	static bool GetMinion(void) { return m_bUseMinion; };
private:
	static D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_move;										//�ړ���
	D3DXCOLOR m_col;										//�F
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nLife;										//�̗�
	static bool m_bBulletChange;
	static bool m_bUseMinion;
	static CGameClear* m_pGameClear;
	int m_nCounterAnim;										//�J�E���^�[
	int m_nLimitMinion;
	int m_nPatternAnim;										//�p�^�[��NO.
	int m_nInvincible;										//���G����										
	PLAYERSTATE m_State;									//�v���C���[�̏�Ԏ擾
	CSound* m_pSound;										//�T�E���h�̃|�C���^
};
#endif