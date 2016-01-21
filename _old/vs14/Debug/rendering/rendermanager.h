#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "environment.h"
#include "renderer.h"

class RenderManager
{
public:
	static Renderer *m_renderer;
	static Renderer *getRenderer() { return m_renderer; }
	static void setRenderer(Renderer *renderer) { m_renderer = renderer; }
};

Renderer *RenderManager::m_renderer = NULL;

#endif