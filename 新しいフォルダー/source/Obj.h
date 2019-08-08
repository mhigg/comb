#pragma once
#include <string>
#include <map>
#include "VECTOR2.h"
#include "classObj.h"
#include "MAP_ID.h"

enum ANIM_TBL {
	ANIM_TBL_START_ID,		// ｱﾆﾒｰｼｮﾝの開始
	ANIM_TBL_FRAME,			// ｱﾆﾒｰｼｮﾝのｺﾏ数
	ANIM_TBL_INV,			// ｺﾏごとの間隔
	ANIM_TBL_LOOP,			// ﾙｰﾌﾟするかどうか
	ANIM_TBL_MAX
};

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

enum OBJ_TYPE {
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_WEAPON,
	OBJ_EFFECT,
	OBJ_EDIT_CURSOR,
	OBJ_SELECTOR,
	OBJ_MAX
};

enum TBL_ID {
	TBL_MAIN,		// 移動方向
	TBL_OPP,		// 移動方向の逆の軸
	TBL_MAX
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,	// 移動方向
	DIR_TBL_REV,	// 移動している方向の逆
	DIR_TBL_OPP1,	// 移動方向の逆の軸①
	DIR_TBL_OPP2,	// 移動方向の逆の軸②
	DIR_TBL_MAX
};

enum SIDE_CHECK {
	OUT_SIDE,		// 0
	IN_SIDE,		// 1
	SIDE_MAX
};


class GameCtrl;

using DIR_TBL_ARY = std::array<int, DIR_MAX>;
using DIR_TBL_A2D = std::array<int[2], DIR_MAX>;
using DIR_TBL_PTR = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>; // ←ｱｲﾃﾑや障害物を追加したときに使う

class Obj
{
public:
	Obj();

	// 受け取ったdrawOffsetを自分の持つdrawOffsetに入れる
	Obj(VECTOR2 drawOffset);
	virtual ~Obj();

	bool Init(
		std::string fileName,		// 画像のﾌｧｲﾙ名
		VECTOR2 divSize,			// 分割ｻｲｽﾞ
		VECTOR2 divCnt				// 分割数の初期化
	);
	bool Init(
		std::string fileName,		// 画像のﾌｧｲﾙ名
		VECTOR2 divSize,			// 分割ｻｲｽﾞ
		VECTOR2 divCnt,				// 分割数の初期化
		VECTOR2 pos					// 座標
	);

	virtual bool initAnim(void) { return true; };	// ｱﾆﾒｰｼｮﾝの設定　AddAnim関数に値を設定する
	void UpDate(
		const GameCtrl &controller,	// 情報更新
		weakListObj objList			// ｺﾝﾄﾛｰﾗｰ自体のﾎﾟｲﾝﾀを渡す
	);
	virtual bool CheckDeath(void) { return false; };	// 死亡判定　基本死んでなければfalse
	virtual bool CheckObjType(OBJ_TYPE type) = 0;		// 指定した値と同じ型が来たらtrueを返す
	virtual void Draw(bool game, int plNum);		// 描画
	void Draw(unsigned int id);		// ID指定描画
	const VECTOR2 &GetPos(void);	// 座標取得関数

	bool AddAnim(
		std::string animName,		// ｱﾆﾒｰｼｮﾝの名前
		int id_x,					// 動き
		int id_y,					// 種別
		int frame,					// 総ｺﾏ数
		int inv,					// ｱﾆﾒｰｼｮﾝ1ｺﾏごとの間隔
		bool loop					// ｱﾆﾒｰｼｮﾝのﾙｰﾌﾟ有無(true:あり,false:なし)
	);

	// 同じ名前のｱﾆﾒｰｼｮﾝをｾｯﾄしたときはtrue
	// 存在しないｱﾆﾒｰｼｮﾝ名をｾｯﾄしたときはfalse
	// 別のｱﾆﾒｰｼｮﾝをｾｯﾄしたときはｱﾆﾒｰｼｮﾝ名を再設定し、ｺﾏ数のｶｳﾝﾄとanimEndFlagをﾘｾｯﾄする
	bool SetAnim(std::string animName);

	std::string GetAnim(void);	// 現在のｱﾆﾒｰｼｮﾝ名を取得する

private:
	virtual void SetMove(const GameCtrl &controller, weakListObj objList) = 0;

	std::string animName;		// 表示するｱﾆﾒｰｼｮﾝ名
	std::map<std::string,int[ANIM_TBL_MAX]> animTable;	// ｱﾆﾒｰｼｮﾝの設定を保存する配列

protected:
	void SetPos(VECTOR2 pos);		// 座標を設定
	void InitScroll(int plNum);		// ｽｸﾛｰﾙｵﾌｾｯﾄを初期化する

	VECTOR2 pos;					// 表示する座標
	VECTOR2 scrollOffset;			// ｽｸﾛｰﾙによるｵﾌｾｯﾄ
	const VECTOR2 drawOffset;		// 描画ｵﾌｾｯﾄ
	VECTOR2 hitRad;					// ｵﾌﾞｼﾞｪｸﾄの当たり判定のｻｲｽﾞ
	VECTOR2 actOff;					// ｵﾌﾞｼﾞｪｸﾄの(当たり判定の)中心座標までのｽﾞﾚ

	std::string imageName;			// 表示する画像のﾌｧｲﾙ名
	VECTOR2 divSize;					// 画像の分割ｻｲｽﾞ
	VECTOR2 divCnt;					// 画像の分割数

	OBJ_TYPE objType;				// ｵﾌﾞｼﾞｪｸﾄの種類

	DIR dir;						// ｵﾌﾞｼﾞｪｸﾄの向いている方向

	unsigned int animCnt;			// ｱﾆﾒｰｼｮﾝのｶｳﾝﾄ
	bool animEndFlag;				// ｱﾆﾒｰｼｮﾝの最終ｺﾏ到達ﾌﾗｸﾞ

	bool visible;					// 点滅ﾌﾗｸﾞ
};