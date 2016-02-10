#include "directionallight.h"

#include "../../util/strutil.h"

#include "../shader.h"

namespace apex
{
	DirectionalLight::DirectionalLight()
	{
		this->direction.set(1.0f);
		this->color.set(1.0f);
	}

	DirectionalLight::DirectionalLight(const Vector3f &dir)
	{
		this->direction.set(dir);
		this->color.set(1.0f);
	}

	DirectionalLight::DirectionalLight(const Vector3f &dir, const Vector4f &color)
	{
		this->direction.set(dir);
		this->color.set(color);
	}

	void DirectionalLight::bindLight(int index, Shader &shader)
	{
		tmpUniform0 = D_LIGHT_NAME + string("[") + to_str<int>(index) + string("].") + D_LIGHT_DIRECTION;
		tmpUniform1 = D_LIGHT_NAME + string("[") + to_str<int>(index) + string("].") + D_LIGHT_COLOR;
		
		shader.setUniform(tmpUniform0, direction);
		shader.setUniform(tmpUniform1, color);
	}
}