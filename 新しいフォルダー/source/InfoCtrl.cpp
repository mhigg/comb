#include "InfoCtrl.h"

bool InfoCtrl::SetPlayerPos(const VECTOR2 & pos, int num)
{
	if (num > 4)
	{
		return false;
	}
	plPos[num] = pos;
	return true;
}

bool InfoCtrl::SetPlayerFlag(bool flag, int num)
{
	if (num > 4)
	{
		return false;
	}
	plFlag[num] = flag;
	return true;
}

void InfoCtrl::SetDamageFlag(bool flag, int num)
{
	if (num > 4)
	{
		return;
	}
	damaged[num] = flag;
	return;
}

bool InfoCtrl::GetDamageFlag(int num)
{
	if (num > 4)
	{
		return false;
	}
	return damaged[num];
}

bool InfoCtrl::SetEnemyPos(const VECTOR2 & pos, int num)
{
	if (num > GENERATE_MAX)
	{
		return false;
	}
	enPos[num]	= pos;
	return true;
}

bool InfoCtrl::SetEnemyFlag(bool flag, int num)
{
	enFlag[num] = flag;
	return true;
}

bool InfoCtrl::SetEnemyName(int num,int name)
{
	enName[num] = name;
	return true;
}

bool InfoCtrl::SetEnemyHit(int num,bool flag)
{
	enHit[num] = flag;
	return false;
}

bool InfoCtrl::SetAddScroll(const VECTOR2 & offset, int num)
{
	if (num > 4)
	{
		return false;
	}
	scrNum[num] = offset;
	return true;
}

bool InfoCtrl::SetScore(int val, int num)
{
	if (num > 4)
	{
		return false;
	}
	plScore[num] = val;
	return true;
}

bool InfoCtrl::SetBonus(int val, int num)
{
	if (num > 4)
	{
		return false;
	}
	plBonus[num] = val;
	return true;
}

bool InfoCtrl::SetSelectChara(CHARA_TYPE val, int num)
{
	if (num > 4)
	{
		return false;
	}
	selectChara[num] = val;
	return true;
}

VECTOR2 InfoCtrl::GetPlayerPos(int num)
{
	if (plFlag[num])
	{
		return plPos[num];
	}
	return VECTOR2(-1, -1);
}

VECTOR2 InfoCtrl::GetEnemyPos(int num)
{
	if (!enFlag[num] && !enHit[num])
	{
		return enPos[num];
	}
	return VECTOR2(-1, -1);
}
bool InfoCtrl::GetPlayerFlag(int num)
{
	return plFlag[num];
}
int InfoCtrl::GetEnemyName(int num)
{
	return enName[num];
}
bool InfoCtrl::GetEnemyHit(int num)
{
	return enHit[num];
}

bool InfoCtrl::GetEnemyFlag(int num)
{
	return enFlag[num];
}
VECTOR2 InfoCtrl::GetAddScroll(int num)
{
	return scrNum[num];
}

int InfoCtrl::GetScore(int num)
{
	return plScore[num];
}

int InfoCtrl::GetBonus(int num)
{
	return plBonus[num];
}

CHARA_TYPE InfoCtrl::GetSelectChara(int num)
{
	return selectChara[num];
}

InfoCtrl::InfoCtrl()
{
	Init();
}


InfoCtrl::~InfoCtrl()
{
}

void InfoCtrl::Init(void)
{
	plPos.resize(4);
	plFlag.resize(4);
	damaged.resize(4);
	scrNum.resize(4);
	enPos.resize(GENERATE_MAX);
	enFlag.resize(GENERATE_MAX);	
	enHit.resize(GENERATE_MAX);
	enName.resize(GENERATE_MAX);

	// ‘S‘Ì‚ÉNON‚ ‚é‚¢‚Í0(¾ÞÛ)‚ð“ü‚ê‚é
	for (int j = 0; j < GENERATE_MAX; j++)
	{	
		enPos[j]		= { 0,0 };
		enFlag[j]	= false;
		enHit[j]		= false;
		enName[j] = 0;
	}
	for (int j = 0; j < 4; j++)
	{
		plPos[j]		= { 0,0 };
		plFlag[j]	= false;
		damaged[j] = false;
		scrNum[j]	= { 0,0 };
		plScore[j] = 0;
		plBonus[j] = 0;
		selectChara[j] = CHARA_MAX;
	}
}
