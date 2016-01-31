#include <iostream>
using namespace std;
#include "opengl_engine.h"
#include <assets/assetmanager.h>
#include <math/apexmath.h>

#include <rendering/vertex.h>
#include <rendering/rendermanager.h>
#include <rendering/game.h>
#include <rendering/texture2d.h>
#include <rendering/shadermanager.h>
#include <scene/node.h>
#include <scene/geometry.h>
#include <util/strutil.h>
#include <rendering/cameras/perspective_camera.h>


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
	TestGame()
	{
	}
	void init();
	void logic();
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

const string MyShader::vscode = "attribute vec3 a_position;\nattribute vec2 a_texcoord0;\nuniform mat4 Apex_ModelMatrix;uniform mat4 Apex_ViewMatrix;uniform mat4 Apex_ProjectionMatrix;\nvarying vec2 v_texCoord0;\nvoid main() {\ngl_Position = Apex_ProjectionMatrix * Apex_ViewMatrix * Apex_ModelMatrix * vec4(a_position, 1.0);\nv_texCoord0 = vec2(a_texcoord0.x, -a_texcoord0.y);\n}";
const string MyShader::fscode = "uniform sampler2D u_texture;\nvarying vec2 v_texCoord0;\nvoid main() {\ngl_FragColor = texture2D(u_texture, v_texCoord0);\n}";

Geometry *mygeom;
Mesh *mesh;
Shader *shader; 
lua_State *lua;
Matrix4f myMatrix;
std::shared_ptr<Texture2D> mytex;

AssetManager *astMgr;

