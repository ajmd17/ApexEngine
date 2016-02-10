#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "lightsource.h"
#include "../../math/vector3f.h"
#include "../../math/vector4f.h"

#include <cstring>
using std::string;

namespace apex
{
	const string D_LIGHT_NAME = "Env_DirectionalLight", D_LIGHT_DIRECTION = "direction", D_LIGHT_COLOR = "color";

	class DirectionalLight : public LightSource
	{
	public:
	private:
		Vector3f direction;

		string tmpUniform0, tmpUniform1;
	public:
		DirectionalLight();

		DirectionalLight(const Vector3f &dir);

		DirectionalLight(const Vector3f &dir, const Vector4f &color);

		const Vector3f &getDirection()
		{
			return direction;
		}

		void setDirection(const Vector3f &dir)
		{
			this->direction.set(dir);
		}

		virtual void bindLight(int index, Shader &shader);
	};
}
#endif