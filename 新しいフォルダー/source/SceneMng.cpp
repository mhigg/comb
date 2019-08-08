#include <DxLib.h>
#include <memory>
#include "SceneMng.h"
#include "EffectMng.h"
#include "TitleScene.h"
#include "GameCtrl.h"


SceneMng::SceneMng()
{
	Init();
}

void SceneMng::Run(void)
{
	activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		gameCtrl->UpDate();
		_drawList.clear();
		activeScene = activeScene->UpDate(std::move(activeScene), (*gameCtrl));
		Draw();
		framCnt++;
	}
}

VECTOR2 SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}

void SceneMng::SetDrawOffset(VECTOR2 drawOffset)
{
	this->drawOffset = drawOffset;
}

VECTOR2 SceneMng::GetPlayScreen(bool singleFlag)
{
	return (singleFlag ? VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y) : VECTOR2(PL_SCREEN_SIZE_X, PL_SCREEN_SIZE_Y));
}

int SceneMng::GetFram(void)
{
	return framCnt;
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);

	ClsDrawScreen();

	for (auto _que : _drawList)
	{
		DrawGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(_que),
			std::get<static_cast<int>(DRAW_QUE::Y)>(_que),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_que),
			true
		);
	}

	ScreenFlip();
}

bool SceneMng::AddDraw(const Que_T& query)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(query) < 0)
	{
		return false;
	}

	_drawList.emplace_back(query);

	return true;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::Init(void)
{
	// ¼½ÃÑˆ—
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536FÓ°ÄÞ‚ÉÝ’è
	ChangeWindowMode(true);				// true:window@false:ÌÙ½¸Ø°Ý
	SetWindowText("TREASURE HUNTER");
	if (DxLib_Init() == -1) return false;

	lpEffectMng.SetUp();

	SetDrawScreen(DX_SCREEN_BACK);

	gameCtrl = std::make_unique<GameCtrl>();

	return true;
}
