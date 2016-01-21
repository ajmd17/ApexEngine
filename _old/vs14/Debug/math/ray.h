#ifndef RAY_H
#define RAY_H

#include "vector3f.h"

class Ray
{
private:
	Vector3f direction, position;
public:

	Ray(Vector3f &position, Vector3f &direction)
	{
		this->position.set(position);
		this->direction.set(direction);
	}

	Ray(Ray &other)
	{
		this->position = other.getPosition();
		this->direction = other.getDirection();
	}

	Vector3f getDirection()
	{
		return direction;
	}

	void setDirection(Vector3f &direction)
	{
		this->direction.set(direction);
	}

	Vector3f getPosition()
	{
		return position;
	}

	void setPosition(Vector3f &position)
	{
		this->position.set(position);
	}
};

#endif