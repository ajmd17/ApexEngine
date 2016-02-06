#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "assetloader.h"

namespace apex
{
	class TextureLoader : public IAssetLoader
	{
	public:
		TextureLoader();

		~TextureLoader() {}

		void resetLoader();

		std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
	};
}
#endif