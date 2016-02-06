#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>
#include <iostream>

#include "math_util.h"
#include "matrix4f.h"

using std::ostream;

namespace apex
{
	class Vector3f
	{
	private:
		Matrix4f tmpRot;
	public:
		static const Vector3f Zero, One, UnitX, UnitY, UnitZ;

		float x, y, z;

		Vector3f()
		{
			set(0.0f);
		}

		Vector3f(float x, float y, float z)
		{
			set(x, y, z);
		}

		Vector3f(float xyz)
		{
			set(xyz);
		}

		Vector3f(const Vector3f &other)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
		}

		float getX() const
		{
			return x;
		}

		float getY() const
		{
			return y;
		}

		float getZ() const
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

		Vector3f &set(const Vector3f &other)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			return *this;
		}

		Vector3f &set(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			return *this;
		}

		Vector3f &set(float xyz)
		{
			this->x = xyz;
			this->y = xyz;
			this->z = xyz;
			return *this;
		}

		Vector3f &add(const Vector3f &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		Vector3f &subtract(const Vector3f &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		Vector3f &multiply(const Vector3f &other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		Vector3f &scale(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			return *this;
		}

		Vector3f &transform(const Matrix4f &mat)
		{
			set(this->x * mat.values[0][0] + this->y * mat.values[0][1] + this->z * mat.values[0][2] + mat.values[0][3],
				this->x * mat.values[1][0] + this->y * mat.values[1][1] + this->z * mat.values[1][2] + mat.values[1][3],
				this->x * mat.values[2][0] + this->y * mat.values[2][1] + this->z * mat.values[2][2] + mat.values[2][3]);
			return *this;
		}

		Vector3f &divide(const Vector3f &other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}

		Vector3f &cross(const Vector3f &other)
		{
			float x1 = (this->y * other.z) - (this->z * other.y);
			float y1 = (this->z * other.x) - (this->x * other.z);
			float z1 = (this->x * other.y) - (this->y * other.x);
			set(x1, y1, z1);
			return *this;
		}

		Vector3f &rotate(const Vector3f &axis, float angle);

		float length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		Vector3f &normalize()
		{
			float len = length();
			float len2 = len*len;
			if (len2 == 0 || len2 == 1)
				return *this;
			this->scale(1.0f / len);
			return *this;
		}

		float dot(Vector3f &other)
		{
			return this->x * other.x + this->y * other.y + this->z * other.z;
		}

		float distanceSqr(Vector3f &other) const
		{
			float dx = this->x - other.x;
			float dy = this->y - other.y;
			float dz = this->z - other.z;
			return dx * dx + dy * dy + dz * dz;
		}

		float distance(Vector3f &other) const
		{
			return sqrt(distanceSqr(other));
		}

		static Vector3f min(const Vector3f &a, const Vector3f &b, Vector3f &outVec)
		{
			outVec.x = MathUtil::min(a.x, b.x);
			outVec.y = MathUtil::min(a.y, b.y);
			outVec.z = MathUtil::min(a.z, b.z);
			return outVec;
		}

		static Vector3f max(const Vector3f &a, const Vector3f &b, Vector3f &outVec)
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
}
#endif