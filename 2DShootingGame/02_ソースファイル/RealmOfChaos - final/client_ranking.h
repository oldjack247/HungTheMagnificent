#ifndef _CRIENT_RANKING_H_
#define _CRIENT_RANKING_H_

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_RANKING 5				// �����L���O�f�[�^��
#define SEND_BUF 256				//����o�b�t�@�̍ő吔
#define REC_BUF 128					//�󂯎��o�b�t�@�̍ő吔
#define SEND_BYTE 5					//����o�C�g��
#define MAX_IP_ADDRESS 128
#define IP_ADDRESS "127.0.0.1"		//IP�A�h���X
#define AZUR

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene2d.h"
#include "scene.h"
#include "score.h"

//=============================================================================
//�N���X
//=============================================================================
class CCrient_ranking : public CScene
{
public:
	typedef struct
	{
		float m_pos_y;											//Y���̈ʒu
		int m_nScore;											//�X�R�A
		int m_nRank;											//����
	} RankingData;

	typedef enum
	{
		COMMAND_TYPE_NONE = 0,
		COMMAND_TYPE_GET_RANKING,		// �����L���O�ꗗ���擾
		COMMAND_TYPE_SET_RANKING		// �����L���O��ݒ�
	} COMMAND_TYPE;

	CCrient_ranking();
	~CCrient_ranking();
	static CCrient_ranking* Create(D3DXVECTOR3 pos, float size_x, float size_y);	//��������
	HRESULT Init(D3DXVECTOR3 pos, float size_x, float size_y);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��
	static void GetRanking(void);								//�X�R�A�ƃ����L���O�̎�M
	static int SetRanking(int nScore);							//�X�R�A�̑��M
private:
	static RankingData m_RankingData[MAX_RANKING];				//�����L���O�f�[�^
	CScore* m_apScore[MAX_RANKING];								//�X�R�A�̃|�C���^							
};
#endif