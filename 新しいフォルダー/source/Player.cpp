#include <DxLib.h>
#include <math.h>
#include <string>
#include "EffekseerForDXLib.h"
#include "Player.h"
#include "Selector.h"
#include "Weapon.h"
#include "Effect.h"
#include "StageMng.h"
#include "SoundMng.h"
#include "InfoCtrl.h"
#include "MapCtrl.h"
#include "ImageMng.h"
#include "EffectMng.h"
#include "BaseScene.h"

Player::Player(PL_NUMBER plNum, VECTOR2 setUpPos, VECTOR2 drawOffset):Obj(drawOffset)
{
	hitRad = VECTOR2(20, 20);
	actOff = VECTOR2(40, 100);
	keyIdTbl = { XINPUT_DOWN,	// 下
				 XINPUT_LEFT,	// 左
				 XINPUT_RIGHT,	// 右
				 XINPUT_UP		// 上
				};

	PosTbl = {  &pos.y,&pos.x,	// 下
				&pos.x,&pos.y,	// 左
				&pos.x,&pos.y,	// 右
				&pos.y,&pos.x	// 上
			 };
	
	SpeedTbl = { PL_DEF_SPEED,  PL_DASH_SPEED,	// 下
				-PL_DEF_SPEED, -PL_DASH_SPEED,	// 左
				 PL_DEF_SPEED,  PL_DASH_SPEED,	// 右
				-PL_DEF_SPEED, -PL_DASH_SPEED	// 上
			   };

	//			MAIN		REV		OPP1	  OPP2
	DirTbl = { DIR_DOWN ,DIR_UP   ,DIR_LEFT ,DIR_RIGHT,	// 下(REV:上)(左・右)
			   DIR_LEFT ,DIR_RIGHT,DIR_DOWN ,DIR_UP,	// 左(REV:右)(上・下)
			   DIR_RIGHT,DIR_LEFT ,DIR_DOWN ,DIR_UP,	// 右(REV:左)(上・下)
			   DIR_UP   ,DIR_DOWN ,DIR_LEFT ,DIR_RIGHT	// 上(REV:下)(左・右)
			  };

	param = { -100,
			   PL_LIFE_MAX,
			  -(state.Power - 1),
			  -state.Guard,
			  -state.Inv
			};

	mapMoveTbl = {
					true,		// NONE
					false,		// WALL1
					false,		// WALL2
					false,		// WALL3
					false,		// WALL4
					false,		// WALL5
					false,		// WALL6
					false,		// WALL7
					false,		// WALL8
					false,		// WALL9
					true,		// WALL10
					true,		// WALL11
					false,		// WALL12
					false,		// WALL13
					false,		// WALL14
					false,		// WALL15
					false,		// WALL16
					false,		// WALL17
					false,		// WALL18
					false,		// WALL19		// GetMapDataの固定ID
					false,		// WALL20
					false,		// WALL21				
					false,		// WALL22
					false,		// WALL23
					false,		// WALL24
					false,		// WALL25
					false,		// WALL26
					false,		// WALL27
					false,		// WALL28
					false,		// WALL29
					false,		// WALL30
					false,		// WALL31
					false,		// WALL32
					false,		// WALL33
					false,		// WALL34
					false,		// WALL35
					false,		// WALL36
					false,		// WALL37	
					false,		// WALL38	
					true,		// WALL39	
					false,		// DOOR1
					false,		// DOOR2
					false,		// DOOR3
					false,		// DOOR4
					true,		// POTION_1
					true,		// POTION_2
					true,		// POTION_3
					true,		// POTION_4
					true,		// COIN_1
					true,		// COIN_2
					true,		// COIN_3
					true,		// COIN_4
					true,		// KEY_1
					true,		// KEY_2
					true,		// MEAT
					true,		// PLAYER
					true,		// ENEMY
					true,		// SWORD
					true,		// SHIELD
					true,		// BOOK
					true,		// GOLD
					true,		// DIA
					false,		// BOX_1		// 宝箱
					false,		// BOX_2		// 空いている宝箱
					true,		// MOTH_1		// ﾂﾎﾞ
					false,		// MOTH_2		// 壊れたﾂﾎﾞ
					true,		// MOTH_3		// 樽
					false,		// MOTH_4		// 壊れた樽
					false,		// TREE_1		// 木
					false,		// TREE_2
					false,		// TREE_3
					false,		// TREE_4
					false,		// HOLL_1		// 井戸
					false,		// HOLL_2
					false,		// HOLL_3
					false,		// HOLL_4
					false,		// STONE_1	// 岩
					false,		// STONE_2
					false,		// STONE_3
					false,		// STONE_4
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true,
					true
	};
	actAdd = {
		VECTOR2(0, hitRad.y * 2),
		VECTOR2(-hitRad.x * 2, 0),
		VECTOR2(hitRad.x * 2, 0),
		VECTOR2(0, -hitRad.y * 2)
	};

	this->plNum = plNum;

	if (lpInfoCtrl.GetSelectChara(plNum) == CHARA_MAFIA )
	{
		Init("image/playerAll.png", VECTOR2(1040 / 13, 840 / 7), VECTOR2(13, 7), setUpPos);
	}
	if (lpInfoCtrl.GetSelectChara(plNum) == CHARA_GIRL)
	{
		Init("image/playerAll2.png", VECTOR2(1040 / 13, 840 / 7), VECTOR2(13, 7), setUpPos);
	}
	if (lpInfoCtrl.GetSelectChara(plNum) == CHARA_OTHER)
	{
		Init("image/playerAll3.png", VECTOR2(1040 / 13, 840 / 7), VECTOR2(13, 7), setUpPos);
	}
	if (lpInfoCtrl.GetSelectChara(plNum) == CHARA_OTHER2)
	{
		Init("image/playerAll3.png", VECTOR2(1040 / 13, 840 / 7), VECTOR2(13, 7), setUpPos);
	}
		
	lpImageMng.GetID("image/num.png", { 30,30 }, { 10,1 });
	lpImageMng.GetID("image/hpnum.png", { 30,30 }, { 10,1 });

	lpImageMng.GetID("image/number.png", VECTOR2(30, 30), VECTOR2(10, 1));



	startPos = pos;
	score = 0;
	oldScore = score;
	acquisitionScore = 0;
	InitScroll(static_cast<int>(plNum));
	initAnim();

	scorePosTbl = {
		{ 750,100 },
		{ 1550,100 },
		{ 750,550 },
		{ 1550,550 },
	};
	hpPosTbl = {
		{ 750,180 },
		{ 1550,180 },
		{ 750,630 },
		{ 1550,630 },
	};
	PlInit();
}

