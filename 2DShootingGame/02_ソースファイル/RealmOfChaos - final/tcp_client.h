#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <winsock2.h>

//=============================================================================
//�}�N����`
//=============================================================================
#define SERVER_PORT_NUM 12345							//�|�[�g�ԍ�
#define BUFFER_NUM 1024									//�o�b�t�@�̍ő吔

//=============================================================================
// tcp_client�N���X
//=============================================================================
class CTcpClient
{
public:
	CTcpClient();										//�R���X�g���N�^
	~CTcpClient();										//�f�X�g���N�^
	static CTcpClient* Create(const char* pHostName, int nPortNum);	//��������
	void Release(void);									//�I������
	bool Init(const char* pHostName, int mPortNum);		//IP�A�h���X,�|�[�g�ԍ�
	int Send(char* pSendData, int nSendDataSize);		//send�֐�
	int Recv(char* pRecvBuf, int nRecvBufSize);			//rec�֐�
	void Close();										//�N���[�Y�֐�
private:
	SOCKET m_sock;										//�\�P�b�g
};
#endif
