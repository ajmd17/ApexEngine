#ifndef QUATERNION_H
#define QUATERNION_H

#include "math_util.h"
#include "vector3f.h"
#include "matrix4f.h"
#include <cmath>

class Quaternion
{
private:
	Vector3f tempX, tempY, tempZ;
public:
	float x, y, z, w;

	Quaternion()
	{
		this->setToIdentity();
	}

	Quaternion(Quaternion &other)
	{
		this->set(other);
	}

	Quaternion(float x, float y, float z, float w)
	{
		this->set(x, y, z, w);
	}

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	float getZ()
	{
		return z;
	}

	Quaternion *set(Quaternion &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
		return this;
	}

	Quaternion *set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return this;
	}

	Quaternion *setToIdentity()
	{
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
		this->w = 1.0;
		return this;
	}

	Quaternion *mult(Quaternion &other)
	{
		Quaternion *res = new Quaternion();
        float x1 = x * other.w + y * other.z - z * other.y + w * other.x;
        float y1 = -x * other.z + y * other.w + z * other.x + w * other.y;
        float z1 = x * other.y - y * other.x + z * other.w + w * other.z;
        float w1 = -x * other.x - y * other.y - z * other.z + w * other.w;
        res->x = x1;
        res->y = y1;
        res->z = z1;
        res->w = w1;
        return res;
	}

	Quaternion *multStore(Quaternion &other)
	{
        float x1 = x * other.w + y * other.z - z * other.y + w * other.x;
        float y1 = -x * other.z + y * other.w + z * other.x + w * other.y;
        float z1 = x * other.y - y * other.x + z * other.w + w * other.z;
        float w1 = -x * other.x - y * other.y - z * other.z + w * other.w;
        this->x = x1;
        this->y = y1;
        this->z = z1;
        this->w = w1;
        return this;
	}

	Vector3f *mult(Vector3f vec)
	{
		Vector3f *res = new Vector3f();

		float vx = vec.x, vy = vec.y, vz = vec.z;
		res->x = w * w * vx + 2 * y * w * vz - 2 * z * w * vy + x * x
		* vx + 2 * y * x * vy + 2 * z * x * vz - z * z * vx - y
		* y * vx;
		res->y = 2 * x * y * vx + y * y * vy + 2 * z * y * vz + 2 * w
		* z * vx - z * z * vy + w * w * vy - 2 * x * w * vz - x
		* x * vy;
		res->z = 2 * x * z * vx + 2 * y * z * vy + z * z * vz - 2 * w
		* y * vx - y * y * vz + 2 * w * x * vy - x * x * vz + w
		* w * vz;

		return res;
	}

	Vector3f *multStore(Vector3f &vec)
	{
		float tempX, tempY;
		tempX = w * w * vec.x + 2 * y * w * vec.z - 2 * z * w * vec.y + x * x * vec.x
		+ 2 * y * x * vec.y + 2 * z * x * vec.z - z * z * vec.x - y * y * vec.x;
		tempY = 2 * x * y * vec.x + y * y * vec.y + 2 * z * y * vec.z + 2 * w * z
		* vec.x - z * z * vec.y + w * w * vec.y - 2 * x * w * vec.z - x * x
		* vec.y;
		vec.z = 2 * x * z * vec.x + 2 * y * z * vec.y + z * z * vec.z - 2 * w * y * vec.x
		- y * y * vec.z + 2 * w * x * vec.y - x * x * vec.z + w * w * vec.z;
		vec.x = tempX;
		vec.y = tempY;
		return &vec;
	}

	float normalize()
	{
		return w * w + x * x + y * y + z * z;
	}

	Quaternion *inverse()
	{
		float n = normalize();
		Quaternion *res = new Quaternion();
		if (n > 0)
		{
			float invN = 1.0f / n;
			res->set(-x * invN, -y * invN, -z * invN, w * invN);
		}
		return res;
	}

	Quaternion *inverseStore()
	{
		float n = normalize();
        if (n > 0.0)
        {
            float invN = 1.0f / n;
            this->x = -x * invN;
            this->y = -y * invN;
            this->z = -z * invN;
            this->w = w * invN;
        }
        return this;
	}

	int getGimbalPole()
	{
		float amt = y * x + z * w;
		return amt > 0.499f ? 1 : (amt < -0.499f ? -1 : 0);
	}

	float getRollRad()
	{
		int pole = getGimbalPole();
		return pole == 0 ? atan2(2.0 * (w * z + y * x), 1.0 - 2.0 * (x * x + z * z)) : pole * 2.0 * atan2(y, w);
	}

	float getPitchRad()
	{
		int pole = getGimbalPole();
		return pole == 0 ? asin(MathUtil::clamp(2.0f * (w * x - z * y), -1.0, 1.0)) : pole * MathUtil::PI * 0.5;
	}

    float getYawRad()
    {
        int pole = getGimbalPole();
        return pole == 0 ? atan2(2.0f * (y * w + x * z), 1.0f - 2.0f * (y * y + x * x)) : 0.0f;
    }

	float getRoll()
	{
		return MathUtil::toDegrees(getRollRad());
	}

	float getPitch()
	{
		return MathUtil::toDegrees(getPitchRad());
	}

	float getYaw()
	{
		return MathUtil::toDegrees(getYawRad());
	}

	Quaternion *setFromAxisRad(Vector3f axis, float rads)
	{
		axis.normalizeStore();

		if (axis.x == 0 && axis.y == 0 && axis.z == 0)
			return set(0, 0, 0, 1);
		else
		{
			float halfAngle = rads / 2.0f;
            float sinHalfAngle = sin(halfAngle);
            this->w = cos(halfAngle);
            this->x = sinHalfAngle * axis.x;
            this->y = sinHalfAngle * axis.y;
            this->z = sinHalfAngle * axis.z; 
		}
		return this;
	}

	Quaternion *setFromAxis(Vector3f axis, float degrees)
	{
		return setFromAxisRad(axis, MathUtil::toRadians(degrees));
	}

	Quaternion *setFromAxes(float xx, float xy, float xz,
                            float yx, float yy, float yz,
                            float zx, float zy, float zz)
	{
		float amt = xx + yy + zz;
		if (amt >= 0.0f)
		{
			float s = sqrt(amt + 1);
			this->w = 0.5f * s;
			this->x = (zy - yz) * (0.5f / s);
			this->y = (xz - zx) * (0.5f / s);
			this->z = (yx - xy) * (0.5f / s);
		}
		else if ((xx > yy) && (xx > zz))
		{
			float s = sqrt(1 + xx - yy - zz);
			this->x = s * 0.5f;
			this->y = (yx + xy) * (0.5f / s);
			this->z = (xz + zx) * (0.5f / s);
			this->w = (zy - yz) * (0.5f / s);
		}
		else if (yy > zz)
		{
			float s = sqrt(1 + yy - xx - zz);
			this->y = s * 0.5f;
			this->x = (yx + xy) * (0.5f / s);
			this->z = (zy + yz) * (0.5f / s);
			this->w = (xz - zx) * (0.5f / s);
		}
		else
		{
			float s = sqrt(1 + zz - xx - yy);
			this->z = s * 0.5f;
			this->x = (xz + zx) * (0.5f / s);
			this->y = (zy + yz) * (0.5f / s);
			this->w = (yx - xy) * (0.5f / s);
		}
        return this;
	}

	Quaternion *setFromMatrix(Matrix4f &mat)
	{
		return setFromAxes(mat.values[Matrix4f::M00], mat.values[Matrix4f::M10], mat.values[Matrix4f::M20],
                    mat.values[Matrix4f::M01], mat.values[Matrix4f::M11], mat.values[Matrix4f::M21],
                    mat.values[Matrix4f::M02], mat.values[Matrix4f::M12], mat.values[Matrix4f::M22]);
	}

	Quaternion *setToLookAt(Vector3f &dir, Vector3f &up)
	{
		tempZ.set(dir);
		tempZ.normalizeStore();
		tempX.set(up);
		tempX.crossStore(dir);
		tempY.set(dir);
		tempY.crossStore(tempX);
		tempY.normalizeStore();
		return setFromAxes(tempX.x, tempX.y, tempX.z,
					tempY.x, tempY.y, tempY.z,
					tempZ.x, tempZ.y, tempZ.z);
	}
};


#endif