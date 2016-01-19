#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "light/lightsource.h"
#include "light/pointlight.h"

class Environment
{
public:
	void addPointLight(PointLight &pl);
};

#endif