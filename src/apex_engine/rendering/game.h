// Abstract game class
#ifndef GAME_H
#define GAME_H

#include "environment.h"

class Game
{
private:
	Environment environment;
public:
    Game() {}
    
    virtual ~Game() {}
    
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void exit() = 0;

	Environment &getEnvironment()
	{
		return environment;
	}

	void setEnvironment(Environment &env)
	{
		this->environment = env;
	}
};

#endif