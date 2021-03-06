#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define PAUSE_POLYGON	(7)			// ポーズ画面の使用するポリゴン数
#define PAUSETEXT		(4)			// ポーズ画面の選択肢数
#define PAUSE_WINDOWX	(160)		// ポーズメニューの幅
#define PAUSE_WINDOWY	(200)		// ポーズメニューの高さ
#define PAUSE_SIZEX		(140)		// ポーズテキストの幅
#define PAUSE_SIZEY		(40)		// ポーズテキストの高さ
#define PAUSETEXT_POSY	(230)		// ポーズテキスト1行目の高さ

//==============================================================================
// ポーズメニュー
//==============================================================================
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	// コンティニュー
	PAUSE_MENU_RETRY,			// リトライ
	PAUSE_MENU_OPTION,			// オプション
	PAUSE_MENU_QUIT,			// 終了
	PAUSE_MENU_MAX
} PAUSE_MENU;

//==============================================================================
// ポーズの構造体
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posBackScreen;			// ポーズ背景の位置
	D3DXVECTOR3 posWindow;				// ポーズウィンドウの位置
	D3DXVECTOR3 posText[PAUSETEXT];		// ポーズテキストの位置
	float fContinue;					// コンテニューテキストのテクスチャ位置
	float fRetry;						// リトライテキストのテクスチャ位置
	float fOption;						// オプションテキストのテクスチャ位置
	float fQuit;						// タイトルへのテキストのテクスチャ位置
	D3DXCOLOR colOption;				// 「あそびかた」ポリゴンの透明度
	bool bOption;						// 「あそびかた」への移行状態
	PAUSE_MENU PauseMenu;				// ポーズメニュー
} PAUSE;


//==============================================================================
// プロトタイプ宣言
//==============================================================================
HRESULT InitPause(void);	// ポーズメニューの初期化処理
void UninitPause(void);		// ポーズメニューの終了処理
void UpdatePause(void);		// ポーズメニューの更新処理
void DrawPause(void);		// ポーズメニューの描画処理
PAUSE GetPause(void);		// ポーズの情報取得

#endif
