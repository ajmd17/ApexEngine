#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightsource.h"

#include "../../math/vector3f.h"
#include "../../math/vector4f.h"

class PointLight : public LightSource
{
public:
	PointLight();
	PointLight(Vector3f &position);
	PointLight(Vector3f &position, float radius);
	PointLight(Vector3f &position, Vector4f &color, float radius);

	virtual void bindLight(int index, Shader &shader);
};

#endif