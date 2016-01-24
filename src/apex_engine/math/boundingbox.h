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

#endif