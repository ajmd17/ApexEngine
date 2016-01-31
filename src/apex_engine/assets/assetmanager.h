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

class Texture2D;

class AssetManager
{
private:
	unordered_map<AssetInfo, ILoadableObject*> loadedAssets;
	unordered_map<char*, std::shared_ptr<IAssetLoader>> loaders;

	std::shared_ptr<TextureLoader> textureLoader;
public:
	AssetManager();

	~AssetManager();

	void registerExt(char *ext, std::shared_ptr<IAssetLoader> loader);

	std::shared_ptr<IAssetLoader> getLoader(char *ext);

	std::shared_ptr<ILoadableObject> load(char *filepath);

	/*template <typename T>
	typename std::enable_if<std::is_base_of<ILoadableObject, T>::value, T*>::type
		load(char *filepath)
	{
		return static_cast<T*> (load(filepath));
	}*/

	void loadModel(char *filepath);

	Texture2D *loadTexture(char *filepath);
};

#endif