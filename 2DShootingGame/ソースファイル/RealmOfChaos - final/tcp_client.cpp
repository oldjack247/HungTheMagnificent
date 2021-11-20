//=============================================================================
//�}�N����`
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "tcp_client.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTcpClient::~CTcpClient()
{
}

//=============================================================================
// ��������
//=============================================================================
CTcpClient* CTcpClient::Create(const char* pHostName, int nPortNum)
{
	CTcpClient* pTcpClient = new CTcpClient;
	if (pTcpClient->Init(pHostName, nPortNum) == false)
	{
		delete pTcpClient;
		pTcpClient = NULL;
	}
	return pTcpClient;
}

//=============================================================================
// �I������
//=============================================================================
void CTcpClient::Release(void)
{
	Close();
	delete this;
}

//=============================================================================
// ����������
//=============================================================================
bool CTcpClient::Init(const char* pHostName, int mPortNum)
{
	//�ڑ���p�\�P�b�g�̐���
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		printf("socket:%d\n", WSAGetLastError());
		return false;
	}

	//�ڑ�����̐ݒ�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(mPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName);
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("connect:%d\n", WSAGetLastError());
		//�\�P�b�g�ڑ����N���[�Y
		closesocket(m_sock);
		return false;
	}
	return true;
}

//=============================================================================
// send�֐�
//=============================================================================
int CTcpClient::Send(char* pSendData, int nSendDataSize)
{
	if (m_sock < 0)
	{
		return 0;
	}
	int nSendSize = send(m_sock, pSendData, nSendDataSize, 0);
	return nSendSize;
}

//=============================================================================
// rec�֐�
//=============================================================================
int CTcpClient::Recv(char* pRecvBuf, int nRecvBufSize)
{
	int nRecvSize = recv(m_sock, pRecvBuf, nRecvBufSize, 0);
	if (nRecvSize <= 0)
	{
		Close();
	}
	return nRecvSize;
}

//=============================================================================
// �N���[�Y�֐�
//=============================================================================
void CTcpClient::Close()
{
	if (m_sock < 0)
	{
		return;
	}
	//�\�P�b�g�ڑ����N���[�Y
	closesocket(m_sock);
	m_sock = -1;
}

