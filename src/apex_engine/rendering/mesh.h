#ifndef MESH_H
#define MESH_H

// Mesh class, contains vertex and index data for 3D models
// Author: Andrew MacDonald

#include "enums.h"
#include "vertex.h"
#include "rendermanager.h"
#include "vertexattributes.h"
#include "animation/skeleton.h"

#include <memory>
using std::shared_ptr;

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace apex
{
	class BoundingBox;

	class Mesh
	{
	private:
		bool uploaded, created;
		int vertexSize;

		std::shared_ptr<Skeleton> skeleton;
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

		~Mesh();

		void render();

		BoundingBox createBoundingBox(vector<Vertex> &vertices, vector<int> &indices);

		BoundingBox createBoundingBox(vector<Vertex> &vertices, vector<int> &indices, Matrix4f &worldTransform);

		BoundingBox createBoundingBox(Matrix4f &worldTransform);

		BoundingBox createBoundingBox();

		std::shared_ptr<Skeleton> getSkeleton();

		void setSkeleton(std::shared_ptr<Skeleton> skeleton);

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
			this->getAttributes().setAttribute(VertexAttributes::POSITIONS);
		//	this->getAttributes().setAttribute(VertexAttributes::NORMALS);
		}

		void setVertices(vector<Vertex> vertices);

		void setVertices(vector<Vertex> vertices, vector<int> indices);
	};
}
#endif