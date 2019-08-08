// ｵﾌﾞｼﾞｪｸﾄのｲﾝｽﾀﾝｽ・ﾏｯﾌﾟのﾛｰﾄﾞなど、MapCtrlをもとにﾏｯﾌﾟ情報を管理・利用する

#pragma once
#include <memory>
#include <array>
#include "VECTOR2.h"

enum VALUE_TYPE {
	VALUE_UPPER_L,	// 開始点
	VALUE_LOWER_R,	// 終了点
	VALUE_AREA,		// ｽｸﾛｰﾙ範囲
	VALUE_MAX
};

#define lpStageMng StageMng::GetInstance()

constexpr int GAME_AREA_SIZE_X = 3200;		// ﾏｯﾌﾟ全体のｻｲｽﾞ
constexpr int GAME_AREA_SIZE_Y = 1920;

constexpr int CHIP_SIZE = 40;				// 1ﾏｽの長さ


class StageMng
{
public:
	static StageMng & GetInstance(void)
	{
		static StageMng s_instance;
		return s_instance;
	}

	const VECTOR2& GetChipSize(void);		// ChipSizeの取得
	const VECTOR2& GetStageSize(void);		// StageSizeの取得
	const VECTOR2& GetScrollValue(VALUE_TYPE type, bool singleFlag);

private:
	StageMng();
	~StageMng();

	bool Init(void);

	std::array<std::array<VECTOR2, 2>, (VALUE_MAX - 1)> scrollTbl;		// ｽｸﾛｰﾙ開始点と終了点
	VECTOR2 stageSize;		// ｽﾃｰｼﾞｻｲｽﾞ
	VECTOR2 chipSize;		// 1ﾏｽのｻｲｽﾞ
};

