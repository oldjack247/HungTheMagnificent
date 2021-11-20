#ifndef _RESULT_H_
#define _RESULT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "scene2d.h"
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRanking;
class CSound;
class CCrient_ranking;

//=============================================================================
//�N���X
//=============================================================================
class CResult : public CScene
{
public:
	CResult(int nPriority = 0);												//�R���X�g���N�^
	~CResult();																//�f�X�g���N�^
	static HRESULT Load(void);												//�e�N�X�`���̓ǂݍ��ݏ���
	static void Unload(void);												//�e�N�X�`���̔j��
	static CResult* Create(D3DXVECTOR3 pos, float size_x, float size_y);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);				//����������
	void Uninit(void);														//�I������
	void Update(void);														//�X�V����
	void Draw(void);														//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2d* m_apScene2D;													//Scene2D�̃|�C���^
	static CBg* m_pBg;														//BG�̃|�C���^
	static CRanking* m_pRanking;											//�����L���O�̃|�C���^
	CSound* m_pSound;														//�T�E���h�̃|�C���^
	static CCrient_ranking* m_pCrient_ranking;
};
#endif