Player::Player()
{
}


Player::~Player()
{
}

bool Player::initAnim(void)
{
	AddAnim("停止", 0, 0, 1, 6, true);
	AddAnim("移動", 0, 1, 6, 8, true);
	AddAnim("疾走", 4, 1, 6, 6, true);
	AddAnim("攻撃", 8, 1, 6, 3, false);
	AddAnim("死亡", 12, 0, 7, 7, false);
	return true;
}

void Player::PlInit(void)
{
	speed = PL_DEF_SPEED;
	life = PL_LIFE_MAX;
	state = { 1,0,0 };
	upTime = { 0,0 };
	invTime = 0;
	bonus = 0;
	randomBonus = GetRand(4);

	damageFlag = false;
	damageCnt = 0;
	deathInv = 0;
	reStartCnt = 0U;
	visible = true;

	afterKeyFlag = false;

	lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
	lpInfoCtrl.SetPlayerPos(pos, static_cast<int>(plNum));

	lpSoundMng.Load("sound/攻撃音.mp3");

	_updater = &Player::Move;				// 初期状態はMove状態
}

VECTOR2 Player::sidePos(VECTOR2 pos, DIR dir, int speed, int sideNum)
{
	VECTOR2 side;
	switch (dir)
	{
	case DIR_DOWN:
		side = { sideNum,(hitRad.y) + speed - 2 };
		break;
	case DIR_LEFT:
		side = { speed - (hitRad.x),sideNum };
		break;
	case DIR_RIGHT:
		side = { (hitRad.x) + speed - 2,sideNum };
		break;
	case DIR_UP:
		side = { sideNum,speed - (hitRad.y) };
		break;
	default:
		break;
	}
	return pos + side;
}

