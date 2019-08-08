#pragma once
#include <list>
#include <array>
#include "BaseScene.h"
#include "Obj.h"
#include "ClassObj.h"

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	uniqueBase UpDate(						// XV
		uniqueBase own,					// Œ»İ‚Ì¼°İ
		const GameCtrl &controller		// ·°æ“¾
	);
private:
	sharedListObj objList;					// ¼ª±ÄŞÎß²İÀ°
	int Init(void);							// ºİ½Ä×¸À‚Æ‚È‚é
	bool EditDraw(void);					// •`‰æ
};

