#include "pointlight.h"

#include "../../util/strutil.h"

#include "../shader.h"

namespace apex
{
	const string PointLight::P_LIGHT_NAME = "Env_PointLights";
	const string PointLight::P_LIGHT_POSITION = "position";
	const string PointLight::P_LIGHT_COLOR = "color";
	const string PointLight::P_LIGHT_RADIUS = "radius";

	PointLight::PointLight()
	{
		this->position.set(0.0f);
		this->color.set(1.0f);
		this->radius = 35.0f;
	}

	PointLight::PointLight(const Vector3f &position)
	{
		this->position.set(position);
		this->color.set(1.0f);
		this->radius = 35.0f;
	}

	PointLight::PointLight(const Vector3f &position, float radius)
	{
		this->position.set(position);
		this->color.set(1.0f);
		this->radius = radius;
	}

	PointLight::PointLight(const Vector3f &position, const Vector4f &color, float radius)
	{
		this->position.set(position);
		this->color.set(color);
		this->radius = radius;
	}

	void PointLight::bindLight(int index, Shader &shader)
	{
		tmpUniform0 = P_LIGHT_NAME + string("[") + to_str<int>(index) + string("].") + P_LIGHT_POSITION;
		tmpUniform1 = P_LIGHT_NAME + string("[") + to_str<int>(index) + string("].") + P_LIGHT_COLOR;
		tmpUniform2 = P_LIGHT_NAME + string("[") + to_str<int>(index) + string("].") + P_LIGHT_RADIUS;
		
		shader.setUniform(tmpUniform0, position);
		shader.setUniform(tmpUniform1, color);
		shader.setUniform(tmpUniform2, radius);
	}
}