void Player::SetMove(const GameCtrl & controller, weakListObj objList)
{
	//lpInfoCtrl.SetPlayerFlag(true, static_cast<int>(plNum));
	lpInfoCtrl.SetPlayerPos(pos,static_cast<int>(plNum));
	damageFlag = lpInfoCtrl.GetDamageFlag(plNum);
	if (!damageFlag)
	{
		GetItem(objList);
	}
	invTime = state.Inv;
	if (!lpInfoCtrl.GetPlayerFlag(plNum)) {
		visible = false;
	}

	auto &chipSize = lpStageMng.GetChipSize().x;

	(this->*_updater)(controller, objList);

	// 時間経過によるステータス変更
	// 攻撃
	if (state.Power >= 2)
	{
		upTime[0]++;
	}
	if (upTime[0] > 600)
	{
		SetData(DATA_POWER, -1);
		upTime[0] -= 600;
	}
	// 防御
	if (state.Guard >= 1)
	{
		upTime[1]++;
	}
	if (upTime[1] > 600)
	{
		SetData(DATA_GUARD, - state.Guard);
		upTime[1] -= 600;
	}
	// 無敵
	if (invTime > 0)
	{
		SetData(DATA_INV, -1);
	}
	else
	{
		invTime = 0;
	}
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return (type == OBJ_PLAYER);
}

void Player::GetItem(weakListObj objList)
{
	auto ItemID = [=] {
		auto id = lpMapCtrl.GetItemData(pos);
		if (lpMapCtrl.GetItemFlag(pos))
		{
			return (id == MAP_ID::MAX ? static_cast<MAP_ID>(ITEM_ID_START) : id);
		}
		return MAP_ID::NONE;
	};

	auto paramUP = [=](auto& paramFlag, auto limNum) {
		paramFlag += (paramFlag < limNum);
		lpMapCtrl.SetItemFlag(pos, false);
	};

	unsigned int num = 1;
	
	switch (ItemID())
	{
		case MAP_ID::POTION_1:	// 赤
			paramUP(NotFlag, num);
			SetData(DATA_POWER, 1); 
			if (state.Power > 2)
			{
				break;
			}
			AddObjList()(objList,std::make_unique<Effect>("image/aura_RED6.efk", pos + VECTOR2(0, 40), 600, scrollOffset, drawOffset + VECTOR2(0, -20)));
			break;
		case MAP_ID::POTION_2:	// 青
			paramUP(NotFlag, num);
			SetData(DATA_GUARD, 1);
			if (state.Guard > 1)
			{
				break;
			}
			AddObjList()(objList, std::make_unique<Effect>("image/aura_BLUE.efk", pos + VECTOR2(0, 40), 600, scrollOffset, drawOffset + VECTOR2(0, -20)));
			break;
		case MAP_ID::POTION_3:	// 緑
			paramUP(NotFlag, num);
			SetData(DATA_LIFE, 2);
			AddObjList()(objList, std::make_unique<Effect>("image/aura_GREEN.efk", pos + VECTOR2(0, 40), 180, scrollOffset, drawOffset + VECTOR2(0, -20)));
			break;
		case MAP_ID::POTION_4:	// 虹
			paramUP(NotFlag, num);
			SetData(DATA_INV, 180);
			AddObjList()(objList, std::make_unique<Effect>("image/aura_RED6.efk", pos + VECTOR2(0, 40), 180, scrollOffset, drawOffset + VECTOR2(0, -20)));
			break;
		case MAP_ID::COIN_1:	// 赤
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			acquisitionScore = 2;
			break;
		case MAP_ID::COIN_2:	// 青
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 3);
			acquisitionScore = 3;
			break;
		case MAP_ID::COIN_3:	// 緑
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 4);
			acquisitionScore = 4;
			break;
		case MAP_ID::COIN_4:	// 黄
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 5);
			acquisitionScore = 5;
			break;
		case MAP_ID::KEY_1:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::KEY_2:
			paramUP(NotFlag, num);
			break;
		case MAP_ID::MEAT:
			paramUP(NotFlag, num);
			SetData(DATA_LIFE, 4);
			break;
		case MAP_ID::SWORD:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			acquisitionScore = 2;
			if (randomBonus == 0)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::SHIELD:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			acquisitionScore = 2;
			if (randomBonus == 1)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::BOOK:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			acquisitionScore = 2;
			if (randomBonus == 2)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::GOLD:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			acquisitionScore = 2;
			if (randomBonus == 3)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
		case MAP_ID::DIA:
			paramUP(NotFlag, num);
			SetData(DATA_SCORE, 2);
			acquisitionScore = 2;
			if (randomBonus == 4)
			{
				SetData(DATA_BONUS, 1);
			}
			break;
	default:
		break;
	}
}

