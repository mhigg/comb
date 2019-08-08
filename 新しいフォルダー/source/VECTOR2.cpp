#include <iostream>
#include "VECTOR2.h"

using namespace std;

VECTOR2::VECTOR2()
{

}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;
	this->y = y;
}

VECTOR2::VECTOR2(VECTOR2f vec) {
	this->x = vec.x;
	this->y = vec.y;
}

VECTOR2::~VECTOR2()
{

}


VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}


int & VECTOR2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		// 返す値はありません。
		// 警告出ても無視してください。
	}
}


bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	//return (!(this->x == vec.x) || !(this->y == vec.y));
	return !((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2::operator>=(const VECTOR2 & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

bool VECTOR2::operator<=(const VECTOR2 & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

bool VECTOR2::operator>(const VECTOR2 & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

bool VECTOR2::operator<(const VECTOR2 & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}


VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

VECTOR2 & VECTOR2::operator/=(int k)
{
	//0割りのｶﾞｰﾄﾞ処理は有無無問
	this->x /= k;
	this->y /= k;
	return (*this);
}


VECTOR2 VECTOR2::operator+() const
{
	return (*this);
}

VECTOR2 VECTOR2::operator-() const
{
	return VECTOR2(-this->x, -this->y);
}

VECTOR2 operator+(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x + v;
	vec.y = u.y + v;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x - v;
	vec.y = u.y - v;
	return vec;
}

VECTOR2 operator+(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

VECTOR2 operator*(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x * v;
	vec.y = u.y * v;
	return vec;
}

VECTOR2 operator*(int u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u * v.x;
	vec.y = u * v.y;
	return vec;
}

VECTOR2 operator*(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

VECTOR2 operator/(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x / v;
	vec.y = u.y / v;
	return vec;
}

VECTOR2 operator/(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x % v;
	vec.y = u.y % v;
	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;
	return vec;
}



VECTOR2f::VECTOR2f()
{
}



VECTOR2f::VECTOR2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

VECTOR2f::VECTOR2f(VECTOR2 vec)
{
	x = vec.x;
	y = vec.y;
}

VECTOR2f::~VECTOR2f()
{

}


VECTOR2f & VECTOR2f::operator=(const VECTOR2f & vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}


float & VECTOR2f::operator[](float i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		// 返す値はありません。
		// 警告出ても無視してください。
	}
}


bool VECTOR2f::operator==(const VECTOR2f & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2f::operator!=(const VECTOR2f & vec) const
{
	//return (!(this->x == vec.x) || !(this->y == vec.y));
	return !((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2f::operator>=(const VECTOR2f & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

bool VECTOR2f::operator<=(const VECTOR2f & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

bool VECTOR2f::operator>(const VECTOR2f & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

bool VECTOR2f::operator<(const VECTOR2f & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}


VECTOR2f & VECTOR2f::operator+=(const VECTOR2f & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

VECTOR2f & VECTOR2f::operator-=(const VECTOR2f & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

VECTOR2f & VECTOR2f::operator*=(float k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

VECTOR2f & VECTOR2f::operator/=(float k)
{
	//0割りのｶﾞｰﾄﾞ処理は有無無問
	this->x /= k;
	this->y /= k;
	return (*this);
}


VECTOR2f VECTOR2f::operator+() const
{
	return (*this);
}

VECTOR2f VECTOR2f::operator-() const
{
	return VECTOR2f(-this->x, -this->y);
}

VECTOR2f operator+(const VECTOR2f & u, float v)
{
	VECTOR2f vec;
	vec.x = u.x + v;
	vec.y = u.y + v;
	return vec;
}

VECTOR2f operator-(const VECTOR2f & u, float v)
{
	VECTOR2f vec;
	vec.x = u.x - v;
	vec.y = u.y - v;
	return vec;
}

VECTOR2f operator+(const VECTOR2f & u, const VECTOR2f & v)
{
	VECTOR2f vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

VECTOR2f operator-(const VECTOR2f & u, const VECTOR2f & v)
{
	VECTOR2f vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

VECTOR2f operator*(const VECTOR2f & u, float v)
{
	VECTOR2f vec;
	vec.x = u.x * v;
	vec.y = u.y * v;
	return vec;
}

VECTOR2f operator*(float u, const VECTOR2f & v)
{
	VECTOR2f vec;
	vec.x = u * v.x;
	vec.y = u * v.y;
	return vec;
}

VECTOR2f operator*(const VECTOR2f & u, const VECTOR2f & v)
{
	VECTOR2f vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

VECTOR2f operator/(const VECTOR2f & u, float v)
{
	VECTOR2f vec;
	vec.x = u.x / v;
	vec.y = u.y / v;
	return vec;
}

VECTOR2f operator/(const VECTOR2f & u, const VECTOR2f & v)
{
	VECTOR2f vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

VECTOR2f operator%(const VECTOR2f & u, float v)
{
	VECTOR2f vec;
	vec.x = fmod(u.x, v);
	vec.y = fmod(u.y, v);
	return vec;
}

VECTOR2f operator%(const VECTOR2f & u, const VECTOR2f & v)
{
	VECTOR2f vec;
	vec.x = fmod(u.x ,v.x);
	vec.y = fmod(u.y, v.y);
	return vec;
}