#ifndef GAME_H
#define GAME_H

// Abstract game class. This is essentially your application
// Author: Andrew MacDonald

#include "../scene/scene.h"
#include "../rendering/rendermanager.h"
#include "../rendering/camera.h"

class Game
{
private:
protected:
	Scene *scene;
	RenderManager *renderMgr;

	Camera *camera;
public:
	Game() 
	{
		scene = new Scene();
		renderMgr = new RenderManager();
	}
    
    ~Game() 
	{
		delete scene;
		delete renderMgr;
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
			this->renderMgr->getEngine()->clear(true, true, false);
			this->renderMgr->render(*camera);
		}
		else
			throw std::runtime_error("RenderManager should not be null");
	}
    
    virtual void init() = 0;

    virtual void logic() = 0;

    virtual void exit() = 0;

	Scene *getScene()
	{
		return scene;
	}
};

#endif