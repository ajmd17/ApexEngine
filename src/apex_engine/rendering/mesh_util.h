#ifndef MESHUTIL_H
#define MESHUTIL_H

#include "../math/boundingbox.h"
#include "../math/matrix4f.h"
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

		for (size_t i = 0; i < mesh.getAttributes().getNumAttributes(); i++)
		{
			offset += prevSize * sizeof(int);
			mesh.getAttributes().getAttribute(i).setOffset(offset);
			prevSize = mesh.getAttributes().getAttribute(i).getSize();
			vertSize += prevSize;
		}

		mesh.setVertexSize(vertSize);


		vector<float> floatBuffer;

		bool positions, texCoords0, texCoords1, normals, tangents, bitangents, boneIndices, boneWeights;

		positions = mesh.getAttributes().hasAttribute(VertexAttributes::POSITIONS);
		texCoords0 = mesh.getAttributes().hasAttribute(VertexAttributes::TEXCOORDS0);
		texCoords1 = mesh.getAttributes().hasAttribute(VertexAttributes::TEXCOORDS1);
		normals = mesh.getAttributes().hasAttribute(VertexAttributes::NORMALS);
		tangents = mesh.getAttributes().hasAttribute(VertexAttributes::TANGENTS);
		bitangents = mesh.getAttributes().hasAttribute(VertexAttributes::BITANGENTS);
		boneIndices = mesh.getAttributes().hasAttribute(VertexAttributes::BONEINDICES);
		boneWeights = mesh.getAttributes().hasAttribute(VertexAttributes::BONEWEIGHTS);

		for (size_t i = 0; i < mesh.vertices.size(); i++)
		{
			if (positions)
			{
				floatBuffer.push_back(mesh.vertices[i].getPosition().x);
				floatBuffer.push_back(mesh.vertices[i].getPosition().y);
				floatBuffer.push_back(mesh.vertices[i].getPosition().z);
			}
			if (texCoords0)
			{
				floatBuffer.push_back(mesh.vertices[i].getTexCoord0().x);
				floatBuffer.push_back(mesh.vertices[i].getTexCoord0().y);
			}
			if (texCoords1)
			{
				floatBuffer.push_back(mesh.vertices[i].getTexCoord1().x);
				floatBuffer.push_back(mesh.vertices[i].getTexCoord1().y);
			}
			if (normals)
			{
				floatBuffer.push_back(mesh.vertices[i].getNormal().x);
				floatBuffer.push_back(mesh.vertices[i].getNormal().y);
				floatBuffer.push_back(mesh.vertices[i].getNormal().z);
			}
			if (tangents)
			{
				floatBuffer.push_back(mesh.vertices[i].getTangent().x);
				floatBuffer.push_back(mesh.vertices[i].getTangent().y);
				floatBuffer.push_back(mesh.vertices[i].getTangent().z);
			}
			if (bitangents)
			{
				floatBuffer.push_back(mesh.vertices[i].getBitangent().x);
				floatBuffer.push_back(mesh.vertices[i].getBitangent().y);
				floatBuffer.push_back(mesh.vertices[i].getBitangent().z);
			}
			if (boneIndices)
			{
				floatBuffer.push_back(static_cast<float>(mesh.vertices[i].getBoneIndex(0)));
				floatBuffer.push_back(static_cast<float>(mesh.vertices[i].getBoneIndex(1)));
				floatBuffer.push_back(static_cast<float>(mesh.vertices[i].getBoneIndex(2)));
				floatBuffer.push_back(static_cast<float>(mesh.vertices[i].getBoneIndex(3)));
			}
			if (boneWeights)
			{
				floatBuffer.push_back(mesh.vertices[i].getBoneWeight(0));
				floatBuffer.push_back(mesh.vertices[i].getBoneWeight(1));
				floatBuffer.push_back(mesh.vertices[i].getBoneWeight(2));
				floatBuffer.push_back(mesh.vertices[i].getBoneWeight(3));
			}
		}

		return floatBuffer;
	}

	static BoundingBox createMeshBoundingBox(Mesh &mesh, BoundingBox &boundingBox, Matrix4f &transform)
	{
		boundingBox.clear();

		for (size_t i = 0; i < mesh.indices.size(); i++)
		{
			Vector3f tmpPosition;
			tmpPosition.set(mesh.vertices[mesh.indices[i]].getPosition());
			tmpPosition.transform(transform);

			boundingBox.extend(tmpPosition);
		}

		return boundingBox;
	}

	static BoundingBox createMeshBoundingBox(Mesh &mesh, BoundingBox &boundingBox)
	{
		Matrix4f tmpMat;
		createMeshBoundingBox(mesh, boundingBox, tmpMat);

		return boundingBox;
	}
};

#endif