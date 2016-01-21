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

	virtual void init() = NULL;
	virtual void update() = NULL;
	virtual void render() = NULL;
	virtual void exit() = NULL;

	Environment getEnvironment()
	{
		return environment;
	}

	void setEnvironment(Environment &env)
	{
		this->environment = env;
	}
};

#endif