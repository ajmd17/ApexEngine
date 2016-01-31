#include "assetmanager.h"

#include <iostream>
using std::getline;
using std::cout;

#include <fstream>
using std::ifstream;

#include "../rendering/texture2d.h"
#include "../util/strutil.h"

AssetManager::AssetManager()
{
	// Create and register default loaders
	this->textureLoader = std::make_shared<TextureLoader>();
	this->registerExt("png", this->textureLoader);
	this->registerExt("jpg", this->textureLoader);
}

AssetManager::~AssetManager()
{
	unordered_map<char *, std::shared_ptr<IAssetLoader> >::iterator it;
	for (auto iterator = loaders.begin(); iterator != loaders.end(); iterator++)
	{
		loaders.erase(iterator);
	}
}

std::shared_ptr<ILoadableObject> AssetManager::load(char *filepath)
{
	std::shared_ptr<IAssetLoader> finalLoader;

	unordered_map<char *, std::shared_ptr<IAssetLoader> >::iterator it;
	for (auto iterator = loaders.begin(); iterator != loaders.end(); iterator++) 
	{
		char *ext = iterator->first;
		std::shared_ptr<IAssetLoader> loader = iterator->second;

		if (endsWith(filepath, ext))
		{
			finalLoader = loader;
			break;
		}
	}

	if (!finalLoader)
	{
		throw std::runtime_error("No suitable loader found");
		return 0;
	}

	ifstream filestream(filepath);
	if (!filestream.is_open())
	{
		throw std::exception("File stream is not valid");
		return 0;
	}

	AssetInfo assetInfo;
	assetInfo.setFilePath(filepath);
	assetInfo.setStream(&filestream);
	std::shared_ptr<ILoadableObject> obj = finalLoader->load(assetInfo);

	filestream.close();

	return obj;
}


void AssetManager::registerExt(char *ext, std::shared_ptr<IAssetLoader> loader)
{
	unordered_map<char *, std::shared_ptr<IAssetLoader> >::iterator it = loaders.find(ext);
	if (it != loaders.end())
		throw std::runtime_error("A loader is already registered for this type");
	else
	{
		loaders[ext] = loader;
	}
}

std::shared_ptr<IAssetLoader> AssetManager::getLoader(char *ext)
{
	unordered_map<char *, std::shared_ptr<IAssetLoader> >::iterator it = loaders.find(ext);
	if (it == loaders.end())
		throw std::runtime_error("No suitable loader found");
	else
		return it->second;
}

Texture2D *AssetManager::loadTexture(char *filepath)
{
	AssetInfo asset;
	asset.setFilePath(filepath);

	Texture2D *res = new Texture2D();
	RenderManager::getEngine()->loadTexture2D(asset, *res);

	return res;
}

void AssetManager::loadModel(char *filepath)
{
	AssetInfo asset;

	ifstream filestream(filepath);

	asset.setStream(&filestream);
	asset.setFilePath(filepath);

	string line;
	if (filestream.is_open())
	{
		//while (getline(filestream, line))
		//{
		//	cout << line << '\n';
		//}
		// assetLoader.loadAsset(asset, outModel);

		filestream.close();
	}
	else cout << "Unable to load model '" << filepath << "'\n";

	

	// return outModel;
} 