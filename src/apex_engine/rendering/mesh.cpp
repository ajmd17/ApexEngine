#include "mesh.h"
#include "../math/boundingbox.h"

BoundingBox Mesh::createBoundingBox(vector<Vertex> &vertices, vector<int> &indices)
{
    Vector3f maxVec(1000000);
    Vector3f minVec(-1000000);
	BoundingBox b(maxVec, minVec);
    
	for (int i = 0; i < indices.size(); i++)
	{
		b.extend(vertices[indices[i]].getPosition());
	}
	return b;
}

BoundingBox Mesh::createBoundingBox(vector<Vertex> &vertices, vector<int> &indices, Matrix4f &worldTransform)
{
    Vector3f maxVec(1000000);
    Vector3f minVec(-1000000);
	BoundingBox b(maxVec, minVec);
    
	Vector3f *tmpVecs = new Vector3f[indices.size()];
	for (int i = 0; i < indices.size(); i++)
	{
		tmpVecs[i] = *(vertices[indices[i]].getPosition().transform(worldTransform));
		b.extend(tmpVecs[i]);
	}
	delete[] tmpVecs;
	return b;
}

BoundingBox Mesh::createBoundingBox(Matrix4f &worldTransform)
{
    BoundingBox aabb;
    aabb = this->createBoundingBox(vertices, indices, worldTransform);
    return aabb;
}

BoundingBox Mesh::createBoundingBox()
{
    BoundingBox aabb;
    aabb = this->createBoundingBox(vertices, indices);
    return aabb;
}