#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(WEP_TYPE weapon, DIR dir, VECTOR2 setUpPos, VECTOR2 scrollOffset, VECTOR2 drawOffset) :Obj(drawOffset)
{
	AtkImgTbl = { "image/ŽaŒ‚_DOWN.png",	"image/ŽaŒ‚_DOWN.png",
				  "image/ŽaŒ‚_Left.png",	"image/ŽaŒ‚_Left.png",
				  "image/ŽaŒ‚_Right.png",	"image/ŽaŒ‚_Right.png",
				  "image/ŽaŒ‚_UP.png",		"image/ŽaŒ‚_UP.png"
	};

	this->scrollOffset = scrollOffset;
	this->weapon = weapon;
	Init("image/aura_red.png"/*AtkImgTbl[dir][weapon]*/, VECTOR2(400, 300), VECTOR2(100, 100), setUpPos);
	initAnim();
	SetAnim("ŽaŒ‚");
}


Weapon::~Weapon()
{
}

int Weapon::WeaponInit(WEP_TYPE weapon)
{
	return 0;
}

bool Weapon::initAnim(void)
{
	AddAnim("ŽaŒ‚", 0, 0, 12, 3, false);
	return true;
}

bool Weapon::CheckDeath(void)
{
	return animEndFlag;
}

bool Weapon::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_TYPE::OBJ_WEAPON);
}

void Weapon::SetMove(const GameCtrl & controller, weakListObj objList)
{
}
