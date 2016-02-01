// Mesh class, contains vertex and index data for 3D models
#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include "rendermanager.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "..\math\boundingbox.h"

class VertexAttribute
{
private:
	string attribName;
	unsigned int size, offset;
public:

	VertexAttribute()
	{

	}

	VertexAttribute(string &attributeName, unsigned int &size)
	{
		this->attribName = attributeName;
		this->size = size;
	}

	string getAttributeName()
	{
		return attribName;
	}

	void setAttributeName(string &name)
	{
		this->attribName = name;
	}

	unsigned int getSize()
	{
		return size;
	}

	void setSize(unsigned int &size)
	{
		this->size = size;
	}

	unsigned int getOffset()
	{
		return offset;
	}

	void setOffset(unsigned int &offset)
	{
		this->offset = offset;
	}
};

class VertexAttributes
{
private:
	vector<VertexAttribute> attribs;
public:
	VertexAttributes()
	{

	}

	int getNumAttributes()
	{
		return attribs.size();
	}

	void setAttribute(VertexAttribute &val)
	{
		attribs.push_back(val);
	}

	void setAttribute(string &name, unsigned int &size)
	{
		setAttribute(VertexAttribute(name, size));
	}

	VertexAttribute getAttribute(int index)
	{
		return attribs[index];
	}
};

class Mesh
{
private:
	bool uploaded;
	VertexAttributes attribs;
public:
	enum PrimitiveType
	{
		Triangles,
		TriangleStrip,
		TriangleFan,
		Quads,
		QuadStrip,
		Lines,
		Points,
		Patches
	};

	unsigned int vbo, ibo, size, vertexSize;
	vector<Vertex> vertices;
	vector<int> indices;
	PrimitiveType primitiveType;

	Mesh()
	{
		uploaded = false;
		vbo = 0;
		ibo = 0;
		this->primitiveType = Mesh::PrimitiveType::Triangles;
	}

	void render()
	{
		if (!uploaded)
		{
			RenderManager::getRenderer()->createMesh(*this);
			RenderManager::getRenderer()->uploadMesh(*this);
			uploaded = true;
		}
		RenderManager::getRenderer()->renderMesh(*this);
	}

	BoundingBox createBoundingBox(vector<Vertex> &vertices, vector<int> &indices)
	{
		BoundingBox b(Vector3f(1000000), Vector3f(-1000000));
		for (int i = 0; i < indices.size(); i++)
		{
			b.extend(vertices[indices[i]].getPosition());
		}
		return b;
	}

	BoundingBox createBoundingBox(vector<Vertex> &vertices, vector<int> &indices, Matrix4f &worldTransform)
	{
		BoundingBox b(Vector3f(1000000), Vector3f(-1000000));
		Vector3f *tmpVecs = new Vector3f[indices.size()];
		for (int i = 0; i < indices.size(); i++)
		{
			tmpVecs[i] = *(vertices[indices[i]].getPosition().mult(worldTransform));
			b.extend(tmpVecs[i]);
		}
		delete[] tmpVecs;
		return b;
	}

	BoundingBox createBoundingBox(Matrix4f &worldTransform)
	{
		return createBoundingBox(vertices, indices, worldTransform);
	}

	BoundingBox createBoundingBox() 
	{ 
		return createBoundingBox(vertices, indices);  
	}

	VertexAttributes getAttributes()
	{
		return attribs;
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
	}

	void setVertices(vector<Vertex> &vertices, vector<int> &indices)
	{
		this->vertices.clear();
		this->indices.clear();

		this->vertices = vertices;
		this->indices = indices;
	}
};

#endif