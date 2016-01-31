#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "environment.h"
#include "engine.h"
#include "camera.h"
#include "enums.h"

#include <vector>
using std::vector;

#include <map>
using std::map;

class Geometry;

class RenderManager
{
private:
	static IEngine *m_engine;

	vector<Geometry*> bucket_opaque, 
					  bucket_transparent,
					  bucket_skybox,
					  bucket_particles;

	map<RenderBucket, vector<Geometry*>> buckets;

	static void addGeometry(vector<Geometry*> *bucket, Geometry *geom);

	static void removeGeometry(vector<Geometry*> *bucket, Geometry *geom);
public:
	RenderManager()
	{
		buckets[OpaqueBucket] = bucket_opaque;
		buckets[TransparentBucket] = bucket_transparent;
		buckets[SkyboxBucket] = bucket_skybox;
		buckets[ParticleBucket] = bucket_particles;
	}

	static IEngine *getEngine() { return m_engine; }

	static void setEngine(IEngine *renderer) { m_engine = renderer; }

	void addGeometry(Geometry *geom);

	void removeGeometry(Geometry *geom);

	void renderBucket(RenderBucket bucket, Camera &camera);

	void render(Camera &camera);
};

#endif