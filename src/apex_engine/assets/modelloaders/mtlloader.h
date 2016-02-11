#ifndef MTLLOADER_H
#define MTLLOADER_H

#include "../assetloader.h"
#include "../../rendering/material.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace apex
{
	class MaterialList : public ILoadableObject 
	{
	private:
		vector<Material> materials;
	public:
		MaterialList() {}

		void clearList() { materials.clear(); }

		void addMaterial(Material m)
		{
			this->materials.push_back(m);
		}

		Material &getLastMaterial()
		{
			return materials[materials.size() - 1];
		}

		bool getMaterial(const string name, Material &outMaterial)
		{
			for (int i = 0; i < materials.size(); i++)
			{
				string nm = "";
				if (materials[i].getString(Material::STRING_NAME, nm))
				{
					if (!strcmp(nm.c_str(), name.c_str()))
					{
						outMaterial = materials[i];
						return true;
					}
				}
			}
			return false;
		}
		
	};

	class MtlLoader : public IAssetLoader
	{
	private:
		vector<string> matNames;
	public:
		MtlLoader()
		{
		}

		~MtlLoader() {}

		void resetLoader()
		{
		}

		std::shared_ptr<ILoadableObject> load(AssetManager *assetMgr, AssetInfo &asset);
	};
}

#endif