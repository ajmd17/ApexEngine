#ifndef GLENGINE_H
#define GLENGINE_H
#include <rendering/engine.h>

#include <rendering/mesh.h>
#include <rendering/mesh_util.h>
#include <rendering/shader.h>

#ifndef __ANDROID__
#define USE_SFML
#include <SFML/Graphics.hpp>
#endif
#ifdef USE_SFML

class WindowGamePair
{
public:
	sf::RenderWindow *window;
	Game *game;
    
	WindowGamePair(sf::RenderWindow *window, Game *game)
	{
		this->window = window;
		this->game = game;
	}
};

#endif

class GLEngine : public IEngine
{
private:
public:
    sf::Mutex globalMutex;
    
    void renderThread(WindowGamePair &pair);

	GLEngine() { this->contextActive = false; }
	~GLEngine() { this->contextActive = false; }

	virtual void createContext(Game *game, int width, int height);
	virtual void viewport(int x, int y, int width, int height);
    virtual void clear(bool clearColor, bool clearDepth, bool clearStencil);
	virtual void clearColor(float r, float g, float b, float a);

	virtual void loadTexture2D(AssetInfo &asset, Texture2D &outTex);
	virtual int genTexture();
	virtual void deleteTexture(int id);
	virtual void bindTexture2D(int i);
	virtual void bindTexture3D(int i);
	virtual void bindCubemap(int i);
	virtual void generateMipmap2D();
	virtual void activeTextureSlot(int slot);

	virtual int generateShaderProgram();
    virtual void bindShaderProgram(int id);
    virtual void compileShaderProgram(int id);
	virtual void deleteShaderProgram(Shader &shader);
	virtual void deleteShader(int &id);
    virtual void addShader(Shader &program, string code, ShaderType type);
    virtual void setShaderUniform(int id, string name, int i);
    virtual void setShaderUniform(int id, string name, float f);
    virtual void setShaderUniform(int id, string name, float x, float y);
    virtual void setShaderUniform(int id, string name, float x, float y, float z);
    virtual void setShaderUniform(int id, string name, float x, float y, float z, float w);
    virtual void setShaderUniform(int id, string name, float matrix[]);

	virtual void createMesh(Mesh &mesh);
	virtual void uploadMesh(Mesh &mesh);
	virtual void deleteMesh(Mesh &mesh);
	virtual void renderMesh(Mesh &mesh);

	virtual void setDepthTest(bool depthTest);
	virtual void setDepthMask(bool depthMask);
	virtual void setDepthClamp(bool depthClamp);
	virtual void setBlend(bool blend);
	virtual void setBlendMode(BlendMode blendMode);
	virtual void setCullFace(bool cullFace);
	virtual void setFaceToCull(Face face);
	virtual void setFaceDirection(FaceDirection faceDirection);
};

#endif