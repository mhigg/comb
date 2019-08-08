// ¹Ş°Ñ“à‚Ì¼°İ‘JˆÚ‚ğŠÇ—‚·‚éE¹Ş°ÑÙ°Ìß

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
	IMAGE,	// •`‰æ½¸Ø°İÊİÄŞÙ
	X,		// ½¸Ø°İ‚Ì‰¡»²½Ş
	Y		// ½¸Ø°İ‚Ìc»²½Ş
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

	void Run(void);								// ¹Ş°ÑÙ°Ìß
	VECTOR2 GetDrawOffset(void);				// •`‰æµÌ¾¯Ä‚ğæ“¾
	void SetDrawOffset(VECTOR2 drawOffset);
	VECTOR2 GetPlayScreen(bool singleFlag);		// 4•ªŠ„‚Ì1‰æ–Ê‚Ì»²½Ş‚ğæ“¾ true:¼İ¸ŞÙ false:ÏÙÁ
	int GetFram(void);							// ¹Ş°Ñ‹N“®‚©‚ç‚ÌÌÚ°Ñ”‚ğæ“¾
	void Draw(void);
	bool AddDraw(const Que_T& query);

private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	VECTOR2 drawOffset;
	int framCnt;

	std::vector<Que_T> _drawList;		// •`‰æ‚·‚é½¸Ø°İ‚ğ‚½‚ß‚ñ‚Å‚¢‚­Ø½Ä
	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

