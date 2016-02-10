#ifndef POINTLIGHT_H
#define POINTLIGHT_H

// A light source that starts at any 3D point in space, has a color and a radius
// Author: Andrew MacDonald

#include "lightsource.h"

#include "../../math/vector3f.h"
#include "../../math/vector4f.h"

#include <cstring>
using std::string;

namespace apex
{
	const string P_LIGHT_NAME = "Env_PointLights", P_LIGHT_POSITION = "position", P_LIGHT_COLOR = "color", P_LIGHT_RADIUS = "radius";

	class PointLight : public LightSource
	{
	public:
	private:
		Vector3f position;
		float radius;

		string tmpUniform0, tmpUniform1, tmpUniform2;
	public:

		PointLight();

		PointLight(const Vector3f &position);

		PointLight(const Vector3f &position, float radius);

		PointLight(const Vector3f &position, const Vector4f &color, float radius);

		const Vector3f &getPosition()
		{
			return position;
		}

		void setPosition(const Vector3f &position)
		{
			this->position.set(position);
		}

		virtual void bindLight(int index, Shader &shader);
	};
}
#endif