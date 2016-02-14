#include "assetmanager.h"

#include <iostream>
using std::getline;

#include <string>

#include <fstream>
using std::ifstream;

#include "../util/strutil.h"
#include "../util/logutil.h"


#include "assetloader.h"
// Default loaders
#include "textureloader.h"
#include "modelloaders/objloader.h"
#include "modelloaders/mtlloader.h"
#include "modelloaders/a3dloader.h"
#include "modelloaders/ogrexmlloader.h"
#include "shaderloader/shaderloader.h"
#include "textfileloader.h"

namespace apex
{
	AssetManager *AssetManager::defaultAssetManager = new AssetManager();

	AssetManager::AssetManager()
	{
		// Create and register default loaders
		this->textureLoader = std::make_shared<TextureLoader>();
		this->registerExt("png", this->textureLoader);
		this->registerExt("jpg", this->textureLoader);
		this->registerExt("bmp", this->textureLoader);
		this->registerExt("tga", this->textureLoader);
		this->registerExt("gif", this->textureLoader);

		this->objLoader = std::make_shared<ObjLoader>();
		this->registerExt("obj", this->objLoader);

		this->mtlLoader = std::make_shared<MtlLoader>();
		this->registerExt("mtl", this->mtlLoader);

		this->a3dLoader = std::make_shared<A3dLoader>();
		this->registerExt("a3d", this->a3dLoader);

		this->ogreXmlLoader = std::make_shared<OgreXmlLoader>();
		this->registerExt("mesh.xml", this->ogreXmlLoader);

		this->shaderLoader = std::make_shared<ShaderLoader>();
		this->registerExt("frag", this->shaderLoader);
		this->registerExt("vert", this->shaderLoader);
		this->registerExt("geom", this->shaderLoader);
		this->registerExt("vs", this->shaderLoader);
		this->registerExt("fs", this->shaderLoader);
		this->registerExt("gs", this->shaderLoader);
		this->registerExt("glsl", this->shaderLoader);

		this->textFileLoader = std::make_shared<TextFileLoader>();
		this->registerExt("txt", this->textFileLoader);
	}

	AssetManager::~AssetManager()
	{
		loaders.clear();
		loadedAssets.clear();
	}

	AssetManager *AssetManager::getDefaultAssetManager()
	{
		return defaultAssetManager;
	}

	std::shared_ptr<ILoadableObject> AssetManager::load(const char *filepath, std::shared_ptr<IAssetLoader> loader)
	{
		ifstream filestream(filepath);
		if (!filestream.is_open())
		{
			engine_log << "Error loading \"" << filepath << "\": Invalid path.\n";
			return 0;
		}

		AssetInfo assetInfo;
		assetInfo.setFilePath(filepath);
		assetInfo.setStream(&filestream);
		std::shared_ptr<ILoadableObject> obj = loader->load(this, assetInfo);

		filestream.close();

		loader->resetLoader();

		loadedAssets[filepath] = obj;

		return obj;
	}

	std::shared_ptr<ILoadableObject> AssetManager::load(const char *filepath)
	{
		for (auto iterator = loadedAssets.begin(); iterator != loadedAssets.end(); iterator++)
		{
			if (strcmp(iterator->first, filepath) == 0)
			{
				engine_log << "Re-using asset: " << filepath << "\n";
				return iterator->second;
			}
		}

		std::shared_ptr<IAssetLoader> finalLoader;

		for (auto iterator = loaders.begin(); iterator != loaders.end(); iterator++)
		{
			const char *ext = iterator->first;
			std::shared_ptr<IAssetLoader> loader = iterator->second;

			if (endsWith(filepath, ext))
			{
				finalLoader = loader;
				break;
			}
		}

		if (!finalLoader)
		{
			engine_log << "Error loading \"" << filepath << "\": File type not supported.\n";
			return 0;
		}

		return load(filepath, finalLoader);
	}

	void AssetManager::registerExt(const char *ext, std::shared_ptr<IAssetLoader> loader)
	{
		unordered_map<const char *, std::shared_ptr<IAssetLoader> >::iterator it = loaders.find(ext);
		if (it != loaders.end())
			throw std::runtime_error("A loader is already registered for this type");
		else
		{
			loaders[ext] = loader;
		}
	}

	std::shared_ptr<IAssetLoader> AssetManager::getLoader(const char *ext)
	{
		unordered_map<const char *, std::shared_ptr<IAssetLoader> >::iterator it = loaders.find(ext);
		if (it == loaders.end())
			throw std::runtime_error("No suitable loader found");
		else
			return it->second;
	}
}