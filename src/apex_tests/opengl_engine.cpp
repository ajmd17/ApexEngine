#include "opengl_engine.h"
#include <rendering/constants.h>
#include <rendering/texture2d.h>
#include <rendering/game.h>

#ifndef USE_SFML // SFML comes with its own image utilities, use this if we aren't using SFML
#ifndef STB_IMAGE_IMPLEMENTATION
// For loading textures.
#define STB_IMAGE_IMPLEMENTATION
#include <assets/util/stb_image.h>
#endif
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#ifndef __APPLE__
#ifndef GLEW_H
#include <GL/glew.h>
#define GLEW_H
#endif
#endif

#ifdef __ANDROID__
#define GL_ES
#include <GLES/gl.h>
#endif

#ifdef USE_SFML
void GLEngine::renderThread(WindowGamePair &pair)
{
	sf::RenderWindow *window = pair.window;
	Game *game = pair.game;

	window->setActive(true);

	game->init();
	game->setRunning(true);

	while (window->isOpen())
	{
		globalMutex.lock();

		if (game != NULL && game->isRunning())
		{
			game->update();
			game->render();
		}
		
		window->display();
		globalMutex.unlock();
        
	}

	window->setActive(false);
}
#endif

void GLEngine::createContext(Game *game, int width, int height)
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(width, height), "Apex Engine");
	window.setVerticalSyncEnabled(true);
    
    bool canCloseWindow = false;

	// Mac OS X / iOS don't need glew.
#ifndef __APPLE__
	glewInit();
#endif

	sf::Thread render_thread(std::bind(&GLEngine::renderThread, this, WindowGamePair(&window, game)));
	sf::Event event;

	window.setActive(false);

	render_thread.launch();
    
	while (window.waitEvent(event))
	{
		if (event.type == sf::Event::Closed)
        {
            
            globalMutex.lock();
            if (game != NULL)
            {
                game->exit();
                game->setRunning(false);
            }
            window.close();
            globalMutex.unlock();
		}
		else if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, window.getSize().x, window.getSize().y);
		}
	}
    
	render_thread.wait();
}

void GLEngine::viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void GLEngine::clear(bool clearColor, bool clearDepth, bool clearStencil)
{
	if (clearColor && clearDepth && clearStencil)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	else if (clearColor && clearDepth)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else if (clearDepth && clearStencil)
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	else if (clearColor && clearStencil)
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	else if (clearColor)
		glClear(GL_COLOR_BUFFER_BIT);
	else if (clearDepth)
		glClear(GL_DEPTH_BUFFER_BIT);
	else if (clearStencil)
		glClear(GL_STENCIL_BUFFER_BIT);
}

void GLEngine::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}


void GLEngine::loadTexture2D(AssetInfo &asset, Texture2D &outTex)
{
	int w;
	int h;
	// Load texture from file:
#ifndef USE_SFML
	int comp;
	unsigned char* image = stbi_load(asset.getFilePath(), &w, &h, &comp, STBI_rgb_alpha);

	if (image == nullptr)
		throw(std::string("Failed to load texture!"));
#endif
#ifdef USE_SFML
	sf::Image img_data;
	if (!img_data.loadFromFile(asset.getFilePath()))
		throw(std::string("Failed to load texture!"));
	w = img_data.getSize().x;
	h = img_data.getSize().y;
#endif
	// Create texture:

	unsigned int m_texture = Texture::genTexture();
	outTex = Texture2D(m_texture);

	outTex.use();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Upload data:

#ifndef USE_SFML
	if (comp == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	else if (comp == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);
#endif
#ifdef USE_SFML

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());
#endif
	outTex.genMipmap();
}

int GLEngine::genTexture()
{
	unsigned int res[1];
	glGenTextures(1, res);
	cout << "Generated texture with ID: " << res[0] << "\n";
	return res[0];
}

void GLEngine::deleteTexture(int id)
{
	unsigned int res[1];
	res[0] = id;
	glDeleteTextures(1, res);
	cout << "Deleted texture with ID: " << res[0] << "\n";
}

void GLEngine::bindTexture2D(int i)
{
	glBindTexture(GL_TEXTURE_2D, i);
}

void GLEngine::bindTexture3D(int i)
{
	glBindTexture(GL_TEXTURE_3D, i);
}

void GLEngine::generateMipmap2D()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GLEngine::activeTextureSlot(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
}

void GLEngine::bindCubemap(int i)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, i);
}

int GLEngine::generateShaderProgram()
{
	GLuint prog = glCreateProgram();
	return (int)prog;
}

void GLEngine::bindShaderProgram(int id)
{
	glUseProgram(id);
}

void GLEngine::compileShaderProgram(int id)
{
	// Bind all default vertex attributes
	glBindAttribLocation(id, 0, A_POSITION.c_str());
	glBindAttribLocation(id, 1, A_TEXCOORD0.c_str());
	glBindAttribLocation(id, 2, A_TEXCOORD1.c_str());
	glBindAttribLocation(id, 3, A_NORMAL.c_str());
	glBindAttribLocation(id, 4, A_TANGENT.c_str());
	glBindAttribLocation(id, 5, A_BITANGENT.c_str());
	glBindAttribLocation(id, 6, A_BONEWEIGHTS.c_str());
	glBindAttribLocation(id, 7, A_BONEINDICES.c_str());

	glLinkProgram(id);
	glValidateProgram(id);

	int linked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, (int*)&linked);
	if (linked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		char *log = new char[maxLength];
		glGetProgramInfoLog(id, maxLength, &maxLength, log);
		glDeleteProgram(id);
		cout << "Log: \n " << log << "\n\n";
		delete[] log;
	}
}

