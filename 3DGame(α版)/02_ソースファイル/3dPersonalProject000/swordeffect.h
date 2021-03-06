#ifndef _SWORDEFFECT_H_
#define _SWORDEFFECT_H_

//=============================================================================
// マクロ定義
//=============================================================================
#define SWORD_EFFECT_NUM (60)									// 剣のエフェクトの出す量
#define SWORD_EFFECT_LIFE (200)									// 剣のエフェクトのライフ
#define SWORD_EFFECT_SIZE (D3DXVECTOR3(3.0f, 3.0f, 0.0f))		// 剣のエフェクトの大きさ
#define SWORD_EFFECT_COLOR (D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))	// 剣のエフェクトの色
#define SWORD_EFFECT_ALPHA_SUBTRACT (0.01f)						// 透明度を減らす量
#define SWORD_EFFECT_SPEED (6.0f)								// 加速度
#define SWORD_EFFECT_CREATE_TIME (5)							// 生成する時間

//=============================================================================
// インクルードファイル
//=============================================================================
#include "billboard.h"
#include "particle.h"

//=============================================================================
// 斬撃エフェクトクラス
//=============================================================================
class CSwordeffect : public CParticle
{
public:
	CSwordeffect(int nPriority = OBJTYPE_PARTICLE);
	~CSwordeffect();

	static CSwordeffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 moveangle, D3DXCOLOR col, int Life);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_MoveAngle;
};
#endif