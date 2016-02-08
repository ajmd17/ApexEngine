#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

// A type of camera, 

#include "../camera.h"
#include "../../math/matrix_util.h"
#include "../../math/vector3f.h"
#include "../../math/quaternion.h"
#include "../../math/frustum.h"

namespace apex
{
	class PerspectiveCamera : public Camera
	{
	protected:
		float pitch, roll, yaw;
	private:
		float fov, n, f;
		Quaternion rotation;
		Vector3f target, up;
		Frustum frustum;
	public:
		PerspectiveCamera(float fov, int width, int height, float n, float f)
		{
			this->translation = Vector3f(0, 0, 0);
			this->direction = Vector3f(0, 0, 1);
			this->up = Vector3f(0, 1, 0);
			this->target = Vector3f(0, 0, 0);

			this->fov = fov;
			this->n = n;
			this->f = f;
			this->width = width;
			this->height = height;
		}

		Vector3f getUpVector()
		{
			return up;
		}

		void setUpVector(Vector3f up)
		{
			this->up.set(up);
		}

		virtual void updateCameraLogic()
		{
		}

		void updateCameraMatrices()
		{
			rotation.setToLookAt(direction, up);
			pitch = rotation.getPitch();
			roll = rotation.getRoll();
			yaw = rotation.getYaw();

			target.set(translation);
			target.add(direction);

			MatrixUtil::setToLookAt(viewMatrix, this->translation, this->target, this->up);
			MatrixUtil::setToProjection(projectionMatrix, this->fov, this->width, this->height, this->n, this->f);

			viewProjectionMatrix.set(viewMatrix);
			viewProjectionMatrix.multiply(projectionMatrix);

			frustum.setViewProjectionMatrix(viewProjectionMatrix);
		}

		Frustum &getFrustum()
		{
			return frustum;
		}

		const float getPitch() { return pitch; }

		const float getRoll() { return roll; }

		const float getYaw() { return yaw; }

		const Quaternion getRotation()
		{
			return rotation;
		}
	};
}
#endif