#include <DxLib.h>
#include <algorithm>
#include <stdlib.h>
#include "Enemy.h"
#include "StageMng.h"
#include "GameCtrl.h"
#include "MapCtrl.h"
#include "InfoCtrl.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int enemyNum, VECTOR2 setUpPos, VECTOR2 drawOffset, int enCnt) :Obj(drawOffset)
{
	Enemy::enCnt = enCnt;
	keyIdTbl = {
		XINPUT_DOWN,			// 下
		XINPUT_LEFT,			// 左
		XINPUT_RIGHT,			// 右
		XINPUT_UP				// 上
	};
	PosTbl = {
		&pos.y,&pos.x,			// 下
		&pos.x,&pos.y,			// 左
		&pos.x,&pos.y,			// 右
		&pos.y,&pos.x			// 上
	};
	SpeedTbl = {
		//			通常						ﾀﾞｯｼｭ
		ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// 下
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED,		// 左
		 ENEMY_SPEED	,  ENEMY_DASH_SPEED,		// 右
		-ENEMY_SPEED	, -ENEMY_DASH_SPEED		// 上
	};
	dirOpp = {
		DIR_DOWN	,DIR_LEFT		,DIR_RIGHT,
		DIR_LEFT		,DIR_DOWN	,DIR_UP,
		DIR_RIGHT	,DIR_DOWN	,DIR_UP,
		DIR_UP			,DIR_LEFT		,DIR_RIGHT
	};
	rootPass = {
		DIR_UP			,DIR_RIGHT	,DIR_LEFT,
		DIR_RIGHT	,DIR_UP		,DIR_DOWN,
		DIR_LEFT		,DIR_UP		,DIR_DOWN,
		DIR_DOWN	,DIR_RIGHT	,DIR_LEFT		
	};
	mapMoveTbl = {
					true,			// NONE
					false,			// WALL1
					false,			// WALL2
					false,			// WALL3
					false,			// WALL4
					false,			// WALL5
					false,			// WALL6
					false,			// WALL7
					false,			// WALL8
					false,			// WALL9
					true,			// WALL10
					true,			// WALL11
					false,	// WALL12
					false,	// WALL13
					false,	// WALL14
					false,	// WALL15
					false,	// WALL16
					false,	// WALL17
					false,	// WALL18
					false,	// WALL19	// GetMapDataの固定ID
					false,	// WALL20
					false,	// WALL21				
					false,	// WALL22
					false,	// WALL23
					false,	// WALL24
					false,	// WALL25
					false,	// WALL26
					false,	// WALL27
					false,	// WALL28
					false,	// WALL29
					false,	// WALL30
					false,	// WALL31
					false,	// WALL32
					false,  // WALL33
					false,  // WALL34
					false,  // WALL35
					false,  // WALL36
					false,	// WALL37	
					false,	// WALL38	
					true,		// WALL39	
					false,	// DOOR1
					false,	// DOOR2
					false,	// DOOR3
					false,	// DOOR4
					true,		// POTION_1
					true,		// POTION_2
					true,		// POTION_3
					true,		// POTION_4
					true,		// COIN_1
					true,	// COIN_2
					true,	// COIN_3
					true,	// COIN_4
					true,	// KEY_1
					true,	// KEY_2
					true,	// MEAT
					true,	// PLAYER
					true,	// ENEMY
					true,	// SWORD
					true,	// SHIELD
					true,	// BOOK
					true,	// GOLD
					true,	// DIA
					true,	// BOX_1	// 宝箱
					true,	// BOX_2	// 空いている宝箱
					true,	// MOTH_1	// ﾂﾎﾞ
					false,	// MOTH_2	// 壊れたﾂﾎﾞ
					true,	// MOTH_3	// 樽
					false,	// MOTH_4	// 壊れた樽
					false,	// TREE_1	// 木
					false,	// TREE_2
					false,	// TREE_3
					false,	// TREE_4
					false,	// HOLL_1	// 井戸
					false,	// HOLL_2
					false,	// HOLL_3
					false,	// HOLL_4
					false,	// STONE_1	// 岩
					false,	// STONE_2
					false,	// STONE_3
					false,	// STONE_4	
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
	this->objType = OBJ_ENEMY;
	actOff = VECTOR2(30, 40);
	hitRad = VECTOR2(30, 30);
	behaviorCnt = 0;
	name = static_cast<ENEMY>(enemyNum);
	life = enemyNum;
	action = ENEM_ACT::MOVE;
	Init("image/enemy.png", VECTOR2(480 / 8,400 / 5),VECTOR2(8,5), setUpPos);
	comPos.resize(12);
	initAnim();
	EnInit();
	CheckFree();
}

void Enemy::EnInit(void)
{
	nearP = 0;
	speed = ENEMY_SPEED;
	// ｶｳﾝﾄ系
	deathCnt = 60;
	timeCnt = 0;
	actCnt = 60;
	addCnt = { 0,0 };
	oppFlag = false;
	rootPos = VECTOR2(-1, -1);
	firstPos = VECTOR2(-1, -1);
}

void Enemy::CheckFree(void)
{
	movePos = 0;
	int actRoot = 0;
	for (int i = 0; i < 4; i++)
	{
		plPos[i] = lpInfoCtrl.GetPlayerPos(i);
		enPos[i] = -1;
		for (int m = 0; m < 3; m++)
		{
			actNum[m] = 0;
			passFlag[i + m * 4] = false;
			checkPos[i + m * 4] = VECTOR2(0, 0);
			comPos[i + m * 4] = 10000.0;
		}
	}
}

bool Enemy::initAnim(void)
{
	visible = true;
	int num = static_cast<int>(name) * 2;
	AddAnim("右待機", num, 0, 2, 10, true);				// 右
	AddAnim("左待機", num + 1, 0, 2, 10, true);		// 左
	AddAnim("右探索", num, 2, 2, 10, true);
	AddAnim("左探索", num + 1, 2, 2, 10, true);
	AddAnim("右発見", num, 4, 1, 30, false);
	AddAnim("左発見", num + 1, 4, 1, 30, false);
	return true;
}

Enemy::~Enemy()
{
}

VECTOR2 Enemy::sidePos(VECTOR2 pos, DIR dir, int speed, int sideNum)
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

VECTOR2 Enemy::Distance(DIR tmpDir,VECTOR2 pos)
{
	switch (tmpDir)
	{
	case DIR_DOWN:
	case DIR_UP:
		while (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], -hitRad.x)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], hitRad.x - 1)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], 0)))]
			&& (pos.y != plPos[nearP].y))
		{	
			pos.y += SpeedTbl[tmpDir][0];	
		}
		break;
	case DIR_RIGHT:
	case DIR_LEFT:
		while (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], -hitRad.x)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], hitRad.x - 1)))]
			&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, tmpDir, SpeedTbl[tmpDir][0], 0)))]
			&& (pos.x != plPos[nearP].x))
		{
			pos.x += SpeedTbl[tmpDir][0];
		}
		break;
	default:
		break;
	}
	return pos;
}

