//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "map.h"
#include "model.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPD3DXMESH CMap::m_pMesh = NULL;
LPD3DXBUFFER CMap::m_pBuffMat = NULL;
DWORD CMap::m_nNumMat = NULL;
D3DXMATRIX CMap::m_mtxWorld = {};	 // 行列計算用
char* CMap::m_apFileName = { "data/MODEL/MAP/map002.x" };// マップ
LPDIRECT3DTEXTURE9 CMap::m_pTexture[MAX_MATERIAL] = {};

//=============================================================================
// インクリメント
//=============================================================================
CMap::CMap(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
}

//=============================================================================
// デクリメント
//=============================================================================
CMap::~CMap()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMap* CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CMap* pMap;
	pMap = new CMap;
	pMap->Init();
	pMap->SetMap(pos, rot, size);
	return pMap;
}

//=============================================================================
// モデルの読み込み
//=============================================================================
HRESULT CMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//Xファイルの読み込み
	D3DXLoadMeshFromX(m_apFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	//テクスチャの読み込み
	LoadTexture();

	return E_NOTIMPL;
}

//=============================================================================
// モデルの破棄
//=============================================================================
void CMap::Unload(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		m_nNumMat = NULL;
	}
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CMap::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マテリアル情報を取り出す
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		//使用しているテクスチャがあれば読み込む
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャ読み込み
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat])))
			{
				return E_FAIL;
			}
		}
	}

	return E_NOTIMPL;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap::Init(void)
{
	//モデルの生成
	m_pModel = CModel::Create();

	//モデルのバインド
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat);

	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		//テクスチャのバインド
		m_pModel->BindTexture(m_pTexture[nCntMat], nCntMat);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMap::Uninit(void)
{
	if (m_pModel != NULL)
	{
		//モデルクラスの終了処理
		m_pModel->Uninit();
		m_pModel = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CMap::Draw(void)
{
	//モデルクラスの描画処理
	m_pModel->Draw();
}

//=============================================================================
// 初期設定
//=============================================================================
void CMap::SetMap(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;			//場所
	m_rot = rot;				//角度
	m_size = size;			//大きさ
	SetObjType(OBJTYPE_SKYBOX); //オブジェクトタイプの設定
}
