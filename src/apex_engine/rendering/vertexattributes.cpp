#include "vertexattributes.h"
#include "constants.h"

namespace apex
{
	VertexAttribute VertexAttributes::POSITIONS = VertexAttribute(A_POSITION, 3);
	VertexAttribute VertexAttributes::TEXCOORDS0 = VertexAttribute(A_TEXCOORD0, 2);
	VertexAttribute VertexAttributes::TEXCOORDS1 = VertexAttribute(A_TEXCOORD1, 2);
	VertexAttribute VertexAttributes::NORMALS = VertexAttribute(A_NORMAL, 3);
	VertexAttribute VertexAttributes::TANGENTS = VertexAttribute(A_TANGENT, 3);
	VertexAttribute VertexAttributes::BITANGENTS = VertexAttribute(A_BITANGENT, 3);
	VertexAttribute VertexAttributes::BONEINDICES = VertexAttribute(A_BONEINDICES, 4);
	VertexAttribute VertexAttributes::BONEWEIGHTS = VertexAttribute(A_BONEWEIGHTS, 4);
}