#pragma once
#include <array>
#include "BaseScene.h"
#include "ClassObj.h"

constexpr auto CHARA_NUM = 4;

using SELECT_POS = std::array< VECTOR2, CHARA_NUM >;

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	uniqueBase UpDate(						// XV
		uniqueBase own,					// Œ»İ‚Ì¼°İ
		const GameCtrl &controller		// ·°æ“¾
	);
private:
	void SelectDraw(void);		// •`‰æ
	int Init(void);				// ‰Šú‰»

	SELECT_POS selectPos;		// ÌßÚ²Ô°–ˆ‚Ì—§‚¿ŠGˆÊ’u
	int selectMode;				// ‘I‚ñ‚¾Ó°ÄŞ
	int backChange;				// ”wŒiØ‚è‘Ö‚¦‚ÌŠÔ
	int selectScreen;

	sharedListObj objList;
};

