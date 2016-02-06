#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "shader.h"

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
		static vector<shared_ptr<Shader>> shaders;

		template<typename ShaderClass>
		typename std::enable_if<std::is_base_of<Shader, ShaderClass>::value, shared_ptr<Shader>>::type
			static getShader(ShaderProperties properties)
		{
			// TODO: Iterate through current shaders and find ones with same class and properties before adding a new one
			shared_ptr<Shader> shaderPtr(new ShaderClass(properties));

			shaders.push_back(shaderPtr);
			return shaders.back();
		}
	};
}
#endif