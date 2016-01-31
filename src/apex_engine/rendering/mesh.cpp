#include "mesh.h"
#include "../math/boundingbox.h"

#include <climits>

void Mesh::setVertices(vector<Vertex> &vertices)
{
	this->vertices.clear();
	this->indices.clear();

	this->vertices = vertices;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		indices.push_back(i);
	}

	setAttributes();

	uploaded = false;
}

void Mesh::setVertices(vector<Vertex> &vertices, vector<int> &indices)
{
	this->vertices.clear();
	this->indices.clear();

	this->vertices = vertices;
	this->indices = indices;

	setAttributes();

	uploaded = false;
}

void Mesh::render()
{
	if (!created)
	{
		RenderManager::getEngine()->createMesh(*this);
		created = true;
	}
	if (!uploaded)
	{
		RenderManager::getEngine()->uploadMesh(*this);
		uploaded = true;
	}
	RenderManager::getEngine()->renderMesh(*this);
}

BoundingBox Mesh::createBoundingBox(vector<Vertex> &vertices, vector<int> &indices)
{
    Vector3f maxVec(static_cast<float>(INT_MAX));
    Vector3f minVec(static_cast<float>(INT_MIN));
	BoundingBox b(maxVec, minVec);
    
	for (size_t i = 0; i < indices.size(); i++)
	{
		b.extend(vertices[indices[i]].getPosition());
	}

	return b;
}

BoundingBox Mesh::createBoundingBox(vector<Vertex> &vertices, vector<int> &indices, Matrix4f &worldTransform)
{
    Vector3f maxVec(static_cast<float>(INT_MAX));
    Vector3f minVec(static_cast<float>(INT_MIN));
	BoundingBox b(maxVec, minVec);
    
	Vector3f *tmpVecs = new Vector3f[indices.size()];
	for (size_t i = 0; i < indices.size(); i++)
	{
		tmpVecs[i] = vertices[indices[i]].getPosition().transform(worldTransform);
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