#pragma once
#include <array>
#include "Obj.h"
#include "VECTOR2.h"
#include "MapCtrl.h"
#include "Player.h"

constexpr int MOVE_SPEED = 40;

//class SceneMng;
class EditCursor :
	public Obj
{
public:
	EditCursor();						// MAP_ID,inputFlam,keyGetRngを初期化する
	EditCursor(VECTOR2 drawOffset);		// MAP_ID,inputFlam,keyGetRng,drawOffsetを初期化する
	~EditCursor();
	void Draw(bool game, int plNum);					// ｶｰｿﾙの点滅処理 SetDrawBlendMode関数使用

private:
	MAP_ID id;		// ﾏｯﾌﾟのﾁｯﾌﾟﾃﾞｰﾀのID

	int keyGetRng;	// 基底ﾌﾚｰﾑ数　ｷｰを離したら初期化
	int inputFlam;	// ｷｰを押しているﾌﾚｰﾑ数　押してないときｾﾞﾛｸﾘｱ

	DIR_TBL_ARY dirTable;		// 入力したｷｰの方向　speedTableと方向を合わせる
	DIR_TBL_ARY scrTable;		// ｽｸﾛｰﾙ用
	DIR_TBL_ARY speedTable;		// ﾌﾞﾛｯｸの移動ｽﾋﾟｰﾄﾞ dirTableと方向を合わせる

	// ｷｰを押したときの処理
	/*
		矢印ｷｰ押下時にｶｰｿﾙの上下左右移動を行う処理
		矢印ｷｰ長押し時に移動速度が上昇していく処理
		Ctrlｷｰ押下時に配置するﾌﾞﾛｯｸを変更する処理
		Spaceｷｰ押下時に選択しているﾌﾞﾛｯｸを配置する処理
	*/
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool MoveDec(VECTOR2 temp, VECTOR2 &dec);		// 長押し処理の関数化
	bool CheckObjType(OBJ_TYPE type);
};

