#include "assetmanager.h"

#include <iostream>
using std::getline;
using std::cout;

#include <fstream>
using std::ifstream;

void AssetManager::loadModel(char *filepath)
{
	LoadedAsset asset;

	ifstream filestream(filepath);

	asset.setStream(&filestream);
	asset.setFilePath(filepath);

	string line;
	if (filestream.is_open())
	{
		//while (getline(filestream, line))
		//{
		//	cout << line << '\n';
		//}
		// assetLoader.loadAsset(asset, outModel);

		filestream.close();
	}
	else cout << "Unable to load model '" << filepath << "'\n";

	

	// return outModel;
} 