#include "shaderlib.h"

#include "constants.h"

#include "light/pointlight.h"
#include "light/directionallight.h"
#include "light/ambientlight.h"

#include "../util/logutil.h"

namespace apex
{


	const std::string lighting =
		"float lambert(vec3 _n, vec3 _l)\n"
		"{\n"
		"	return dot(_n, _l);\n"
		"}\n";

	const std::string apex3d =
		// Main uniforms
		"uniform mat4 " + APEX_MODELMATRIX + ";\n"
		"uniform mat4 " + APEX_VIEWMATRIX + ";\n"
		"uniform mat4 " + APEX_PROJECTIONMATRIX + ";\n"
		"uniform mat4 " + APEX_NORMALMATRIX + ";\n"
		"uniform vec3 " + APEX_CAMERAPOSITION + ";\n"
		"uniform float " + APEX_ELAPSEDTIME + ";\n"
		// Environment
		"uniform vec4 " + ENV_FOGCOLOR + ";\n"
		"uniform float " + ENV_FOGSTART + ";\n"
		"uniform float " + ENV_FOGEND + ";\n"
		"uniform float " + ENV_FOGDENSITY + ";\n"
		"uniform int " + ENV_NUMPOINTLIGHTS + ";\n"
		"uniform int " + ENV_NUMSPOTLIGHTS + ";\n"

		// Lighting structs
		"struct PointLight\n"
		"{\n"
		"    vec3 " + PointLight::P_LIGHT_POSITION + ";\n"
		"    vec4 " + PointLight::P_LIGHT_COLOR + ";\n"
		"    float " + PointLight::P_LIGHT_RADIUS + ";\n"
		"};\n"

		"struct AmbientLight\n"
		"{\n"
		"    vec4 " + AmbientLight::A_LIGHT_COLOR + ";\n"
		"};\n"

		"struct DirectionalLight\n"
		"{\n"
		"    vec3 " + DirectionalLight::D_LIGHT_DIRECTION + ";\n"
		"    vec4 " + DirectionalLight::D_LIGHT_COLOR + ";\n"
		"};\n"

		"uniform DirectionalLight " + DirectionalLight::D_LIGHT_NAME + ";\n"
		"uniform PointLight " + PointLight::P_LIGHT_NAME + "[4];\n"
		"uniform AmbientLight " + AmbientLight::A_LIGHT_NAME + ";\n"

		;


	std::unordered_map<std::string, std::string> ShaderLib::initMap()
	{
		std::unordered_map<std::string, std::string> map;

		map[std::string("lighting")] = lighting;
		map[std::string("apex3d")] = apex3d;
		return map;
	}

	std::unordered_map<std::string, std::string> ShaderLib::strMap = ShaderLib::initMap();

	void ShaderLib::registerInclude(std::string name, std::string code)
	{
		strMap[name] = code;
	}

	const std::string ShaderLib::getCode(std::string name)
	{
		return strMap[name];
	}
}