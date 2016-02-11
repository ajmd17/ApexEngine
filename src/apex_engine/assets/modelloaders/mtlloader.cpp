#include "mtlloader.h"

#include "../../rendering/texture2d.h"
#include "../assetmanager.h"
#include "../../util/strutil.h"
#include "../../util/logutil.h"

namespace apex
{
	std::shared_ptr<ILoadableObject> MtlLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		std::shared_ptr<MaterialList> mtlList(new MaterialList());

		std::string line;
		while (std::getline(*asset.getStream(), line))
		{
			vector<string> tokens = split(line, ' ');
			tokens = removeEmptyStrings(tokens);

			if (tokens.size() == 0 || strcmp(tokens[0].c_str(), "#") == 0)
			{
			}
			else if (!strcmp(tokens[0].c_str(), "newmtl"))
			{
				string name = tokens[1];

				Material mtl;
				mtl.setString(Material::STRING_NAME, name);
				mtlList->addMaterial(mtl);
			}
			else if (!strcmp(tokens[0].c_str(), "Kd"))
			{
				float r = atof(tokens[1].c_str());
				float g = atof(tokens[2].c_str());
				float b = atof(tokens[3].c_str());

				Vector4f col(r, g, b, 1.0f);
				mtlList->getLastMaterial().setVector4f(Material::COLOR_DIFFUSE, col);
			}
			else if (!strcmp(tokens[0].c_str(), "Ka"))
			{
				/*float r = atof(tokens[1].c_str());
				float g = atof(tokens[2].c_str());
				float b = atof(tokens[3].c_str());

				Vector4f col(r, g, b, 1.0f);
				mtlList->getLastMaterial().setVector4f(Material::COLOR_AMBIENT, col);*/
			}
			else if (!strcmp(tokens[0].c_str(), "Ks"))
			{
				/*float r = atof(tokens[1].c_str());
				float g = atof(tokens[2].c_str());
				float b = atof(tokens[3].c_str());

				Vector4f col(r, g, b, 1.0f);
				mtlList->getLastMaterial().setVector4f(Material::COLOR_SPECULAR, col);*/
			}
			else if (!strcmp(tokens[0].c_str(), "Ns"))
			{
				string spec = tokens[1];
				float fSpec = atof(spec.c_str());
				mtlList->getLastMaterial().setVector4f(Material::FLOAT_SHININESS, fSpec * 0.001f);
			}
			else if (!strcmp(tokens[0].c_str(), "map_Kd"))
			{
				string texName = tokens[tokens.size() - 1]; 
				
				std::string currentDir = std::string(asset.getFilePath());
				currentDir = currentDir.substr(0, currentDir.find_last_of("\\/"));
				
				if (!contains(currentDir, "/") && !contains(currentDir, "\\"))	// the file path is just current file name,															   
				{																// so just make the string empty
					currentDir = "";
				}

				currentDir += "/" + texName;
			
				shared_ptr<Texture2D> tex = assetMgr->loadAs<Texture2D>(currentDir.c_str());
				mtlList->getLastMaterial().setTexture(Material::TEXTURE_DIFFUSE, tex);
			}
			else if (!strcmp(tokens[0].c_str(), "map_bump"))
			{
				string texName = tokens[tokens.size() - 1];

				std::string currentDir = std::string(asset.getFilePath());
				currentDir = currentDir.substr(0, currentDir.find_last_of("\\/"));

				if (!contains(currentDir, "/") && !contains(currentDir, "\\"))	// the file path is just current file name,															   
				{																// so just make the string empty
					currentDir = "";
				}

				currentDir += "/" + texName;

				shared_ptr<Texture2D> tex = assetMgr->loadAs<Texture2D>(currentDir.c_str());
				mtlList->getLastMaterial().setTexture(Material::TEXTURE_NORMAL, tex);
			}
		}

		return std::static_pointer_cast<ILoadableObject>(mtlList);
	}
}