#ifndef ASSETLOADER_H
#define ASSETLOADER_H

// Asset loader interface.
// Author: Andrew MacDonald

#include "assetinfo.h"
#include "loadableobject.h"

class IAssetLoader
{
public:
	IAssetLoader() {}

	virtual void resetLoader() = 0;

	virtual ILoadableObject *load(AssetInfo &asset) = 0;
};

#endif