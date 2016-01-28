#include "geometry.h"
#include "../rendering/camera.h"

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