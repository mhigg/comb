#include "Effect.h"
#include "EffekseerForDXLib.h"
#include "EffectMng.h"
#include "InfoCtrl.h"


Effect::Effect()
{
}

Effect::Effect(std::string efkName, VECTOR2 setUpPos, int lastingTime, VECTOR2 scrollOffset, VECTOR2 drawOffset) :Obj(drawOffset)
{
	SetPos(setUpPos);
	this->scrollOffset = scrollOffset;
	this->lastingTime = lastingTime;
	efkImg = lpEffectMng.GetID(efkName, 5.0f)[0];
	time = 0;
}


Effect::~Effect()
{
}

bool Effect::CheckDeath(void)
{
	return (lastingTime <= 0);
}

bool Effect::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_EFFECT);
}

void Effect::Draw(bool game, int plNum)
{
	DrawEffekseer2D();
}

void Effect::SetMove(const GameCtrl & controller, weakListObj objList)
{
	scrollOffset = lpInfoCtrl.GetAddScroll(0);
	pos = lpInfoCtrl.GetPlayerPos(0);
	int playingEffectHandle = -1;
	// エフェクトを再生する。
	if (time % 60 == 0)
	{
		playingEffectHandle = PlayEffekseer2DEffect(efkImg);
	}

	SetPosPlayingEffekseer2DEffect(playingEffectHandle, pos.x + drawOffset.x - scrollOffset.x, pos.y + drawOffset.y - scrollOffset.y, 0);

	UpdateEffekseer2D();
	

	// 時間を経過させる。
	time++;

	lastingTime--;
}
