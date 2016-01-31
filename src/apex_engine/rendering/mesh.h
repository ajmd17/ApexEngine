#ifndef MESH_H
#define MESH_H

// Mesh class, contains vertex and index data for 3D models
// Author: Andrew MacDonald

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
		this->primitiveType = Triangles;
	}

	void render();

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

	void setAttributes()
	{
		//TODO: Automatically detect what attributes to set instead of just assuming everything
		this->getAttributes().setAttribute(VertexAttributes::POSITIONS);
		this->getAttributes().setAttribute(VertexAttributes::TEXCOORDS0);
		this->getAttributes().setAttribute(VertexAttributes::TEXCOORDS1);
		this->getAttributes().setAttribute(VertexAttributes::NORMALS);
		this->getAttributes().setAttribute(VertexAttributes::TANGENTS);
		this->getAttributes().setAttribute(VertexAttributes::BITANGENTS);
		this->getAttributes().setAttribute(VertexAttributes::BONEINDICES);
		this->getAttributes().setAttribute(VertexAttributes::BONEWEIGHTS);
	}

	void setVertices(vector<Vertex> &vertices);

	void setVertices(vector<Vertex> &vertices, vector<int> &indices);
};

#endif