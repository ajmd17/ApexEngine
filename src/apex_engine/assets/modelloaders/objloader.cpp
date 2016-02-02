#include "objloader.h"

#include "../../scene/spatial.h"
#include "../../scene/node.h"
#include "../../scene/geometry.h"

#include "../../rendering/vertex.h"

#include "../../util/strutil.h"

#include <fstream>
#include <sstream>
#include <string>

#include <algorithm>

#include <memory>
using std::shared_ptr;

void ObjLoader::resetLoader()
{
	this->hasNormals = false;
	this->hasTexCoords = false;

	this->objIndices.clear();
	this->texCoords.clear();
	this->positions.clear();
	this->normals.clear();
	this->names.clear();
	this->namesMtl.clear();
	this->materials.clear();
	this->mtlOrder.clear();
}

vector<ObjIndex> *ObjLoader::currentList()
{
	if (objIndices.size() == 0)
		newMesh("child_0");
	return objIndices[objIndices.size() - 1];
}

void ObjLoader::newMesh(const string &name)
{
	int counter = 0;
	string nm = name;

	while (std::find(names.begin(), names.end(), nm) != names.end())
	{
		counter++;
		nm = name + "_" + std::to_string(static_cast<long long>(counter));
	}

	vector<ObjIndex> *vec = new vector<ObjIndex>();
	objIndices.push_back(vec);

	names.push_back((counter == 0 ? name : name + "_" + std::to_string(static_cast<long long>(counter))));
	namesMtl.push_back(name);
}

ObjIndex ObjLoader::parseObjIndex(const string &token)
{
	vector<string> values = split(token, '/');

	ObjIndex res;

	if (values.size() > 0)
	{
		res.vertex_idx = parseInt(values[0]) - 1;
		if (values.size() > 1)
		{
			if (strcmp(values[1].c_str(), "") != 0)
			{
				hasTexCoords = true;
				res.texcoord_idx = parseInt(values[1]) - 1;
			}
			if (values.size() > 2)
			{
				if (strcmp(values[2].c_str(), "") != 0)
				{
					hasNormals = true;
					res.normal_idx = parseInt(values[2]) - 1;
				}
			}
		}
	}

	return res;
}

Material &ObjLoader::materialWithName(const string name)
{
	for (int i = 0; i < materials.size(); i++)
	{
		string outName;
		if (materials[i].getString(Material::STRING_NAME, outName))
		{
			if (strcmp(outName.c_str(), name.c_str()) == 0)
				return materials[i];
		}
	}
	Material m;
	m.setString(Material::STRING_NAME, name);
	return m;
}

std::shared_ptr<ILoadableObject> ObjLoader::load(AssetInfo &asset)
{
	Node *node = new Node();
	node->setName("Objthing");

	std::string line;
	while (std::getline(*asset.getStream(), line))
	{
		vector<string> tokens = split(line, ' ');
		tokens = removeEmptyStrings(tokens);

		if (tokens.size() == 0 || strcmp(tokens[0].c_str(), "#") == 0)
		{
		}
		else if (strcmp(tokens[0].c_str(), "v") == 0)
		{
			float x = parseFloat(tokens[1]);
			float y = parseFloat(tokens[2]);
			float z = parseFloat(tokens[3]);
			Vector3f vec(x, y, z);
			positions.push_back(vec);
		}
		else if (strcmp(tokens[0].c_str(), "vn") == 0)
		{
			float x = parseFloat(tokens[1]);
			float y = parseFloat(tokens[2]);
			float z = parseFloat(tokens[3]);
			Vector3f vec(x, y, z);
			normals.push_back(vec);
		}
		else if (strcmp(tokens[0].c_str(), "vt") == 0)
		{
			float x = parseFloat(tokens[1]);
			float y = parseFloat(tokens[2]);
			Vector2f vec(x, y);
			texCoords.push_back(vec);
		}
		else if (strcmp(tokens[0].c_str(), "f") == 0)
		{
			vector<ObjIndex> *c_idx = currentList();
			for (int i = 0; i < tokens.size() - 3; i++)
			{
				c_idx->push_back(parseObjIndex(tokens[1]));
				c_idx->push_back(parseObjIndex(tokens[2 + i]));
				c_idx->push_back(parseObjIndex(tokens[3 + i]));
			}
		}
		else if (strcmp(tokens[0].c_str(), "usemtl") == 0)
		{
			string matname = tokens[1];
			newMesh(matname);
		}
	}

	for (int i = 0; i < objIndices.size(); i++)
	{
		vector<ObjIndex> *c_idx = objIndices[i];
		vector<Vertex> vertices;

		for (int j = 0; j < c_idx->size(); j++)
		{
			Vertex vert(positions[(*c_idx)[j].vertex_idx],
						(hasTexCoords ? texCoords[(*c_idx)[j].texcoord_idx] : Vector2f()),
						(hasNormals ? normals[(*c_idx)[j].normal_idx] : Vector3f()));

			vertices.push_back(vert);
		}

		shared_ptr<Mesh> mesh(new Mesh());
		mesh->setVertices(vertices);

		Geometry *geom = new Geometry();
		geom->setName(names[i]);
		geom->setMesh(mesh);
		node->add(geom);

		delete c_idx;
	}

	std::shared_ptr<ILoadableObject> resPtr (node);
	return resPtr;
}