void Player::SetData(SCORE_DATA data, int val)
{
	switch (data)
	{
	case DATA_SCORE:
		score += val;
		if (score < 0)
		{
			score = 0;
		}
		if (score >= 10000)
		{
			score = 10000;
		}
		break;
	case DATA_LIFE:
		life = (life + val >= PL_LIFE_MAX ? PL_LIFE_MAX : life + val);
		break;
	case DATA_POWER:
		state.Power += val;
		if (state.Power > 3)
		{
			state.Power = 3;
		}
		break;
	case DATA_GUARD:
		state.Guard += val;
		if (state.Guard > 3)
		{
			state.Guard = 3;
		}
		break;
	case DATA_INV:
		state.Inv += val;
		break;
	case DATA_BONUS:
		bonus += val;
		break;
	}
	lpInfoCtrl.SetScore(score, static_cast<int>(plNum));
	lpInfoCtrl.SetBonus(bonus, static_cast<int>(plNum));
}

void Player::Draw(bool game, int plNum)
{
	Obj::Draw(game, plNum);
	StateDraw();
}

void Player::StateDraw(void)
{
	int drawID;
	int drawPos = 0;
	auto DrawScore = score * 100;
	VECTOR2 scorePos = scorePosTbl[plNum];
	if (DrawScore > 100 && DrawScore < 1000)
	{
		scorePos.x = scorePosTbl[plNum].x - 60;
	}
	if (DrawScore > 1000 && DrawScore < 10000)
	{
		scorePos.x = scorePosTbl[plNum].x - 90;
	}
	if (DrawScore > 10000 && DrawScore < 100000)
	{
		scorePos.x = scorePosTbl[plNum].x - 120;
	}
	if (GetJoypadNum() == 1)
	{
		scorePosTbl[0] = scorePosTbl[1];
		hpPosTbl[0] = hpPosTbl[1];
	}
	DrawGraph(scorePosTbl[plNum].x - 100, scorePosTbl[plNum].y - 45, IMAGE_ID("image/score_.png")[0], true);
	DrawGraph(hpPosTbl[plNum].x - 100, hpPosTbl[plNum].y - 45, IMAGE_ID("image/hp_.png")[0], true);
	for (auto charaCode : std::string{ std::to_string(DrawScore) })
	{
		drawID = charaCode - '0';
		if (drawID != -1)
		{
			{
				DrawGraph(scorePos.x + (30 * drawPos), scorePosTbl[plNum].y, IMAGE_ID("image/num.png")[drawID], true);
			}
		}
		drawPos++;
	}
	for (auto charaCode : std::string{ std::to_string(life) })
	{
		drawID = charaCode - '0';
		if (drawID != -1)
		{
			{
				DrawGraph(hpPosTbl[plNum].x, hpPosTbl[plNum].y, IMAGE_ID("image/hpnum.png")[drawID], true);
			}
		}
	}
}

void Player::Stop(const GameCtrl & controller, weakListObj objList)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);

	_updater = &Player::Move;

	// ﾌﾟﾚｲﾔｰのﾀﾞﾒｰｼﾞ受け(ﾃﾞﾊﾞｯｸﾞ用)
	if (inputTbl[plNum][XINPUT_MAP] & (!inputTblOld[plNum][XINPUT_MAP]))
	{
		SetAnim("停止");
		_updater = &Player::Damage;
	}

	if (inputTbl[plNum][XINPUT_ATT] & (!inputTblOld[plNum][XINPUT_ATT]))
	{
		SetAnim("攻撃");
		PlaySoundMem(lpSoundMng.GetID("sound/攻撃音.mp3"), DX_PLAYTYPE_BACK);
		AddObjList()(objList, std::make_unique<Weapon>(WEP_KNIFE, dir, pos, scrollOffset, drawOffset));
//		AddObjList()(objList, std::make_unique<Effect>("image/laser.efk", pos + VECTOR2(50, 40), 33, scrollOffset, drawOffset + VECTOR2(0, -20)));
		_updater = &Player::Attack;
	}
}

