#ifndef A3DEXPORTER_H
#define A3DEXPORTER_H

#include "../a3dmodel.h"

#include "../../scene/spatial.h"
#include "../../scene/geometry.h"
#include "../../scene/node.h"

#include "../../math/vector2f.h"
#include "../../math/vector3f.h"

#include "../../rendering/vertex.h"
#include "../../rendering/constants.h"

#include "../../util/xml/xml_writer.h"
#include "../../util/strutil.h"

#include <fstream>
using std::ofstream;

#include <algorithm>

#include <vector>
using std::vector;

namespace apex
{
	
	inline bool vec_contains(const vector<Vector3f> &list, const Vector3f &item, int &outIndex)
	{
		for (size_t i = 0; i < list.size(); i++)
		{
			const Vector3f &cvec = list[i];

			if (cvec.x == item.x && cvec.y == item.y && cvec.z == item.z)
			{
				outIndex = i;
				return true;
			}
		}

		outIndex = list.size();
		return false;
	}

	inline bool vec_contains(const vector<Vector2f> &list, const Vector2f &item, int &outIndex)
	{
		for (size_t i = 0; i < list.size(); i++)
		{
			const Vector2f &cvec = list[i];

			if (cvec.x == item.x && cvec.y == item.y)
			{
				outIndex = i;
				return true;
			}
		}

		outIndex = list.size();
		return false;
	}

	class A3dExporter
	{
	private:
		XmlWriter *xml;

