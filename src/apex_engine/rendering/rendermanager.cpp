#include "rendermanager.h"
#include "../scene/geometry.h"
#include "../util/logutil.h"

#include <algorithm>

namespace apex
{
	IEngine *RenderManager::m_engine = 0;

	void RenderManager::addGeometry(vector<Geometry*> *bucket, Geometry *geom)
	{
		if (std::find(bucket->begin(), bucket->end(), geom) != bucket->end())
		{
			engine_log << "Geometry '" << geom->getName() << "' already in render list.\n";
		}
		else
		{
			bucket->push_back(geom);
		}
	}

	void RenderManager::removeGeometry(vector<Geometry*> *bucket, Geometry *geom)
	{
		if (std::find(bucket->begin(), bucket->end(), geom) != bucket->end())
		{
			bucket->erase(std::find(bucket->begin(), bucket->end(), geom));
		}
		else {
			engine_log << "Geometry '" << geom->getName() << "' not in in render list.\n";
		}
	}

	void RenderManager::addGeometry(Geometry *geom)
	{
		RenderManager::addGeometry(&buckets[geom->getBucket()], geom);
	}

	void RenderManager::removeGeometry(Geometry *geom)
	{
		RenderManager::removeGeometry(&buckets[geom->getBucket()], geom);
	}

	void RenderManager::renderBucket(RenderBucket bucket, Camera &camera)
	{
		vector<Geometry*> geomList = buckets[bucket];
		if (geomList.size() > 0)
		{
			for (size_t i = 0; i < geomList.size(); i++)
			{
				geomList[i]->render(camera);
			}
		}
	}

	void RenderManager::render(Camera &camera)
	{
		getEngine()->viewport(0, 0, camera.getWidth(), camera.getHeight());
		
		this->renderBucket(OpaqueBucket, camera);
		this->renderBucket(TransparentBucket, camera);
		this->renderBucket(SkyboxBucket, camera);
		this->renderBucket(ParticleBucket, camera);
	}
}