float rot;
void TestGame::init()
{
	astMgr = new AssetManager();
	mytex = std::dynamic_pointer_cast<Texture2D>(astMgr->load("test.png"));
	RenderManager::getEngine()->clearColor(1, 1, 1, 1);
    
	
	std::shared_ptr<Texture2D> mytex2 = std::dynamic_pointer_cast<Texture2D>(astMgr->load("test.jpg"));
	
	this->camera = new PerspectiveCamera(45, 512, 512, 1.0, 100.0);

	rot = 0;
	

	mygeom = new Geometry();
	mygeom->getMaterial().setTexture(Material::TEXTURE_DIFFUSE, mytex2.get());
	mygeom->setLocalTranslation(Vector3f(0, -0.5f, 3.0f));
	this->scene->getRootNode()->add(mygeom);



	vector<Vertex> myVerts;
	mesh = new Mesh();
	myVerts.push_back(Vertex(Vector3f(-1, 0, 0), Vector2f(0, 0)));
	myVerts.push_back(Vertex(Vector3f(0, 1, 0), Vector2f(0.5, 1)));
	myVerts.push_back(Vertex(Vector3f(1, 0, 0), Vector2f(1, 0)));
	mesh->setVertices(myVerts);
	mygeom->setMesh(mesh);

    
    ShaderProperties props;
	shader = ShaderManager::getShader<MyShader> (props);
	mygeom->setShader(shader);



	
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
			.addFunction("copy", (Matrix4f &(Matrix4f::*) (Matrix4f &)) &Matrix4f::set)
			.addFunction("new", (Matrix4f &(Matrix4f::*) ()) &Matrix4f::setToIdentity)
			
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
			.addFunction("invert", &Matrix4f::invert)
			.addFunction("transpose", &Matrix4f::transpose)

			.endClass()
		

			.beginClass <Vector2f>("Vector2f")
			.addConstructor <void(*) (void)>()

			.addProperty("x", &Vector2f::getX, &Vector2f::setX)
			.addProperty("y", &Vector2f::getY, &Vector2f::setY)

			// constructor things
			.addFunction("copy", (Vector2f &(Vector2f::*) (Vector2f &)) &Vector2f::set)
			.addFunction("new", (Vector2f &(Vector2f::*) (float, float)) &Vector2f::set)
			.addFunction("set", (Vector2f &(Vector2f::*) (float, float)) &Vector2f::set)

			// standard vector functions
			.addFunction("add", &Vector2f::add)
			.addFunction("subtract", &Vector2f::subtract)
			.addFunction("multiply", &Vector2f::multiply)
			.addFunction("scale", &Vector2f::scale)
			.addFunction("divide", &Vector2f::divide)
			.addFunction("normalize", &Vector2f::normalize)
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
			.addFunction("copy", (Vector3f &(Vector3f::*) (Vector3f &)) &Vector3f::set)
			.addFunction("new", (Vector3f &(Vector3f::*) (float, float, float)) &Vector3f::set)
			.addFunction("set", (Vector3f &(Vector3f::*) (float, float, float)) &Vector3f::set)

			// standard vector functions
			.addFunction("add", &Vector3f::add)
			.addFunction("subtract", &Vector3f::subtract)
			.addFunction("multiply", &Vector3f::multiply)
			.addFunction("scale", &Vector3f::scale)
			.addFunction("transform", &Vector3f::transform)
			.addFunction("divide", &Vector3f::divide)
			.addFunction("cross", &Vector3f::cross)
			.addFunction("normalize", &Vector3f::normalize)
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
			.addFunction("copy", (Vector4f &(Vector4f::*) (Vector4f &)) &Vector4f::set)
			.addFunction("new", (Vector4f &(Vector4f::*) (float, float, float, float)) &Vector4f::set)
			.addFunction("set", (Vector4f &(Vector4f::*) (float, float, float, float)) &Vector4f::set)

			// standard vector functions
			.addFunction("add", &Vector4f::add)
			.addFunction("subtract", &Vector4f::subtract)
			.addFunction("multiple", &Vector4f::multiply)
			.addFunction("scale", &Vector4f::scale)
			.addFunction("transform", &Vector4f::transform)
			.addFunction("divide", &Vector4f::divide)
			.addFunction("normalize", &Vector4f::normalize)
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

			.addFunction("getParent", &Spatial::getParent)

			.addFunction("setLocalTranslation", &Spatial::setLocalTranslation)
			.addFunction("setLocalRotation", &Spatial::setLocalRotation)
			.addFunction("setLocalScale", &Spatial::setLocalScale)

			.addFunction("getLocalTranslation", &Spatial::getLocalTranslation)
			.addFunction("getLocalRotation", &Spatial::getLocalRotation)
			.addFunction("getLocalScale", &Spatial::getLocalScale)

			.addFunction("getGlobalTranslation", &Spatial::getGlobalTranslation)
			.addFunction("getGlobalRotation", &Spatial::getGlobalRotation)
			.addFunction("getGlobalScale", &Spatial::getGlobalScale)

			//.addFunction("update", &Spatial::update(&renderManager))
			.addFunction("setNeedsTransformUpdate", &Spatial::setNeedsTransformUpdate)
			.addFunction("setNeedsParentUpdate", &Spatial::setNeedsParentUpdate)

			.addFunction("isAttachedToRoot", &Spatial::isAttachedToRoot)

			.endClass()

			.deriveClass <Node, Spatial>("Node")
			.addConstructor <void(*) (void)>()

			.addFunction("size", &Node::size)
			.addFunction("add", &Node::add)
			.addFunction("getAt", &Node::getAt<Spatial>)
			.addFunction("getByName", &Node::getByName<Spatial>)
			.addFunction("contains", &Node::contains)
			.addFunction("remove", &Node::remove)
			.addFunction("removeAt", &Node::removeAt)

			.endClass()

		.endNamespace();

	LuaRef lua_init = getGlobal(lua, "main");
	lua_init();
}

void TestGame::exit()
{
	delete camera;
	delete mygeom;
	delete mesh;
	delete shader;
}

void TestGame::logic()
{
	LuaRef lua_logic = getGlobal(lua, "logic");
	lua_logic();
	
	rot += 1;
	mygeom->setLocalRotation(Quaternion().setFromAxis(Vector3f(0, 1, 0), rot));


	Texture *texPtr;
	if (mygeom->getMaterial().getTexture(Material::TEXTURE_DIFFUSE, texPtr))
	{
		texPtr->use();
	}


	if (rot > 100 && this->scene->getRootNode()->size() > 0)
	{
		mygeom->setBucket(TransparentBucket);
	}
}

int main()
{
	IEngine *pEngine = new GLEngine();
	RenderManager::setEngine(pEngine);

	Game *game = new TestGame();

	pEngine->createContext(game, 300, 150);

	delete game;
	//delete pEngine;

	return 0;
}