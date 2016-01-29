#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "environment.h"
#include "engine.h"

#include <vector>
using std::vector;

class Geometry;

class RenderManager
{
private:
	static IEngine *m_engine;

	vector<Geometry*> geometry;
public:
	RenderManager()
	{
	}

	static IEngine *getEngine() { return m_engine; }

	static void setEngine(IEngine *renderer) { m_engine = renderer; }

	void addGeometry(Geometry *geom);

	void removeGeometry(Geometry *geom);
};

#endif