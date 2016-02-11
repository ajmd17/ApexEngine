#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

namespace apex
{
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

		static void clear();

		virtual void use();

		virtual void end();

		virtual void setFilter(TextureFilterMode min, TextureFilterMode mag);

		virtual void genMipmap();
	};
}
#endif