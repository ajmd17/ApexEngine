#ifndef ASSETLOADER_H
#define ASSETLOADER_H

// Asset loader interface.
// Author: Andrew MacDonald

#include "assetinfo.h"
#include "loadableobject.h"

#include <memory>

namespace apex
{
	class AssetManager;

	class IAssetLoader
	{
	public:
		IAssetLoader() {}

		virtual void resetLoader() = 0;

		virtual std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset) = 0;
	};
}
#endif