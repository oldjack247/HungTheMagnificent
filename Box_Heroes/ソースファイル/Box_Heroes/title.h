#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"

//==============================================================================
// エンターサインの状態
//==============================================================================
typedef enum
{
	ENTERSIGN_NORMAL = 0,	// 表示状態
	ENTERSIGN_NONE,			// 非表示状態
	ENTERSIGN_ACTIVE,		// キー入力時の点滅
	ENTERSIGN_MOVE,			// サインの移動
	ENTERSIGN_MAX
} ENTERSIGN;

//==============================================================================
// 自動遷移の状態
//==============================================================================
typedef enum
{
	TITLE_NONE = 0,	// 何もしない
	TITLE_AUTO,		// 自動遷移
	TITLE_MAX
} TITLEAUTO;

//==============================================================================
// タイトルの構造体
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posTitle;			// タイトル画面の位置
	D3DXVECTOR3 posTitlelogo;		// タイトルロゴの位置
	D3DXVECTOR3 posTitleEnter[2];	// エンターサインの位置
	D3DXCOLOR colSign;				// エンターサインの色・透明度
	ENTERSIGN Sign;					// エンターサインの状態
	TITLEAUTO titleauto;			// 自動画面遷移の状態
	int nCntMoveLogo;				// ロゴの移動カウンター
	int nSignAppear;				// エンターサイン出現カウント
	int nMoveSign;					// エンターサインの移動カウンター
	int nSignCounter;				// エンターサインの点滅カウンター
	int nShiftCount;				// 自動画面遷移へのカウンター
}TITLE;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
HRESULT InitTitle(void);	// タイトル画面の初期化処理
void UninitTitle(void);		// タイトル画面の終了処理
void UpdateTitle(void);		// タイトル画面の更新処理
void DrawTitle(void);		// タイトル画面の描画処理
TITLE GetTitle(void);		// タイトルの情報
void EnterSign(void);		// エンターサインの情報

#endif