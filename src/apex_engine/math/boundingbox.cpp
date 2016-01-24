#include "boundingbox.h"

BoundingBox BoundingBox::clear()
{
	Vector3f min_vec(0);
	Vector3f max_vec(0);
	this->createBoundingBox(min_vec, max_vec);
	return *this;
}

BoundingBox BoundingBox::createBoundingBox(Vector3f &dimMin, Vector3f &dimMax)
{
	min.set(dimMin);
	max.set(dimMax);

	center.set(min)->addStore(max)->scaleStore(0.5f);

	extent.set(dimMax);
	extent.subStore(dimMin);

	dimensions.set(max)->subStore(min)->scaleStore(0.5f);

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
	this->extend(b.min).extend(b.max);
	return *this;
}

BoundingBox BoundingBox::extend(Vector3f &point)
{
	Vector3f minVec, maxVec;
	Vector3f::min(min, point, minVec);
	Vector3f::max(max, point, maxVec);
	this->createBoundingBox(minVec, maxVec);
	return *this;
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
	tmpVec.scaleStore(tMin);
	outVec.addStore(tmpVec);

	return true;
}