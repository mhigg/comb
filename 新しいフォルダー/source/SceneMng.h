// �ްѓ��̼�ݑJ�ڂ��Ǘ�����E�ް�ٰ��

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
	IMAGE,	// �`�潸ذ������
	X,		// ��ذ݂̉�����
	Y		// ��ذ݂̏c����
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

	void Run(void);								// �ް�ٰ��
	VECTOR2 GetDrawOffset(void);				// �`��̾�Ă��擾
	void SetDrawOffset(VECTOR2 drawOffset);
	VECTOR2 GetPlayScreen(bool singleFlag);		// 4��������1��ʂ̻��ނ��擾 true:�ݸ�� false:���
	int GetFram(void);							// �ްыN����������ڰѐ����擾
	void Draw(void);
	bool AddDraw(const Que_T& query);

private:
	SceneMng();
	~SceneMng();
	bool Init(void);

	VECTOR2 drawOffset;
	int framCnt;

	std::vector<Que_T> _drawList;		// �`�悷�齸ذ݂����ߍ���ł���ؽ�
	uniqueBase activeScene;
	std::unique_ptr<GameCtrl> gameCtrl;
};

