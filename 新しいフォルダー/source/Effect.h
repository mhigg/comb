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

	int efkImg;			// ｴﾌｪｸﾄﾃﾞｰﾀ名:efkﾌｧｲﾙ
	int lastingTime;	// ｴﾌｪｸﾄの持続時間

	int time;
};

