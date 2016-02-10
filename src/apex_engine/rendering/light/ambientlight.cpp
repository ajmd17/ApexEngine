#include "ambientlight.h"

#include "../../util/strutil.h"

#include "../shader.h"

namespace apex
{
	const string AmbientLight::A_LIGHT_NAME = "Env_AmbientLight";
	const string AmbientLight::A_LIGHT_COLOR = "color";

	AmbientLight::AmbientLight()
	{
		this->color.set(0.1f, 0.1f, 0.1f, 1.0f);
	}

	AmbientLight::AmbientLight(const Vector4f &color)
	{
		this->color.set(color);
	}

	void AmbientLight::bindLight(int index, Shader &shader)
	{
		tmpUniform0 = A_LIGHT_NAME + to_str<int>(index) + A_LIGHT_COLOR;
		
		shader.setUniform(tmpUniform0, color);
	}
}