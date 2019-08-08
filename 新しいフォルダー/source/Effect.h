#pragma once
#include "Obj.h"
#include "VECTOR2.h"

class Effect :
	public Obj
{
public:
	Effect();
	Effect(std::string efkName, VECTOR2 setUpPos, int lastingTime, VECTOR2 scrollOffset, VECTOR2 drawOffset);
	~Effect();

	bool CheckDeath(void);
	bool CheckObjType(OBJ_TYPE type);
	void Draw(bool game, int plNum);

private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	int efkImg;			// ´Ìª¸ÄÃŞ°À–¼:efkÌ§²Ù
	int lastingTime;	// ´Ìª¸Ä‚Ì‘±ŠÔ

	int time;
};

