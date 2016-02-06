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

#include <assets/loadedtext.h>

#include "sharedptr_conv.h"
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <luabind/luabind.hpp>

//#include <LuaBridge.h>

//using namespace luabridge;


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

class testclass
{
public:
	testclass(const std::string& s) : m_string(s) {}
	void print_string() { std::cout << m_string << "\n"; }

private:
	std::string m_string;
};

const string MyShader::vscode = "#version 120\nattribute vec3 a_position;\nattribute vec2 a_texcoord0;\nattribute vec3 a_normal;\nuniform mat4 Apex_ModelMatrix;uniform mat4 Apex_ViewMatrix;uniform mat4 Apex_ProjectionMatrix;\nvarying vec2 v_texCoord0;\nvarying vec3 v_normal;\nvoid main() {\ngl_Position = Apex_ProjectionMatrix * Apex_ViewMatrix * Apex_ModelMatrix * vec4(a_position, 1.0);\nv_texCoord0 = vec2(a_texcoord0.x, -a_texcoord0.y);\nv_normal = a_normal;\n}";
const string MyShader::fscode = "#version 120\nuniform sampler2D u_texture;\nvarying vec2 v_texCoord0;\nvarying vec3 v_normal;\nvoid main() {\nfloat ndotl = dot(v_normal, vec3(1.0));\ngl_FragColor = vec4(v_normal, 1.0);\n}";

Geometry *mygeom;
Mesh *mesh;
Matrix4f myMatrix;


