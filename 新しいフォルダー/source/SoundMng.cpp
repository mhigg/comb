#include "DxLib.h"
#include "SoundMng.h"



const int & SoundMng::GetID(std::string f_name)
{
	if (soundId.find(f_name) == soundId.end())
	{
		soundId[f_name] = LoadSoundMem(f_name.c_str());
	}
	return soundId[f_name];
}

void SoundMng::Load(std::string f_name)
{
	if (soundId.find(f_name) == soundId.end())
	{
		soundId[f_name] = LoadSoundMem(f_name.c_str());
	}
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}
