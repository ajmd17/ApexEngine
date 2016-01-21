#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <cmath>
#include <iostream>
#include "math_util.h"

using std::ostream;

class Vector2f
{
public:
	static Vector2f Zero, One, UnitX, UnitY;

	float x, y;

	Vector2f()
	{
		set(0.0f);
	}

	Vector2f(Vector2f &other)
	{
		set(other);
	}

	Vector2f(float x, float y)
	{
		set(x, y);
	}

	Vector2f(float xy)
	{
		set(xy);
	}

	// Required copy constructor
	Vector2f(const Vector2f &other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	float &getX()
	{
		return x;
	}

	float &getY()
	{
		return y;
	}

	void setX(float x)
	{
		this->x = x;
	}

	void setY(float y)
	{
		this->y = y;
	}

	Vector2f *set(Vector2f &other)
	{
		this->x = other.x;
		this->y = other.y;
		return this;
	}

	Vector2f *set(float x, float y)
	{
		this->x = x;
		this->y = y;
		return this;
	}

	Vector2f *set(float xy)
	{
		this->x = xy;
		this->y = xy;
		return this;
	}

	Vector2f *add(Vector2f &other)
	{
		Vector2f *res = new Vector2f(*this);
		res->x += other.x;
		res->y += other.y;
		return res;
	}

	Vector2f *addStore(Vector2f &other)
	{
		this->x += other.x;
		this->y += other.y;
		return this;
	}

	Vector2f *sub(Vector2f &other)
	{
		Vector2f *res = new Vector2f(*this);
		res->x -= other.x;
		res->y -= other.y;
		return res;
	}

	Vector2f *subStore(Vector2f &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return this;
	}

	Vector2f *mult(Vector2f &other)
	{
		Vector2f *res = new Vector2f(*this);
		res->x *= other.x;
		res->y *= other.y;
		return res;
	}

	Vector2f *multStore(Vector2f &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return this;
	}

	Vector2f *mult(float scalar)
	{
		Vector2f *res = new Vector2f(*this);
		res->x *= scalar;
		res->y *= scalar;
		return res;
	}

	Vector2f *multStore(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return this;
	}

	Vector2f *div(Vector2f &other)
	{
		Vector2f *res = new Vector2f(*this);
		res->x /= other.x;
		res->y /= other.y;
		return res;
	}

	Vector2f *divStore(Vector2f &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return this;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2f *normalize()
	{
		Vector2f *res = new Vector2f(*this);
		float len = length();
		float len2 = len*len;
		if (len2 == 0 || len2 == 1)
			return res;
		res->multStore(1.0f / len);
		return res;
	}

	Vector2f *normalizeStore()
	{
		float len = length();
		float len2 = len*len;
		if (len2 == 0 || len2 == 1)
			return this;
		this->multStore(1.0f / len);
		return this;
	}

	float dot(Vector2f &other)
	{
		return this->x * other.x + this->y * other.y;
	}

	float distanceSqr(Vector2f &other)
	{
		float dx = this->x - other.x;
		float dy = this->y - other.y;
		return dx * dx + dy * dy;
	}

	float distance(Vector2f &other)
	{
		return sqrt(distanceSqr(other));
	}

	static Vector2f min(Vector2f &a, Vector2f &b, Vector2f &outVec)
	{
		outVec.x = MathUtil::min(a.x, b.x);
		outVec.y = MathUtil::min(a.y, b.y);
		return outVec;
	}

	static Vector2f max(Vector2f &a, Vector2f &b, Vector2f &outVec)
	{
		outVec.x = MathUtil::max(a.x, b.x);
		outVec.y = MathUtil::max(a.y, b.y);
		return outVec;
	}

	friend ostream& operator<<(ostream& out, const Vector2f &vec) // output
	{
		out << "[" << vec.x << ", " << vec.y << "]";
		return out;
	}
};

#endif