#include "shader.h"
#include "environment.h"
#include "camera.h"
#include "mesh.h"
#include "rendermanager.h"
#include "constants.h"

#include "../util/logutil.h"

namespace apex
{
	Shader::Shader(ShaderProperties properties, string vs_code, string fs_code)
	{
		// 2 shaders. Create the space to store their IDs.
		this->m_shaderCounter = 0;

		const int numShaders = 2; // vertex, fragment
		this->m_shaderIDs = new int[numShaders];

		this->properties = properties;
		this->create();

		string formatted_vs = ShaderUtil::formatShaderProperties(vs_code, properties);
		formatted_vs = ShaderUtil::formatShaderVersion(formatted_vs);
		this->addVertexProgram(formatted_vs);

		string formatted_fs = ShaderUtil::formatShaderProperties(fs_code, properties);
		formatted_fs = ShaderUtil::formatShaderVersion(formatted_fs);
		this->addFragmentProgram(formatted_fs);

		this->compileShader();
		RenderManager::getEngine()->bindShaderProgram(0);
	}

	Shader::~Shader()
	{
		engine_log << "Deleting shader with ID: " << getProgramID() << "\n";

		/*if (this->getProgramID() != 0)
			RenderManager::getEngine()->deleteShaderProgram(*this);

		const unsigned int arraySize = sizeof(m_shaderIDs) / sizeof(m_shaderIDs[0]);
		for (unsigned int i = 0; i < arraySize; i++)
		{
			if (m_shaderIDs[i] != 0)
				RenderManager::getEngine()->deleteShader(m_shaderIDs[i]);
		}*/ // causing an error
		delete[] m_shaderIDs;
	}

	void Shader::create()
	{
		this->id = RenderManager::getEngine()->generateShaderProgram();
	}

	void Shader::use()
	{
		RenderManager::getEngine()->bindShaderProgram(this->id);
	}

	void Shader::end()
	{
		RenderManager::getEngine()->bindShaderProgram(0);
	}

	void Shader::addProgram(ShaderType type, string &code)
	{
		RenderManager::getEngine()->addShader(*this, code, type);
	}

	void Shader::compileShader()
	{
		RenderManager::getEngine()->compileShaderProgram(this->id);
	}

	void Shader::setDefaultValues()
	{
		RenderManager::getEngine()->setDepthClamp(true);
		RenderManager::getEngine()->setFaceDirection(Ccw);
	}

	void Shader::applyMaterial(Material &material)
	{
		this->currentMaterial = &material;

		bool outDepthTest;
		currentMaterial->getBool(Material::BOOL_DEPTHTEST, outDepthTest);
		RenderManager::getEngine()->setDepthTest(outDepthTest);

		bool outDepthMask;
		currentMaterial->getBool(Material::BOOL_DEPTHMASK, outDepthMask);
		RenderManager::getEngine()->setDepthMask(outDepthMask);

		bool cullEnabled;
		currentMaterial->getBool(Material::BOOL_CULLENABLED, cullEnabled);

		if (cullEnabled)
		{
			RenderManager::getEngine()->setCullFace(true);

			int faceToCull;
			currentMaterial->getInt(Material::INT_FACETOCULL, faceToCull);

			if (faceToCull == 0)
				RenderManager::getEngine()->setFaceToCull(Back);
			else if (faceToCull == 1)
				RenderManager::getEngine()->setFaceToCull(Front);
		}
		else
			RenderManager::getEngine()->setCullFace(false);

		float alphaDiscard;
		currentMaterial->getFloat(Material::FLOAT_ALPHADISCARD, alphaDiscard);
		this->setUniform(MATERIAL_ALPHADISCARD, alphaDiscard);
	}

	void Shader::applyTransforms(Matrix4f &modelMatrix, Matrix4f &viewMatrix, Matrix4f &projectionMatrix)
	{
		this->modelMatrix = modelMatrix;
		this->viewMatrix = viewMatrix;
		this->projectionMatrix = projectionMatrix;
		this->normalMatrix.set(modelMatrix);
		normalMatrix.invert();
		normalMatrix.transpose();
	}

	void Shader::update(Camera &cam, Mesh &mesh)
	{
		this->setDefaultValues();
		this->setUniform(APEX_MODELMATRIX, modelMatrix);
		this->setUniform(APEX_VIEWMATRIX, viewMatrix);
		this->setUniform(APEX_PROJECTIONMATRIX, projectionMatrix);
		this->setUniform(APEX_NORMALMATRIX, normalMatrix);
		this->setUniform(APEX_CAMERAPOSITION, cam.getTranslation());
	}

	void Shader::setUniform(string name, int i)
	{
		RenderManager::getEngine()->setShaderUniform(this->id, name, i);
	}

	void Shader::setUniform(string name, float f)
	{
		RenderManager::getEngine()->setShaderUniform(this->id, name, f);
	}

	void Shader::setUniform(string name, float x, float y)
	{
		RenderManager::getEngine()->setShaderUniform(this->id, name, x, y);
	}

	void Shader::setUniform(string name, float x, float y, float z)
	{
		RenderManager::getEngine()->setShaderUniform(this->id, name, x, y, z);
	}

	void Shader::setUniform(string name, float x, float y, float z, float w)
	{
		RenderManager::getEngine()->setShaderUniform(this->id, name, x, y, z, w);
	}

	void Shader::setUniform(string name, Matrix4f &mat)
	{
		RenderManager::getEngine()->setShaderUniform(this->id, name, mat.get1DArray());
	}
}