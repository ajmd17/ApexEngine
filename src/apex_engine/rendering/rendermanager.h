#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "environment.h"
#include "engine.h"

class RenderManager
{
private:
	static IEngine *m_engine;
public:
	static IEngine *getEngine() { return m_engine; }
	static void setEngine(IEngine *renderer) { m_engine = renderer; }
};

#endif