#pragma once
#include <map>

#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:
	static SoundMng &GetInstance(void)
	{
		static SoundMng s_instance;
		return s_instance;
	}

	const int& GetID(std::string f_name);
	void Load(std::string f_name);
private:
	SoundMng();
	~SoundMng();

	std::map<std::string, int> soundId;
};
