#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "shader.h"

#include <type_traits>

#include <string>
using std::string;

#include <vector>
using std::vector;

class ShaderManager
{
public:
	static vector<Shader*> shaders;

	template<typename ShaderClass>
	typename std::enable_if<std::is_base_of<Shader, ShaderClass>::value, Shader*>::type
	static getShader(ShaderProperties properties)
	{
		// TODO: Iterate through current shaders and find ones with same class and properties before adding a new one
		
		shaders.push_back(new ShaderClass(properties));
		return shaders.back();
	}
};

#endif