#include "a3dloader.h"
using namespace rapidjson;

namespace apex
{
	std::shared_ptr<ILoadableObject> A3dLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";

		MyHandler handler;
		Reader reader;
		StringStream ss(json);
		reader.Parse(ss, handler);

		return 0;
	}
}