#ifndef POINTLIGHT_H
#define POINTLIGHT_H

// A light source that starts at any 3D point in space, has a color and a radius
// Author: Andrew MacDonald

#include "lightsource.h"

#include "../../math/vector3f.h"
#include "../../math/vector4f.h"

namespace apex
{
	class PointLight : public LightSource
	{
	public:
		PointLight();
		PointLight(Vector3f &position);
		PointLight(Vector3f &position, float radius);
		PointLight(Vector3f &position, Vector4f &color, float radius);

		virtual void bindLight(int index, Shader &shader);
	};
}
#endif