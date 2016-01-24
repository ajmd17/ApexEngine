#include "shader.h"
#include "environment.h"
#include "camera.h"
#include "mesh.h"
#include "rendermanager.h"
#include "constants.h"

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
	RenderManager::getRenderer()->bindShaderProgram(0);
}

Shader::~Shader()
{
	if (this->getProgramID() != 0)
		RenderManager::getRenderer()->deleteShaderProgram(*this);

	int arraySize = sizeof(m_shaderIDs) / sizeof(m_shaderIDs[0]);
	for (int i = 0; i < arraySize; i++)
	{
		if (m_shaderIDs[i] != 0)
			RenderManager::getRenderer()->deleteShader(m_shaderIDs[i]);
	}
	delete[] m_shaderIDs;
}

void Shader::create()
{
	this->id = RenderManager::getRenderer()->generateShaderProgram();
}

void Shader::use()
{
	RenderManager::getRenderer()->bindShaderProgram(this->id);
}

void Shader::end()
{
    RenderManager::getRenderer()->bindShaderProgram(0);
}

void Shader::addProgram(ShaderType type, string &code)
{
	RenderManager::getRenderer()->addShader(*this, code, type);
}

void Shader::compileShader()
{
	RenderManager::getRenderer()->compileShaderProgram(this->id);
}

void Shader::setDefaultValues()
{
	RenderManager::getRenderer()->setDepthClamp(true);
	RenderManager::getRenderer()->setFaceDirection(FaceDirection::Ccw);
}

void Shader::applyMaterial(Material &material)
{
	this->currentMaterial = material;

	bool outDepthTest;
	currentMaterial.getBool(Material::BOOL_DEPTHTEST, outDepthTest);
	RenderManager::getRenderer()->setDepthTest(outDepthTest);

	bool outDepthMask;
	currentMaterial.getBool(Material::BOOL_DEPTHMASK, outDepthMask);
	RenderManager::getRenderer()->setDepthMask(outDepthMask);

	bool cullEnabled;
	currentMaterial.getBool(Material::BOOL_CULLENABLED, cullEnabled);

	if (cullEnabled)
	{
		RenderManager::getRenderer()->setCullFace(true);

		int faceToCull;
		currentMaterial.getInt(Material::INT_FACETOCULL, faceToCull);

		if (faceToCull == 0)
			RenderManager::getRenderer()->setFaceToCull(Face::Back);
		else if (faceToCull == 1)
			RenderManager::getRenderer()->setFaceToCull(Face::Front);
	}
	else
		RenderManager::getRenderer()->setCullFace(false);

	float alphaDiscard;
	currentMaterial.getFloat(Material::FLOAT_ALPHADISCARD, alphaDiscard);
	this->setUniform(MATERIAL_ALPHADISCARD, alphaDiscard);

	RenderManager::getRenderer()->setCullFace(false);
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
	
void Shader::setUniform(string name, Matrix4f &mat)
{
	RenderManager::getRenderer()->setShaderUniform(this->id, name, mat.values);
}