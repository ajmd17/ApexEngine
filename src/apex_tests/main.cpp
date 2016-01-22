#include <iostream>
using namespace std;
#include "glrenderer.h"
#include <math\apexmath.h>
#include <rendering\rendermanager.h>
#include <rendering\game.h>


extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}
#include <LuaBridge.h>

using namespace luabridge;


class TestGame : public Game
{
public:
	Material *mat;
	RenderManager renderManager;
	TestGame()
	{
	}
	void init();
	void update();
	void render();
	void exit();
};
Mesh *mesh;
Shader *shader; 
lua_State *lua;

void TestGame::init()
{

	this->renderManager.getRenderer()->clearColor(1, 0, 0, 1);
	Quaternion quat = Quaternion();
	quat.setFromAxis(Vector3f::UnitY, 30);
	


	Vector3f vec = Vector3f(5.0f, 2.0, -1.0);
	cout << "Vector before multiplying by a matrix: " << vec << "\n";

	Matrix4f myMatrix;
	//MatrixUtil::setToRotation(myMatrix, quat);
	MatrixUtil::setToTranslation(myMatrix, Vector3f(0, 10, 0));
	vec.transformStore(myMatrix);
	cout << "Vector after multiplying by a matrix: " << vec << "\n";

	mat = new Material();
	Vector4f col;
	mat->getVector4f(Material::COLOR_DIFFUSE, col);
	cout << "Material: " << col << "\n";
	mat->setVector4f(Material::COLOR_DIFFUSE, Vector4f(0.0));
	mat->getVector4f(Material::COLOR_DIFFUSE, col);
	cout << "Material: " << col << "\n";

	delete mat;

	vector<Vertex> myVerts;
	mesh = new Mesh();
	myVerts.push_back(Vertex(Vector3f(-1, 0, 0)));
	myVerts.push_back(Vertex(Vector3f(0, 1, 0)));
	myVerts.push_back(Vertex(Vector3f(1, 0, 0)));
	mesh->setVertices(myVerts);

	GLuint test = 0;
	glGenBuffers(1, &test);
	cout << test << "\n";

	shader = new Shader(ShaderProperties(), string("attribute vec3 a_position;\nvoid main() {\ngl_Position = vec4(a_position, 1.0);\n}"), string("void main() {\ngl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n}"));
	
	
	this->renderManager.getRenderer()->clearColor(1, 0, 0, 1);




	



	// Test Lua
	lua = luaL_newstate();
	luaL_dofile(lua, "script.lua");
	luaL_openlibs(lua);


	// Note: we don't expose any of the functions from C++ that create new objects.
	// Users will have to create temporary values in scripts in order to achieve this.
	getGlobalNamespace(lua)
		.beginNamespace("math")
			.beginClass <Matrix4f>("matrix4f")
			.addConstructor <void(*) (void)>()

			// constructor things
			.addFunction("copy", (Matrix4f *(Matrix4f::*) (Matrix4f &)) &Matrix4f::set)
			.addFunction("new", (Matrix4f *(Matrix4f::*) ()) &Matrix4f::setToIdentity)
			
			.addProperty("m00", &Matrix4f::getM <Matrix4f::M00>, &Matrix4f::setM <Matrix4f::M00>)
			.addProperty("m01", &Matrix4f::getM <Matrix4f::M01>, &Matrix4f::setM <Matrix4f::M01>)
			.addProperty("m02", &Matrix4f::getM <Matrix4f::M02>, &Matrix4f::setM <Matrix4f::M02>)
			.addProperty("m03", &Matrix4f::getM <Matrix4f::M03>, &Matrix4f::setM <Matrix4f::M03>)

			.addProperty("m10", &Matrix4f::getM <Matrix4f::M10>, &Matrix4f::setM <Matrix4f::M10>)
			.addProperty("m11", &Matrix4f::getM <Matrix4f::M11>, &Matrix4f::setM <Matrix4f::M11>)
			.addProperty("m12", &Matrix4f::getM <Matrix4f::M12>, &Matrix4f::setM <Matrix4f::M12>)
			.addProperty("m13", &Matrix4f::getM <Matrix4f::M13>, &Matrix4f::setM <Matrix4f::M13>)

			.addProperty("m20", &Matrix4f::getM <Matrix4f::M20>, &Matrix4f::setM <Matrix4f::M20>)
			.addProperty("m21", &Matrix4f::getM <Matrix4f::M21>, &Matrix4f::setM <Matrix4f::M21>)
			.addProperty("m22", &Matrix4f::getM <Matrix4f::M22>, &Matrix4f::setM <Matrix4f::M22>)
			.addProperty("m23", &Matrix4f::getM <Matrix4f::M23>, &Matrix4f::setM <Matrix4f::M23>)

			.addProperty("m30", &Matrix4f::getM <Matrix4f::M30>, &Matrix4f::setM <Matrix4f::M30>)
			.addProperty("m31", &Matrix4f::getM <Matrix4f::M31>, &Matrix4f::setM <Matrix4f::M31>)
			.addProperty("m32", &Matrix4f::getM <Matrix4f::M32>, &Matrix4f::setM <Matrix4f::M32>)
			.addProperty("m33", &Matrix4f::getM <Matrix4f::M33>, &Matrix4f::setM <Matrix4f::M33>)

			.addFunction("identity", &Matrix4f::setToIdentity)
			.addFunction("invert", &Matrix4f::invertStore)
			.addFunction("transpose", &Matrix4f::transposeStore)

			.endClass()
		

			.beginClass <Vector2f>("vector2f")
			.addConstructor <void(*) (void)>()

			.addProperty("x", &Vector2f::getX, &Vector2f::setX)
			.addProperty("y", &Vector2f::getY, &Vector2f::setY)

			// constructor things
			.addFunction("copy", (Vector2f *(Vector2f::*) (Vector2f &)) &Vector2f::set)
			.addFunction("new", (Vector2f *(Vector2f::*) (float, float)) &Vector2f::set)
			.addFunction("set", (Vector2f *(Vector2f::*) (float, float)) &Vector2f::set)

			// standard vector functions
			.addFunction("add", &Vector2f::addStore)
			.addFunction("sub", &Vector2f::subStore)
			.addFunction("mult", &Vector2f::multStore)
			.addFunction("scale", &Vector2f::scaleStore)
			.addFunction("divide", &Vector2f::divStore)
			.addFunction("normalize", &Vector2f::normalizeStore)
			.addFunction("dot", &Vector2f::dot)
			.addFunction("length", &Vector2f::length)
			.addFunction("distance", &Vector2f::distance)
			.addFunction("distanceSqr", &Vector2f::distanceSqr)
			.endClass()


			.beginClass <Vector3f>("vector3f")
			.addConstructor <void(*) (void)>()

			.addProperty("x", &Vector3f::getX, &Vector3f::setX)
			.addProperty("y", &Vector3f::getY, &Vector3f::setY)
			.addProperty("z", &Vector3f::getZ, &Vector3f::setZ)

			// constructor things
			.addFunction("copy", (Vector3f *(Vector3f::*) (Vector3f &)) &Vector3f::set)
			.addFunction("new", (Vector3f *(Vector3f::*) (float, float, float)) &Vector3f::set)
			.addFunction("set", (Vector3f *(Vector3f::*) (float, float, float)) &Vector3f::set)

			// standard vector functions
			.addFunction("add", &Vector3f::addStore)
			.addFunction("sub", &Vector3f::subStore)
			.addFunction("mult", &Vector3f::multStore)
			.addFunction("scale", &Vector3f::scaleStore)
			.addFunction("transform", &Vector3f::transformStore)
			.addFunction("divide", &Vector3f::divStore)
			.addFunction("cross", &Vector3f::crossStore)
			.addFunction("normalize", &Vector3f::normalizeStore)
			.addFunction("dot", &Vector3f::dot)
			.addFunction("length", &Vector3f::length)
			.addFunction("distance", &Vector3f::distance)
			.addFunction("distanceSqr", &Vector3f::distanceSqr)
			.endClass()

			.beginClass <Vector4f>("vector4f")
			.addConstructor <void(*) (void)>()

			.addProperty("x", &Vector4f::getX, &Vector4f::setX)
			.addProperty("y", &Vector4f::getY, &Vector4f::setY)
			.addProperty("z", &Vector4f::getZ, &Vector4f::setZ)
			.addProperty("w", &Vector4f::getW, &Vector4f::setW)

			// constructor things
			.addFunction("copy", (Vector4f *(Vector4f::*) (Vector4f &)) &Vector4f::set)
			.addFunction("new", (Vector4f *(Vector4f::*) (float, float, float, float)) &Vector4f::set)
			.addFunction("set", (Vector4f *(Vector4f::*) (float, float, float, float)) &Vector4f::set)

			// standard vector functions
			.addFunction("add", &Vector4f::addStore)
			.addFunction("sub", &Vector4f::subStore)
			.addFunction("mult", &Vector4f::multStore)
			.addFunction("scale", &Vector4f::scaleStore)
			.addFunction("transform", &Vector4f::transformStore)
			.addFunction("divide", &Vector4f::divStore)
			.addFunction("normalize", &Vector4f::normalizeStore)
			.addFunction("dot", &Vector4f::dot)
			.addFunction("length", &Vector4f::length)
			.addFunction("distance", &Vector4f::distance)
			.addFunction("distanceSqr", &Vector4f::distanceSqr)
			.endClass()
		.endNamespace();


	// Set constants:
		/*	setGlobal(lua, &Vector2f::UnitX, "vec2_x");
			setGlobal(lua, &Vector2f::UnitY, "vec2_y");
			setGlobal(lua, &Vector2f::One, "vec2_one");

			setGlobal(lua, &Vector3f::UnitX, "vec3_x");
			setGlobal(lua, &Vector3f::UnitY, "vec3_y");
			setGlobal(lua, &Vector3f::UnitZ, "vec3_z");*/
	

	Vector3f myvec(7, 8, 9);
	std::cout << myvec.x << "\n";
	setGlobal(lua, &myvec, "myvec");

	LuaRef lua_init = getGlobal(lua, "main");
	lua_init();



}

void TestGame::exit()
{
}

void TestGame::update()
{
	LuaRef lua_logic = getGlobal(lua, "logic");
	lua_logic();
}

void TestGame::render()
{
	if (this->renderManager.getRenderer() != NULL) {
		this->renderManager.getRenderer()->clear(true, true, false);

		shader->use();
		mesh->render();
		shader->end();
	}
}

int main()
{
	Renderer *pRenderer = new GLRenderer();
	RenderManager::setRenderer(pRenderer);
	Game *game = new TestGame();

	pRenderer->createContext(game, 300, 150);

	delete mesh;
	delete shader;
	delete pRenderer;
	delete game;

	return 0;
}