#include "rendermanager.h"
#include "../scene/geometry.h"

#include <algorithm>
#include <iostream>

IEngine *RenderManager::m_engine = 0;

void RenderManager::addGeometry(Geometry *geom)
{
	if (std::find(geometry.begin(), geometry.end(), geom) != geometry.end()) 
	{
		std::cout << "Geometry '" << geom->getName() << "' already in render list.\n";
	}
	else 
	{
		this->geometry.push_back(geom);
	}
}

void RenderManager::removeGeometry(Geometry *geom)
{
	if (std::find(geometry.begin(), geometry.end(), geom) != geometry.end()) 
	{
		this->geometry.erase(std::find(geometry.begin(), geometry.end(), geom));
	}
	else {
		std::cout << "Geometry '" << geom->getName() << "' not in in render list.\n";
	}
}