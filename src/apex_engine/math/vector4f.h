#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <cmath>
#include <iostream>
#include "math_util.h"
#include "matrix4f.h"

using std::ostream;

namespace apex
{
	class Vector4f
	{
	public:
		static const Vector4f Zero, One, UnitX, UnitY, UnitZ;

		float x, y, z, w;

		Vector4f()
		{
			set(0.0f);
		}

		Vector4f(float x, float y, float z, float w)
		{
			set(x, y, z, w);
		}

		Vector4f(float xyzw)
		{
			set(xyzw);
		}
		Vector4f(const Vector4f &other)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			this->w = other.w;
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

		float getW() const
		{
			return w;
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

		void setW(float w)
		{
			this->w = w;
		}

		Vector4f &set(const Vector4f &other)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			this->w = other.w;
			return *this;
		}

		Vector4f &set(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
			return *this;
		}

		Vector4f &set(float xyzw)
		{
			this->x = xyzw;
			this->y = xyzw;
			this->z = xyzw;
			this->w = xyzw;
			return *this;
		}

		Vector4f &add(const Vector4f &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		Vector4f &subtract(const Vector4f &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		Vector4f &multiply(const Vector4f &other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}

		Vector4f &scale(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			this->w *= scalar;
			return *this;
		}

		Vector4f &transform(const Matrix4f &mat)
		{
			this->set(this->x * mat.values[0][0] + this->y * mat.values[0][1] + this->z * mat.values[0][2] + this->w * mat.values[0][3],
				this->x * mat.values[1][0] + this->y * mat.values[1][1] + this->z * mat.values[1][2] + this->w * mat.values[1][3],
				this->x * mat.values[2][0] + this->y * mat.values[2][1] + this->z * mat.values[2][2] + this->w * mat.values[2][3],
				this->x * mat.values[3][0] + this->y * mat.values[3][1] + this->z * mat.values[3][2] + this->w * mat.values[3][3]);
			return *this;
		}

		Vector4f &divide(const Vector4f &other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this;
		}

		float length() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		Vector4f &normalize()
		{
			float len = length();
			float len2 = len*len;
			if (len2 == 0 || len2 == 1)
				return *this;
			this->scale(1.0f / len);
			return *this;
		}

		float dot(const Vector4f &other)
		{
			return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
		}

		float distanceSqr(const Vector4f &other) const
		{
			float dx = this->x - other.x;
			float dy = this->y - other.y;
			float dz = this->z - other.z;
			float dw = this->w - other.w;
			return dx * dx + dy * dy + dz * dz + dw * dw;
		}

		float distance(const Vector4f &other) const
		{
			return sqrt(distanceSqr(other));
		}

		Vector4f &lerp(const Vector4f &toVector, const float amt)
		{
            this->x = MathUtil::lerp(this->x, toVector.x, amt);
            this->y = MathUtil::lerp(this->y, toVector.y, amt);
            this->z = MathUtil::lerp(this->z, toVector.z, amt);
            this->w = MathUtil::lerp(this->w, toVector.w, amt);

            return *this;
		}

		static Vector4f min(const Vector4f &a, const Vector4f &b, Vector4f &outVec)
		{
			outVec.x = MathUtil::min(a.x, b.x);
			outVec.y = MathUtil::min(a.y, b.y);
			outVec.z = MathUtil::min(a.z, b.z);
			outVec.w = MathUtil::min(a.w, b.w);
			return outVec;
		}

		static Vector4f max(const Vector4f &a, const Vector4f &b, Vector4f &outVec)
		{
			outVec.x = MathUtil::max(a.x, b.x);
			outVec.y = MathUtil::max(a.y, b.y);
			outVec.z = MathUtil::max(a.z, b.z);
			outVec.w = MathUtil::max(a.w, b.w);
			return outVec;
		}

		friend ostream& operator<<(ostream& out, const Vector4f &vec) // output
		{
			out << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
			return out;
		}
	};
}
#endif