int Enemy::SerchPlayer(bool flag)
{
	VECTOR2 tmpPos = Enemy::pos;
	for (int i = 0; i < 4; i++)
	{
		plPos[i] = lpInfoCtrl.GetPlayerPos(i);
		if (plPos[i] != VECTOR2(-1, -1))
		{
			VECTOR2 tmp = tmpPos - plPos[i];
			enPos[i] = static_cast<int>(sqrt(tmp.x * tmp.x) + sqrt(tmp.y * tmp.y));
		}
	}
	int plNum = 0;
	for (int i = 1; i < 4; i++)
	{
		if (enPos[i] < enPos[plNum] && enPos[i] != -1)
		{
			plNum = i;
		}
	}
	if (!flag)
	{
		return enPos[plNum];
	}
	return plNum;
}

void Enemy::SetMove(const GameCtrl & controller, weakListObj objList)
{
	scrollOffset = lpInfoCtrl.GetAddScroll(0);

	// ﾀﾞﾒｰｼﾞをうけてるかるかどうか
	if (lpInfoCtrl.GetEnemyHit(Enemy::enCnt))
	{
		action = ENEM_ACT::DAMAGE;
	}
	// 最も近いﾌﾟﾚｲﾔｰの検索
	nearP = SerchPlayer(true);

	// 敵の種類によってﾊﾟﾀｰﾝを変える
	switch (name)
	{
	case ENEMY::ENEMY_1:
		GateKeeper();
		break;
	case ENEMY::ENEMY_2:
		Undette();
		break;
	case ENEMY::ENEMY_3:
		Zombie();
		break;
	default:
		break;
	}
	(this->*_updater)(controller);
	switch (action)
	{
	case ENEM_ACT::SERCH:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("右発見");
			break;
		case DIR_LEFT:
			SetAnim("左発見");
			break;
		default:
			break;
		}
		break;
	case ENEM_ACT::MOVE:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("右待機");
			break;
		case DIR_LEFT:
			SetAnim("左待機");
			break;
		default:
			break;
		}
		break;
	case ENEM_ACT::TRA:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("右待機");
			break;
		case DIR_LEFT:
			SetAnim("左待機");
			break;
		default:
			break;
		}
		break;
	case ENEM_ACT::CONST_MOVE:
		switch (dir)
		{
		case DIR_RIGHT:
			SetAnim("右待機");
			break;
		case DIR_LEFT:
			SetAnim("左待機");
			break;
		default:
			break;
		}
	}
	if (behaviorCnt == 0)
	{
		SetAnim("左待機");
	}
	
	lpInfoCtrl.SetEnemyPos(pos, enCnt);
	timeCnt++;
	behaviorCnt++;
}

