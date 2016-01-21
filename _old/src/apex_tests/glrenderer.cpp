#include "glrenderer.h"
#include <rendering/constants.h>

// For loading textures.
#define STB_IMAGE_IMPLEMENTATION
#include <assets/util/stb_image.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

void GLRenderer::renderThread(WindowGamePair &pair)
{
	sf::RenderWindow *window = pair.window;
	Game *game = pair.game;

	window->setActive(true);

	game->init();

	while (window->isOpen())
	{
		globalMutex.lock();

		if (game != NULL)
		{
			game->update();
			game->render();
		}

		/*glRotatef(0.1, 0, 1, 0);
		glColor3f(0, 1, 0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0.0, 0);
		glVertex3f(0.0,0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glEnd();*/


		window->display();
		globalMutex.unlock();
	}

	window->setActive(false);
}

void GLRenderer::createContext(Game *game, int width, int height)
{
#ifndef __APPLE__
	sf::RenderWindow window;
	window.create(sf::VideoMode(width, height), "Apex Engine");

	glewInit();

	sf::Thread render_thread(std::bind(&GLRenderer::renderThread, this, WindowGamePair(&window, game)));
	sf::Event event;

	window.setActive(false);

	render_thread.launch();
	while (window.waitEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			if (game != NULL)
				game->exit();
			window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, window.getSize().x, window.getSize().y);
		}
	}
	render_thread.wait();

#endif
#ifdef __APPLE__
	sf::RenderWindow window;
	window.create(sf::VideoMode(width, height), "Apex Engine");

	if (game != NULL)
		game->init();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				if (game != NULL)
					game->exit();
				window.close();
			}
		}
		this->viewport(0, 0, window.getSize().x, window.getSize().y);
		if (game != NULL)
		{
			game->update();
			game->render();
		}
        
        glRotatef(0.1, 0, 1, 0);
        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, 0.0, 0);
        glVertex3f(0.0,0.5, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glEnd();

		window.display();
	}
#endif
}

void GLRenderer::viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void GLRenderer::clear(bool clearColor, bool clearDepth, bool clearStencil)
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

void GLRenderer::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

int GLRenderer::genTexture()
{
	unsigned int res[1];
	glGenTextures(1, res);
	cout << "Generated texture with ID: " << res[0] << "\n";
	return res[0];
}

void GLRenderer::deleteTexture(int id)
{
	unsigned int res[1];
	res[0] = id;
	glDeleteTextures(1, res);
	cout << "Deleted texture with ID: " << res[0] << "\n";
}

void GLRenderer::bindTexture2D(int i)
{
	glBindTexture(GL_TEXTURE_2D, i);
}

void GLRenderer::bindTexture3D(int i)
{
	glBindTexture(GL_TEXTURE_3D, i);
}

void GLRenderer::bindCubemap(int i)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, i);
}

int GLRenderer::generateShaderProgram()
{
	GLuint prog = glCreateProgram();
	return (int)prog;
}

void GLRenderer::bindShaderProgram(int id)
{
	glUseProgram(id);
}

void GLRenderer::compileShaderProgram(int id)
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

void GLRenderer::deleteShaderProgram(Shader &shader)
{
	glDeleteProgram(shader.getProgramID());
}

void GLRenderer::deleteShader(int &id)
{
	glDeleteShader(id);
}

void GLRenderer::addShader(Shader &program, string code, ShaderType type)
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
	case ShaderType::GeometryShader:
		i_type = GL_GEOMETRY_SHADER;
		str_type = "Geometry Shader";
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

void GLRenderer::setShaderUniform(int id, string name, int i)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform1i(loc, i);
}

void GLRenderer::setShaderUniform(int id, string name, float f)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform1f(loc, f);
}

void GLRenderer::setShaderUniform(int id, string name, float x, float y)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform2f(loc, x, y);
}

void GLRenderer::setShaderUniform(int id, string name, float x, float y, float z)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform3f(loc, x, y, z);
}

void GLRenderer::setShaderUniform(int id, string name, float x, float y, float z, float w)
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniform4f(loc, x, y, z, w);
}

void GLRenderer::setShaderUniform(int id, string name, float matrix[])
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(loc, 1, true, matrix);
}

void GLRenderer::createMesh(Mesh &mesh)
{
	glGenBuffers(1, &(mesh.vbo));
	glGenBuffers(1, &(mesh.ibo));
}

void GLRenderer::uploadMesh(Mesh &mesh)
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

void GLRenderer::deleteMesh(Mesh &mesh)
{
	glDeleteBuffers(1, &(mesh.vbo));
	glDeleteBuffers(1, &(mesh.ibo));
}

void GLRenderer::renderMesh(Mesh &mesh)
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::setDepthTest(bool depthTest)
{
	if (depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void GLRenderer::setDepthMask(bool depthMask)
{
	glDepthMask(depthMask);
}

void GLRenderer::setDepthClamp(bool depthClamp)
{
	if (depthClamp)
		glEnable(GL_DEPTH_CLAMP);
	else
		glDisable(GL_DEPTH_CLAMP);
}

void GLRenderer::setBlend(bool blend)
{
	if (blend)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void GLRenderer::setBlendMode(BlendMode blendMode)
{
	if (blendMode == BlendMode::AlphaBlend)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void GLRenderer::setCullFace(bool cullFace)
{
	if (cullFace)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void GLRenderer::setFaceToCull(Face face)
{
	switch (face)
	{
	case Face::Back:
		glCullFace(GL_BACK);
	case Face::Front:
		glCullFace(GL_FRONT);
	}
}

void GLRenderer::setFaceDirection(FaceDirection faceDirection)
{
	switch (faceDirection)
	{
	case FaceDirection::Ccw:
		glFrontFace(GL_CCW);
	case FaceDirection::Cw:
		glFrontFace(GL_CW);
	}
}