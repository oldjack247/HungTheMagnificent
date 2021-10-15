#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
//#include "number.h"
#include "scene2d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define	SCORE_POS_X			SCREEN_WIDTH - (35.0f * 8)		// �X�R�A�̕\����ʒu(�w���W)
#define	SCORE_POS_Y			20.0f							// �X�R�A�̕\����ʒu(�x���W)
#define	SCORE_WIDTH			35.0f							// �X�R�A�̐����̕�
#define	SCORE_HEIGHT		70.0f							// �X�R�A�̐����̍���
#define	SCORE_INTERVAL_X	35.0f - 3.0f					// �X�R�A�̐����̕\���Ԋu
#define	NUM_PLACE			8								// �X�R�A�̌���

//=============================================================================
//�N���X
//=============================================================================
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITYTYPE_UI);						//�R���X�g���N�^
	~CScore();														//�f�X�g���N�^
	static HRESULT Load(void);										//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);										//�e�N�X�`���̔j��
	static CScore* Create(D3DXVECTOR3 pos, float size_x, float size_y);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);		//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	void AddScore(int nValue);										//�X�R�A�̉��Z�����֐�
	int GetScore(void) { return m_nScore; }							//�X�R�A�̏��擾�֐�
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;							//�e�N�X�`��
	CScene2d* m_apScene2D[NUM_PLACE];								//Scene2D�̃|�C���^
	int m_nScore;													//�X�R�A

};
#endif