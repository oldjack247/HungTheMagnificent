//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CLight::Init(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライトの方向ベクトル
	D3DXVECTOR3 vecDir;

	//ライトのクリア
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.5f, -1.0f, 1.0f);

	//正規化する（大きさ1のベクトルにする必要がある）
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;

	//ライトの設定
	pDevice->SetLight(0, &m_light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//=============================================================================
// 終了処理
//=============================================================================
void CLight::Uninit(void)
{
}
