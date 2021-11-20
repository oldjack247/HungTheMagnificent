#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
// �T�E���h�N���X
//=============================================================================
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_LABEL_TITLE_BGM = 0,
		SOUND_LABEL_GAME_BGM,
		SOUND_LABEL_2FBOSS_BATTLE_BGM,
		SOUND_LABEL_PLAYER_BULLET,
		SOUND_LABEL_BULLET_HIT,
		SOUND_LABEL_1FBOSS_BULLET,
		SOUND_LABEL_2FBOSS_CHARGE,
		SOUND_LABEL_2FBOSS_BULLET_FIRE,
		SOUND_LABEL_2FBOSS_FIRE_LOOP,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT InitSound(HWND hWnd);							//����������
	void UninitSound(void);									//�I������
	HRESULT PlaySound(SOUND_LABEL label);					//�T�E���h�Đ�����
	void StopSound(SOUND_LABEL label);						//�T�E���h��~����
	void StopSound(void);									//�T�E���h��~����

private:
	typedef struct
	{
		char* pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2* m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

															// �e���f�ނ̃p�����[�^
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
