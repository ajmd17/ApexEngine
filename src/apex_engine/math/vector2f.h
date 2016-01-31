#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <cmath>
#include <iostream>
#include "math_util.h"

using std::ostream;

class Vector2f
{
public:
	static const Vector2f Zero, One, UnitX, UnitY;

	float x, y;

	Vector2f()
	{
		set(0.0f);
	}

	Vector2f(float x, float y)
	{
		set(x, y);
	}

	Vector2f(float xy)
	{
		set(xy);
	}
	
	Vector2f(const Vector2f &other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	float getX() const
	{
		return x;
	}

	float getY() const
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

	Vector2f &set(Vector2f &other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Vector2f &set(float x, float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	Vector2f &set(float xy)
	{
		this->x = xy;
		this->y = xy;
		return *this;
	}

	Vector2f &add(Vector2f &other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vector2f &subtract(Vector2f &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vector2f &multiply(Vector2f &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vector2f &scale(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	Vector2f &divide(Vector2f &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2f &normalize()
	{
		float len = length();
		float len2 = len*len;
		if (len2 == 0 || len2 == 1)
			return *this;
		this->scale(1.0f / len);
		return *this;
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