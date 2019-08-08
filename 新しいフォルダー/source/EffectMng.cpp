#include "EffectMng.h"
#include "EffekseerForDXLib.h"
#include "SceneMng.h"

EffectMng::EffectMng()
{
	Init();
}


EffectMng::~EffectMng()
{
}

bool EffectMng::SetUp(void)
{
	//int playingEffectHandle = -1;
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	return true;
}

const VEC_INT & EffectMng::GetID(std::string efk_name, float magnification)
{
	if (effectMap.find(efk_name) == effectMap.end())
	{
		effectMap[efk_name].resize(1);

		// LoadEffekseerEffect(efkÌ§²Ù–¼, Šg‘å—¦)
		effectMap[efk_name][0] = LoadEffekseerEffect(efk_name.c_str(), magnification);
	}

	return effectMap[efk_name];
}

bool EffectMng::Init(void)
{
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_Set2DSetting(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	return true;
}
