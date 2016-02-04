#include "textureloader.h"
#include "../rendering/texture2d.h"

TextureLoader::TextureLoader()
{
}

void TextureLoader::resetLoader() {}

std::shared_ptr<ILoadableObject> TextureLoader::load(AssetManager *assetMgr, AssetInfo &asset)
{
	Texture2D *tex = new Texture2D();
	RenderManager::getEngine()->loadTexture2D(asset, *tex);

	std::shared_ptr<ILoadableObject> res(tex);

	return res;
}