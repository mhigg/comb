#include "DxLib.h"
#include "TitleScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "GameCtrl.h"
#include "SoundMng.h"


TitleScene::TitleScene()
{
	TitleScene::Init();
}

TitleScene::~TitleScene()
{

}

uniqueBase TitleScene::UpDate(uniqueBase own, const GameCtrl & controller)
{
	auto &inputState = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputStateOld = controller.GetInputState(KEY_TYPE_OLD);
	auto ctrl = controller.GetCtrl(KEY_TYPE_NOW);
	auto cntOld = controller.GetCtrl(KEY_TYPE_OLD);
	if ((ctrl[KEY_INPUT_F1]) & (!cntOld[KEY_INPUT_F1]))
	{
		PlaySoundMem(lpSoundMng.GetID("sound/Œˆ’è‰¹.wav"), DX_PLAYTYPE_BACK);
		StopSoundMem(lpSoundMng.GetID("sound/TitleBGM.mp3"));
		sceneflag = true;
	}
	if (sceneflag)
	{
		scenecnt += 6;
		if (scenecnt >= 1920)
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			return std::make_unique<MenuScene>();
		}
	}
	if (inputState[0][static_cast<int>(INPUT_ID::START)] & !inputStateOld[0][static_cast<int>(INPUT_ID::START)])
	{
		PlaySoundMem(lpSoundMng.GetID("sound/Œˆ’è‰¹.wav"), DX_PLAYTYPE_BACK);
		StopSoundMem(lpSoundMng.GetID("sound/TitleBGM.mp3"));
		sceneflag = true;
	}
	if (sceneflag)
	{
		scenecnt += 6;
		if (scenecnt >= 1920)
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			return std::make_unique<MenuScene>();
		}
	}
	TitleDraw();
	TitleScene::cnt++;
	return std::move(own);
}

void TitleScene::TitleDraw(void)
{
	cnt++;

	SetDrawScreen(titleScreen);
	ClsDrawScreen();
	if (cnt > 1)
	{
		DrawGraph(0, 0, IMAGE_ID("image/TitleD.png")[0], true);
		DrawGraph(1200, 700, IMAGE_ID("image/ƒRƒA‚Ì‚Ý.png")[0], true);
	}
	
	if (cnt / 30 % 3)
	{
		DrawGraph(400, 750, IMAGE_ID("image/psk.png")[0], true);
	}

	// Ìª°ÄÞ²Ý—p
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt * 3);

	// Ìª°ÄÞ±³Ä
	FadeOut();

	lpSceneMng.AddDraw({ titleScreen, 0,0 });
}

bool TitleScene::FadeOut(void)
{
	if (sceneflag)
	{
		fadeOutCnt -= 3;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeOutCnt);

		if (scenecnt > 1920)
		{
			fadeOutCnt = 0;
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
	return true;
}

int TitleScene::Init(void)
{
	cnt = 0;
	scenecnt = 0;
	fadeOutCnt = 255;
	sceneflag = false;

	PlaySoundMem(lpSoundMng.GetID("sound/TitleBGM.mp3"), DX_PLAYTYPE_LOOP);

	titleScreen = MakeScreen(1920, 960, true);

	return 0;
}
