// ｹﾞｰﾑ内のｼｰﾝ遷移を管理する・ｹﾞｰﾑﾙｰﾌﾟ

#pragma once
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"

constexpr int SCREEN_SIZE_X = 1600;
constexpr int SCREEN_SIZE_Y = 960;

constexpr int PL_SCREEN_SIZE_X = 800;
constexpr int PL_SCREEN_SIZE_Y = 480;

#define lpSceneMng SceneMng::GetInstance()

using Que_T = std::tuple<int, int, int>;

enum class DRAW_QUE
{
	IMAGE,	// 描画ｽｸﾘｰﾝﾊﾝﾄﾞﾙ
	X,		// ｽｸﾘｰﾝの横ｻｲｽﾞ
	Y		// ｽｸﾘｰﾝの縦ｻｲｽﾞ
};

class GameCtrl;

class SceneMng
{
public:
	static SceneMng & GetInstance(void)
	{
		static SceneMng s_instance;
		return s_instance;
	}

	void Run(void);								// ｹﾞｰﾑﾙｰﾌﾟ
	VECTOR2 GetDrawOffset(void);				// 描画ｵﾌｾｯﾄを取得
	void SetDrawOffset(VECTOR2 drawOffset);
	VECTOR2 GetPlayScreen(bool singleFlag);		// 4分割時の1画面のｻｲｽﾞを取得 true:ｼﾝｸﾞﾙ false:ﾏﾙﾁ
	int GetFram(void);							// ｹﾞｰﾑ起動時からのﾌﾚｰﾑ数を取得
	void Draw(void);
	bool AddDraw(const Que_T& query);

private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	VECTOR2 drawOffset;
	int framCnt;

	std::vector<Que_T> _drawList;		// 描画するｽｸﾘｰﾝをため込んでいくﾘｽﾄ
	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

