#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "MAP_ID.h"
#include "ClassObj.h"
#include "Selector.h"

#define lpInfoCtrl InfoCtrl::GetInstance()
constexpr int GENERATE_MAX = 20;

class InfoCtrl
{
public:
	static InfoCtrl &GetInstance(void)
	{
		static InfoCtrl s_Instance;
		return s_Instance;
	}
	bool SetPlayerPos(const VECTOR2 & pos, int num);
	bool SetPlayerFlag(bool flag, int num);
	void SetDamageFlag(bool flag, int num);
	bool GetDamageFlag(int num);
	bool SetAddScroll(const VECTOR2 & offset, int num);					// ﾌﾟﾚｲﾔｰのみが呼ぶ

	bool SetEnemyPos(const VECTOR2 & pos, int num);
	bool SetEnemyFlag(bool flag, int num);
	bool SetEnemyName(int num,int name);
	bool SetEnemyHit(int num, bool flag);

	bool SetScore(int val, int num);									// ｽｺｱｾｯﾄ(ﾘｻﾞﾙﾄ用)
	bool SetBonus(int val, int num);									// ﾎﾞｰﾅｽｾｯﾄ(ﾘｻﾞﾙﾄ用)
	bool SetSelectChara(CHARA_TYPE val, int num);			// 選んでいるｷｬﾗｾｯﾄ

	VECTOR2 GetPlayerPos(int num);
	bool GetPlayerFlag(int num);
	int GetEnemyName(int num);
	bool GetEnemyHit(int num);

	VECTOR2 GetEnemyPos(int num);
	bool GetEnemyFlag(int num);

	VECTOR2 GetAddScroll(int num);							
	int GetScore(int num);												// ｽｺｱ取得(ﾘｻﾞﾙﾄ用)
	int GetBonus(int num);												// ﾎﾞｰﾅｽ取得(ﾘｻﾞﾙﾄ用)
	CHARA_TYPE GetSelectChara(int num);									// 選んでいるｷｬﾗ取得
private:
	InfoCtrl();
	~InfoCtrl();

	void Init(void);
	std::vector<VECTOR2> enPos;					// 座標管理
	std::vector<bool> enFlag;					// 存在するかどうか
	std::vector<bool> enHit;					// 当たり判定中か
	std::vector<int> enName;					// 敵の名前
	std::vector<VECTOR2>plPos;
	std::vector<bool> plFlag;
	std::vector<bool> damaged;
	std::vector<VECTOR2> scrNum;
	std::array<int,4> plScore;					// 最大ﾌﾟﾚｲﾔｰ数のｽｺｱ
	std::array<int,4> plBonus;					// 最大ﾌﾟﾚｲﾔｰ数のﾎﾞｰﾅｽ
	std::array<CHARA_TYPE,4> selectChara;		// 最大ﾌﾟﾚｲﾔｰ数の選んだｷｬﾗ
};

