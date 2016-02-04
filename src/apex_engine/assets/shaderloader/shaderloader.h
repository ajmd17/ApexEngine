#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include "../assetloader.h"

class ShaderLoader : public IAssetLoader
{
public:
	ShaderLoader();

	~ShaderLoader() {}

	void resetLoader();

	std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
};

#endif