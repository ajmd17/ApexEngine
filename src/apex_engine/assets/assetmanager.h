#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "loadedasset.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

class Texture2D;

class AssetManager
{
private:
	vector<LoadedAsset> loadedAssets;
public:
	AssetManager() {}

	~AssetManager()
	{

	}

	template <typename AssetType>
	AssetType *load(const char *filepath)
	{}

	void loadModel(char *filepath);

	Texture2D *loadTexture(char *filepath);
};

#endif