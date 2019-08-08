#pragma once
#include <array>
#include "Obj.h"
#include "MapCtrl.h"
#include "GameCtrl.h"
#include "VECTOR2.h"

enum PL_NUMBER {
	PL_1,
	PL_2,
	PL_3,
	PL_4,
	PL_MAX
};

enum SCORE_DATA
{
	DATA_SCORE,
	DATA_LIFE,
	DATA_POWER,
	DATA_GUARD,
	DATA_INV,
	DATA_BONUS,
	DATA_MAX
};

struct State {
	int Power;	// 攻撃力
	int Guard;	// 防御力
	int Inv;	// 無敵時間
};

constexpr int PL_DEF_SPEED = 2;					// 歩いているときの移動速度
constexpr int PL_DASH_SPEED = 4;				// 走っているときの移動速度
constexpr unsigned int PL_RESTART_CNT = 120U;	// ﾘｽﾎﾟｰﾝまでの時間
constexpr int PL_LIFE_MAX = 3;					// ﾌﾟﾚｲﾔｰの体力上限

using UP_TIME = std::array < int, 2 >;
using ACT_ARR = std::array<VECTOR2, DIR_MAX>;


class Player :
	public Obj
{
public:
	Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset);	// 引数付きｺﾝｽﾄﾗｸﾀｰ
	Player();
	~Player();
	bool initAnim(void);						// ｱﾆﾒｰｼｮﾝ管理
	void SetData(SCORE_DATA data, int val);		// ﾌﾟﾚｲﾔｰの持つﾃﾞｰﾀの集計
	void StateDraw(void);						// ｽﾃｰﾀｽの描画
private:
	void PlInit(void);		// ﾘｽﾎﾟｰﾝの際にも必要な初期化処理まとめ
	void SetMove(const GameCtrl &controller, weakListObj objList);
	bool CheckObjType(OBJ_TYPE type);
	void GetItem(weakListObj objList);		// ｱｲﾃﾑ取得
	void Draw(bool game, int plNum) override;
	VECTOR2 sidePos			// ｻｲﾄﾞ判定
	(
		VECTOR2 pos,		// 現在位置座標
		DIR dir,			// 向いている方向
		int speed,			// 移動ｽﾋﾟｰﾄﾞ
		int sideNum
	);

// ---------- ﾌﾟﾚｲﾔｰの状態関数 ------------
	void Stop(const GameCtrl & controller, weakListObj objList);		// 停止状態
	void Move(const GameCtrl & controller, weakListObj objList);		// 歩き／走り状態
	void Attack(const GameCtrl & controller, weakListObj objList);		// 攻撃時
	void Damage(const GameCtrl & controller, weakListObj objList);		// ﾀﾞﾒｰｼﾞ時

	int speed;
	VECTOR2 startPos;			// ｽﾀｰﾄ地点(ﾘｽﾎﾟｰﾝ用)
	ACT_ARR actAdd;				// 当たり判定分の加算座標ﾃｰﾌﾞﾙ
	unsigned int NotFlag;		// 使い道不明
	State state;				// ﾌﾟﾚｲﾔｰの攻撃力/防御力/無敵時間

	int score;					// 所持ｽｺｱ
	int life;						// ﾌﾟﾚｲﾔｰの体力
	int invTime;				// inv減算用
	int damageCnt;			// ﾀﾞﾒｰｼﾞを受けてからのｶｳﾝﾄ
	bool damageFlag;		// ﾀﾞﾒｰｼﾞをうけているﾌﾗｸﾞ
	int deathInv;				// 死亡時倒れたままの時間
	int bonus;					// ﾎﾞｰﾅｽ
	int oldScore;				// 直前のｽｺｱ
	int additionTime;		// 加算するまでの時間
	int acquisitionScore;	// 加算減算されたｽｺｱ
	bool acquisitionflag;	// 表示ﾌﾗｸﾞ
	int displayTime;			// 表示する時間
	unsigned int reStartCnt;
	std::array<int,SCORE_DATA::DATA_MAX> param;

// ---------- ﾃｰﾌﾞﾙ配列 ------------
	UP_TIME	upTime;				// ステータス(攻撃,防御)上昇時間
	DIR_TBL_ARY keyIdTbl;		// 移動方向
	DIR_TBL_PTR PosTbl;			// ﾎﾟｲﾝﾀを直接格納
	DIR_TBL_A2D SpeedTbl;		// 移動速度
	DIR_TBL_DIR DirTbl;			// 移動制御
	MAP_MOVE_TBL mapMoveTbl;	// 移動制御,移動可能ｵﾌﾞｼﾞｪｸﾄならtrueを返す←ｱｲﾃﾑや障害物を追加したときに使う
	std::vector<VECTOR2> scorePosTbl;
	std::vector<VECTOR2> hpPosTbl;

	bool afterKeyFlag;			// keyの後入力を優先させるﾌﾗｸﾞ
	PL_NUMBER plNum;			// 自分が何番目のﾌﾟﾚｲﾔｰかの番号
	int randomBonus;			// ランダムにボーナスアイテムを決める
	int numTemp;
	int digit;

	void (Player::*_updater)(const GameCtrl & controller, weakListObj objList);		// 状態関数ﾎﾟｲﾝﾀ
};

