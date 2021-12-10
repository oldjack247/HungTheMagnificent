#ifndef _RESULT_H_
#define _RESULT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
// ���U���g�N���X
//=============================================================================
class CResult :public CMode
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_GAMEOVER,
		TYPE_CLEAR,
		TYPE_MAX
	}TYPE;
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	TYPE m_Type;
};

#endif