// Abstract renderer class. Depending on the platform, the engine will use a specific renderer.

#ifndef RENDERER_H
#define RENDERER_H

#include <string>
using std::string;

#ifndef GAME_H
#include "game.h"
#define GAME_H
#endif

#ifndef TEXTURE_H
#include "texture.h"
#define TEXTURE_H
#endif

#ifndef LOADEDASSET_H
#include "..\assets\loadedasset.h"
#define LOADEDASSET_H
#endif

#include "shader_enums.h"

#ifndef CAMERA_H
#include "camera.h"
#define CAMERA_H
#endif

class Mesh;

class Renderer
{
public:
	enum Face { Back, Front };
	enum FaceDirection { Cw, Ccw };
	enum BlendMode { AlphaBlend, Opaque };
	enum AudioPlayState { Playing, Paused, Stopped };

	Renderer() { }
	~Renderer() { }

	/* Rendering stuff */
	virtual void createContext(Game *game, int width, int height) = NULL;
	virtual void viewport(int x, int y, int width, int height) = NULL;
    virtual void clear(bool clearColor, bool clearDepth, bool clearStencil) = NULL;
	virtual void clearColor(float r, float g, float b, float a) = NULL;
    void drawVertex(float x, float y);
    void drawVertex(float x, float y, float z);
    void drawLine(Camera cam, float x1, float y1, float z1, float x2, float y2, float z2);
    void drawTriangle(Camera cam, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	/* End rendering stuff */

	/* Mesh stuff */
	virtual void createMesh(Mesh &mesh) = NULL;
	virtual void uploadMesh(Mesh &mesh) = NULL;
	virtual void deleteMesh(Mesh &mesh) = NULL;
	virtual void renderMesh(Mesh &mesh) = NULL;
	/* End mesh stuff */

	/* Texture stuff */
	void loadTexture2D(LoadedAsset asset);
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
	virtual int generateShaderProgram() = NULL;
    virtual void bindShaderProgram(int id) = NULL;
    virtual void compileShaderProgram(int id) = NULL;
    virtual void addShader(int id, string code, ShaderType type) = NULL;
    virtual void setShaderUniform(int id, string name, int i) = NULL;
    virtual void setShaderUniform(int id, string name, float f) = NULL;
    virtual void setShaderUniform(int id, string name, float x, float y) = NULL;
    virtual void setShaderUniform(int id, string name, float x, float y, float z) = NULL;
    virtual void setShaderUniform(int id, string name, float x, float y, float z, float w) = NULL;
    virtual void setShaderUniform(int id, string name, float matrix[]) = NULL;
	/* End shader stuff */

	/* Framebuffer stuff */
	void genFramebuffers(int n, int *framebuffers);
    void setupFramebuffer(int framebufferID, int colorTextureID, int depthTextureID, int width, int height);
    void bindFramebuffer(int id);
	/* End framebuffer stuff */

	/* Enabling and disabling */
	void setDepthTest(bool depthTest);
    void setDepthMask(bool depthMask);
    void setDepthClamp(bool depthClamp);
    void setBlend(bool blend);
    void setBlendMode(BlendMode blendMode);
    void setCullFace(bool cullFace);
    void setFaceToCull(Face face);
    void setFaceDirection(FaceDirection faceDirection);
	/* End enabling and disabling */
};

#endif