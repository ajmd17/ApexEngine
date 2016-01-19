#include "pointlight.h"
#include "../shader.h"

PointLight::PointLight() 
{
	//PointLight(Vector3f(0, 0, 0));
}

PointLight::PointLight(Vector3f &position)
{
	//PointLight(position, 15.0f);
}

void PointLight::bindLight(int index, Shader &shader)
{
}