void Enemy::GateKeeper(void)
{
	switch (action)
	{
	case ENEM_ACT::WAIT:
		if (GetRand(60) % 30 == 0)
		{
			action = ENEM_ACT::CONST_MOVE;
		}
		_updater = &Enemy::Wait;
		break;
	case ENEM_ACT::CONST_MOVE:
		_updater = &Enemy::ConstMove;
		break;
	case ENEM_ACT::TRA:
		_updater = &Enemy::Track;
		break;
	case ENEM_ACT::BACK:
		_updater = &Enemy::Back;
		break;
	case ENEM_ACT::SERCH:
		_updater = &Enemy::Serch;
		break;
	case ENEM_ACT::DAMAGE:
		_updater = &Enemy::Damage;
		return;
	default:
		action = ENEM_ACT::WAIT;
		_updater = &Enemy::Wait;
		break;
	}
	return;
}

void Enemy::Undette(void)
{
	switch (action)
	{
	case ENEM_ACT::WAIT:
		if (GetRand(60) % 30 == 0)
		{
			action = ENEM_ACT::MOVE;
		}
		_updater = &Enemy::Wait;
		break;
	case ENEM_ACT::MOVE:
		_updater = &Enemy::Move;
		break;
	case ENEM_ACT::TRA:
		_updater = &Enemy::Track;
		break;
	case ENEM_ACT::DAMAGE:
		_updater = &Enemy::Damage;
		return;
	default:
		action = ENEM_ACT::MOVE;
		_updater = &Enemy::Move;
		break;
	}
}

void Enemy::Zombie(void)
{
	switch (action)
	{
	case ENEM_ACT::WAIT:
		if (GetRand(60) % 30 == 0)
		{
			action = ENEM_ACT::MOVE;
		}
		_updater = &Enemy::Wait;
		break;
	case ENEM_ACT::MOVE:
		_updater = &Enemy::Move;
		break;
	case ENEM_ACT::TRA:
		_updater = &Enemy::Track;
		break;
	case ENEM_ACT::DAMAGE:
		_updater = &Enemy::Damage;
		return;
	default:
		action = ENEM_ACT::MOVE;
		_updater = &Enemy::Move;
		break;
	}
}

void Enemy::ConstMove(const GameCtrl & controller)
{
	if (SerchPlayer(false) < SERCH_LIM - 50)
	{
		firstPos = pos;
		action = ENEM_ACT::SERCH;
		return;
	}
	if (oppFlag)
	{
		Enemy::dir = DIR_RIGHT;
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], 0)))])
		{
			// 移動不可のオブジェクトが隣にあった場合
			oppFlag = false;
			action = ENEM_ACT::WAIT;
			return;
		}
		// 移動処理-----------------------------
		(*PosTbl[Enemy::dir][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		return;
	}
	else
	{
		Enemy::dir = DIR_LEFT;
		if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
			|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], 0)))])
		{
			// 移動不可のオブジェクトが隣にあった場合
			oppFlag = true;
			action = ENEM_ACT::WAIT;
			return;
		}
		// 移動処理-----------------------------
		(*PosTbl[Enemy::dir][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		return;
	}
}

