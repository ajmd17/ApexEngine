#ifndef MESHUTIL_H
#define MESHUTIL_H

#include "../math/boundingbox.h"
#include "../math/matrix4f.h"
#include "mesh.h"
#include "vertex.h"

#include <vector>
using std::vector;

namespace apex
{
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
				offset += prevSize;
				mesh.getAttributes().getAttribute(i).setOffset(offset);
				prevSize = mesh.getAttributes().getAttribute(i).getSize();
				vertSize += prevSize;
			}

			mesh.setVertexSize(vertSize);

			vector<float> floatBuffer(mesh.vertices.size() * vertSize);

			bool positions, texCoords0, texCoords1, normals, tangents, bitangents, boneIndices, boneWeights;
			VertexAttribute posAttr, texCoord0Attr, texCoord1Attr, normAttr, tangAttr, bitangAttr, boneIAttr, boneWAttr;

			positions = mesh.getAttributes().getAttribute(VertexAttributes::POSITIONS.getAttributeName(), posAttr);
			texCoords0 = mesh.getAttributes().getAttribute(VertexAttributes::TEXCOORDS0.getAttributeName(), texCoord0Attr);
			texCoords1 = mesh.getAttributes().getAttribute(VertexAttributes::TEXCOORDS1.getAttributeName(), texCoord1Attr);
			normals = mesh.getAttributes().getAttribute(VertexAttributes::NORMALS.getAttributeName(), normAttr);
			tangents = mesh.getAttributes().getAttribute(VertexAttributes::TANGENTS.getAttributeName(), tangAttr);
			bitangents = mesh.getAttributes().getAttribute(VertexAttributes::BITANGENTS.getAttributeName(), bitangAttr);
			boneIndices = mesh.getAttributes().getAttribute(VertexAttributes::BONEINDICES.getAttributeName(), boneIAttr);
			boneWeights = mesh.getAttributes().getAttribute(VertexAttributes::BONEWEIGHTS.getAttributeName(), boneWAttr);

			for (size_t i = 0; i < mesh.vertices.size(); i++)
			{
				if (positions)
				{
					floatBuffer.at((i * vertSize) + posAttr.getOffset()) = mesh.vertices[i].getPosition().x;
					floatBuffer.at((i * vertSize) + posAttr.getOffset() + 1) = mesh.vertices[i].getPosition().y;
					floatBuffer.at((i * vertSize) + posAttr.getOffset() + 2) = mesh.vertices[i].getPosition().z;
				}
				if (normals)
				{
					floatBuffer.at((i * vertSize) + normAttr.getOffset()) = mesh.vertices[i].getNormal().x;
					floatBuffer.at((i * vertSize) + normAttr.getOffset() + 1) = mesh.vertices[i].getNormal().y;
					floatBuffer.at((i * vertSize) + normAttr.getOffset() + 2) = mesh.vertices[i].getNormal().z;
				}
				if (texCoords0)
				{
					floatBuffer.at((i * vertSize) + texCoord0Attr.getOffset()) = mesh.vertices[i].getTexCoord0().x;
					floatBuffer.at((i * vertSize) + texCoord0Attr.getOffset() + 1) = mesh.vertices[i].getTexCoord0().y;
					
				}
				if (texCoords1)
				{
					floatBuffer.at((i * vertSize) + texCoord1Attr.getOffset()) = mesh.vertices[i].getTexCoord1().x;
					floatBuffer.at((i * vertSize) + texCoord1Attr.getOffset() + 1) = mesh.vertices[i].getTexCoord1().y;
				}
				if (tangents)
				{
					floatBuffer.at((i * vertSize) + tangAttr.getOffset()) = mesh.vertices[i].getTangent().x;
					floatBuffer.at((i * vertSize) + tangAttr.getOffset() + 1) = mesh.vertices[i].getTangent().y;
					floatBuffer.at((i * vertSize) + tangAttr.getOffset() + 2) = mesh.vertices[i].getTangent().z;
				}
				if (bitangents)
				{
					floatBuffer.at((i * vertSize) + bitangAttr.getOffset()) = mesh.vertices[i].getBitangent().x;
					floatBuffer.at((i * vertSize) + bitangAttr.getOffset() + 1) = mesh.vertices[i].getBitangent().y;
					floatBuffer.at((i * vertSize) + bitangAttr.getOffset() + 2) = mesh.vertices[i].getBitangent().z;
				}
				if (boneIndices)
				{
					floatBuffer.at((i * vertSize) + boneIAttr.getOffset()) = static_cast<float>(mesh.vertices[i].getBoneIndex(0));
					floatBuffer.at((i * vertSize) + boneIAttr.getOffset() + 1) = static_cast<float>(mesh.vertices[i].getBoneIndex(1));
					floatBuffer.at((i * vertSize) + boneIAttr.getOffset() + 2) = static_cast<float>(mesh.vertices[i].getBoneIndex(2));
					floatBuffer.at((i * vertSize) + boneIAttr.getOffset() + 3) = static_cast<float>(mesh.vertices[i].getBoneIndex(3));
				}
				if (boneWeights)
				{
					floatBuffer.at((i * vertSize) + boneWAttr.getOffset()) = mesh.vertices[i].getBoneWeight(0);
					floatBuffer.at((i * vertSize) + boneWAttr.getOffset() + 1) = mesh.vertices[i].getBoneWeight(1);
					floatBuffer.at((i * vertSize) + boneWAttr.getOffset() + 2) = mesh.vertices[i].getBoneWeight(2);
					floatBuffer.at((i * vertSize) + boneWAttr.getOffset() + 3) = mesh.vertices[i].getBoneWeight(3);
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
}
#endif