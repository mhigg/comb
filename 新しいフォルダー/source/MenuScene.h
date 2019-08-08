#pragma once
#include <array>
#include "BaseScene.h"

constexpr int BOX_SIZE_X	= 460;
constexpr int BOX_SIZE_Y	= 90;			// 変えなくていいかも
constexpr int PUSH_SIZE		= 40;			// 選択中のﾒﾆｭｰﾊﾞｰのｵﾌｾｯﾄ

enum MODE {
	MODE_MALTI,		// ﾏﾙﾁﾓｰﾄﾞ
	MODE_SINGLE,		// ｼﾝｸﾞﾙﾓｰﾄﾞ
	MODE_HOWTO,		// 操作方法画面
	MODE_MAX
};

using BOX_ARRAY = std::array< VECTOR2, MODE_MAX >;
using MOVE_FLAG = std::array< bool, MODE_MAX >;
using SELECT_POINT = std::array< int, MODE_MAX >;

class MenuScene :
	public BaseScene
{
public:
	MenuScene();
	~MenuScene();
	uniqueBase UpDate(					// 更新
		uniqueBase own,					// 現在のｼｰﾝ
		const GameCtrl &controller		// ｷｰ取得
	);
private:
	void MenuDraw(void);		// 描画
	int Init(void);				// 初期化
	BOX_ARRAY movePos;			// Boxの座標を持つ配列
	MOVE_FLAG moveFlag;			// Boxの移動制御用配列
	SELECT_POINT selectPoint;	// 選んでいる奴の加算値
	MODE nowMode;				// どのﾓｰﾄﾞを選択しているか
	bool descriptionFlag;	    // 説明
	bool pushFlag;

	unsigned int count;			// MenuScene中のｶｳﾝﾄ
	double add;					// ﾒﾆｭｰﾊﾞｰの加算値
	VECTOR2 size;				// Boxのｻｲｽﾞ

	int menuScreen;
};

