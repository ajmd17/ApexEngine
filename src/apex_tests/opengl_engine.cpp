#include "opengl_engine.h"
#include <rendering/constants.h>
#include <rendering/texture2d.h>
#include <rendering/game.h>

#include <input/inputmanager.h>

namespace apex
{
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

#if defined (__UNIX__) || defined (unix) || defined (__LINUX__) || defined (linux) || defined (LINUX)
#include <X11/Xlib.h>
#define LINUX
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

#include <util/logutil.h>

#ifdef USE_SFML

	int convertSFMLMouseCode(int btn)
	{
		switch (btn)
		{
		case sf::Mouse::Left:
			return apex::MouseButton::Left;
			break;
		case sf::Mouse::Right:
			return apex::MouseButton::Right;
			break;
		case sf::Mouse::Middle:
			return apex::MouseButton::Middle;
			break;

		default:
			return apex::MouseButton::UndefinedButton;
			break;
		}
	}

// todo: add more
	int convertSFMLKeyCode(int keyCode)
	{
		switch (keyCode)
		{
		case sf::Keyboard::A:
			return apex::A;
			break;
		case sf::Keyboard::B:
			return apex::B;
			break;
		case sf::Keyboard::C:
			return apex::C;
			break;
		case sf::Keyboard::D:
			return apex::D;
			break;
		case sf::Keyboard::E:
			return apex::E;
			break;
		case sf::Keyboard::F:
			return apex::F;
			break;
		case sf::Keyboard::G:
			return apex::G;
			break;
		case sf::Keyboard::H:
			return apex::H;
			break;
		case sf::Keyboard::I:
			return apex::I;
			break;
		case sf::Keyboard::J:
			return apex::J;
			break;
		case sf::Keyboard::K:
			return apex::K;
			break;
		case sf::Keyboard::L:
			return apex::L;
			break;
		case sf::Keyboard::M:
			return apex::M;
			break;
		case sf::Keyboard::N:
			return apex::N;
			break;
		case sf::Keyboard::O:
			return apex::O;
			break;
		case sf::Keyboard::P:
			return apex::P;
			break;
		case sf::Keyboard::Q:
			return apex::Q;
			break;
		case sf::Keyboard::R:
			return apex::R;
			break;
		case sf::Keyboard::S:
			return apex::S;
			break;
		case sf::Keyboard::T:
			return apex::T;
			break;
		case sf::Keyboard::U:
			return apex::U;
			break;
		case sf::Keyboard::V:
			return apex::V;
			break;
		case sf::Keyboard::W:
			return apex::W;
			break;
		case sf::Keyboard::X:
			return apex::X;
			break;
		case sf::Keyboard::Y:
			return apex::Y;
			break;
		case sf::Keyboard::Z:
			return apex::Z;
			break;
		case sf::Keyboard::Num0:
			return apex::Num0;
			break;
		case sf::Keyboard::Num1:
			return apex::Num1;
			break;
		case sf::Keyboard::Num2:
			return apex::Num2;
			break;
		case sf::Keyboard::Num3:
			return apex::Num3;
			break;
		case sf::Keyboard::Num4:
			return apex::Num4;
			break;
		case sf::Keyboard::Num5:
			return apex::Num5;
			break;
		case sf::Keyboard::Num6:
			return apex::Num6;
			break;
		case sf::Keyboard::Num7:
			return apex::Num7;
			break;
		case sf::Keyboard::Num8:
			return apex::Num8;
			break;
		case sf::Keyboard::Num9:
			return apex::Num9;
			break;
		case sf::Keyboard::LAlt:
			return apex::LeftAlt;
			break;
		case sf::Keyboard::LControl:
			return apex::LeftCtrl;
			break;
		case sf::Keyboard::LShift:
			return apex::LeftShift;
		case sf::Keyboard::RAlt:
			return apex::RightAlt;
			break;
		case sf::Keyboard::RControl:
			return apex::RightCtrl;
			break;
		case sf::Keyboard::RShift:
			return apex::RightShift;
		case sf::Keyboard::Right:
			return apex::RightArrow;
			break;
		case sf::Keyboard::Left:
			return apex::LeftArrow;
			break;
		case sf::Keyboard::Up:
			return apex::UpArrow;
			break;
		case sf::Keyboard::Down:
			return apex::DownArrow;
			break;
		case sf::Keyboard::BackSpace:
			return apex::Backspace;
			break;
		case sf::Keyboard::Return:
			return apex::Enter;
			break;
		case sf::Keyboard::Period:
			return apex::Period;
			break;
		case sf::Keyboard::Space:
			return apex::Space;
			break;


		default:
			return apex::UndefinedKey;
			break;
		}
	}

