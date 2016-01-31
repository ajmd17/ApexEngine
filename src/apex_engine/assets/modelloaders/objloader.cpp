#include "objloader.h"

#include "../../scene/spatial.h"

void ObjLoader::resetLoader()
{

}

std::shared_ptr<ILoadableObject> ObjLoader::load(AssetInfo &asset)
{
	throw std::exception("Obj loader not implemented");
}