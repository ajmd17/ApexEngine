#include "environment.h"
#include "camera.h"
#include "mesh.h"
#include "rendermanager.h"
#include "shader.h"

void Shader::create()
{
	this->id = RenderManager::getRenderer()->generateShaderProgram();
}

void Shader::use()
{
	RenderManager::getRenderer()->bindShaderProgram(this->id);
}

void Shader::addProgram(ShaderType type, string &code)
{
	RenderManager::getRenderer()->addShader(id, code, type);
}

void Shader::compileShader()
{
	RenderManager::getRenderer()->compileShaderProgram(this->id);
}

void Shader::setDefaultValues()
{
	RenderManager::getRenderer()->setDepthClamp(true);
	RenderManager::getRenderer()->setFaceDirection(Renderer::FaceDirection::Ccw);
}

void Shader::applyMaterial(Material &material)
{
	this->currentMaterial = material;

	bool outDepthTest;
	currentMaterial.getBool(Material::MATERIAL_DEPTHTEST, outDepthTest);
	RenderManager::getRenderer()->setDepthTest(outDepthTest);

	bool outDepthMask;
	currentMaterial.getBool(Material::MATERIAL_DEPTHMASK, outDepthMask);
	RenderManager::getRenderer()->setDepthMask(outDepthMask);

	bool cullEnabled;
	currentMaterial.getBool(Material::MATERIAL_CULLENABLED, cullEnabled);

	if (cullEnabled)
	{
		RenderManager::getRenderer()->setCullFace(true);

		int faceToCull;
		currentMaterial.getInt(Material::MATERIAL_FACETOCULL, faceToCull);

		if (faceToCull == 0)
			RenderManager::getRenderer()->setFaceToCull(Renderer::Face::Back);
		else if (faceToCull == 1)
			RenderManager::getRenderer()->setFaceToCull(Renderer::Face::Front);
	}
	else
		RenderManager::getRenderer()->setCullFace(false);

	float alphaDiscard;
	currentMaterial.getFloat(Material::MATERIAL_ALPHADISCARD, alphaDiscard);
	this->setUniform(MATERIAL_ALPHADISCARD, alphaDiscard);
}

void Shader::end()
{

}

void Shader::update(Environment &environment, Camera &cam, Mesh &mesh)
{
	this->setDefaultValues();
	this->setUniform(APEX_WORLDMATRIX, worldMatrix);
	this->setUniform(APEX_VIEWMATRIX, viewMatrix);
	this->setUniform(APEX_PROJECTIONMATRIX, projectionMatrix);
	this->setUniform(APEX_CAMERAPOSITION, cam.getTranslation());
}

void Shader::setUniform(string name, int i)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, i);
}

void Shader::setUniform(string name, float f)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, f);
}

void Shader::setUniform(string name, float x, float y)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, x, y);
}

void Shader::setUniform(string name, float x, float y, float z)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, x, y, z);
}

void Shader::setUniform(string name, float x, float y, float z, float w)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, x, y, z, w);
}
	
void Shader::setUniform(string name, Matrix4f mat)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, mat.values);
}