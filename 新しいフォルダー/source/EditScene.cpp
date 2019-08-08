#include "DxLib.h"
#include <windows.h>
#include "SceneMng.h"
#include "EditScene.h"
#include "MapCtrl.h"
#include "ImageMng.h"
#include "EditCursor.h"
#include "GameCtrl.h"
#include "GameScene.h"
#include "StageMng.h"

EditScene::EditScene()
{
	EditScene::Init();
}

EditScene::~EditScene()
{
}

uniqueBase EditScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto cnt = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);

	if (cnt[KEY_INPUT_F5])
	{
		// ﾛｰﾄﾞ
		if (MessageBox(
			NULL,
			"エディット内容をロードしますか？",
			"確認ダイアログ",
			MB_OKCANCEL
		) == IDOK)
		{
			lpMapCtrl.MapLoad(objList, true);
		}
	}
	if (cnt[KEY_INPUT_F6])
	{
		// ｾｰﾌﾞ
		if (MessageBox(
			NULL,
			"エディット内容をセーブしますか？",
			"確認ダイアログ",
			MB_OKCANCEL
		) == IDOK)
		{
			lpMapCtrl.MapSave();
		}
	}
	if (cnt[KEY_INPUT_F1] & (!cntOld[KEY_INPUT_F1]))
	{
		return std::make_unique<GameScene>();
	}
	if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
	{
		return std::make_unique<GameScene>();
	}

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	EditDraw();
	return std::move(own);
}

bool EditScene::EditDraw(void)
{
	ClsDrawScreen();
	lpMapCtrl.Draw(true);
	for (auto& itr : (*objList))
	{
		itr->Draw(false, 0);
	}
	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
	VECTOR2 offset(VECTOR2(0, 0));

	for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE)
	{
		tmp2.x = tmp1.x;
		DrawLine(offset + tmp1, offset + tmp2, 0x00ffffff, true);
	}
	tmp1 = VECTOR2(0, 0);
	tmp2.x = GAME_SCREEN_SIZE_X;
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE)
	{
		tmp2.y = tmp1.y;
		DrawLine(offset + tmp1, offset + tmp2, 0x00ffffff, true);
	}
	DrawString(0, 0, "EditScene", 0x00ff0000);
	ScreenFlip();
	return true;
}

int EditScene::Init(void)
{
	if (!objList)
	{
		objList = std::make_shared<sharedList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapCtrl.SetUp(lpStageMng.GetChipSize(), lpSceneMng.GetDrawOffset());
	auto obj = AddObjList()(objList, std::make_unique<EditCursor>(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y)));
	(*obj)->Init("image/mapImage.png", VECTOR2(40, 40), VECTOR2(8, 10));
	return 0;
}