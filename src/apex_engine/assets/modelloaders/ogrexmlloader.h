#ifndef OGREXMLLOADER_H
#define OGREXMLLOADER_H

#include "../assetloader.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "../../util/xml/sax_parser.h"

namespace apex
{

	class OgreXmlLoader : public IAssetLoader
	{
	private:
	public:
		OgreXmlLoader() {}

		~OgreXmlLoader() {}

		void resetLoader();

		std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
	};
}

#endif