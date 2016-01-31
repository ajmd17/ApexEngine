#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "spatial.h"

#include "../rendering/shader.h"
#include "../rendering/mesh.h"
#include "../rendering/mesh_util.h"
#include "../rendering/material.h"
#include "../rendering/enums.h"

#include "../math/boundingbox.h"

class RenderManager;

class Camera;

class Geometry : public Spatial
{
private:
	RenderManager *renderMgr; // Contains a list of all geometry that can be rendered (attached to the root node)
	Shader *shader;
	Mesh *mesh;

	Material material;
	RenderBucket bucket;

	BoundingBox localBoundingBox, globalBoundingBox;
	bool localBoundingBoxCreated, globalBoundingBoxCreated;

	void updateGlobalBoundingBox();

	void updateLocalBoundingBox();
public:
	Geometry() : Spatial() 
	{ 
		this->mesh = 0;
		this->bucket = OpaqueBucket;
	}

	Geometry(char *name) : Spatial(name) 
	{ 
		this->mesh = 0;
		this->bucket = OpaqueBucket;
	}

	Geometry(Mesh *mesh) : Spatial() 
	{ 
		this->mesh = mesh;
		this->bucket = OpaqueBucket;
	}

	Geometry(Mesh *mesh, char *name) : Spatial(name) 
	{ 
		this->mesh = mesh; 
		this->bucket = OpaqueBucket;
	}

	void update(RenderManager *renderMgr);

	void render(Camera &cam);

	void updateParents();

	Mesh *getMesh()
	{
		return this->mesh;
	}

	void setMesh(Mesh *mesh)
	{
		this->mesh = mesh;
	}

	Material &getMaterial() 
	{ 
		return material; 
	}

	void setMaterial(Material material)
	{
		this->material = material;
	}

	Shader *getShader()
	{
		return shader;
	}

	void setShader(Shader *shader)
	{
		this->shader = shader;
	}

	RenderBucket getBucket()
	{
		return bucket;
	}

	void setBucket(RenderBucket bucket);

	BoundingBox &getGlobalBoundingBox()
	{
		if (!globalBoundingBoxCreated)
		{
			updateGlobalBoundingBox();
			globalBoundingBoxCreated = true;
		}
		return globalBoundingBox;
	}

	BoundingBox &getLocalBoundingBox()
	{
		if (!localBoundingBoxCreated)
		{
			updateLocalBoundingBox();
			localBoundingBoxCreated = true;
		}
		return localBoundingBox;
	}
};

#endif