		void saveMesh(Mesh *mesh)
		{
			xml->beginElement(TOKEN_MESH);

			vector<Vector3f> tmpPositions, tmpNormals;
			vector<Vector2f> tmpTexCoords0, tmpTexCoords1;
			//vector<BoneAssign> tmpBoneAssigns;

			vector<int> facesP, facesN, facesT0, facesT1;
			vector<Vertex> tmpVerts;

			for (size_t i = 0; i < mesh->indices.size(); i++)
				tmpVerts.push_back(mesh->vertices[mesh->indices[i]]);

			for (size_t i = 0; i < tmpVerts.size(); i++)
			{
				Vertex v = tmpVerts[i];

				int indices[4];

				if (!vec_contains(tmpPositions, v.getPosition(), indices[0]))
					tmpPositions.push_back(v.getPosition());
				if (!vec_contains(tmpNormals, v.getNormal(), indices[1]))
					tmpNormals.push_back(v.getNormal());
				if (!vec_contains(tmpTexCoords0, v.getTexCoord0(), indices[2]))
					tmpTexCoords0.push_back(v.getTexCoord0());
				if (!vec_contains(tmpTexCoords1, v.getTexCoord1(), indices[3]))
					tmpTexCoords1.push_back(v.getTexCoord1());

				facesP.push_back(indices[0]);
				facesN.push_back(indices[1]);
				facesT0.push_back(indices[2]);
				facesT1.push_back(indices[3]);

				/*for (int j = 0; j < 4; j++)
				{
					if (tmpVerts[i].getBoneWeight(j) > 0.0f)
					{
						boneAssigns.push_back(BoneAssign(i, tmpVerts[i].getBoneWeight(j), tmpVerts[i].getBoneIndex(j)));
					}
				}*/
			}

			bool writeNormals = facesN.size() > 0 && mesh->getAttributes().hasAttribute(VertexAttributes::NORMALS);
			bool writeTexCoords0 = facesT0.size() > 0 && mesh->getAttributes().hasAttribute(VertexAttributes::TEXCOORDS0);
			bool writeTexCoords1 = facesT1.size() > 0 && mesh->getAttributes().hasAttribute(VertexAttributes::TEXCOORDS1);

			xml->attribute(TOKEN_HAS_POSITIONS, to_str<bool>(facesP.size() > 0 && mesh->getAttributes().hasAttribute(VertexAttributes::POSITIONS)));
			xml->attribute(TOKEN_HAS_NORMALS, to_str<bool>(writeNormals));
			xml->attribute(TOKEN_HAS_TEXCOORDS0, to_str<bool>(writeTexCoords0));
			xml->attribute(TOKEN_HAS_TEXCOORDS1, to_str<bool>(writeTexCoords1));

			xml->beginElement(TOKEN_VERTICES);

			if (mesh->getAttributes().hasAttribute(VertexAttributes::POSITIONS))
			{
				for (size_t i = 0; i < tmpPositions.size(); i++)
				{
					xml->beginElement(TOKEN_POSITION);
					xml->attribute("x", to_str<float>(tmpPositions[i].x));
					xml->attribute("y", to_str<float>(tmpPositions[i].y));
					xml->attribute("z", to_str<float>(tmpPositions[i].z));
					xml->endElement();
				}
			}
			if (writeNormals)
			{
				for (size_t i = 0; i < tmpNormals.size(); i++)
				{
					xml->beginElement(TOKEN_NORMAL);
					xml->attribute("x", to_str<float>(tmpNormals[i].x));
					xml->attribute("y", to_str<float>(tmpNormals[i].y));
					xml->attribute("z", to_str<float>(tmpNormals[i].z));
					xml->endElement();
				}
			}
			if (writeTexCoords0)
			{
				for (size_t i = 0; i < tmpTexCoords0.size(); i++)
				{
					xml->beginElement(TOKEN_TEXCOORD0);
					xml->attribute("x", to_str<float>(tmpTexCoords0[i].x));
					xml->attribute("y", to_str<float>(tmpTexCoords0[i].y));
					xml->endElement();
				}
			}
			if (writeTexCoords1)
			{
				for (size_t i = 0; i < tmpTexCoords1.size(); i++)
				{
					xml->beginElement(TOKEN_TEXCOORD1);
					xml->attribute("x", to_str<float>(tmpTexCoords1[i].x));
					xml->attribute("y", to_str<float>(tmpTexCoords1[i].y));
					xml->endElement();
				}
			}

			xml->endElement(); // vertices

			xml->beginElement(TOKEN_FACES);

			int stride = 1;
			if (writeNormals) stride++;
			if (writeTexCoords0) stride++;
			if (writeTexCoords1) stride++;

			for (size_t i = 0; i < facesP.size(); i+=3)
			{
				xml->beginElement(TOKEN_FACE);
				xml->attribute("i0", to_str<int>(facesP[i]) +"/" +
					(writeNormals ? to_str<int>(facesN[i]) : "") + "/" +
					(writeTexCoords0 ? to_str<int>(facesT0[i]) : "") + "/" +
					(writeTexCoords1 ? to_str<int>(facesT1[i]) : ""));

				xml->attribute("i1", to_str<int>(facesP[i + 1]) +"/" +
					(writeNormals ? to_str<int>(facesN[i + 1]) : "") + "/" +
					(writeTexCoords0 ? to_str<int>(facesT0[i + 1]) : "") + "/" +
					(writeTexCoords1 ? to_str<int>(facesT1[i + 1]) : ""));

				xml->attribute("i2", to_str<int>(facesP[i + 2]) +"/" +
					(writeNormals ? to_str<int>(facesN[i + 2]) : "") + "/" +
					(writeTexCoords0 ? to_str<int>(facesT0[i + 2]) : "") + "/" +
					(writeTexCoords1 ? to_str<int>(facesT1[i + 2]) : ""));

				xml->endElement(); // face
			}

			xml->endElement(); // faces

			/*if (boneAssigns.size() > 0)
			{
				xml->beginElement(TOKEN_BONE_ASSIGNS);
				for (size_t i = 0; i < boneAssigns.size(); i++)
				{
					xml->beginElement(TOKEN_BONE_ASSIGN);
					xml->attribute(TOKEN_VERTEXINDEX, to_str<int>(boneAssigns[i].getVertexIndex()));
					xml->attribute(TOKEN_BONEINDEX, to_str<int>(boneAssigns[i].getBoneIndex()));
					xml->attribute(TOKEN_BONEWEIGHT, to_str<float>(boneAssigns[i].getBoneWeight()));
					xml->endElement(); // bone assign
				}
				xml->endElement(); // bone assigns
			}

			if (mesh->getSkeleton() != 0)
			{
				// if vector doesnt contain mesh's skeleton,
				// add it.

				// blah blah write assign
			}*/

			xml->endElement(); // mesh
		}

