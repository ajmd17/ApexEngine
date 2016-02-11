#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "spatial.h"

#include "../rendering/shader.h"
#include "../rendering/shader_util.h"
#include "../rendering/shadermanager.h"

#include "../rendering/mesh.h"
#include "../rendering/mesh_util.h"

#include "../rendering/material.h"

#include "../rendering/enums.h"

#include "../math/boundingbox.h"

#include <memory>
using std::shared_ptr;

namespace apex
{
	class RenderManager;

	class Camera;

	class Geometry : public Spatial
	{
	private:
		static int geom_count;

		RenderManager *renderMgr; // Contains a list of all geometry that can be rendered (attached to the root node)

		shared_ptr<Shader> shader, normalsShader, depthShader;
		shared_ptr<Mesh> mesh;

		ShaderProperties geomShaderProperties;

		Material material;

		RenderBucket bucket;

		BoundingBox localBoundingBox, globalBoundingBox;
		bool localBoundingBoxCreated, globalBoundingBoxCreated;

		Vector3f tmpMin, tmpMax;

		void updateGlobalBoundingBox();

		void updateLocalBoundingBox();
	public:
		Geometry();

		Geometry(string name);

		Geometry(shared_ptr<Mesh> mesh);

		Geometry(shared_ptr<Mesh> mesh, string name);

		~Geometry();

		void update(RenderManager *renderMgr, const float dt);

		void render(Camera &cam, Environment &env);

		void updateParents();

		Mesh *getMesh()
		{
			return this->mesh.get();
		}

		void setMesh(shared_ptr<Mesh> mesh)
		{
			this->mesh = mesh;
			this->setNeedsLocalBoundingBoxUpdate();
			this->setNeedsGlobalBoundingBoxUpdate();

			Spatial *par = this->getParent();

			while (par != 0)
			{

				par->setNeedsGlobalBoundingBoxUpdate();
				par->setNeedsLocalBoundingBoxUpdate();
				par = par->getParent();
				
			}
		}

		Material &getMaterial()
		{
			return material;
		}

		void setMaterial(Material &material)
		{
			this->material = material;
		}

		shared_ptr<Shader> getShader()
		{
			return shader;
		}

		void setShader(shared_ptr<Shader> shader)
		{
			this->shader = shader;
		}

		template <typename ShaderClass>
		typename std::enable_if<std::is_base_of<Shader, ShaderClass>::value>::type
			setShader(ShaderProperties &properties)
		{
			// Temporary set shader properties to DEFAULT, to make sure
			// the default code is compiled 
			properties.setProperty("DEFAULT", true);

			shared_ptr<Shader> shaderPtr =
				ShaderManager::getShader<ShaderClass>(properties);

			properties.setProperty("DEFAULT", false);

			this->setShader(shaderPtr);
		}

		template <typename ShaderClass>
		typename std::enable_if<std::is_base_of<Shader, ShaderClass>::value>::type
			setShader()
		{
			this->updateShaderProperties();

			this->setShader<ShaderClass>(this->geomShaderProperties);
		}

		shared_ptr<Shader> getNormalsShader()
		{
			return normalsShader;
		}

		void setNormalsShader(shared_ptr<Shader> shader)
		{
			this->normalsShader = shader;
		}

		shared_ptr<Shader> getDepthShader()
		{
			return depthShader;
		}

		void setDepthShader(shared_ptr<Shader> shader)
		{
			this->depthShader = shader;
		}

		RenderBucket getBucket()
		{
			return bucket;
		}

		void setBucket(RenderBucket bucket);

		void updateShaderProperties();

		void setNeedsTransformUpdate()
		{
			Spatial::setNeedsTransformUpdate();
		}

		BoundingBox &getGlobalBoundingBox();

		BoundingBox &getLocalBoundingBox();
	};
}
#endif