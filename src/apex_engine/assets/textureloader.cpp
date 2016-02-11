#include "textureloader.h"
#include "../rendering/texture2d.h"

namespace apex
{
	TextureLoader::TextureLoader()
	{
	}

	void TextureLoader::resetLoader() {}

	std::shared_ptr<ILoadableObject> TextureLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		std::shared_ptr<Texture2D> tex(new Texture2D());
		RenderManager::getEngine()->loadTexture2D(asset, *tex.get());

		return std::static_pointer_cast<ILoadableObject> (tex);
	}
}