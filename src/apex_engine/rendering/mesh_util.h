#ifndef MESHUTIL_H
#define MESHUTIL_H

#include "mesh.h"
#include "vertex.h"

#include <vector>
using std::vector;

class MeshUtil
{
public:
	static vector<float> createFloatBuffer(Mesh &mesh)
	{
		vector<Vertex> _verts = mesh.vertices;
		unsigned int vertSize = 0,
				prevSize = 0,
				offset = 0;

		for (int i = 0; i < mesh.getAttributes().getNumAttributes(); i++)
		{
			offset += prevSize * sizeof(int);
			mesh.getAttributes().getAttribute(i).setOffset(offset);
			prevSize = mesh.getAttributes().getAttribute(i).getSize();
			vertSize += prevSize;
		}

		mesh.setVertexSize(vertSize);


		vector<float> floatBuffer;
		for (int i = 0; i < mesh.vertices.size(); i++)
		{
			//TODO: Use vertex attributes to check
			
			floatBuffer.push_back(mesh.vertices[i].getPosition().x);
			floatBuffer.push_back(mesh.vertices[i].getPosition().y);
			floatBuffer.push_back(mesh.vertices[i].getPosition().z);
		}

		return floatBuffer;
	}
};

#endif