#include "vertexattributes.h"
#include "constants.h"

namespace apex
{
	VertexAttribute VertexAttributes::POSITIONS = VertexAttribute(A_POSITION.c_str(), 3);
	VertexAttribute VertexAttributes::TEXCOORDS0 = VertexAttribute(A_TEXCOORD0.c_str(), 2);
	VertexAttribute VertexAttributes::TEXCOORDS1 = VertexAttribute(A_TEXCOORD1.c_str(), 2);
	VertexAttribute VertexAttributes::NORMALS = VertexAttribute(A_NORMAL.c_str(), 3);
	VertexAttribute VertexAttributes::TANGENTS = VertexAttribute(A_TANGENT.c_str(), 3);
	VertexAttribute VertexAttributes::BITANGENTS = VertexAttribute(A_BITANGENT.c_str(), 3);
	VertexAttribute VertexAttributes::BONEINDICES = VertexAttribute(A_BONEINDICES.c_str(), 4);
	VertexAttribute VertexAttributes::BONEWEIGHTS = VertexAttribute(A_BONEWEIGHTS.c_str(), 4);
}