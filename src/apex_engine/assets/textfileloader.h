#ifndef TEXTFILELOADER_H
#define TEXTFILELOADER_H

// Loads basic text files.
// Author: Andrew MacDonald

#include "assetloader.h"
#include "loadedtext.h"

class TextFileLoader : public IAssetLoader
{
public:
	TextFileLoader() {}

	~TextFileLoader() {}

	void resetLoader() {}

	std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset)
	{
		std::string finalString = "";

		std::string line;
		while (std::getline(*asset.getStream(), line))
		{
			finalString += line + "\n";
		}

		std::shared_ptr<ILoadableObject> loadedTextFile(new LoadedText(finalString));
		return loadedTextFile;
	}
};

#endif