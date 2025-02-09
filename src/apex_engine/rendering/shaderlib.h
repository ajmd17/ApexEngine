#ifndef BASE_SHADER_LIB_H
#define BASE_SHADER_LIB_H

// the strings that will be included in the engine as default shaders.

#include <cstring>
#include <unordered_map>

// Contains code that can be #included in GLSL shaders

namespace apex
{
	class ShaderLib
	{
	private:
		

		static std::unordered_map<std::string, std::string> strMap;

		static std::unordered_map<std::string, std::string> initMap();
	public:

		static void registerInclude(std::string name, std::string code);

		static const std::string getCode(std::string name);
	};
}

#endif
