#include "shaderloader.h"
#include "../loadedtext.h"

#include "../../util/strutil.h"
#include "../../util/logutil.h"

#include "../../rendering/shaderlib.h"

#include "../assetmanager.h"

#include <vector>
#include <string>

namespace apex
{
	ShaderLoader::ShaderLoader()
	{
		ShaderLib::init();
	}

	void ShaderLoader::resetLoader()
	{
	}

	std::shared_ptr<ILoadableObject> ShaderLoader::load(AssetManager *assetMgr, AssetInfo &asset)
	{
		std::string INCLUDE = "#include";

		const int INTERNAL = 0, EXTERNAL = 1;

		std::string finalString = "";
		std::vector<std::string> lines;

		std::string line;
		while (std::getline(*asset.getStream(), line))
		{
			if (startsWith(trim(line), INCLUDE))
			{
				std::vector<std::string> tokens = split(line, ' ');

				if (tokens.size() != 2) // #include <something> or #include "something"
					throw std::invalid_argument("Invalid include statement");

				int includeType;
				std::string inc = tokens[1];
				if (contains(inc, std::string("<")) || contains(inc, std::string(">")))
					includeType = INTERNAL;
				else
					includeType = EXTERNAL;

				int len = strlen(inc.c_str());
				inc = inc.substr(1, len - 2);

				std::string shaderCode;
				if (includeType == INTERNAL)
					shaderCode = ShaderLib::getCode(inc);
				else if (includeType == EXTERNAL)
				{
					std::string currentDir = std::string(asset.getFilePath());
					currentDir = currentDir.substr(0, currentDir.find_last_of("\\/"));

					if (!contains(currentDir, "/") && !contains(currentDir, "\\"))	// the file path is just current file name,															   
					{																// so just make the string empty
						currentDir = "";
					}

					// append the requested file name, so we can load the included file
					currentDir += "./" + inc;

					std::shared_ptr<LoadedText> shaderc = assetMgr->loadAs<LoadedText>(currentDir.c_str());
					shaderCode = shaderc->getText();
				}

				lines.push_back(shaderCode);
			}
			else
			{
				lines.push_back(line);
			}
		}

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			finalString += lines[i];
			finalString += "\n";
		}

		std::shared_ptr<ILoadableObject> loadedText(new LoadedText(finalString));
		return loadedText;
	}
}