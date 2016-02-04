#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../assetloader.h"
#include "../assetinfo.h"

#include "../../math/vector3f.h"
#include "../../math/vector2f.h"

#include "../../rendering/material.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

class ObjIndex
{
public:
	int vertex_idx, normal_idx, texcoord_idx;

	ObjIndex(int v, int n, int t)
	{
		this->vertex_idx = v;
		this->normal_idx = n;
		this->texcoord_idx = t;
	}

	ObjIndex()
	{
		this->vertex_idx = 0;
		this->normal_idx = 0;
		this->texcoord_idx = 0;
	}
};

class ObjLoader : public IAssetLoader
{
private:
	vector<string> names;
	vector<string> namesMtl;

	vector<vector<ObjIndex>*> objIndices;
	vector<Vector3f> positions;
	vector<Vector3f> normals;
	vector<Vector2f> texCoords;

	vector<Material> materials;
	vector<Material> mtlOrder;

	bool hasTexCoords, hasNormals;

	vector<ObjIndex> *currentList();

	void newMesh(const string &name);

	ObjIndex parseObjIndex(const string &token);

	Material &materialWithName(const string name);
public:
	ObjLoader() 
	{
		this->hasTexCoords = false;
		this->hasNormals = false;
	}

	~ObjLoader() {}

	void resetLoader();

	std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
};

#endif