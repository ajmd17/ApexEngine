#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "shader.h"
#include "shader_util.h"

#include "../util/logutil.h"

#include <type_traits>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

namespace apex
{
	class ShaderManager
	{
	public:
		static vector<std::pair<shared_ptr<Shader>, ShaderProperties>> shaders;

		template<typename ShaderClass>
		typename std::enable_if<std::is_base_of<Shader, ShaderClass>::value, shared_ptr<Shader>>::type
			static getShader(ShaderProperties properties)
		{

			for (int i = 0; i < shaders.size(); i++)
			{
				if (dynamic_cast<ShaderClass*>(shaders[i].first.get()) != 0)
				{
					if (ShaderUtil::compareShaderProperties(shaders[i].second, properties) &&
                        ShaderUtil::compareShaderProperties(properties, shaders[i].second))
					{
                        return shaders[i].first;
					}
				}
			}

			shared_ptr<Shader> shaderPtr(new ShaderClass(properties));

			std::pair<shared_ptr<Shader>, ShaderProperties> p = std::make_pair(shaderPtr, properties);
			shaders.push_back(p);

			apex::engine_log << "# of shaders initalized: " << shaders.size() << "\n";

			return shaders.back().first;
		}
	};
}
#endif