	void GLEngine::renderThread(WindowGamePair &pair)
	{
		sf::Window *window = pair.window;
		Game *game = pair.game;

		sf::Clock clock;

		window->setActive(true);

		if (game != NULL)
		{
			game->getInputManager()->setWidth(window->getSize().x);
			game->getInputManager()->setHeight(window->getSize().y);
		}

		if (game != NULL)
			game->init();

		while (window->isOpen())
		{
			globalMutex.lock();

			float dt = clock.restart().asSeconds();

			if (game != NULL)
			{
				if (game->getInputManager() != 0)
				{
					game->getInputManager()->_setWindowPos(window->getPosition().x, window->getPosition().y);
					game->getInputManager()->_setMousePos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
				}

				game->update(dt);
				game->render();
			}

			window->display();
			globalMutex.unlock();
		}

		window->setActive(false);
	}

	void GLEngine::createContext(Game *game, int width, int height)
	{
        #ifdef LINUX
        XInitThreads();
        #endif

		sf::Window window;
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.antialiasingLevel = 4;

		window.create(sf::VideoMode(width, height, 32), "Apex Engine", sf::Style::Default, settings);
		window.setVerticalSyncEnabled(true);
		window.setKeyRepeatEnabled(false);

		engine_log << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n\n";

		this->contextActive = true;

		// Mac OS X / iOS don't need glew.
#ifndef __APPLE__
		glewInit();
#endif
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);

		sf::Thread render_thread(std::bind(&GLEngine::renderThread, this, WindowGamePair(&window, game)));
		sf::Event event;

		window.setActive(false);

		render_thread.launch();

		while (window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				globalMutex.lock();
				if (game != NULL)
				{
					game->exit();
				}
				globalMutex.unlock();
			}
			else if (event.type == sf::Event::Resized)
			{
				if (game != NULL)
				{
					game->getInputManager()->setWidth(window.getSize().x);
					game->getInputManager()->setHeight(window.getSize().y);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (game != NULL)
				{
					int code = event.key.code;
					int codeConv = convertSFMLKeyCode(code);
					game->getInputManager()->keyDown(codeConv);
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (game != NULL)
				{
					int code = event.key.code;
					int codeConv = convertSFMLKeyCode(code);
					game->getInputManager()->keyUp(codeConv);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (game != NULL)
				{
					int code = event.mouseButton.button;
					int codeConv = convertSFMLMouseCode(code);
					game->getInputManager()->mouseButtonDown(codeConv);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (game != NULL)
				{
					int code = event.mouseButton.button;
					int codeConv = convertSFMLMouseCode(code);
					game->getInputManager()->mouseButtonReleased(codeConv);
				}
			}
		}
		render_thread.wait();
	}

	void GLEngine::setMousePosition(int x, int y)
	{
		sf::Mouse::setPosition(sf::Vector2i(x, y));
	}

#endif // USE_SFML

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
		outTex.setID(m_texture);

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

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int GLEngine::genTexture()
	{
		unsigned int res[1];
		glGenTextures(1, res);
		engine_log << "Generated texture with ID: " << res[0] << "\n";
		return res[0];
	}

	void GLEngine::deleteTexture(int id)
	{
		unsigned int res[1];
		res[0] = id;
		glDeleteTextures(1, res);
		engine_log << "Deleted texture with ID: " << res[0] << "\n";
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
			engine_log << "Log: \n " << log << "\n\n";
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
		case VertexShader:
			i_type = GL_VERTEX_SHADER;
			str_type = "Vertex Shader";
			break;
		case FragmentShader:
			i_type = GL_FRAGMENT_SHADER;
			str_type = "Fragment Shader";
			break;
#ifndef __APPLE__
#ifndef GL_ES
		case GeometryShader:
			i_type = GL_GEOMETRY_SHADER;
			str_type = "Geomsetry Shader";
			break;
		case TessEvalShader:
			i_type = GL_TESS_EVALUATION_SHADER;
			str_type = "Tessellation Evaluation Shader";
			break;
		case TessControlShader:
			i_type = GL_TESS_CONTROL_SHADER;
			str_type = "Tessellation Control Shader";
			break;
#endif
#endif
		default:
			throw std::runtime_error("Invalid shader type.");
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

			engine_log << "Shader compile error! Shader type: " << str_type << "\n";
			engine_log << "Compile log: \n" << log << "\n";

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
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

		for (size_t i = 0; i < mesh.getAttributes().getNumAttributes(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, mesh.getAttributes().getAttribute(i).getSize(), GL_FLOAT, false, mesh.getVertexSize() * sizeof(GL_FLOAT), (void*)mesh.getAttributes().getAttribute(i).getOffset());
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
		glDrawElements(GL_TRIANGLES, mesh.size, GL_UNSIGNED_INT, 0);

		for (size_t i = 0; i < mesh.getAttributes().getNumAttributes(); i++)
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
		glDepthMask((depthMask ? GL_TRUE : GL_FALSE));
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
		if (blendMode == AlphaBlended)
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
		case Back:
			glCullFace(GL_BACK);
		case Front:
			glCullFace(GL_FRONT);
		}
	}

	void GLEngine::setFaceDirection(FaceDirection faceDirection)
	{
		switch (faceDirection)
		{
		case Ccw:
			glFrontFace(GL_CCW);
		case Cw:
			glFrontFace(GL_CW);
		}
	}
}
