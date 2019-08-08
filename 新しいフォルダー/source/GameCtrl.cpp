#include <DxLib.h>
#include "GameCtrl.h"


GameCtrl::GameCtrl()
{
	padTbl = {
		DX_INPUT_PAD1,
		DX_INPUT_PAD2,
		DX_INPUT_PAD3,
		DX_INPUT_PAD4
	};

	int j_Num = GetJoypadNum();
	if (j_Num <= 0) j_Num = 1;
	inputState.resize(j_Num);
	inputStateOld.resize(j_Num);
	padData.resize(j_Num);
}


GameCtrl::~GameCtrl()
{
}

const KEY_ARY & GameCtrl::GetCtrl(KEY_TYPE type) const
{
	if (type == KEY_TYPE_NOW)
	{
		return keyData;
	}

	return keyDataOld;
}

const std::vector<INPUT_ARY> & GameCtrl::GetInputState(KEY_TYPE type) const
{
	if (type == KEY_TYPE_NOW)
	{
		return inputState;
	}

	return inputStateOld;
}

bool GameCtrl::UpDate(void)
{
	keyDataOld = keyData;
	GetHitKeyStateAll(&keyData[0]);
	
	int j_Num = GetJoypadNum();
	for (int p = 0; p < j_Num; p++)
	{
		GetJoypadXInputState(padTbl[p], &padData[p]);
	}

	inputStateOld = inputState;
	for (int p = 0; p < j_Num; p++)
	{
		// ˆÚ“®ŠÖ˜A
		inputState[p][XINPUT_DOWN] = (padData[p].ThumbLY < -20000) | padData[p].Buttons[XINPUT_BUTTON_DPAD_DOWN] | keyData[KEY_INPUT_DOWN];
		inputState[p][XINPUT_LEFT] = (padData[p].ThumbLX < -20000) | padData[p].Buttons[XINPUT_BUTTON_DPAD_LEFT] | keyData[KEY_INPUT_LEFT];
		inputState[p][XINPUT_RIGHT] = (padData[p].ThumbLX > 20000) | padData[p].Buttons[XINPUT_BUTTON_DPAD_RIGHT] | keyData[KEY_INPUT_RIGHT];
		inputState[p][XINPUT_UP] = (padData[p].ThumbLY > 20000) | padData[p].Buttons[XINPUT_BUTTON_DPAD_UP] | keyData[KEY_INPUT_UP];

		// ±¸¼®ÝŠÖ˜A
		inputState[p][XINPUT_ATT] = padData[p].Buttons[XINPUT_BUTTON_B];
		inputState[p][XINPUT_MAP] = padData[p].Buttons[XINPUT_BUTTON_X];

		// •¨’Í‚Ý/ÀÞ¯¼­(LB/RB)
		inputState[p][XINPUT_GET_LB] = padData[p].Buttons[XINPUT_BUTTON_LEFT_SHOULDER];
		inputState[p][XINPUT_RUN_RB] = padData[p].Buttons[XINPUT_BUTTON_RIGHT_SHOULDER];

		// ‚»‚Ì‘¼(ÒÆ­°,Îß°½Þ‚È‚Ç)
		inputState[p][XINPUT_START] = padData[p].Buttons[XINPUT_BUTTON_START];
		inputState[p][XINPUT_PAUSE] = padData[p].Buttons[XINPUT_BUTTON_BACK] | keyData[KEY_INPUT_LSHIFT];
	}


	return true;
}
