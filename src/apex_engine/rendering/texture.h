#ifndef TEXTURE_H
#define TEXTURE_H

// This object can be loaded
#include "../assets/loadableobject.h"

#include "enums.h"
#include "rendermanager.h"

namespace apex
{
	class Texture : public ILoadableObject
	{
	protected:
		int id;
	public:
		Texture()
		{
			this->id = 0;
		}

		Texture(int id)
		{
			this->id = id;
		}

		virtual ~Texture()
		{
			if (id != 0 && RenderManager::getEngine() != NULL)
			{
				//RenderManager::getEngine()->deleteTexture(id);
			}
		}

		const int &getID()
		{
			return id;
		}

		void setID(int id)
		{
			this->id = id;
		}

		static int genTexture()
		{
			int res = RenderManager::getEngine()->genTexture();
			return res;
		}

		static void activeTextureSlot(int slot)
		{
			RenderManager::getEngine()->activeTextureSlot(slot);
		}

		virtual void use() = 0;

		virtual void setFilter(TextureFilterMode min, TextureFilterMode mag) = 0;

		virtual void genMipmap() = 0;
	};
}
#endif