#include "geometry.h"

#include "../rendering/camera.h"
#include "../rendering/rendermanager.h"

#include "../util/logutil.h"

#include <unordered_map>
using std::unordered_map;

#include "../rendering/texture.h"

namespace apex
{
	int Geometry::geom_count = 0;

	Geometry::Geometry() : Spatial()
	{
		this->renderMgr = 0;
		this->mesh = 0;
		this->shader = 0;
		this->bucket = OpaqueBucket;
		this->setName("geometry_" + to_str(geom_count++));
	}

	Geometry::Geometry(string name) : Spatial(name)
	{
		this->renderMgr = 0;
		this->mesh = 0;
		this->shader = 0;
		this->bucket = OpaqueBucket;
	}

	Geometry::Geometry(shared_ptr<Mesh> mesh) : Spatial()
	{
		this->renderMgr = 0;
		this->mesh = mesh;
		this->shader = 0;
		this->bucket = OpaqueBucket;
		this->setName("geometry_" + to_str(++geom_count));
	}

	Geometry::Geometry(shared_ptr<Mesh> mesh, string name) : Spatial(name)
	{
		this->renderMgr = 0;
		this->mesh = mesh;
		this->shader = 0;
		this->bucket = OpaqueBucket;
	}

	Geometry::~Geometry()
	{
		engine_log << "Deleting geometry: " << getName() << "\n";
	}

	void Geometry::render(Camera &cam, Environment &env)
	{
		if (this->shader != 0 && this->mesh != 0)
		{
			shader->use();
			shader->applyTransforms(this->getGlobalMatrix(), cam.getViewMatrix(), cam.getProjectionMatrix());
			shader->applyMaterial(this->material);

			shader->update(cam, *mesh, env);

			this->mesh->render();

			shader->end();
		}
	}

	void Geometry::updateParents()
	{
		Spatial::updateParents();
		if (renderMgr != 0)
		{
			if (this->isAttachedToRoot())
				this->renderMgr->addGeometry(this);
			else
				this->renderMgr->removeGeometry(this);
		}
	}

	void Geometry::update(RenderManager *renderMgr, const float dt)
	{
		this->renderMgr = renderMgr;

		Spatial::update(renderMgr, dt);
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
		tmpMin.set(localBoundingBox.getMin());
		tmpMax.set(localBoundingBox.getMax());
		tmpMin.transform(this->getGlobalMatrix());
		tmpMax.transform(this->getGlobalMatrix());
		globalBoundingBox.createBoundingBox(tmpMin, tmpMax);
	}

	void Geometry::updateLocalBoundingBox()
	{
		if (mesh != NULL)
			MeshUtil::createMeshBoundingBox(*mesh, localBoundingBox);
	}

	BoundingBox &Geometry::getGlobalBoundingBox()
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

	void Geometry::updateShaderProperties()
	{
		this->geomShaderProperties.values.clear();

		if (this->mesh != 0 && mesh->getSkeleton() != 0 && 
			this->mesh->getAttributes().hasAttribute(VertexAttributes::BONEINDICES) &&
			this->mesh->getAttributes().hasAttribute(VertexAttributes::BONEWEIGHTS))
		{
			geomShaderProperties.setProperty(string("SKINNING"), true);
		}

		for (std::unordered_map<std::string, bool>::iterator i = this->material.booleans.begin(); 
			i != this->material.booleans.end(); ++i)

		{ } // Don't worry about this for now at least

		for (std::unordered_map<std::string, std::shared_ptr<Texture>>::iterator i = this->material.textures.begin();
		i != this->material.textures.end(); ++i)

		{
			this->geomShaderProperties.setProperty(i->first, (i->second != 0));
		} // Only set textures as important things to include in the shader properties
	}
}
