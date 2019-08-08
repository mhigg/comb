#include <DxLib.h>
#include "SelectScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "MenuScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "Selector.h"
#include "GameCtrl.h"

SelectScene::SelectScene()
{
	SelectScene::Init();
}


SelectScene::~SelectScene()
{
}

uniqueBase SelectScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);

	if ((cnt[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		return std::make_unique<EditScene>();
	}
	if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
	{
		return std::make_unique<GameScene>();
	}
	// BACK(ç∂SHIFT)Ç≈“∆≠∞Ç÷ñﬂÇÈ
	if ((cnt[KEY_INPUT_LSHIFT]) & (!cntOld[KEY_INPUT_LSHIFT]))
	{
		return std::make_unique<MenuScene>();
	}
	if (inputState[0][XINPUT_PAUSE] & !inputStateOld[0][XINPUT_PAUSE])
	{
		return std::make_unique<MenuScene>();
	}

	for (auto& itr : (*objList))
	{
		itr->UpDate(controller, objList);
	}

	SelectDraw();
	return std::move(own);
}

void SelectScene::SelectDraw(void)
{
	SetDrawScreen(selectScreen);
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/select.png")[0], true);
	if (GetJoypadNum() >= 2)
	{
		DrawGraph(800, 0, IMAGE_ID("image/select.png")[0], true);
	}
	if (GetJoypadNum() >= 3)
	{
		DrawGraph(0, 480, IMAGE_ID("image/select.png")[0], true);
	}
	if (GetJoypadNum() == 4)
	{
		DrawGraph(800, 480, IMAGE_ID("image/select.png")[0], true);
	}

	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);

	for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += 800)
	{
		tmp2.x = tmp1.x;
		DrawLine(tmp1, tmp2, 0x00ffffff, true);
	}
	tmp1 = VECTOR2(0, 0);
	tmp2.x = GAME_SCREEN_SIZE_X;
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += 480)
	{
		tmp2.y = tmp1.y;
		DrawLine(tmp1, tmp2, 0x00ffffff, true);
	}
	DrawString(0, 0, "SelectScene", 0x00ff0000);

	// Ãﬂ⁄≤‘∞ÇÃêîï™óßÇøäGï`âÊ
	for (auto& itr : (*objList))
	{
		itr->Draw(false, 0);
	}
	
	lpSceneMng.AddDraw({ selectScreen, 0,0 });
}

int SelectScene::Init(void)
{
	if (!objList)
	{
		objList = std::make_shared<sharedList>();
	}
	objList->clear();
	
	selectPos = {
		VECTOR2(100,100),
		VECTOR2(900,100),
		VECTOR2(100,580),
		VECTOR2(900,580),
	};
	for (int pIdx = 0; pIdx < GetJoypadNum(); pIdx++)
	{
		AddObjList()(objList, std::make_unique<Selector>(static_cast<PL_NUMBER>(pIdx), selectPos[pIdx], lpSceneMng.GetDrawOffset()));
	}
	backChange = 0;
	selectScreen = MakeScreen(1920, 960);

	return 0;
}
