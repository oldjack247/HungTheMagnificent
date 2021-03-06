#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "mode.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_DEATH_ENEMY_NUM (10) // 敵の最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;

//=============================================================================
// ゲームクラス
//=============================================================================
class CGame :public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* GetPlayer(void);
	static void SubtractEnemy(void) {
		m_nEnemyNum--; m_nEnemyDeathTotal++;
	}

private:
	static CPlayer* m_pPlayer;				// プレイヤー
	static int m_nEnemyNum;					// 敵の数
	static int m_nEnemyDeathTotal;			// 敵倒した総数
	bool m_bEnemyCreate;					// 敵を生成するかどうか
	int m_nEnemyCreateTime;					// 敵を生成する時間
	int m_nDisplace;						// 数字をずらす時間
	int m_nEnemyDeathTotalOld;				// 1フレーム前の敵の総数
};
#endif