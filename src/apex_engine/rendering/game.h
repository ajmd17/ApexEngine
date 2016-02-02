#ifndef GAME_H
#define GAME_H

// Abstract game class. This is essentially your application
// Author: Andrew MacDonald

#include "../scene/scene.h"
#include "../rendering/rendermanager.h"
#include "../rendering/camera.h"
#include "../assets/assetmanager.h"

class Game
{
private:
	int width, height;
protected:
	Scene *scene;

	RenderManager *renderMgr;
	AssetManager *assetMgr;

	Camera *camera;
public:
	Game() 
	{
		scene = new Scene();

		renderMgr = new RenderManager();
		assetMgr = new AssetManager();
	}
    
    ~Game() 
	{
		delete assetMgr;
		delete renderMgr;
		delete scene;
	}

	void update()
	{
		if (this->camera != NULL)
		{
			this->camera->update();
		}

		this->scene->getRootNode()->update(this->renderMgr);
		this->logic();
	}

	void render()
	{
		if (this->renderMgr != NULL)
		{
			this->renderMgr->getEngine()->viewport(0, 0, this->getWidth(), this->getHeight());
			this->renderMgr->getEngine()->clear(true, true, false);
			this->renderMgr->render(*camera);
		}
		else
			throw std::runtime_error("RenderManager should not be null");
	}
    
    virtual void init() = 0;

    virtual void logic() = 0;

    virtual void exit() = 0;

	const int getWidth()
	{
		return width;
	}

	void setWidth(int width)
	{
		this->width = width;
	}

	const int getHeight()
	{
		return height;
	}

	void setHeight(int height)
	{
		this->height = height;
	}

	Scene *getScene()
	{
		return scene;
	}

	AssetManager *getAssetManager()
	{
		return assetMgr;
	}

	RenderManager *getRenderManager()
	{
		return renderMgr;
	}
};

#endif