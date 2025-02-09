#ifndef CAMERA_H
#define CAMERA_H

// Abstract Camera class. A camera contains the math necessary to properly render things with projection.
// Author: Andrew MacDonald

#include "../math/vector3f.h"
#include "../math/matrix4f.h"

namespace apex
{
	class Camera
	{
	protected:
		Vector3f translation, direction;
		Matrix4f viewMatrix, projectionMatrix, viewProjectionMatrix;

		unsigned int width, height;
	public:
		virtual void updateCameraLogic(const float dt) = 0;

		virtual void updateCameraMatrices() = 0;

		unsigned int getWidth()
		{
			return width;
		}

		void setWidth(unsigned int width)
		{
			this->width = width;
		}

		unsigned int getHeight()
		{
			return height;
		}

		void setHeight(unsigned int height)
		{
			this->height = height;
		}

		Vector3f &getTranslation()
		{
			return translation;
		}

		void setTranslation(Vector3f &vec)
		{
			translation.set(vec);
		}

		Vector3f &getDirection()
		{
			return direction;
		}

		void setDirection(Vector3f &vec)
		{
			direction.set(vec);
		}

		Matrix4f &getViewMatrix()
		{
			return viewMatrix;
		}

		Matrix4f &getProjectionMatrix()
		{
			return projectionMatrix;
		}

		Matrix4f &getViewProjectionMatrix()
		{
			return viewProjectionMatrix;
		}

		void rotate(const Vector3f &axis, float angle)
		{
			direction.rotate(axis, angle);
			direction.normalize();
		}

		void update(const float dt)
		{
			updateCameraLogic(dt);
			updateCameraMatrices();
		}
	};
}
#endif