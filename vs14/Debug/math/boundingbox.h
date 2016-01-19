#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "matrix4f.h"
#include "vector3f.h"
#include "transform.h"
#include "ray.h"
#include "math_util.h"
#include <cmath>

class BoundingBox
{
private:
	const static int MAX_SIZE =  1000000;
	const static int MIN_SIZE = -1000000;
	const static int NUM_CORNERS = 8;

	Vector3f corners[NUM_CORNERS];
	Matrix4f matrix;

	Vector3f max, min, center, extent, dimensions;
public:
	BoundingBox clear();

	BoundingBox createBoundingBox(Vector3f &, Vector3f &);

	BoundingBox extend(BoundingBox &b);

	BoundingBox extend(Vector3f &point);

	void updateCorners();

	/**
		Intersect this BoundingBox with a Ray. Returns true if intersected. 
		The hit point will be stored in outVec.
	*/
	bool intersect(Ray &ray, Vector3f &outVec);

	BoundingBox()
	{
		for (int i = 0; i < NUM_CORNERS; i++)
		{
			corners[i] = Vector3f(0.0);
		}
		
		createBoundingBox(Vector3f(MAX_SIZE), Vector3f(MIN_SIZE));
	}

	BoundingBox(Vector3f &dimMin, Vector3f &dimMax)
	{
		for (int i = 0; i < NUM_CORNERS; i++)
		{
			corners[i] = Vector3f(0.0);
		}
		createBoundingBox(dimMin, dimMax);
	}

	Vector3f getMin()
	{
		return min;
	}

	Vector3f getMax()
	{
		return max;
	}

	Vector3f getCenter()
	{
		return center;
	}

	Vector3f getExtent()
	{
		return extent;
	}
};

BoundingBox BoundingBox::clear()
{
	return createBoundingBox(Vector3f(MAX_SIZE), Vector3f(MIN_SIZE));
}

BoundingBox BoundingBox::createBoundingBox(Vector3f &dimMin, Vector3f &dimMax)
{
	min.set(dimMin);
	max.set(dimMax);

	center.set(min)->addStore(max)->multStore(0.5f);

	extent.set(dimMax);
	extent.subStore(dimMin);

	dimensions.set(max)->subStore(min)->multStore(0.5f);

	updateCorners();

	return *this;
}

void BoundingBox::updateCorners()
{
	corners[0].set(max.x, max.y, max.z);
	corners[1].set(min.x, max.y, max.z);
	corners[2].set(min.x, max.y, min.z);
	corners[3].set(max.x, max.y, min.z);
	corners[4].set(max.x, min.y, max.z);
	corners[5].set(min.x, min.y, max.z);
	corners[6].set(min.x, min.y, min.z);
	corners[7].set(max.x, min.y, min.z);
}

BoundingBox BoundingBox::extend(BoundingBox &b)
{
	return this->extend(b.min).extend(b.max);
}

BoundingBox BoundingBox::extend(Vector3f &point)
{
	Vector3f minVec, maxVec;
	return this->createBoundingBox(Vector3f::min(min, point, minVec), Vector3f::max(max, point, maxVec));
}

bool BoundingBox::intersect(Ray &ray, Vector3f &outVec)
{
	const float epsilon = 1e-6f;
    float tMin = MIN_SIZE, tMax = MAX_SIZE;
	
	if (abs(ray.getDirection().x) < epsilon)
	{
		if (ray.getPosition().x < min.x || ray.getPosition().x > max.x)
		{
			outVec.set(0, 0, 0);
			return false; // invalid. Doesnt collide
		}
	}
	else
	{
		tMin = (min.x - ray.getPosition().x) / ray.getDirection().x;
		tMax = (max.x - ray.getPosition().x) / ray.getDirection().x;
		if (tMin > tMax)
		{
			float temp = tMin;
			tMin = tMax;
			tMax = temp;
		}
	}
	
	if (abs(ray.getDirection().y) < epsilon)
	{
		if (ray.getPosition().y < min.y || ray.getPosition().y > max.y)
		{
			outVec.set(0, 0, 0);
			return false; // invalid. Doesnt collide
		}
	}
	else
	{
		float tMinY = (min.y - ray.getPosition().y) / ray.getDirection().y;
		float tMaxY = (max.y - ray.getPosition().y) / ray.getDirection().y;

		if (tMinY > tMaxY)
		{
			float temp = tMinY;
			tMinY = tMaxY;
			tMaxY = temp;
		}

		if (tMin > tMaxY || tMinY > tMax)
		{
			outVec.set(0, 0, 0);
			return false; // invalid. Doesnt collide
		}

		if (tMinY > tMin) tMin = tMinY;
		if (tMaxY < tMax) tMax = tMaxY;
	}

	if (abs(ray.getDirection().z) < epsilon)
	{
		if (ray.getPosition().z < min.z || ray.getPosition().z > max.z)
		{
			outVec.set(0, 0, 0);
			return false; // invalid. Doesnt collide
		}
	}
	else
	{
		float tMinZ = (min.z - ray.getPosition().z) / ray.getDirection().z;
		float tMaxZ = (max.z - ray.getPosition().z) / ray.getDirection().z;

		if (tMinZ > tMaxZ)
		{
			float temp = tMinZ;
			tMinZ = tMaxZ;
			tMaxZ = temp;
		}

		if (tMin > tMaxZ || tMinZ > tMax)
		{
			outVec.set(0, 0, 0);
			return false; // invalid. Doesnt collide
		}

		if (tMinZ > tMin) tMin = tMinZ;
		if (tMaxZ < tMax) tMax = tMaxZ;
	}

	outVec.set(ray.getPosition());
	Vector3f tmpVec = Vector3f(ray.getDirection());
	tmpVec.multStore(tMin);
	outVec.addStore(tmpVec);

	return true;
}

#endif