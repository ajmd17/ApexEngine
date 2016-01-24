#ifndef ASSETLOADER_H
#define ASSETLOADER_H

// Asset loader interface.
// Author: Andrew MacDonald

#include "loadedasset.h"

class AssetLoader
{
public:
	AssetLoader() {}

	virtual void resetLoader() = 0;

	template <typename ReturnType>
	ReturnType *load(LoadedAsset &asset) {}
};

#endif