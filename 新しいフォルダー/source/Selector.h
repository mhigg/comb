#pragma once
#include <array>
#include "Obj.h"
#include "Player.h"

enum CHARA_TYPE {
	CHARA_MAFIA,
	CHARA_GIRL,
	CHARA_OTHER,
	CHARA_OTHER2,
	CHARA_MAX
};

#define lpSelector Selector::GetInstance()

using STR_CHR_IMG = std::array<std::string, CHARA_MAX>;

class Selector :
	public Obj
{
public:
	Selector();
	Selector(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);
	~Selector();

	bool CheckObjType(OBJ_TYPE type);
	void Draw(bool game, int plNum) override;

	CHARA_TYPE GetSelChara(void);	
private:
	void SetMove(const GameCtrl &controller, weakListObj objList);

	CHARA_TYPE selectChara;		// ﾌﾟﾚｲﾔｰ毎の今選択しているｷｬﾗ
	STR_CHR_IMG standImgTbl;	// 選択したﾌﾟﾚｲﾔｰの画像
	STR_CHR_IMG pNumImgTbl;		// 何ﾌﾟﾚｲﾔｰ目かの画像
	
	std::string Image;
	PL_NUMBER plNum;
};

