#include <DxLib.h>
#include <memory>
#include "GameScene.h"
#include "EditScene.h"
#include "ResultScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "StageMng.h"
#include "GameCtrl.h"
#include "InfoCtrl.h"
#include "Player.h"
#include "VECTOR2.h"
#include "SoundMng.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

uniqueBase GameScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto ctrlOld = controller.GetCtrl(KEY_TYPE_OLD);

	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	
	if (ctrl[KEY_INPUT_F1] & ~ctrlOld[KEY_INPUT_F1])
	{
		return std::make_unique<EditScene>();
	}
	if (ctrl[KEY_INPUT_F2] & ~ctrlOld[KEY_INPUT_F2])
	{
		StopSoundMem(lpSoundMng.GetID("sound/naked.wav"));
		return std::make_unique<ResultScene>();
	}
#ifdef _DEBUG
	if (inputState[0][XINPUT_START] & !inputStateOld[0][XINPUT_START])
	{
		return std::make_unique<EditScene>();
	}
	
#endif // DEBUG

	for (auto& obj : (*objList))
	{
		obj->UpDate(controller, objList);
	}
	objList->remove_if([](sharedObj &obj) { return obj->CheckDeath(); });

	// écÇËéûä‘å∏è≠
	gameFrame--;

	Draw();

	if (gameFrame % 1800 == 0)
	{
		int tmp = 0;
		for (int i = 0; i < GENERATE_MAX; i++)
		{
			if (lpInfoCtrl.GetEnemyFlag(i))
			{
				VECTOR2 Ipos = lpMapCtrl.GetItemPos(MAP_ID::ENEMY, tmp);
				lpMapCtrl.SetUpEnemy(objList, i, Ipos.x, Ipos.y,lpInfoCtrl.GetEnemyName(i));
				tmp++;
			}
		}
		lpMapCtrl.SetItemFlagAll();
	}

	return move(own);
}

int GameScene::Init(void)
{
	if (!objList)
	{
		objList = std::make_shared<sharedList>();
	}
	objList->clear();

	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapCtrl.SetUp(lpStageMng.GetChipSize(), lpSceneMng.GetDrawOffset());
	lpMapCtrl.MapLoad(objList, false);
	lpSoundMng.GetID("sound/naked.wav");
	gameFrame = 10800;
	tile = LoadGraph("image/tile.png", true);
	bool single = lpMapCtrl.GetMode();
	VECTOR2 size = lpSceneMng.GetPlayScreen(single);
	int pl = (single ? 1 : GetJoypadNum());
	for (int p = 0; p < pl; p++)
	{
		ghGameScreen[p] = MakeScreen(size.x, size.y, true);
	}
	gameScreen = MakeScreen(1920, 960, true);
	single = lpMapCtrl.GetMode();
	PlaySoundMem(lpSoundMng.GetID("sound/naked.wav"), DX_PLAYTYPE_LOOP);
	player = std::make_shared<Player>();
	return 0;
}

void GameScene::Draw(void)
{
	//SetDrawScreen(gameScreen);
	ClsDrawScreen();
	(*objList).sort([](sharedObj& obj1, sharedObj& obj2) { return (*obj1).GetPos().y < (*obj2).GetPos().y; });

	lpMapCtrl.Draw(single);

	int plMax = (single ? 1 : GetJoypadNum());
	for (int p = 0; p < plMax; p++)
	{
		SetDrawScreen(ghGameScreen[p]);
		ClsDrawScreen();

		//DrawGraph(0, 0, tile, true);
		VECTOR2 plPos = lpInfoCtrl.GetPlayerPos(p);

		// objListÇ©ÇÁâÊñ äOÇÃµÃﬁºﬁ™∏ƒÇèúäOÇ∑ÇÈ
		//auto tmpList = (*objList);
		//tmpList.erase(tmpList.remove_if([&](sharedObj &tmp) {
		//	if (tmp->GetPos().x < plPos.x - CHIP_SIZE * 6
		//		|| tmp->GetPos().x > plPos.x + CHIP_SIZE * 6
		//		|| tmp->GetPos().y < plPos.y - CHIP_SIZE * 6
		//		|| tmp->GetPos().y > plPos.y + CHIP_SIZE * 6)
		//	{
		//		return true;
		//	}
		//	return false;
		//}));

		// Å¶ ï`âÊÇÃø∞ƒèàóù
		//tmpList.sort([](sharedObj& obj1, sharedObj& obj2) { return (*obj1).GetPos().y < (*obj2).GetPos().y; });
		//int playerNum = GetJoypadNum();

		for (auto& obj : (*objList))
		{
			obj->Draw(false, p);
		}

		auto plScr = lpMapCtrl.GetScreenPos(p);
		lpSceneMng.AddDraw({ ghGameScreen[p], plScr.x, plScr.y });
	}

	//auto plScr = lpMapCtrl.GetScreenPos(2);
	//lpSceneMng.AddDraw({ ghGameScreen[1], plScr.x, plScr.y });

	//for (int p = 0; p < GetJoypadNum(); p++)
	//{
	//	DrawGraph(lpMapCtrl.GetScreenPos(p).x, lpMapCtrl.GetScreenPos(p).y, ghGameScreen[p], true);
	//}

	auto _befor = GetDrawScreen();
	SetDrawScreen(gameScreen);
	ClsDrawScreen();

#ifdef _DEBUG

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

	DrawString(0, 800, "GameScene", 0x00ff0000);
	DrawFormatString(1400, 930, 0xff, "frame / 60:%d", lpSceneMng.GetFram() / 60);

#else
#endif // DEBUG

	// éûä‘ï\é¶
	int timeDigit = 0;
	int minNumTemp = gameFrame / 3600;
	int secondNumTemp = (gameFrame % 3600) / 60;
	// ï™Ç™0ÇÃéû
	if (minNumTemp < 1)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - 40, 10, lpImageMng.GetID("image/number2.png", { 40,30 }, { 10,1 })[0], true);
	}
	// ï™
	while (minNumTemp > 0)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - 40, 10, lpImageMng.GetID("image/number2.png", { 40,30 }, { 10,1 })[minNumTemp % 10], true);
		minNumTemp /= 10;
	}
	// ïbÇ™0ÇÃéû
	if (secondNumTemp < 10)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2, 10, lpImageMng.GetID("image/number2.png", { 40,30 }, { 10,1 })[0], true);
	}
	if (secondNumTemp < 1)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2, 10, lpImageMng.GetID("image/number2.png", { 40,30 }, { 10,1 })[0], true);
	}
	// ïb
	while (secondNumTemp > 0)
	{
		DrawGraph(GAME_SCREEN_SIZE_X / 2 - (timeDigit + 1) * 20 + (30), 10, lpImageMng.GetID("image/number2.png", { 40,30 }, { 10,1 })[secondNumTemp % 10], true);
		secondNumTemp /= 10;
		timeDigit++;
	}
	DrawGraph(GAME_SCREEN_SIZE_X / 2 - 10, 16, IMAGE_ID("image/jikan.png")[0], true);
	DrawGraph(GAME_SCREEN_SIZE_X / 2 - 70, 5, IMAGE_ID("image/sunatokei.png")[0], true);

	lpSceneMng.AddDraw({ gameScreen, 0,0 });

	SetDrawScreen(_befor);
	
}

int	DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(
		vec1.x,
		vec1.y,
		vec2.x,
		vec2.y,
		Color,
		Thickness
	);
	return 0;
}