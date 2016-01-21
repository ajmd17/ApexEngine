#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "..\shader.h"

class LightSource
{
public:
	virtual void bindLight(int index, Shader &shader) = NULL;
};

#endif