void Player::Move(const GameCtrl & controller, weakListObj objList)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);
	auto &inputTblOld = controller.GetInputState(KEY_TYPE_OLD);

	reStartCnt -= (reStartCnt > 0);		// 真の場合の1をｶｳﾝﾄから減らす
	visible = true;
	if ((reStartCnt / 3) % 2)
	{
		visible = false;
	}

	// ﾌﾟﾚｲﾔｰのﾀﾞﾒｰｼﾞ受け(ﾃﾞﾊﾞｯｸﾞ用)
	if (inputTbl[plNum][XINPUT_MAP] & (!inputTblOld[plNum][XINPUT_MAP]))
	{
		damageFlag = true;
		SetAnim("停止");
		return;
	}

	if (inputTbl[plNum][XINPUT_ATT] & (!inputTblOld[plNum][XINPUT_ATT]))
	{
		SetAnim("攻撃");
		PlaySoundMem(lpSoundMng.GetID("sound/攻撃音.mp3"), DX_PLAYTYPE_BACK);
		AddObjList()(objList, std::make_unique<Weapon>(WEP_KNIFE, dir, pos, scrollOffset, drawOffset));
//		AddObjList()(objList, std::make_unique<Effect>("image/laser.efk", pos + VECTOR2(50, 40), 33, scrollOffset, drawOffset + VECTOR2(0, -20)));
		_updater = &Player::Attack;
		return;
	}
//--------- 敵に当たった時の処理 ----------
	if (state.Inv == 0)
	{
		for (int i = 0; (i < GENERATE_MAX) && (damageFlag == false); i++)
		{
			VECTOR2 ePos = lpInfoCtrl.GetEnemyPos(i);
			if (ePos != VECTOR2(-1, -1))
			{
				VECTOR2f tmp = { ePos - pos };
				if (tmp.x * tmp.x + tmp.y * tmp.y <= 2500)
				{
					// 当たってるとき
					lpInfoCtrl.SetDamageFlag(true, plNum);
				}
			}
		}
	}

	if (damageFlag)
	{
		if (!reStartCnt)
		{
			SetAnim("停止");
			_updater = &Player::Damage;
		}
		damageFlag = false;
		return;
	}
// ----------------------------------------

	VECTOR2 scrollStart = lpStageMng.GetScrollValue(VALUE_UPPER_L, lpMapCtrl.GetMode());
	VECTOR2 scrollEnd = lpStageMng.GetScrollValue(VALUE_LOWER_R, lpMapCtrl.GetMode());

	auto Move = [&, dir = Player::dir](DIR_TBL_ID id){
		if (inputTbl[plNum][keyIdTbl[DirTbl[dir][id]]])
		{
			Player::dir = DirTbl[dir][id];		// 方向のｾｯﾄ

			if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]], -hitRad.x + 2)))]
			 || !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Player::dir, SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]],  hitRad.x - 3 /*(旧:- 1 - 2)*/)))])
			{
				Player::dir = DirTbl[dir][id];
				// 移動不可のオブジェクトが隣にあった場合
				return false;
			}

			// 移動処理-----------------------------
			// 変更したい座標の変数アドレス += 移動量
			(*PosTbl[Player::dir][TBL_MAIN]) += SpeedTbl[Player::dir][inputTbl[plNum][XINPUT_RUN_RB]];
			
			if ((pos.x >= scrollStart.x) && (pos.x <= (scrollEnd.x)))
			{
				scrollOffset.x = pos.x - scrollStart.x;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			if ((pos.y >= scrollStart.y) && (pos.y <= (scrollEnd.y)))
			{
				scrollOffset.y = pos.y - scrollStart.y;
				lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
			}
			lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
			return true;
		}
		return false;
	};

	// 後key処理------------------------------------
	if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP1 - (afterKeyFlag << 1)))		// OPP1,OPP2に移動しなかった場合
		|| Move(static_cast<DIR_TBL_ID>(DIR_TBL_OPP2 - (afterKeyFlag << 1)))))	// (key入力がなかった場合)
	{
		afterKeyFlag = false;
		if (!(Move(static_cast<DIR_TBL_ID>(DIR_TBL_MAIN + (afterKeyFlag << 1)))	// MAIN,REVに移動しなかった場合
			|| Move(static_cast<DIR_TBL_ID>(DIR_TBL_REV + (afterKeyFlag << 1)))))// (key入力がなかった場合)
		{
			SetAnim("停止");
			return;
		}
	}
	else
	{
		// OPP1もしくはOPP2にkey入力があった場合の情報
		afterKeyFlag = static_cast<bool>(inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP1]]]);
		afterKeyFlag |= static_cast<bool>(inputTbl[plNum][keyIdTbl[DirTbl[dir][DIR_TBL_OPP2]]]);
		afterKeyFlag ^= static_cast<int>(GetAnim() == "停止");
	}
	// ﾌﾟﾚｲﾔｰが走っているときは疾走ｱﾆﾒｰｼｮﾝにする
	if (inputTbl[plNum][XINPUT_RUN_RB])
	{
		SetAnim("疾走");
		return;
	}
	SetAnim("移動");
}

