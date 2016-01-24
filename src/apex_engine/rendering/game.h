// Abstract game class
#ifndef GAME_H
#define GAME_H

#include "../scene/scene.h"

class Game
{
private:
	Scene *scene;
	bool running;
public:
	Game() 
	{ 
		running = false; 
		scene = new Scene();
	}
    
    ~Game() 
	{
		delete scene;
	}
    
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void exit() = 0;

	void setRunning(bool running) 
	{ 
		this->running = running; 
	}

	bool isRunning() const
	{
		return running;
	}

	Scene *getScene()
	{
		return scene;
	}
};

#endif