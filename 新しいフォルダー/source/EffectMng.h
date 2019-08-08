#pragma once
#include <map>
#include <vector>

#define lpEffectMng EffectMng::GetInstance()

using VEC_INT = std::vector<int>;

class EffectMng
{
public:
	static EffectMng & GetInstance(void)
	{
		static EffectMng s_instance;
		return s_instance;
	}

	bool SetUp(void);
	const VEC_INT & GetID(std::string efk_name, float magnification);

private:
	EffectMng();
	~EffectMng();

	bool Init(void);

	std::map<std::string, VEC_INT> effectMap;
};