void GLEngine::deleteShaderProgram(Shader &shader)
{
	glDeleteProgram(shader.getProgramID());
}

void GLEngine::deleteShader(int &id)
{
	glDeleteShader(id);
}

void GLEngine::addShader(Shader &program, string code, ShaderType type)
{
	int i_type;
	string str_type = "Undefined";
	switch (type)
	{
	case ShaderType::VertexShader:
		i_type = GL_VERTEX_SHADER;
		str_type = "Vertex Shader";
		break;
	case ShaderType::FragmentShader:
		i_type = GL_FRAGMENT_SHADER;
		str_type = "Fragment Shader";
		break;
#ifndef __APPLE__
#ifndef GL_ES
	case ShaderType::GeometryShader:
		i_type = GL_GEOMETRY_SHADER;
		str_type = "Geomsetry Shader";
		break;
	case ShaderType::TessEvalShader:
		i_type = GL_TESS_EVALUATION_SHADER;
		str_type = "Tessellation Evaluation Shader";
		break;
	case ShaderType::TessControlShader:
		i_type = GL_TESS_CONTROL_SHADER;
		str_type = "Tessellation Control Shader";
		break;
#endif
#endif
    default:
        throw std::runtime_error ("Invalid shader type.");
	}

	int shader = glCreateShader(i_type);
	program.m_shaderIDs[program.m_shaderCounter++] = shader;

	const char *c_str = code.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);
	glAttachShader(program.getProgramID(), shader);

	int status = -1;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, NULL, log);

		cout << "Shader compile error! Shader type: " << str_type << "\n";
		cout << "Compile log: \n" << log << "\n";

		delete[] log;
	}
}

void GLEngine::setShaderUniform(int id, string name, int i)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform1i(loc, i);
}

void GLEngine::setShaderUniform(int id, string name, float f)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform1f(loc, f);
}

void GLEngine::setShaderUniform(int id, string name, float x, float y)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform2f(loc, x, y);
}

void GLEngine::setShaderUniform(int id, string name, float x, float y, float z)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform3f(loc, x, y, z);
}

void GLEngine::setShaderUniform(int id, string name, float x, float y, float z, float w)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform4f(loc, x, y, z, w);
}

void GLEngine::setShaderUniform(int id, string name, float matrix[])
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(loc, 1, true, matrix);
}

void GLEngine::createMesh(Mesh &mesh)
{
	glGenBuffers(1, &(mesh.vbo));
	glGenBuffers(1, &(mesh.ibo));
}

void GLEngine::uploadMesh(Mesh &mesh)
{
	mesh.size = mesh.indices.size();
	vector<float> vertexBuffer = MeshUtil::createFloatBuffer(mesh);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(float), &vertexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(int), &mesh.indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLEngine::deleteMesh(Mesh &mesh)
{
	glDeleteBuffers(1, &(mesh.vbo));
	glDeleteBuffers(1, &(mesh.ibo));
}

void GLEngine::renderMesh(Mesh &mesh)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	for (int i = 0; i < mesh.getAttributes().getNumAttributes(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, mesh.getAttributes().getAttribute(i).getSize(), GL_FLOAT, false, mesh.getVertexSize() * sizeof(GL_FLOAT), (void*)mesh.getAttributes().getAttribute(i).getOffset());
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
	glDrawElements(GL_TRIANGLES, mesh.size, GL_UNSIGNED_INT, 0);

	for (int i = 0; i < mesh.getAttributes().getNumAttributes(); i++)
	{
		glDisableVertexAttribArray(i);
	}

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLEngine::setDepthTest(bool depthTest)
{
	if (depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void GLEngine::setDepthMask(bool depthMask)
{
	glDepthMask(depthMask);
}

void GLEngine::setDepthClamp(bool depthClamp)
{
	if (depthClamp)
		glEnable(GL_DEPTH_CLAMP);
	else
		glDisable(GL_DEPTH_CLAMP);
}

void GLEngine::setBlend(bool blend)
{
	if (blend)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void GLEngine::setBlendMode(BlendMode blendMode)
{
	if (blendMode == BlendMode::AlphaBlend)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void GLEngine::setCullFace(bool cullFace)
{
	if (cullFace)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void GLEngine::setFaceToCull(Face face)
{
	switch (face)
	{
	case Face::Back:
		glCullFace(GL_BACK);
	case Face::Front:
		glCullFace(GL_FRONT);
	}
}

void GLEngine::setFaceDirection(FaceDirection faceDirection)
{
	switch (faceDirection)
	{
	case FaceDirection::Ccw:
		glFrontFace(GL_CCW);
	case FaceDirection::Cw:
		glFrontFace(GL_CW);
	}
}