float rot;
void TestGame::init()
{
	RenderManager::getEngine()->clearColor(0.75, 0, 0, 1);
    
	//shared_ptr<LoadedText> sc = getAssetManager()->loadAs<LoadedText>("test_shader.fs");
//	engine_log << sc->getText() << "\n";
	
	std::shared_ptr<Texture2D> mytex = getAssetManager()->loadAs<Texture2D>("test.jpg");
	
	this->camera = new PerspectiveCamera(75, 1024, 1024, 1.0, 100.0);


	rot = 0;
	

	// Create a new lua state
	lua_State *myLuaState = luaL_newstate(); 
	luaL_openlibs(myLuaState);

	// Connect LuaBind to this lua state
	luabind::open(myLuaState);


	luabind::module(myLuaState)
	[
		luabind::class_<Matrix4f>("Matrix4f")

		.def(luabind::constructor<>())

		.property("m00", &Matrix4f::getM<0, 0>, &Matrix4f::setM<0, 0>)
		.property("m01", &Matrix4f::getM<0, 1>, &Matrix4f::setM<0, 1>)
		.property("m02", &Matrix4f::getM<0, 2>, &Matrix4f::setM<0, 2>)
		.property("m03", &Matrix4f::getM<0, 3>, &Matrix4f::setM<0, 3>)

		.property("m10", &Matrix4f::getM<1, 0>, &Matrix4f::setM<1, 0>)
		.property("m11", &Matrix4f::getM<1, 1>, &Matrix4f::setM<1, 1>)
		.property("m12", &Matrix4f::getM<1, 2>, &Matrix4f::setM<1, 2>)
		.property("m13", &Matrix4f::getM<1, 3>, &Matrix4f::setM<1, 3>)

		.property("m20", &Matrix4f::getM<2, 0>, &Matrix4f::setM<2, 0>)
		.property("m21", &Matrix4f::getM<2, 1>, &Matrix4f::setM<2, 1>)
		.property("m22", &Matrix4f::getM<2, 2>, &Matrix4f::setM<2, 2>)
		.property("m23", &Matrix4f::getM<2, 3>, &Matrix4f::setM<2, 3>)

		.property("m30", &Matrix4f::getM<3, 0>, &Matrix4f::setM<3, 0>)
		.property("m31", &Matrix4f::getM<3, 1>, &Matrix4f::setM<3, 1>)
		.property("m32", &Matrix4f::getM<3, 2>, &Matrix4f::setM<3, 2>)
		.property("m33", &Matrix4f::getM<3, 3>, &Matrix4f::setM<3, 3>)

		.def("setToIdentity", &Matrix4f::setToIdentity)
		.def("invert", &Matrix4f::invert)
		.def("transpose", &Matrix4f::transpose)
		.def("multiply", &Matrix4f::multiply)
		.def("scale", &Matrix4f::scale)

		,

		luabind::class_<Quaternion>("Quaternion")

		.def(luabind::constructor<>()) // don't let a user directly set the	
									   // values of a quaternion.
		.property("w", &Quaternion::getW)
		.property("x", &Quaternion::getX)
		.property("y", &Quaternion::getY)
		.property("z", &Quaternion::getZ)

		.def("new", &Quaternion::setToIdentity)
		.def("copy", (Quaternion &(Quaternion::*) (Quaternion &)) &Quaternion::set)

		.def("setFromAxis", &Quaternion::setFromAxis)
		.def("multiply", (Quaternion &(Quaternion::*) (Quaternion &)) &Quaternion::multiply)

		.def("getPitch", &Quaternion::getPitch)
		.def("getRoll", &Quaternion::getRoll)
		.def("getYaw", &Quaternion::getYaw)
		,

		luabind::class_<Vector3f>("Vector3f")

		.def(luabind::constructor<float, float, float>())

		.property("x", &Vector3f::getX, &Vector3f::setX)
		.property("y", &Vector3f::getY, &Vector3f::setY)
		.property("z", &Vector3f::getZ, &Vector3f::setZ)

		.def("new", (Vector3f &(Vector3f::*) (float, float, float)) &Vector3f::set)
		.def("set", (Vector3f &(Vector3f::*) (float, float, float)) &Vector3f::set)
		.def("copy", (Vector3f &(Vector3f::*) (Vector3f &)) &Vector3f::set)

		.def("add", &Vector3f::add)
		.def("subtract", &Vector3f::subtract)
		.def("multiply", &Vector3f::multiply)
		.def("divide", &Vector3f::divide)
		.def("scale", &Vector3f::scale)
		.def("transform", &Vector3f::transform)
		.def("distance", &Vector3f::distance)
		.def("distanceSqr", &Vector3f::distanceSqr)
		.def("normalize", &Vector3f::normalize)
		.def("dot", &Vector3f::dot)
		.def("cross", &Vector3f::cross)
		.def("length", &Vector3f::length)

		,

		luabind::class_<Spatial, std::shared_ptr<Spatial>>("Spatial")
		
		.def("getName", &Spatial::getName)
		.def("setName", &Spatial::setName)

		.def("getParent", &Spatial::getParent)
		
		.def("setLocalTranslation", &Spatial::setLocalTranslation)
		.def("setLocalScale", &Spatial::setLocalScale)
		.def("setLocalRotation", &Spatial::setLocalRotation)

		.def("getLocalTranslation", &Spatial::getLocalTranslation)
		.def("getLocalScale", &Spatial::getLocalScale)
		.def("getLocalRotation", &Spatial::getLocalRotation)

		.def("getGlobalTranslation", &Spatial::getGlobalTranslation)
		.def("getGlobalScale", &Spatial::getGlobalScale)
		.def("getGlobalRotation", &Spatial::getGlobalRotation)

		.def("setNeedsTransformUpdate", &Spatial::setNeedsTransformUpdate)
		.def("setNeedsParentUpdate", &Spatial::setNeedsParentUpdate)
		,

		luabind::class_<Node, Spatial, std::shared_ptr<Spatial>>("Node")
		
		.def(luabind::constructor<std::string>())

		.def("size", &Node::size)
		.def("add", &Node::add)
		.def("getAt", &Node::getAt<Spatial>)
		.def("getNodeAt", &Node::getAt<Node>)
		.def("getGeomAt", &Node::getAt<Geometry>)
		.def("getByName", &Node::getByName<Spatial>)
		.def("contains", &Node::contains)
		.def("remove", &Node::remove)
		.def("removeAt", &Node::removeAt)
	];


	// Define a lua function that we can call
	luaL_dostring(
		myLuaState,
		""
		"n = Node('parent')\n"
		"n2 = Node('child')\n"
		"n3 = Node('sub')\n"
		"n2:add(n3)\n"
		"n:add(n2)\n"
		"quat = Quaternion()\n"
		"vec0 = Vector3f(1.0, 2.0, 3.0)\n"
		"quat:setFromAxis(vec0, 90)\n"
		"print (vec0.x, vec0.y, vec0.z)\n"
		"print (quat.w, quat.x, quat.y, quat.z)\n"
		"print (\"size:\", n:size())\n"
		"print (\"bye, \", n:getAt(0):getName())\n"
		"n:removeAt(0);\n"
		"print (\"size:\", n:size())\n"
		"print (\"bye!\")\n"
		);

	lua_close(myLuaState);

	/*mygeom = new Geometry();
	mygeom->getMaterial().setTexture(Material::TEXTURE_DIFFUSE, mytex2.get());
	mygeom->setLocalTranslation(Vector3f(0, -0.5f, 5.0f));
	//this->scene->getRootNode()->add(mygeom);*/


	ShaderProperties props;
	shared_ptr<Shader> shaderPtr = ShaderManager::getShader<MyShader>(props);

	std::shared_ptr<Node> cube = getAssetManager()->loadAs<Node>("./data/models/cube.obj");
	cube->setLocalTranslation(Vector3f(0, -1, 2.5f));
	cube->setLocalScale(Vector3f(0.3f));
	cube->getAt<Geometry>(0)->setShader(shaderPtr);
	this->getScene()->getRootNode()->add(cube);


	std::shared_ptr<Node> loadedmodel = getAssetManager()->loadAs<Node>("./data/models/logo.obj");

	loadedmodel->setLocalTranslation(Vector3f(0, 1, 7));

    loadedmodel->getAt<Geometry>(0)->setShader(shaderPtr);
	loadedmodel->getAt<Geometry>(0)->getMaterial().setTexture(Material::TEXTURE_DIFFUSE, mytex);
    loadedmodel->getAt<Geometry>(0)->getMaterial().setBool(Material::BOOL_CULLENABLED, false);
	loadedmodel->getAt<Geometry>(1)->setShader(shaderPtr);
	this->getScene()->getRootNode()->add(loadedmodel);

	/*vector<Vertex> myVerts;
	mesh = new Mesh();
	myVerts.push_back(Vertex(Vector3f(-1, 0, 0), Vector2f(0, 0)));
	myVerts.push_back(Vertex(Vector3f(0, 1, 0), Vector2f(0.5, 1)));
	myVerts.push_back(Vertex(Vector3f(1, 0, 0), Vector2f(1, 0)));
	mesh->setVertices(myVerts);
	mygeom->setMesh(mesh);
	mygeom->setLocalTranslation(Vector3f(0, 0, 4));*/


	
	// Test Lua
	//lua = luaL_newstate();
	//luaL_dofile(lua, "script.lua");
	//luaL_openlibs(lua);


}

void TestGame::exit()
{
	delete camera;
	delete mesh;
}

void TestGame::logic()
{
	//LuaRef lua_logic = getGlobal(lua, "logic");
	//lua_logic();

	rot += 1;

	Quaternion &qr = scene->getRootNode()->getAt<Spatial>(1)->getLocalRotation();
	qr.setFromAxis(Vector3f(0, 1, 0), rot);
	scene->getRootNode()->getAt<Spatial>(1)->setNeedsTransformUpdate();

	Quaternion &qr1 = scene->getRootNode()->getAt<Spatial>(0)->getLocalRotation();
	qr1.setFromAxis(Vector3f(1, 0, 0), rot);
	scene->getRootNode()->getAt<Spatial>(0)->setNeedsTransformUpdate();
}

int main()
{
	IEngine *pEngine = new GLEngine();
	RenderManager::setEngine(pEngine);

	Game *game = new TestGame();

	pEngine->createContext(game, 800, 480);

	delete game;
	//delete pEngine;

	cout << "\nExited the engine test\n";
	system("pause");
	return 0;
}