		void saveGeometry(Geometry *geometry)
		{
			xml->beginElement(TOKEN_GEOMETRY);
			xml->attribute(TOKEN_NAME, geometry->getName());

			xml->beginElement(TOKEN_TRANSLATION);
			xml->attribute("x", to_str<float>(geometry->getLocalTranslation().x));
			xml->attribute("y", to_str<float>(geometry->getLocalTranslation().y));
			xml->attribute("z", to_str<float>(geometry->getLocalTranslation().z));
			xml->endElement(); // translation

			xml->beginElement(TOKEN_SCALE);
			xml->attribute("x", to_str<float>(geometry->getLocalScale().x));
			xml->attribute("y", to_str<float>(geometry->getLocalScale().y));
			xml->attribute("z", to_str<float>(geometry->getLocalScale().z));
			xml->endElement(); // scale

			xml->beginElement(TOKEN_ROTATION);
			xml->attribute("x", to_str<float>(geometry->getLocalRotation().x));
			xml->attribute("y", to_str<float>(geometry->getLocalRotation().y));
			xml->attribute("z", to_str<float>(geometry->getLocalRotation().z));
			xml->attribute("w", to_str<float>(geometry->getLocalRotation().w));
			xml->endElement(); // rotation

			if (geometry->getMesh() != 0)
				saveMesh(geometry->getMesh());
			//saveMaterial(&geometry->getMaterial());
			
			xml->endElement(); // geometry
		}

		void saveNode(Node *node)
		{
			xml->beginElement(TOKEN_NODE);
			if (!apex::str_eql(node->getName(), "root"))
				xml->attribute(TOKEN_NAME, node->getName());
			else
				xml->attribute(TOKEN_NAME, "root_model");

			xml->beginElement(TOKEN_TRANSLATION);
			xml->attribute("x", to_str<float>(node->getLocalTranslation().x));
			xml->attribute("y", to_str<float>(node->getLocalTranslation().y));
			xml->attribute("z", to_str<float>(node->getLocalTranslation().z));
			xml->endElement(); // translation

			xml->beginElement(TOKEN_SCALE);
			xml->attribute("x", to_str<float>(node->getLocalScale().x));
			xml->attribute("y", to_str<float>(node->getLocalScale().y));
			xml->attribute("z", to_str<float>(node->getLocalScale().z));
			xml->endElement(); // scale

			xml->beginElement(TOKEN_ROTATION);
			xml->attribute("x", to_str<float>(node->getLocalRotation().x));
			xml->attribute("y", to_str<float>(node->getLocalRotation().y));
			xml->attribute("z", to_str<float>(node->getLocalRotation().z));
			xml->attribute("w", to_str<float>(node->getLocalRotation().w));
			xml->endElement(); // rotation

			for (size_t i = 0; i < node->size(); i++)
				saveSpatial(node->getAt<Spatial>(i).get());
			
			xml->endElement(); // node
		}

		void saveSpatial(Spatial *spatial)
		{
			Node *n;
			Geometry *g;

			if (g = dynamic_cast<Geometry*>(spatial))
				saveGeometry(g);
			else if (n = dynamic_cast<Node*>(spatial))
				saveNode(n);
			return;
		}
	public:
		A3dExporter() {}

		void exportFile(const char *filepath, Spatial *spatial)
		{
			xml = new XmlWriter(filepath);

			xml->beginDocument();
			xml->beginElement(TOKEN_MODEL);

			this->saveSpatial(spatial);
			// this->saveSkeletons();

			xml->endElement(); // model
			xml->close();

			delete xml;
		}
	};
}

#endif