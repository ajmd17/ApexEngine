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
#include <rendering/cameras/fps_camera.h>
#include <input/inputmanager.h>
#include <assets/loadedtext.h>

#include <assets/exporters/a3dexporter.h>

#include "sharedptr_conv.h"
extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <luabind/luabind.hpp>

using namespace apex;

class TestGame : public Game
{
public:
	TestGame()
	{
	}
	void init();
	void logic(const float dt);
	void exit();
};

class MyShader : public Shader
{
private:
public:
	MyShader(ShaderProperties &properties)
	{
		shared_ptr<LoadedText> vsShader = AssetManager::getDefaultAssetManager()->loadAs<LoadedText>("./data/shaders/simple.vs.glsl");
		shared_ptr<LoadedText> fsShader = AssetManager::getDefaultAssetManager()->loadAs<LoadedText>("./data/shaders/simple.fs.glsl");

		this->createShader(properties, vsShader->getText(), fsShader->getText());
	}

	void update(Camera &cam, Mesh &mesh, Environment &env)
	{
		Shader::update(cam, mesh, env);

		shared_ptr<Texture> diff;
		bool hasDiffuse = false;
		if (hasDiffuse = currentMaterial->getTexture(Material::TEXTURE_DIFFUSE, diff))
		{
			Texture::activeTextureSlot(0);
			diff->use();
			this->setUniform("u_texture", 0);
		}
		else
		{
			Texture2D::clear();
		}
	}

};
Geometry *mygeom;
Mesh *mesh;
Matrix4f myMatrix;


float rot;
void TestGame::init()
{
	RenderManager::getEngine()->clearColor(97.0/255.0, 119.0/255.0, 171.0/255.0, 1);

	//
	//shared_ptr<LoadedText> sc = getAssetManager()->loadAs<LoadedText>("test_shader.fs");
	//engine_log << sc->getText() << "\n";

	//std::shared_ptr<Texture2D> mytex = getAssetManager()->loadAs<Texture2D>("test.jpg");

	this->camera = new FPSCamera(inputMgr, 45, 0.5f, 100.0f);


	rot = 0;
#pragma region LUA

	const bool enableLua = false;

	if (enableLua)
	{
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
			.def("copy", (Quaternion &(Quaternion::*) (const Quaternion &)) &Quaternion::set)

			.def("setFromAxis", &Quaternion::setFromAxis)
			.def("multiply", (Quaternion &(Quaternion::*) (const Quaternion &)) &Quaternion::multiply)

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
			.def("copy", (Vector3f &(Vector3f::*) (const Vector3f &)) &Vector3f::set)

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
	}
#pragma endregion LUA
	/*mygeom = new Geometry();
	mygeom->getMaterial().setTexture(Material::TEXTURE_DIFFUSE, mytex2.get());
	mygeom->setLocalTranslation(Vector3f(0, -0.5f, 5.0f));
	//this->scene->getRootNode()->add(mygeom);*/


	ShaderProperties props;
	props.setProperty(string("LIGHTING"), false);
	props.setProperty(string("TEST"), true);

	
	//shared_ptr<Shader> shaderPtr = ShaderManager::getShader<MyShader>(props);



	std::shared_ptr<Node> torus = getAssetManager()->loadAs<Node>("./data/models/torus.obj");
	torus->setLocalTranslation(Vector3f(0, 0, -3.5f));
	torus->getAt<Geometry>(0)->setShader<MyShader>();
	this->getScene()->getRootNode()->add(torus);
	
	std::shared_ptr<Node> sphere = getAssetManager()->loadAs<Node>("./data/models/test.obj");/*
	sphere->getAt<Geometry>(0)->setShader<MyShader>();
	this->getScene()->getRootNode()->add(sphere);

	std::shared_ptr<Node> cube = getAssetManager()->loadAs<Node>("./data/models/cube.obj");
	cube->setLocalTranslation(Vector3f(0, 0, 3.5f));
	cube->getAt<Geometry>(0)->setShader<MyShader>();
	this->getScene()->getRootNode()->add(cube);*/

	/*
	std::shared_ptr<Node> loadedmodel = getAssetManager()->loadAs<Node>("./data/models/NO.obj");

	loadedmodel->setLocalTranslation(Vector3f(0, 1, 7));
	loadedmodel->setLocalRotation(Quaternion().setFromAxis(Vector3f::UnitY, -90));

    loadedmodel->getAt<Geometry>(0)->setShader<MyShader>();
    loadedmodel->getAt<Geometry>(0)->getMaterial().setBool(Material::BOOL_CULLENABLED, false);
	loadedmodel->getAt<Geometry>(1)->setShader<MyShader>();
	loadedmodel->getAt<Geometry>(2)->setShader<MyShader>();
	loadedmodel->getAt<Geometry>(3)->setShader<MyShader>();
	loadedmodel->getAt<Geometry>(4)->setShader<MyShader>();
	loadedmodel->getAt<Geometry>(5)->setShader<MyShader>();
	this->getScene()->getRootNode()->add(loadedmodel);*/


	/*vector<Vertex> myVerts;
	mesh = new Mesh();
	myVerts.push_back(Vertex(Vector3f(-1, 0, 0), Vector2f(0, 0)));
	myVerts.push_back(Vertex(Vector3f(0, 1, 0), Vector2f(0.5, 1)));
	myVerts.push_back(Vertex(Vector3f(1, 0, 0), Vector2f(1, 0)));
	mesh->setVertices(myVerts);
	mygeom->setMesh(mesh);
	mygeom->setLocalTranslation(Vector3f(0, 0, 4));*/



	
	A3dExporter a3dExporter;
	a3dExporter.exportFile("test_saving.a3d", sphere.get());

	shared_ptr<Node> a3d = getAssetManager()->loadAs<Node>("test_saving.a3d");
	a3d->getAt<Node>(0)->getAt<Geometry>(0)->setShader<MyShader>();
	this->getScene()->getRootNode()->add(a3d);

}

void TestGame::exit()
{
	delete camera;
	delete mesh;
}

void TestGame::logic(const float dt)
{

	rot += dt*50.0f;
	/*Quaternion &qr = scene->getRootNode()->getAt<Spatial>(1)->getLocalRotation();
	qr.setFromAxis(Vector3f(1, 1, 0), rot*1.25f);
	scene->getRootNode()->getAt<Spatial>(1)->setNeedsTransformUpdate();*/

	/*Vector3f &scl = scene->getRootNode()->getAt<Node>(1)->getAt<Spatial>(1)->getLocalScale();
	scl.set(sin(rot*0.025f) * 2.0f + 1.0f,1,sin(rot*0.05f)+1.0f);
	

	Quaternion &qrot = scene->getRootNode()->getAt<Node>(1)->getAt<Spatial>(1)->getLocalRotation();
	qrot.setFromAxis(Vector3f(1, 0, 0), rot*1.25f);
	scene->getRootNode()->getAt<Node>(1)->getAt<Spatial>(1)->setNeedsTransformUpdate();
	*/


	//Quaternion &qr1 = scene->getRootNode()->getAt<Spatial>(0)->getLocalRotation();
	//qr1.setFromAxis(Vector3f(1, 1, 0), rot);
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
