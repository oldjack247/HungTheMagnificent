#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"

//==============================================================================
// プロトタイプ宣言
//==============================================================================
HRESULT InitTutorial(void);	// チュートリアル画面の初期化処理
void UninitTutorial(void);	// チュートリアル画面の終了処理
void UpdateTutorial(void);	// チュートリアル画面の更新処理
void DrawTutorial(void);	// チュートリアル画面の描画処理

#endif
