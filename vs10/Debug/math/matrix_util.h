#ifndef MATRIXUTIL_H
#define MATRIXUTIL_H

#include "quaternion.h"
#include "matrix4f.h"
#include "vector3f.h"

class MatrixUtil
{
private:
	static Matrix4f tmpMat, tmpMat2;
	static Vector3f tempVec, tempVec2, l_vex, l_vey, l_vez;
public:
	static void setToTranslation(Matrix4f &mat, Vector3f &translation)
	{
		mat.setToIdentity();

		mat.values[Matrix4f::M03] = translation.getX();
		mat.values[Matrix4f::M13] = translation.getY();
		mat.values[Matrix4f::M23] = translation.getZ();
	}

	static void setToRotation(Matrix4f &mat, Quaternion &rotation)
	{
		mat.setToIdentity();

		float xx = rotation.x * rotation.x;
        float xy = rotation.x * rotation.y;
        float xz = rotation.x * rotation.z;
        float xw = rotation.x * rotation.w;
		float yy = rotation.y * rotation.y;
		float yz = rotation.y * rotation.z;
		float yw = rotation.y * rotation.w;
		float zz = rotation.z * rotation.z;
		float zw = rotation.z * rotation.w;

		mat.values[Matrix4f::M00] = 1.0 - 2.0 * (yy + zz);
		mat.values[Matrix4f::M10] = 2.0 * (xy - zw);
		mat.values[Matrix4f::M20] = 2.0 * (xz + yw);
		mat.values[Matrix4f::M30] = 0.0;
		mat.values[Matrix4f::M01] = 2.0 * (xy + zw);
		mat.values[Matrix4f::M11] = 1.0 - 2.0 * (xx + zz);
		mat.values[Matrix4f::M21] = 2.0 * (yz - xw);
		mat.values[Matrix4f::M31] = 0.0;
		mat.values[Matrix4f::M02] = 2.0 * (xz - yw);
		mat.values[Matrix4f::M12] = 2.0 * (yz + xw);
		mat.values[Matrix4f::M22] = 1.0 - 2.0 * (xx + yy);
		mat.values[Matrix4f::M32] = 0.0;
		mat.values[Matrix4f::M03] = 0.0;
		mat.values[Matrix4f::M13] = 0.0;
		mat.values[Matrix4f::M23] = 0.0;
		mat.values[Matrix4f::M33] = 1.0;
	}

	static void setToRotation(Matrix4f &mat, Vector3f &axis, float angle)
	{
		mat.setToIdentity();

		Quaternion *tempQ = new Quaternion();
		tempQ->setFromAxis(axis, angle);
		setToRotation(mat, *tempQ);
		delete tempQ;
	}

	static void setToScaling(Matrix4f &mat, Vector3f &scale)
	{
		mat.setToIdentity();

		mat.values[Matrix4f::M00] = scale.getX();
		mat.values[Matrix4f::M11] = scale.getY();
		mat.values[Matrix4f::M22] = scale.getZ();
	}

	static void setToProjection(Matrix4f &mat, float fov, float w, float h, float n, float f)
	{
		mat.setToIdentity();

		float ar = w / h;
		float tanHalfFov = tan(MathUtil::toRadians(fov / 2.0));
		float range = n - f;

		mat.values[Matrix4f::M00] = 1.0f / (tanHalfFov * ar);
        mat.values[Matrix4f::M01] = 0.0f;
        mat.values[Matrix4f::M02] = 0.0f;
        mat.values[Matrix4f::M03] = 0.0f;

        mat.values[Matrix4f::M10] = 0.0f;
        mat.values[Matrix4f::M11] = 1.0f / (tanHalfFov);
        mat.values[Matrix4f::M12] = 0.0f;
        mat.values[Matrix4f::M13] = 0.0f;

        mat.values[Matrix4f::M20] = 0.0f;
        mat.values[Matrix4f::M21] = 0.0f;
        mat.values[Matrix4f::M22] = (-n - f) / range;
        mat.values[Matrix4f::M23] = (2.0f * f * n) / range;

        mat.values[Matrix4f::M30] = 0.0f;
        mat.values[Matrix4f::M31] = 0.0f;
        mat.values[Matrix4f::M32] = 1.0f;
        mat.values[Matrix4f::M33] = 0.0f;
	}

	static void setToLookAt(Matrix4f &mat, Vector3f &dir, Vector3f &up)
	{
		mat.setToIdentity();

		l_vez.set(dir);
		l_vez.normalizeStore();
		l_vex.set(dir);
		l_vex.normalizeStore();
		l_vex.crossStore(up);
		l_vex.normalizeStore();
		l_vey.set(l_vex);
		l_vey.cross(l_vez);
		l_vey.normalizeStore();

		mat.values[Matrix4f::M00] = l_vex.x;
        mat.values[Matrix4f::M01] = l_vex.y;
        mat.values[Matrix4f::M02] = l_vex.z;

        mat.values[Matrix4f::M10] = l_vey.x;
        mat.values[Matrix4f::M11] = l_vey.y;
        mat.values[Matrix4f::M12] = l_vey.z;

        mat.values[Matrix4f::M20] = l_vez.x;
        mat.values[Matrix4f::M21] = l_vez.y;
        mat.values[Matrix4f::M22] = l_vez.z;
	}

	static void setToLookAt(Matrix4f &mat, Vector3f &pos, Vector3f &target, Vector3f &up)
	{
		mat.setToIdentity();
		tempVec.set(target);
		tempVec.subStore(pos);
		tempVec2.set(pos);
		tempVec2.multStore(-1);
		setToTranslation(tmpMat, tempVec2);
		setToLookAt(tmpMat2, tempVec, up);
		mat.set(tmpMat);
		mat.multStore(tmpMat2);
	}

	static void setToOrtho(Matrix4f &mat, float left, float right, float bottom, float top, float nearClip, float farClip)
	{
		float x_orth = 2.0f / (right - left);
        float y_orth = 2.0f / (top - bottom);
        float z_orth = 2.0f / (farClip - nearClip);
        float tx = -1 * ((right + left) / (right - left));
        float ty = -1 * ((top + bottom) / (top - bottom));
        float tz = -1 * ((farClip + nearClip) / (farClip - nearClip));

        mat.values[Matrix4f::M00] = x_orth;
        mat.values[Matrix4f::M10] = 0;
        mat.values[Matrix4f::M20] = 0;
        mat.values[Matrix4f::M30] = 0;
        mat.values[Matrix4f::M01] = 0;
        mat.values[Matrix4f::M11] = y_orth;
        mat.values[Matrix4f::M21] = 0;
        mat.values[Matrix4f::M31] = 0;
        mat.values[Matrix4f::M02] = 0;
        mat.values[Matrix4f::M12] = 0;
        mat.values[Matrix4f::M22] = z_orth;
        mat.values[Matrix4f::M32] = 0;
        mat.values[Matrix4f::M03] = tx;
        mat.values[Matrix4f::M13] = ty;
        mat.values[Matrix4f::M23] = tz;
        mat.values[Matrix4f::M33] = 1;
	}
};

#endif