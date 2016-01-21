#include <iostream>
using namespace std;
#include "glrenderer.h"
#include <math/apexmath.h>
#include <rendering/rendermanager.h>
#include <rendering/game.h>
#include <rendering/material.h>
#include <rendering/texture2d.h>
#include <assets/assetmanager.h>

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

void TestGame::init()
{

	this->renderManager.getRenderer()->clearColor(1, 0, 0, 1);
	Quaternion quat;
	quat.setFromAxis(Vector3f::UnitY, 30);
	

	AssetManager am;
	am.loadModel("data/assets/hi.txt");

	Vector3f vec(5.0f, 2.0, -1.0);
	cout << "Vector before multiplying by a matrix: " << vec << "\n";

	Matrix4f myMatrix;
    Vector3f myvec(0, 10, 0);
	MatrixUtil::setToTranslation(myMatrix, myvec);
	vec.multStore(myMatrix);
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
    
    Vertex verts[3];
    Vector3f vecs[3];
    
    vecs[0] = Vector3f(-0.5f, 0, 0.2f);
    vecs[1] = Vector3f(0, 0.5f, 0.2f);
    vecs[2] = Vector3f(0.5f, 0, 0.2f);
    
    for (int i = 0; i < 3; i++)
    {
        verts[i] = Vertex(vecs[i]);
    }
    
	mesh = new Mesh();
	myVerts.push_back(verts[0]);
	myVerts.push_back(verts[1]);
	myVerts.push_back(verts[2]);
	mesh->setVertices(myVerts);


	mesh->getAttributes().setAttribute("a_position", 3);


    ShaderProperties props;
	shader = new Shader(props, string("#version 120\nattribute vec3 a_position;\nvoid main() {\ngl_Position = vec4(a_position, 1.0);\n}"),
											string("#version 120\nuniform vec4 u_color;\nvoid main() {\ngl_FragColor = u_color;\n}"));
	
	
	this->renderManager.getRenderer()->clearColor(1, 0, 0, 1);
}

void TestGame::exit()
{
}

void TestGame::update()
{
}

Vector4f color(0.0, 0.5, 1.0, 1.0);
string u_color = "u_color";

void TestGame::render()
{
	if (this->renderManager.getRenderer() != NULL) {
		this->renderManager.getRenderer()->clear(true, true, false);
        shader->use();
        shader->setUniform(u_color, color);
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