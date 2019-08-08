#include <DxLib.h>
#include "StageMng.h"


StageMng::StageMng()
{
	Init();
}


StageMng::~StageMng()
{
}

const VECTOR2 & StageMng::GetChipSize(void)
{
	return chipSize;
}

const VECTOR2 & StageMng::GetStageSize(void)
{
	return stageSize;
}

const VECTOR2 & StageMng::GetScrollValue(VALUE_TYPE type, bool singleFlag)
{
	if (type == VALUE_AREA)
	{
		return (scrollTbl[singleFlag][VALUE_LOWER_R] - scrollTbl[singleFlag][VALUE_UPPER_L]);
	}
	return scrollTbl[singleFlag][type];
}

bool StageMng::Init(void)
{
	scrollTbl = {
//		  VALUE_UPPER_L								VALUE_LOWER_R
		VECTOR2(320, 200), VECTOR2(GAME_AREA_SIZE_X, GAME_AREA_SIZE_Y) - VECTOR2(480, 280),		// œŸ¡(false=0)
		VECTOR2(800, 480), VECTOR2(GAME_AREA_SIZE_X, GAME_AREA_SIZE_Y) - VECTOR2(800, 480)		// º›∏ﬁŸ(true=1)
	};

	stageSize = VECTOR2(GAME_AREA_SIZE_X, GAME_AREA_SIZE_Y);
	chipSize = VECTOR2(CHIP_SIZE, CHIP_SIZE);
	return true;
}
