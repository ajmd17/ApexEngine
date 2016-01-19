#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "environment.h"
#include "renderer.h"

class RenderManager
{
private:
	static Renderer *m_renderer;
public:
	static Renderer *getRenderer() { return m_renderer; }
	static void setRenderer(Renderer *renderer) { m_renderer = renderer; }
};

#endif