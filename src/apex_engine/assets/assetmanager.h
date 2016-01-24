#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

// Asset manager for the engine.
// Author: Andrew MacDonald

#include "loadedasset.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <map>
using std::map;

#include "assetloader.h"

class Texture2D;

class AssetManager
{
private:
	vector<LoadedAsset> loadedAssets;
	//static map<char*, AssetLoader*> loaders;
public:
	AssetManager() {}

	~AssetManager()
	{
	}

	template <typename AssetType>
	static AssetType *load(const char *filepath)
	{
		//LoadedAsset ast(0, filepath);
		//AssetType returnedAsset = AssetManager::loaders["apx"]->load<AssetType>(ast);
		return 0;
	}

	void loadModel(char *filepath);

	Texture2D *loadTexture(char *filepath);
};

#endif