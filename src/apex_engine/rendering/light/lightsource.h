#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

class Shader;

class LightSource
{
public:
	virtual void bindLight(int index, Shader &shader) = 0;
};

#endif