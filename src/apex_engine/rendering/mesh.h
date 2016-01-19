// Mesh class, contains vertex and index data for 3D models
#ifndef MESH_H
#define MESH_H

#include "enums.h"
#include "vertex.h"
#include "rendermanager.h"
#include "vertexattributes.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

class BoundingBox;

class Mesh
{
private:
	bool uploaded, created;
	int vertexSize;
public:

	unsigned int vbo, ibo, size;

	vector<Vertex> vertices;
	vector<int> indices;

	PrimitiveType primitiveType;
	VertexAttributes attribs;

	Mesh()
	{
		uploaded = false;
		created = false;
		vbo = 0;
		ibo = 0;
		this->primitiveType = PrimitiveType::Triangles;
	}

	~Mesh()
	{
	}

	void render()
	{
		if (!created)
		{
			RenderManager::getRenderer()->createMesh(*this);
			created = true;
		}
		if (!uploaded)
		{
			RenderManager::getRenderer()->uploadMesh(*this);
			uploaded = true;
		}
		RenderManager::getRenderer()->renderMesh(*this);
	}

	BoundingBox createBoundingBox(vector<Vertex> &vertices, vector<int> &indices);

	BoundingBox createBoundingBox(vector<Vertex> &vertices, vector<int> &indices, Matrix4f &worldTransform);

	BoundingBox createBoundingBox(Matrix4f &worldTransform);

	BoundingBox createBoundingBox();

	VertexAttributes &getAttributes()
	{
		return attribs;
	}

	int &getVertexSize()
	{
		return vertexSize;
	}

	void setVertexSize(int vertSize)
	{
		this->vertexSize = vertSize;
	}

	void setVertices(vector<Vertex> &vertices)
	{
		this->vertices.clear();
		this->indices.clear();

		this->vertices = vertices;

		for (int i = 0; i < vertices.size(); i++)
		{
			indices.push_back(i);
		}

		this->getAttributes().setAttribute(VertexAttributes::POSITIONS);

		uploaded = false;
	}

	void setVertices(vector<Vertex> &vertices, vector<int> &indices)
	{
		this->vertices.clear();
		this->indices.clear();

		this->vertices = vertices;
		this->indices = indices;

		uploaded = false;
	}
};

#endif