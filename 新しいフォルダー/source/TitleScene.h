#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	uniqueBase UpDate(						// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void TitleDraw(void);	// 描画
	bool FadeOut(void);		// ﾌｪｰﾄﾞｱｳﾄ用関数
	int Init(void);			// 初期化
	int cnt;				// 点滅ｶｳﾝﾄ

	int fadeOutCnt;			// ﾌｪｰﾄﾞｱｳﾄ用ｶｳﾝﾄ
	int scenecnt;			// ｼｰﾝ切り替え用ｶｳﾝﾄ
	bool sceneflag;			// ｼｰﾝが切り替わるﾌﾗｸﾞ

	int titleScreen;
};

