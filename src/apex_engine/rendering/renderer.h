// Abstract renderer class. Depending on the platform, the engine will use a specific renderer.

#ifndef RENDERER_H
#define RENDERER_H

#include <string>
using std::string;

#include "game.h"

#include "texture.h"

#include "../assets/loadedasset.h"

#include "enums.h"

#include "camera.h"
#include <iostream>
using std::cout;

class Mesh;

class Renderer
{
public:

    Renderer() {}
    virtual ~Renderer() {}

	/* Rendering stuff */
	virtual void createContext(Game *game, int width, int height) = 0;
	virtual void viewport(int x, int y, int width, int height) = 0;
	virtual void clear(bool clearColor, bool clearDepth, bool clearStencil) = 0;
	virtual void clearColor(float r, float g, float b, float a) = 0;
	void drawVertex(float x, float y);
	void drawVertex(float x, float y, float z);
	void drawLine(Camera &cam, float x1, float y1, float z1, float x2, float y2, float z2);
	void drawTriangle(Camera &cam, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	/* End rendering stuff */

	/* Mesh stuff */
	virtual void createMesh(Mesh &mesh) = 0;
	virtual void uploadMesh(Mesh &mesh) = 0;
	virtual void deleteMesh(Mesh &mesh) = 0;
	virtual void renderMesh(Mesh &mesh) = 0;
	/* End mesh stuff */

	/* Texture stuff */
	void loadTexture2D(LoadedAsset &asset);
	void loadCubemap(string filepaths[]);
	int genTexture();
	void bindTexture2D(int i);
	void bindTexture3D(int i);
	void bindCubemap(int i);
	void generateMipmap2D();
	void generateMipmapCubemap();
	void activeTextureSlot(int slot);
	/* End texture stuff */

	/* Shader stuff */
	virtual int generateShaderProgram() = 0;
	virtual void bindShaderProgram(int id) = 0;
	virtual void compileShaderProgram(int id) = 0;
	virtual void deleteShaderProgram(Shader &shader) = 0;
	virtual void deleteShader(int &id) = 0;
	virtual void addShader(Shader &program, string code, ShaderType type) = 0;
	virtual void setShaderUniform(int id, string name, int i) = 0;
	virtual void setShaderUniform(int id, string name, float f) = 0;
	virtual void setShaderUniform(int id, string name, float x, float y) = 0;
	virtual void setShaderUniform(int id, string name, float x, float y, float z) = 0;
	virtual void setShaderUniform(int id, string name, float x, float y, float z, float w) = 0;
	virtual void setShaderUniform(int id, string name, float matrix[]) = 0;
	/* End shader stuff */

	/* Framebuffer stuff */
	void genFramebuffers(int n, int *framebuffers);
	void setupFramebuffer(int framebufferID, int colorTextureID, int depthTextureID, int width, int height);
	void bindFramebuffer(int id);
	/* End framebuffer stuff */

	/* Enabling and disabling */
	virtual void setDepthTest(bool depthTest) = 0;
	virtual void setDepthMask(bool depthMask) = 0;
	virtual void setDepthClamp(bool depthClamp) = 0;
	virtual void setBlend(bool blend) = 0;
	virtual void setBlendMode(BlendMode blendMode) = 0;
	virtual void setCullFace(bool cullFace) = 0;
	virtual void setFaceToCull(Face face) = 0;
	virtual void setFaceDirection(FaceDirection faceDirection) = 0;
	/* End enabling and disabling */
};

#endif