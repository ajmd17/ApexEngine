#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>
#include <iostream>
#include "math_util.h"
#include "matrix4f.h"

using std::ostream;

class Vector3f
{
public:
	static Vector3f Zero, One, UnitX, UnitY, UnitZ;

	float x, y, z;

	Vector3f()
	{
		set(0.0f);
	}

	Vector3f(Vector3f &other)
	{
		set(other);
	}

	Vector3f(float x, float y, float z)
	{
		set(x, y, z);
	}

	Vector3f(float xyz)
	{
		set(xyz);
	}

	// Required copy constructor
	Vector3f(const Vector3f &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	float &getX()
	{
		return x;
	}

	float &getY()
	{
		return y;
	}

	float &getZ()
	{
		return z;
	}

	void setX(float x)
	{
		this->x = x;
	}

	void setY(float y)
	{
		this->y = y;
	}

	void setZ(float z)
	{
		this->z = z;
	}

	Vector3f *set(Vector3f &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return this;
	}

	Vector3f *set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		return this;
	}

	Vector3f *set(float xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
		return this;
	}

	Vector3f *add(Vector3f &other)
	{
		Vector3f *res = new Vector3f(*this);
		res->x += other.x;
		res->y += other.y;
		res->z += other.z;
		return res;
	}

	Vector3f *addStore(Vector3f &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return this;
	}

	Vector3f *sub(Vector3f &other)
	{
		Vector3f *res = new Vector3f(*this);
		res->x -= other.x;
		res->y -= other.y;
		res->z -= other.z;
		return res;
	}

	Vector3f *subStore(Vector3f &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return this;
	}

	Vector3f *mult(Vector3f &other)
	{
		Vector3f *res = new Vector3f(*this);
		res->x *= other.x;
		res->y *= other.y;
		res->z *= other.z;
		return res;
	}

	Vector3f *multStore(Vector3f &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return this;
	}

	Vector3f *mult(float scalar)
	{
		Vector3f *res = new Vector3f(*this);
		res->x *= scalar;
		res->y *= scalar;
		res->z *= scalar;
		return res;
	}

	Vector3f *multStore(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return this;
	}

	Vector3f *mult(Matrix4f &mat)
	{
		Vector3f *res = new Vector3f();
		res->set(this->x * mat.values[Matrix4f::M00] + this->y * mat.values[Matrix4f::M01] + this->z * mat.values[Matrix4f::M02] + mat.values[Matrix4f::M03],
				 this->x * mat.values[Matrix4f::M10] + this->y * mat.values[Matrix4f::M11] + this->z * mat.values[Matrix4f::M12] + mat.values[Matrix4f::M13],
				 this->x * mat.values[Matrix4f::M20] + this->y * mat.values[Matrix4f::M21] + this->z * mat.values[Matrix4f::M22] + mat.values[Matrix4f::M23]);
		return res;
	}

	Vector3f *multStore(Matrix4f &mat)
	{
		return set(this->x * mat.values[Matrix4f::M00] + this->y * mat.values[Matrix4f::M01] + this->z * mat.values[Matrix4f::M02] + mat.values[Matrix4f::M03],
				 this->x * mat.values[Matrix4f::M10] + this->y * mat.values[Matrix4f::M11] + this->z * mat.values[Matrix4f::M12] + mat.values[Matrix4f::M13],
				 this->x * mat.values[Matrix4f::M20] + this->y * mat.values[Matrix4f::M21] + this->z * mat.values[Matrix4f::M22] + mat.values[Matrix4f::M23]);
	}

	Vector3f *div(Vector3f &other)
	{
		Vector3f *res = new Vector3f(*this);
		res->x /= other.x;
		res->y /= other.y;
		res->z /= other.z;
		return res;
	}

	Vector3f *divStore(Vector3f &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return this;
	}

	Vector3f *cross(Vector3f &other)
	{
		Vector3f *res = new Vector3f(*this);
		float x1 = (res->y * other.z) - (res->z * other.y);
        float y1 = (res->z * other.x) - (res->x * other.z);
        float z1 = (res->x * other.y) - (res->y * other.x);
        res->set(x1, y1, z1);
        return res;
	}

	Vector3f *crossStore(Vector3f &other)
	{
		float x1 = (this->y * other.z) - (this->z * other.y);
        float y1 = (this->z * other.x) - (this->x * other.z);
        float z1 = (this->x * other.y) - (this->y * other.x);
        return set(x1, y1, z1);
	}

	float length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3f *normalize()
	{
		Vector3f *res = new Vector3f(*this);
		float len = length();
		float len2 = len*len;
		if (len2 == 0 || len2 == 1)
			return res;
		res->multStore(1.0f / len);
		return res;
	}

	Vector3f *normalizeStore()
	{
		float len = length();
		float len2 = len*len;
		if (len2 == 0 || len2 == 1)
			return this;
		this->multStore(1.0f / len);
		return this;
	}

	float dot(Vector3f &other)
	{
		return this->x * other.x + this->y * other.y + this->z * other.z;
	}

	float distanceSqr(Vector3f &other)
	{
		float dx = this->x - other.x;
		float dy = this->y - other.y;
		float dz = this->z - other.z;
		return dx * dx + dy * dy + dz * dz;
	}

	float distance(Vector3f &other)
	{
		return sqrt(distanceSqr(other));
	}

	static Vector3f min(Vector3f &a, Vector3f &b, Vector3f &outVec)
	{
		outVec.x = MathUtil::min(a.x, b.x);
		outVec.y = MathUtil::min(a.y, b.y);
		outVec.z = MathUtil::min(a.z, b.z);
		return outVec;
	}

	static Vector3f max(Vector3f &a, Vector3f &b, Vector3f &outVec)
	{
		outVec.x = MathUtil::max(a.x, b.x);
		outVec.y = MathUtil::max(a.y, b.y);
		outVec.z = MathUtil::max(a.z, b.z);
		return outVec;
	}

	friend ostream& operator<<(ostream& out, const Vector3f &vec) // output
	{
		out << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
		return out;
	}
};

#endif