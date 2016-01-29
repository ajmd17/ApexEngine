#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

// A bounding box/cube in 3D space.
// Author: Andrew MacDonald

#include "matrix4f.h"
#include "vector3f.h"
#include "transform.h"
#include "ray.h"
#include "math_util.h"

#include <cmath>
#include <climits>

class BoundingBox
{
private:
	const static int MAX_SIZE = INT_MAX;
	const static int MIN_SIZE = INT_MIN;
	const static int NUM_CORNERS = 8;

	Vector3f corners[NUM_CORNERS];
	Matrix4f matrix;

	Vector3f max, min, center, dimensions;
public:
	BoundingBox clear();

	BoundingBox createBoundingBox(Vector3f &, Vector3f &);

	void extend(BoundingBox &b);

	void extend(Vector3f &point);

	void updateCorners();

	/**
		Intersect this BoundingBox with a Ray. Returns true if intersected. 
		The hit point will be stored in outVec.
	*/
	bool intersect(Ray &ray, Vector3f &outVec);

	BoundingBox()
	{
		this->clear();
	}

	BoundingBox(Vector3f &dimMin, Vector3f &dimMax)
	{
		this->createBoundingBox(dimMin, dimMax);
	}

	const Vector3f getMin()
	{
		return min;
	}

	const Vector3f getMax()
	{
		return max;
	}

	const Vector3f getCenter()
	{
		return center;
	}

	const Vector3f getDimensions()
	{
		return dimensions;
	}

	const float getWidth()
	{
		return dimensions.x;
	}

	const float getHeight()
	{
		return dimensions.y;
	}

	const float getLength()
	{
		return dimensions.z;
	}
};

#endif