#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

// Asset manager for the engine.
// Author: Andrew MacDonald

#include "assetinfo.h"
#include "loadableobject.h"

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
	static map<AssetInfo, ILoadableObject*> loadedAssets;
	static map<char*, IAssetLoader*> loaders;

public:
	AssetManager() {}

	~AssetManager()
	{
	}

	template <typename T>
	static void registerExt(const char *ext);

	static ILoadableObject *load(char *filepath)
	{

	}

	/*template <typename ObjectType>
	typename std::enable_if<std::is_base_of<ObjectType, LoadableObject>::value, ObjectType*>::type
	static load(char *filepath)
	{
		return static_cast<ObjectType>(load(filepath));
	}*/

	static void loadModel(char *filepath);

	static Texture2D *loadTexture(char *filepath);
};

#endif