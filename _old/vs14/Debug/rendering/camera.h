// Abstract Camera class. A camera contains the math necessary to properly render things.
#ifndef CAMERA_H
#define CAMERA_H

#include "..\math\vector3f.h"

class Camera
{
private:
	Vector3f translation, direction;
public:
	Vector3f getTranslation()
	{
		return translation;
	}

	void setTranslation(Vector3f &vec)
	{
		translation.set(vec);
	}

	Vector3f getDirection()
	{
		return direction;
	}

	void setDirection(Vector3f &vec)
	{
		direction.set(vec);
	}
};

#endif