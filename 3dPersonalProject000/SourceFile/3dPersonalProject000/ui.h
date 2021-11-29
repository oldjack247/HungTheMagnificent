#ifndef _UI_H_
#define _UI_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_TITLE				("data/TEXTURE/title.png")				// �^�C�g���̃e�N�X�`��
#define TEXTURE_TUTORIAL			("data/TEXTURE/tutorial.png")			// �`���[�g���A���̃e�N�X�`�� 
#define TEXTURE_GAMEOVER			("data/TEXTURE/gameover.png")			// �Q�[���I�[�o�[�̃e�N�X�`��
#define TEXTURE_RESULT				("data/TEXTURE/result.png")				// ���U���g�̃e�N�X�`��
#define TEXTURE_HP					("data/TEXTURE/hp.png")					// HP�̃e�N�X�`��
#define TEXTURE_HPFLAME				("data/TEXTURE/hpflame.png")			// HP�̘g�̃e�N�X�`��
#define TEXTURE_HPSPBACK			("data/TEXTURE/hpspback.png")			// HP��SP�̌��̃e�N�X�`��
#define TEXTURE_SP					("data/TEXTURE/sp.png")					// SP�̃e�N�X�`��
#define TEXTURE_SPFLAME				("data/TEXTURE/spflame.png")			// SP�̃t�g�̃e�N�X�`��
#define TEXTURE_ENEMYREMAINDER		("data/TEXTURE/enemyrimainder.png")		// �G�̓|�����̃e�N�X�`��
#define TEXTURE_PRESSSTART			("data/TEXTURE/pressstart.png")			// PRESSSTART�̃e�N�X�`��

#define PLAYER_HP_COLOR				(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))			// HP�̐F
#define PLAYER_SP_COLOR				(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f))			// SP�̐F
//#define PLAYER_ST_COLOR				(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))		// ST�̐F

#define PLAYER_HP_GAUGE				(D3DXVECTOR3(250.0f, 30.0f, 0.0f))		// HP�̃Q�[�W�̍��W
#define PLAYER_HP_GAUGE_SIZE		(D3DXVECTOR3(450.0f, 20.0f, 0.0f))		// HP�̃Q�[�W�̃T�C�Y

#define PLAYER_SP_GAUGE				(D3DXVECTOR3(250.0f, 50.0f, 0.0f))		// SP�̃Q�[�W�̍��W
#define PLAYER_SP_GAUGE_SIZE		(D3DXVECTOR3(450.0f, 20.0f, 0.0f))		// SP�̃Q�[�W�̃T�C�Y

#define PLAYER_ST_GAUGE				(D3DXVECTOR3(250.0f, 70.0f, 0.0f))		// ST�̃Q�[�W�̍��W
#define PLAYER_ST_GAUGE_SIZE		(D3DXVECTOR3(450.0f, 20.f, 0.0f))		// ST�̃Q�[�W�̃T�C�Y

#define PRESSSTART_CHANGECOLOR_QUANTITY (0.01f)								// PRESSSTART�̐F��ω��������
#define PRESSSTART_POS (D3DXVECTOR3(SCREEN_CENTER_X, 550.0f, 0.0f))			// PRESSSTART�̍��W
#define PRESSSTART_SIZE (D3DXVECTOR3(1000.0f, 140.0f, 0.0f))				// PRESSSTART�̃T�C�Y

//=============================================================================
// UI�N���X
//=============================================================================
class CUi :public CScene2D
{
public:
	CUi(int nPriority = OBJTYPE_UI);
	~CUi();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_TITLE,
		TYPE_TUTORIAL,
		TYPE_GAMEOVER,
		TYPE_RESULT,
		TYPE_PLAYER_LIFE,
		TYPE_HP,
		TYPE_HPFRAME,
		TYPE_HPSPBACK,
		TYPE_PLAYER_SP,
		TYPE_SP,
		TYPE_SPFRAME,
		TYPE_PRESSSTART,
		TYPE_MAX
	}TYPE;

	static CUi* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type); // �N���G�C�g

	static HRESULT Load(void);	// �e�N�X�`���̓ǂݍ���
	static void Unload(void);	// �e�N�X�`���̔j��

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];	// �e�N�X�`���̏��
	D3DXVECTOR3	m_pos;								// ���W
	D3DXVECTOR3	m_size;								// �T�C�Y
	TYPE		m_type;								// �^�C�v
	bool		m_bPressenterflash;					// �Â����邩���邭���邩
};
#endif // !_UI_H_
