#ifndef MATRIXUTIL_H
#define MATRIXUTIL_H

#include "quaternion.h"
#include "matrix4f.h"
#include "vector3f.h"

namespace apex
{
	class MatrixUtil
	{
	private:
		static Matrix4f tmpMat, tmpMat2;
		static Vector3f tempVec, tempVec2, l_vex, l_vey, l_vez;
	public:
		static void setToTranslation(Matrix4f &mat, Vector3f &translation);

		static void setToRotation(Matrix4f &mat, Quaternion &rotation);

		static void setToRotation(Matrix4f &mat, Vector3f &axis, float angle);

		static void setToScaling(Matrix4f &mat, Vector3f &scale);

		static void setToProjection(Matrix4f &mat, float fov, int w, int h, float n, float f);

		static void setToLookAt(Matrix4f &mat, Vector3f &dir, Vector3f &up);

		static void setToLookAt(Matrix4f &mat, Vector3f &pos, Vector3f &target, Vector3f &up);

		static void setToOrtho(Matrix4f &mat, float left, float right, float bottom, float top, float nearClip, float farClip);
	};
}
#endif