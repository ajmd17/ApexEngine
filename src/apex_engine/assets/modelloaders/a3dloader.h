#ifndef A3DLOADER_H
#define A3DLOADER_H

#include "../assetloader.h"
#include "../a3dmodel.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "../../util/xml/sax_parser.h"

namespace apex
{

	class A3dLoader : public IAssetLoader
	{
	private:
	public:
		A3dLoader() {}

		~A3dLoader() {}

		void resetLoader();

		std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
	};
}

#endif