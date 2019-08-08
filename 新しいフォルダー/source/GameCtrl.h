// ｺﾝﾄﾛｰﾗｰ(ｷｰﾎﾞｰﾄﾞ)の入力情報を取得する

#pragma once
#include <DxLib.h>
#include <array>
#include <vector>
#include "VECTOR2.h"
#include "INPUT_ID.h"

//別名定義
using KEY_ARY = std::array<char, 256>;
using INPUT_ARY = std::array<bool, static_cast<int>(INPUT_ID::MAX)>;

#define XINPUT_DOWN	static_cast<int>(INPUT_ID::DOWN)		// 下
#define XINPUT_LEFT	static_cast<int>(INPUT_ID::LEFT)		// 左
#define XINPUT_RIGHT static_cast<int>(INPUT_ID::RIGHT)		// 右
#define XINPUT_UP	static_cast<int>(INPUT_ID::UP)			// 上
#define XINPUT_ATT static_cast<int>(INPUT_ID::ATT)			// 攻撃
#define XINPUT_MAP	static_cast<int>(INPUT_ID::MAP)			// ﾏｯﾌﾟ表示
#define XINPUT_GET_LB static_cast<int>(INPUT_ID::GET_LB)	// 物を掴む,物を置く,移動key + 物を掴んでる状態でLBkeyを押す = 物を投げる
#define XINPUT_RUN_RB static_cast<int>(INPUT_ID::RUN_RB)	// ﾀﾞｯｼｭ
#define XINPUT_START static_cast<int>(INPUT_ID::START)		// 決定
#define XINPUT_PAUSE static_cast<int>(INPUT_ID::PAUSE)		// ﾎﾟｰｽﾞ


enum KEY_TYPE
{
	KEY_TYPE_NOW,	//現在のｷｰ情報
	KEY_TYPE_OLD,	//1ﾌﾚｰﾑ前の情報
	KEY_TYPE_MAX
};

class GameCtrl
{
public:
	GameCtrl();
	~GameCtrl();
	const KEY_ARY &GetCtrl(KEY_TYPE type) const;	//ｷｰ情報取得用関数
	const std::vector<INPUT_ARY> &GetInputState(KEY_TYPE type) const;	// ｹﾞｰﾑﾊﾟｯﾄﾞとｷｰﾎﾞｰﾄﾞの情報取得
	bool UpDate(void);		//ｷｰの押下状態を取得,更新する

private:
	KEY_ARY keyData;	//現在の押下状態
	KEY_ARY keyDataOld;	//1ﾌﾚｰﾑ前の押下状態

	std::vector<XINPUT_STATE> padData;	// 現在のｹﾞｰﾑﾊﾟｯﾄﾞ状態
	int padDataOld;			// 1ﾌﾚｰﾑ前のｹﾞｰﾑﾊﾟｯﾄﾞ状態

	std::array<unsigned int, 4> padTbl;

	std::vector<INPUT_ARY> inputState;	// ｷｰﾎﾞｰﾄﾞとﾊﾟｯﾄﾞの押下状態 trueなら押されている状態
	std::vector<INPUT_ARY> inputStateOld;
};

