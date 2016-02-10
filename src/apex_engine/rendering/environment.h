#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// The environment part of the scene. 
// Author: Andrew MacDonald

#include "light/lightsource.h"
#include "light/pointlight.h"
#include "light/directionallight.h"

#include <vector>
using std::vector;

namespace apex
{
	class Environment
	{
	private:
		DirectionalLight directionalLight;
		vector<PointLight> pointLights;
	public:
		Environment() {};

		~Environment() { pointLights.clear(); }

		const unsigned int getNumPointLights()
		{
			return pointLights.size();
		}

		void setDirectionalLight(DirectionalLight dl)
		{
			this->directionalLight = dl;
		}

		DirectionalLight &getDirectionalLight()
		{
			return directionalLight;
		}

		void addPointLight(PointLight pl)
		{
			pointLights.push_back(pl);
		}

		PointLight &getPointLight(int i)
		{
			return pointLights[i];
		}
	};
}
#endif