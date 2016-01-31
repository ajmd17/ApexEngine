#ifndef CAMERA_H
#define CAMERA_H

// Abstract Camera class. A camera contains the math necessary to properly render things with projection.
// Author: Andrew MacDonald

#include "../math/vector3f.h"
#include "../math/matrix4f.h"

class Camera
{
protected:
	Vector3f translation, direction;
	Matrix4f viewMatrix, projectionMatrix, viewProjectionMatrix;
public:
	virtual void updateCameraLogic() = 0;

	virtual void updateCameraMatrices() = 0;

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

	void update()
	{
		updateCameraLogic();
		updateCameraMatrices();
	}
};

#endif