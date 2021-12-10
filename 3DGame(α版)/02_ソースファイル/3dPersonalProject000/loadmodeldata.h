#ifndef _MODELLOAD_H_
#define _MODELLOAD_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MATERIAL (50)
#define MAX_TEXT (256) 

//=============================================================================
// ���[�h���f���f�[�^�N���X
//=============================================================================
class CLoadmodeldata
{
public:
	typedef enum
	{
		MODELDATA_PLAYER = 0,
		MODELDATA_ENEMY,
		MODELDATA_ROCK,
		MODELDATA_MAX
	}MODELDATATYPE;

	static HRESULT LoadModelData(char* cFileName, int nType);
	static HRESULT LoadTexture(int nType);

	static LPD3DXMESH GetMesh(int nType, int nNumPart) { return m_pMesh[nType][nNumPart]; }
	static LPD3DXBUFFER GetBuffMat(int nType, int nNumPart) { return m_pBuffMat[nType][nNumPart]; }
	static DWORD GetNumMat(int nType, int nNumPart) { return m_nNumMat[nType][nNumPart]; }
	static char GetModelFileName(int nType, int nNumPart) { return *cModelFileName[nType][nNumPart]; }
	static int GetNumParts(int nType) { return m_nNumParts[nType]; }
	static LPDIRECT3DTEXTURE9 GetTextureData(int nType, int nNumPart) { return *m_pTexture[nType][nNumPart]; }

private:
	static LPD3DXMESH m_pMesh[MODELDATA_MAX][MAX_PARTS];	  // ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[MODELDATA_MAX][MAX_PARTS]; // �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[MODELDATA_MAX][MAX_PARTS];		  // �}�e���A�����̐�
	static char cModelFileName[MODELDATA_MAX][MAX_PARTS][MAX_TEXT];
	static int m_nNumParts[MODELDATA_MAX];
	static int m_nModelNum;
	static LPDIRECT3DTEXTURE9 m_pTexture[MODELDATA_MAX][MAX_PARTS][MAX_MATERIAL];
};

#endif