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

		shader->update(cam, *mesh);
		
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

void Geometry::setBucket(RenderBucket bucket)
{
	if (bucket != this->bucket)
	{
		if (renderMgr != NULL && this->isAttachedToRoot())
		{
			this->renderMgr->removeGeometry(this);
			this->bucket = bucket;
			this->renderMgr->addGeometry(this);
		}
		else
			this->bucket = bucket;
	}
}

void Geometry::updateGlobalBoundingBox()
{
	if (mesh != NULL)
		MeshUtil::createMeshBoundingBox(*mesh, globalBoundingBox, getGlobalMatrix());
}

void Geometry::updateLocalBoundingBox()
{
	if (mesh != NULL)
		MeshUtil::createMeshBoundingBox(*mesh, localBoundingBox);
}

BoundingBox &Geometry::getGlobalBoundingBox()
{
	if (!globalBoundingBoxCreated)
	{
		updateGlobalBoundingBox();
		globalBoundingBoxCreated = true;
	}

	if (this->updateFlags & Spatial::updateGlobalBoundingBoxFlag)
	{
		updateGlobalBoundingBox();
		this->updateFlags &= ~Spatial::updateGlobalBoundingBoxFlag;
	}

	return globalBoundingBox;
}

BoundingBox &Geometry::getLocalBoundingBox()
{
	if (!localBoundingBoxCreated)
	{
		updateLocalBoundingBox();
		localBoundingBoxCreated = true;
	}

	if (this->updateFlags & Spatial::updateLocalBoundingBoxFlag)
	{
		updateLocalBoundingBox();
		this->updateFlags &= ~Spatial::updateLocalBoundingBoxFlag;
	}

	return localBoundingBox;
}