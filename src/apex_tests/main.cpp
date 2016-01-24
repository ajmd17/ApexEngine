#include <iostream>
using namespace std;
#include "glrenderer.h"
#include <assets/assetmanager.h>
#include <math/apexmath.h>
#include <rendering/rendermanager.h>
#include <rendering/game.h>
#include <rendering/texture2d.h>
#include <rendering/shadermanager.h>
#include <scene/node.h>


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

class MyShader : public Shader
{
private:
public:
	static const string vscode, fscode;
	MyShader(ShaderProperties &properties) : Shader(properties, vscode, fscode)
	{
	}
};

const string MyShader::vscode = "attribute vec3 a_position;\nattribute vec2 a_texcoord0;\nuniform mat4 u_mat;\nvarying vec2 v_texCoord0;\nvoid main() {\ngl_Position =u_mat * vec4(a_position, 1.0);\nv_texCoord0 = vec2(a_texcoord0.x, -a_texcoord0.y);\n}";
const string MyShader::fscode = "uniform sampler2D u_texture;\nvarying vec2 v_texCoord0;\nvoid main() {\ngl_FragColor = texture2D(u_texture, v_texCoord0);\n}";

Mesh *mesh;
Shader *shader; 
lua_State *lua;
Matrix4f myMatrix;
Texture2D *mytex;


float rot;
void TestGame::init()
{
	AssetManager astMgr;
	mytex = astMgr.loadTexture("tex.png");

	this->renderManager.getRenderer()->clearColor(1, 0, 0, 1);


	Node *n = new Node("root");
	Node *n2 = new Node();

	n2->setLocalTranslation(Vector3f(4, 7, 1));
	n->setLocalTranslation(Vector3f(9, 9, 9));

	n->add(n2);
	n->update();

	cout << n->get<Node>(0)->getGlobalTranslation() << "\n";

	delete n;
	delete n2;


	
	rot = 0;

	mat = new Material();
	Vector4f col;
	mat->setTexture(Material::TEXTURE_DIFFUSE, *mytex);
	mat->getVector4f(Material::COLOR_DIFFUSE, col);


	vector<Vertex> myVerts;
	mesh = new Mesh();
	myVerts.push_back(Vertex(Vector3f(-1, 0, 3), Vector2f(0, 0)));
	myVerts.push_back(Vertex(Vector3f(0, 1, 3), Vector2f(0.5, 1)));
	myVerts.push_back(Vertex(Vector3f(1, 0, 3), Vector2f(1, 0)));
	mesh->setVertices(myVerts);

	shader = ShaderManager::getShader<MyShader>(ShaderProperties());
	
	// Test Lua
	lua = luaL_newstate();
	luaL_dofile(lua, "script.lua");
	luaL_openlibs(lua);


	// Note: we don't expose any of the functions from C++ that create new objects.
	// Users will have to create temporary values in scripts in order to achieve this.
	getGlobalNamespace(lua)
		.beginNamespace("Math")
			.beginClass <Matrix4f>("Matrix4f")
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
		

			.beginClass <Vector2f>("Vector2f")
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


			.beginClass <Vector3f>("Vector3f")
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

			.beginClass <Vector4f>("Vector4f")
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
		.endNamespace()
		.beginNamespace("Scene")
			.beginClass <Spatial>("Spatial")

			.addFunction("setName", &Spatial::setName)
			.addFunction("getName", &Spatial::getName)

			.addFunction("setLocalTranslation", &Spatial::setLocalTranslation)
			.addFunction("setLocalRotation", &Spatial::setLocalRotation)
			.addFunction("setLocalScale", &Spatial::setLocalScale)

			.addFunction("getLocalTranslation", &Spatial::getLocalTranslation)
			.addFunction("getLocalRotation", &Spatial::getLocalRotation)
			.addFunction("getLocalScale", &Spatial::getLocalScale)
			//.addFunction("getLocalBoundingBox", &Spatial::getLocalBoundingBox)

			.addFunction("getGlobalTranslation", &Spatial::getGlobalTranslation)
			.addFunction("getGlobalRotation", &Spatial::getGlobalRotation)
			.addFunction("getGlobalScale", &Spatial::getGlobalScale)
			//.addFunction("getGlobalMatrix", &Spatial::getGlobalMatrix)
			//.addFunction("getGlobalTransform", &Spatial::getGlobalTransform)
			//.addFunction("getGlobalBoundingBox", &Spatial::getGlobalBoundingBox)

			.addFunction("update", &Spatial::update)
			.addFunction("setUpdateNeeded", &Spatial::setUpdateNeeded)

			.addFunction("isAttachedToRoot", &Spatial::isAttachedToRoot)

			.endClass()

			.deriveClass <Node, Spatial>("Node")
			.addConstructor <void(*) (void)>()

			.addFunction("size", &Node::size)
			.addFunction("add", &Node::add)
			.addFunction("get", &Node::get)
			.addFunction("remove", &Node::remove)
			.addFunction("removeAt", &Node::removeAt)

			.endClass()

		.endNamespace();

	LuaRef lua_init = getGlobal(lua, "main");
	lua_init();
}

void TestGame::exit()
{
	delete mat;
	delete mytex;
	delete mesh;
	delete shader;
}

void TestGame::update()
{
	LuaRef lua_logic = getGlobal(lua, "logic");
	lua_logic();

	rot += 1;
	Matrix4f proj, tmp;
	MatrixUtil::setToRotation(myMatrix, *Quaternion().setFromAxis(Vector3f(0,1,0), rot));
	MatrixUtil::setToProjection(proj, 45, 512, 512, 0.5, 100.0);
	tmp.set(myMatrix);
	myMatrix.set(proj);
	myMatrix.multStore(tmp);
}

void TestGame::render()
{
	if (this->renderManager.getRenderer() != NULL) {
		this->renderManager.getRenderer()->clear(true, true, false);

		shader->use();

		mytex->activeTextureSlot(0);
		mytex->use();
		shader->setUniform("u_texture", 0);

		shader->setUniform("u_mat", myMatrix);

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

	delete pRenderer;
	delete game;

	return 0;
}