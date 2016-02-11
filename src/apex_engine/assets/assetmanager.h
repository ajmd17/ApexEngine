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

namespace apex
{
	class IAssetLoader;

	class AssetManager
	{
	private:
		unordered_map<const char*, std::shared_ptr<ILoadableObject>> loadedAssets;
		unordered_map<const char*, std::shared_ptr<IAssetLoader>> loaders;

		static AssetManager *defaultAssetManager;

		// Default loaders
		std::shared_ptr<IAssetLoader> textureLoader;
		std::shared_ptr<IAssetLoader> objLoader;
		std::shared_ptr<IAssetLoader> mtlLoader;
		std::shared_ptr<IAssetLoader> a3dLoader;
		std::shared_ptr<IAssetLoader> shaderLoader;
		std::shared_ptr<IAssetLoader> textFileLoader;
	public:
		AssetManager();

		~AssetManager();

		void registerExt(const char *ext, std::shared_ptr<IAssetLoader> loader);

		std::shared_ptr<IAssetLoader> getLoader(const char *ext);

		std::shared_ptr<ILoadableObject> load(const char *filepath, std::shared_ptr<IAssetLoader> loader);

		std::shared_ptr<ILoadableObject> load(const char *filepath);

		static AssetManager *getDefaultAssetManager();

		template <typename T>
		typename std::enable_if<std::is_base_of<ILoadableObject, T>::value, std::shared_ptr<T>>::type
			loadAs(const char *filepath)
		{
			std::shared_ptr<T> res = std::dynamic_pointer_cast<T> (load(filepath));
			return res;
		}

		template <typename T>
		typename std::enable_if<std::is_base_of<ILoadableObject, T>::value, std::shared_ptr<T>>::type
			loadAs(const char *filepath, std::shared_ptr<IAssetLoader> loader)
		{
			std::shared_ptr<T> res = std::dynamic_pointer_cast<T> (load(filepath, loader));
			return res;
		}
	};
}
#endif