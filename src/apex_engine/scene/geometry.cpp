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

void Geometry::setParent(Spatial *parent)
{
	Spatial::setParent(parent);

	if (this->getParent() != NULL)
		this->renderManager->addGeometry(this);
	else
		this->renderManager->removeGeometry(this);
}