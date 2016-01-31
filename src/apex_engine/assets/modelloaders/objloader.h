#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../assetloader.h"
#include "../assetinfo.h"

class ObjLoader : public IAssetLoader
{
public:
	ObjLoader() 
	{
	}

	~ObjLoader() {}

	void resetLoader();

	std::shared_ptr<ILoadableObject> load(AssetInfo &asset);
};

#endif