void Enemy::Move(const GameCtrl & controller)
{
	int num = GetRand(10) + 20;
	if (!(timeCnt % num))
	{
		switch (GetRand(4))
		{
		case 0:
			Enemy::dir = DIR_DOWN;
			break;
		case 1:
			Enemy::dir = DIR_LEFT;
			break;
		case 2:
			Enemy::dir = DIR_RIGHT;
			break;
		case 3:
			Enemy::dir = DIR_UP;
			break;
		case 4:
			action = ENEM_ACT::SERCH;
		default:
			break;
		}
		timeCnt = 0;
	}	
	if (action == ENEM_ACT::SERCH)
	{
		return;
	}
	if (!mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], -hitRad.x)))]
		|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], hitRad.x - 1)))]
		|| !mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, Enemy::dir, SpeedTbl[Enemy::dir][0], 0)))])
	{
		// 移動不可のオブジェクトが隣にあった場合
		Enemy::dir = dir;
		return;
	}
	// 移動処理-----------------------------
	(*PosTbl[Enemy::dir][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
	return;
}

void Enemy::Track(const GameCtrl & controller)
{
	//-----------移動-------------
	int tmpAct = actRoot % 4;
	movePos = 0;
	switch (tmpAct)
	{
	case 0:
	case 3:
		if ((*PosTbl[tmpAct][TBL_MAIN]) != checkPos[actRoot].y
			&& ((*PosTbl[tmpAct][TBL_MAIN]) != plPos[nearP].y))
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], 0)))])
			{
				dir = static_cast<DIR>(tmpAct);
				(*PosTbl[tmpAct][TBL_MAIN]) += SpeedTbl[tmpAct][0];
				movePos += SpeedTbl[tmpAct][0];
				if ((*PosTbl[tmpAct][TBL_MAIN]) == plPos[nearP].y
				|| (*PosTbl[tmpAct][TBL_MAIN]) == checkPos[actRoot].y)
				{
					rootPos = pos;
					return;
				}
			}
		}
		else
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], 0)))])
			{
				dir = dirOpp[tmpAct][actRoot / 4];
				(*PosTbl[tmpAct][TBL_OPP]) += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
				movePos += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
			}
			if ((*PosTbl[tmpAct][TBL_OPP]) == plPos[nearP].x
			||	(*PosTbl[tmpAct][TBL_OPP]) == checkPos[actRoot].x)
			{
				action = ENEM_ACT::BACK;
				return;
			}
		}
		break;
	case 1:
	case 2:
		if ((*PosTbl[tmpAct][TBL_MAIN]) != checkPos[actRoot].x
			&& (*PosTbl[tmpAct][TBL_MAIN]) != plPos[nearP].x)
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, static_cast<DIR>(tmpAct), SpeedTbl[static_cast<DIR>(tmpAct)][0], 0)))])
			{
				dir = static_cast<DIR>(tmpAct);
				(*PosTbl[tmpAct][TBL_MAIN]) += SpeedTbl[tmpAct][0];
				movePos += SpeedTbl[tmpAct][0];
				if ((*PosTbl[tmpAct][TBL_MAIN]) == plPos[nearP].x
				|| (*PosTbl[tmpAct][TBL_MAIN]) == checkPos[actRoot].x)
				{
					rootPos = pos;
					return;
				}
			}
		}
		else
		{
			if (mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], -hitRad.x)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], hitRad.x - 1)))]
				&& mapMoveTbl[static_cast<int>(lpMapCtrl.GetMapData(sidePos(pos, dirOpp[tmpAct][actRoot / 4], SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0], 0)))])
			{
				dir = dirOpp[tmpAct][actRoot / 4];
				(*PosTbl[tmpAct][TBL_OPP]) += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
				movePos += SpeedTbl[dirOpp[tmpAct][actRoot / 4]][0];
			}
			if ((*PosTbl[tmpAct][TBL_OPP]) == plPos[nearP].y
			|| (*PosTbl[tmpAct][TBL_OPP]) == checkPos[actRoot].y)
			{
				action = ENEM_ACT::BACK;
				return;
			}
		}
		break;
	}
	if (movePos == 0)
	{
		action = ENEM_ACT::BACK;
		return;
	}
}