void Player::Attack(const GameCtrl & controller, weakListObj objList)
{
	reStartCnt -= (reStartCnt > 0);		// 真の場合の1をｶｳﾝﾄから減らす
	visible = true;
	if ((reStartCnt / 3) % 2)
	{
		visible = false;
	}

	if (!animEndFlag)
	{
		// 攻撃処理
		VECTOR2f actPos = pos + actAdd[Player::dir];
		for (int i = 0; i < GENERATE_MAX; i++)
		{
			auto tmp = lpInfoCtrl.GetEnemyPos(i);
			VECTOR2f ePos = VECTOR2f(tmp.x, tmp.y);
			if (tmp != VECTOR2(-1, -1))
			{
				VECTOR2f act = { ePos - actPos };
				if (sqrt(act.x * act.x) + sqrt(act.y * act.y) <= 40)
				{
					// 当たってるとき
					lpInfoCtrl.SetEnemyHit(i,true);
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			auto tmp = lpInfoCtrl.GetPlayerPos(i);
			VECTOR2f pPos = VECTOR2f(tmp.x, tmp.y);
			if (tmp != VECTOR2(-1, -1) && i != plNum)
			{
				VECTOR2f act = { pPos - actPos };
				if (sqrt(act.x * act.x) + sqrt(act.y * act.y) <= 40)
				{
					// 当たってるとき
					lpInfoCtrl.SetDamageFlag(true, i);
				}
			}
		}
		return;
	}
	// ｱﾆﾒｰｼｮﾝが終わったら元に戻す
	_updater = &Player::Move;
}

void Player::Damage(const GameCtrl & controller, weakListObj objList)
{
	auto &inputTbl = controller.GetInputState(KEY_TYPE_NOW);

	auto DeathPrc = [this]()
	{
		if (animEndFlag)
		{
			if (deathInv >= 80)
			{
				return true;
			}
		}
		dir = DIR_DOWN;
		SetAnim("死亡");
		return false;
	};

	if (reStartCnt)
	{
		_updater = &Player::Move;
	}

	// 死亡処理
	if (life  < 1)
	{
		if (DeathPrc())
		{
			// ﾘｽﾎﾟｰﾝ処理
			pos = startPos;
			SetData(DATA_SCORE, - 5);
			oldScore = score;
			InitScroll(static_cast<int>(plNum));
			PlInit();
			reStartCnt = PL_RESTART_CNT;
		}
		deathInv++;
		return;
	}

	if (damageCnt)
	{
		if (damageCnt % 4 == 0)
		{
			DIR tmp = DirTbl[dir][DIR_TBL_REV];
			int speed = SpeedTbl[tmp][inputTbl[plNum][0]] / 2 * -3 * (10 - damageCnt / 4);

			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, -speed,  -hitRad.x + 1)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmp, -speed, hitRad.x - 2)))])
			{
				VECTOR2 scrollStart = lpStageMng.GetScrollValue(VALUE_UPPER_L, lpMapCtrl.GetMode());
				VECTOR2 scrollEnd = lpStageMng.GetScrollValue(VALUE_LOWER_R, lpMapCtrl.GetMode());

				// 移動不可のオブジェクトが後ろにない場合
				(*PosTbl[tmp][TBL_MAIN]) += -speed;
				if ((pos.x >= scrollStart.x) && (pos.x <= (scrollEnd.x)))
				{
					scrollOffset.x = pos.x - scrollStart.x;
					lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
				}
				if ((pos.y >= scrollStart.y) && (pos.y <= (scrollEnd.y)))
				{
					scrollOffset.y = pos.y - scrollStart.y;
					lpMapCtrl.AddScroll(scrollOffset, static_cast<int>(plNum));
				}
				lpInfoCtrl.SetAddScroll(scrollOffset, static_cast<int>(plNum));
			}
			if (damageCnt / 8 % 2 == 0)
			{
				visible = false;
			}
			if(damageCnt / 8 % 2)
			{
				visible = true;
			}
		}
		if (damageCnt >= 40)
		{
			damageCnt = 0;
			
			// ﾀﾞﾒｰｼﾞｱﾆﾒｰｼｮﾝが終わったら遷移(予定)
			lpInfoCtrl.SetDamageFlag(false, plNum);
			_updater = &Player::Move;
			visible = true;
			state.Inv = 120;
			return;
		}
		damageCnt++;
		return;
	}
	else
	{
		SetData(DATA_LIFE, -1);
		damageCnt++;
		return;
	}
}