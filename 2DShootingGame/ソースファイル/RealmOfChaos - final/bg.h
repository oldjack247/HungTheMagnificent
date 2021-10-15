#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//�}�N����`
//=============================================================================
#define BG_SIZE_X	1280		//X���W�̃T�C�Y
#define BG_SIZE_Y	720			//Y���W�̃T�C�Y
#define SUN_SIZE	500
#define MAX_BG 4

//=============================================================================
//�O���錾
//=============================================================================
class CManager;

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�N���X
//=============================================================================
class CBg :public CScene
{
public:
	// Bg�̎��
	typedef enum
	{
		BG_SPACE_1 = 0,
		BG_SPACE_2,
		BG_SPACE_3,
		BG_SUN,
		BG_SPACE_MAX,
	}BG_TYPE;

	// �񋓌^��`
	typedef enum
	{
		BG_MOVE = 0,
		BG_STOP,
		BG_MAX
	}BG_MOVETYPE;

	CBg(int nPriority = PRIORITYTYPE_BG);
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);					//����������
	static HRESULT Load(void);
	static void Unload(void);

	static CBg* Create(D3DXVECTOR3 pos, int nPriority, BG_MOVETYPE MoveType);	//��������
	void Uninit(void);															//�I������
	void Update(void);															//�X�V����
	void Draw(void);															//�`�揈��
	void SetBgType(BG_MOVETYPE MoveType) { m_BgType = MoveType; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG];
	CScene2d* m_apScene2D[MAX_BG];
	BG_MOVETYPE m_BgType;
	D3DXVECTOR3 m_pos;
	int m_nCounterAnim;
	int m_nPatternAnim;
};
#endif
