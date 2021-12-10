//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include "client_ranking.h"
#include "main.h"
#include "tcp_client.h"
#include "score.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CCrient_ranking::RankingData CCrient_ranking::m_RankingData[MAX_RANKING] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCrient_ranking::CCrient_ranking()
{
	memset(m_RankingData, 0, sizeof(m_RankingData));
	memset(m_apScore, 0, sizeof(m_apScore));
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCrient_ranking::~CCrient_ranking()
{
}

//=============================================================================
// ��������
//=============================================================================
CCrient_ranking* CCrient_ranking::Create(D3DXVECTOR3 pos, float size_x, float size_y)
{
	CCrient_ranking* pCrient_ranking = NULL;
	if (pCrient_ranking == NULL)
	{
		pCrient_ranking = new CCrient_ranking;
	}
	pCrient_ranking->Init(pos, size_x, size_y);
	return pCrient_ranking;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCrient_ranking::Init(D3DXVECTOR3 pos, float size_x, float size_y)
{
	GetRanking();
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		m_apScore[nCntRank] = CScore::Create(D3DXVECTOR3(600.0f, 70.0f + (nCntRank * 130), 0.0f), size_x, size_y);
		m_apScore[nCntRank]->AddScore(m_RankingData[nCntRank].m_nScore);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCrient_ranking::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCrient_ranking::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCrient_ranking::Draw(void)
{
}

//=============================================================================
// �X�R�A�ƃ����L���O�̎�M
//=============================================================================
void CCrient_ranking::GetRanking(void)
{
	char aDestIPAddr[MAX_IP_ADDRESS] = IP_ADDRESS;

	int nIndex = 0;

	//pTcpClient�����A�T�[�o�[�ɐڑ�
	CTcpClient* pTcpClient = CTcpClient::Create(aDestIPAddr, SERVER_PORT_NUM);
	//Send�����s
	//����
	char aSendBuf[SEND_BUF];

	aSendBuf[0] = COMMAND_TYPE_GET_RANKING;

	pTcpClient->Send(aSendBuf, 1);

	//�����L���O�ꗗ�擾���X�|���X���M
	char aRecvBuf[BUFFER_NUM];
	memset(aRecvBuf, 0, sizeof(aRecvBuf));

	//Recv�����s
	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		int nScore = *(int*)&aRecvBuf[nIndex];
		nScore = ntohl(nScore);
		m_RankingData[nCntRank].m_nScore = nScore;
		nIndex += sizeof(int);
	}
}

//=============================================================================
// �X�R�A�̑��M
//=============================================================================
int CCrient_ranking::SetRanking(int nScore)
{

	char aDestIPAddr[128] = IP_ADDRESS;

	CTcpClient* pTcpClient = CTcpClient::Create(aDestIPAddr, SERVER_PORT_NUM);
	int nIndex = 0;

	//TCP����M�N���X�̐ݒ�
	if (pTcpClient == NULL)
	{
		return 0;
	}

	//�����L���O�ݒ胊�N�G�X�g�̑��M
	//1�o�C�g��:COMMAND_TYPE_SET_RANKING��ݒ�
	char aSendBuf[SEND_BUF];
	aSendBuf[0] = COMMAND_TYPE_SET_RANKING;
	//2�`5�o�C�g��:�X�R�A��ݒ�
	nScore = htonl(nScore);
	memcpy(&aSendBuf[1], &nScore, sizeof(int));
	//���M
	//�S������
	pTcpClient->Send(aSendBuf, SEND_BYTE);
	//�����L���O�ݒ�̃��X�|���X����M
	char aRecvBuf[REC_BUF];
	memset(&aRecvBuf[0], 0, sizeof(aRecvBuf));
	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));
	pTcpClient->Release();
	return (int)aRecvBuf[0];
}
