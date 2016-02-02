#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

// Asset manager for the engine.
// Author: Andrew MacDonald

#include "assetinfo.h"
#include "loadableobject.h"

#include <vector>
using std::vector;

#include <memory>

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

#include <map>
using std::map;

#include "assetloader.h"

// Default loaders
#include "textureloader.h"
#include "modelloaders/objloader.h"

class AssetManager
{
private:
	unordered_map<char*, std::shared_ptr<ILoadableObject>> loadedAssets;
	unordered_map<char*, std::shared_ptr<IAssetLoader>> loaders;

	// Default loaders
	std::shared_ptr<TextureLoader> textureLoader;
	std::shared_ptr<ObjLoader> objLoader;
public:
	AssetManager();

	~AssetManager();

	void registerExt(char *ext, std::shared_ptr<IAssetLoader> loader);

	std::shared_ptr<IAssetLoader> getLoader(char *ext);

	ILoadableObject *load(char *filepath, std::shared_ptr<IAssetLoader> loader);

	ILoadableObject *load(char *filepath);
};

#endif