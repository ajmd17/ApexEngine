#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

// Abstract class for anything that may emit light in the scene
// Author: Andrew MacDonald

class Shader;

class LightSource
{
public:
	virtual void bindLight(int index, Shader &shader) = 0;
};

#endif