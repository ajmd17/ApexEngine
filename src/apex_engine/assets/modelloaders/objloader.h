#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../assetloader.h"
#include "../assetinfo.h"
#include "../assetmanager.h"
#include "../../scene/spatial.h"

class ObjLoader : public IAssetLoader
{
public:
	ObjLoader() 
	{
	//	AssetManager::registerExt<this>("obj");
	}

	~ObjLoader() {}

	ILoadableObject *load(AssetInfo &asset)
	{
		return 0;
	}
};

#endif