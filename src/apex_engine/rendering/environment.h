#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// The environment part of the scene. 
// Author: Andrew MacDonald

#include "light/lightsource.h"
#include "light/pointlight.h"

namespace apex
{
	class Environment
	{
	public:
		void addPointLight(PointLight &pl);
	};
}
#endif