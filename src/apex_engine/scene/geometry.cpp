#include "geometry.h"

#include "../rendering/camera.h"
#include "../rendering/rendermanager.h"

void Geometry::render(Camera &cam)
{
	if (this->shader != 0 && this->mesh != 0)
	{
		shader->use();
		shader->applyTransforms(this->getGlobalMatrix(), cam.getViewMatrix(), cam.getProjectionMatrix());
		shader->applyMaterial(this->material);
		
		this->mesh->render();

		shader->end();
	}
}

void Geometry::updateParents()
{
	Spatial::updateParents();
	
	if (renderMgr != NULL && this->isAttachedToRoot())
		this->renderMgr->addGeometry(this);
	else
		this->renderMgr->removeGeometry(this);
}

void Geometry::update(RenderManager *renderMgr)
{
	this->renderMgr = renderMgr;

	Spatial::update(renderMgr);
}