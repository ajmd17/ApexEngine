#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

class Texture2D : public Texture
{
public:
	Texture2D() : Texture(0)
	{
	}

	Texture2D(int id) : Texture(id)
	{
	}

	~Texture2D()
	{

	}

	virtual void use();

	virtual void setFilter(TextureFilterMode min, TextureFilterMode mag);

	virtual void genMipmap();
};

#endif