//-------------ﾊﾟｽ探索(移動ﾊﾟｽがない時のみ)-----------
void Enemy::Serch(const GameCtrl & controller)
{
	if (actCnt == 60)
	{
		CheckFree();
		//---------------第一分岐点の設定----------------
		for (DIR tmp = DIR_DOWN; tmp < DIR::DIR_MAX; tmp = static_cast<DIR>(tmp + 1))
		{
			VECTOR2 tmpPos = pos;
			checkPos[static_cast<int>(tmp)] = Distance(tmp, tmpPos);
			passFlag[static_cast<int>(tmp)] = true;
			//------------第二分岐点の設定---------------
			for (int opp = 1; opp < 3; opp++)
			{
				int setDir = tmp + opp * 4;
				checkPos[setDir] = Distance(dirOpp[tmp][opp], checkPos[static_cast<int>(tmp)]);
				passFlag[setDir] = true;
			}
		}
		//---------優先度を設定-------------
		for (int e = 0; e < 12; e++)
		{
			if (passFlag[e])
			{
				VECTOR2 exPos = { plPos[nearP].x - checkPos[e].x ,plPos[nearP].y - checkPos[e].y };
				comPos[e] = sqrt(exPos.x*exPos.x) + sqrt(exPos.y * exPos.y);
			}
		}
		// 第一、第二分岐点までのDIRを決定
		for (int e = 1; e < 12; e++)
		{
			if (comPos[e] < comPos[actRoot])
			{
				actNum[2] = e;
				actRoot = e;
			}
		}
	}
	if (actCnt <= 0)
	{
		action = ENEM_ACT::TRA;
		actCnt = 60;
		return;
	}
	actCnt--;
	return;
}

void Enemy::Escape(const GameCtrl & controller)
{
}

void Enemy::Wait(const GameCtrl & controller)
{
	// 何もしない
	return;
}

void Enemy::Back(const GameCtrl & controller)
{
	if (pos == firstPos)
	{
		action = ENEM_ACT::WAIT;
		return;
	}
	int tmpAct = actRoot % 4;
	int tmpAfter = actRoot / 4;
	switch (rootPass[tmpAct][tmpAfter])
	{
	case 0:
	case 3:
		// 曲がったところへ移動
		if ((*PosTbl[rootPass[tmpAct][tmpAfter]][TBL_MAIN]) != rootPos.y)
		{
			Enemy::dir = rootPass[tmpAct][tmpAfter];
			(*PosTbl[rootPass[tmpAct][tmpAfter]][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		}
		// 追跡開始地点へ移動
		else if ((*PosTbl[rootPass[tmpAct][0]][TBL_MAIN]) != firstPos.x)
		{
			Enemy::dir = rootPass[tmpAct][0];
			(*PosTbl[rootPass[tmpAct][0]][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		}
		else
		{
			rootPos = VECTOR2(-1, -1);
			firstPos = VECTOR2(-1, -1);
			action = ENEM_ACT::CONST_MOVE;
			return;
		}
		break;
	case 1:
	case 2:
		// 曲がったところへ移動
		if ((*PosTbl[rootPass[tmpAct][tmpAfter]][TBL_MAIN]) != rootPos.x)
		{
			Enemy::dir = rootPass[tmpAct][tmpAfter];
			(*PosTbl[rootPass[tmpAct][tmpAfter]][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		}
		// 追跡開始地点へ移動
		else if ((*PosTbl[rootPass[tmpAct][0]][TBL_MAIN]) != firstPos.y)
		{
			Enemy::dir = rootPass[tmpAct][0];
			(*PosTbl[rootPass[tmpAct][0]][TBL_MAIN]) += SpeedTbl[Enemy::dir][0];
		}
		else
		{
			rootPos = VECTOR2(-1, -1);
			firstPos = VECTOR2(-1, -1);
			action = ENEM_ACT::CONST_MOVE;
			return;
		}
		break;
	}
	return;
}

void Enemy::Damage(const GameCtrl & controller)
{
	// 点滅の処理
	if (deathCnt % 5 == 0)
	{
		visible = !visible;
	}
	deathCnt--;
	if (deathCnt == 0)
	{
		action = ENEM_ACT::WAIT;
		life--;
		deathCnt = 60;
		if (life == -1)
		{
			deathFlag = true;
			lpInfoCtrl.SetEnemyFlag(true, enCnt);
		}
		lpInfoCtrl.SetEnemyHit(Enemy::enCnt, false);
	}
}

bool Enemy::CheckDeath(void)
{
	return deathFlag;
}

bool Enemy::CheckObjType(OBJ_TYPE type)
{
	return (type == objType);
}

const OBJ_TYPE & Enemy::GetObjType(void) const
{
	return objType;
}

void Enemy::SetDeathFlag(bool deathFlag)
{
	this->deathFlag = deathFlag;
}
