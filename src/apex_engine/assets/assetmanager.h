#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "loadedasset.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

class AssetManager
{
private:
	vector<LoadedAsset> loadedAssets;
public:
	AssetManager() {}

	~AssetManager()
	{

	}

	void loadModel(char *filepath);
};

#endif