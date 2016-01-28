#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../rendering/shader.h"
#include "../rendering/mesh.h"
#include "../rendering/material.h"
#include "spatial.h"

class Camera;

class Geometry : public Spatial
{
private:
	Shader *shader;
	Mesh *mesh;
	Material material;
public:
	Geometry() : Spatial() { this->mesh = 0;  }

	Geometry(char *name) : Spatial(name) { this->mesh = 0; }

	Geometry(Mesh *mesh) : Spatial() { this->mesh = mesh; }

	Geometry(Mesh *mesh, char *name) : Spatial(name) { this->mesh = mesh; }

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

	void render(Camera &cam);
};

#endif