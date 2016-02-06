#include "shaderlib.h"

namespace apex
{
	const std::string lighting =
		"float lambert(vec3 _n, vec3 _l)\n"
		"{\n"
		"	return dot(_n, _l);\n"
		"}\n";

	std::unordered_map<std::string, std::string> ShaderLib::strMap;

	void ShaderLib::init()
	{
		strMap["lighting"] = lighting;
	}

	void ShaderLib::registerInclude(std::string name, std::string code)
	{
		strMap[name] = code;
	}

	const std::string ShaderLib::getCode(std::string name)
	{
		return strMap[name];
	}
}