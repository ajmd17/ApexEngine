#include "texture2d.h"

namespace apex
{
	void Texture2D::use()
	{
		RenderManager::getEngine()->bindTexture2D(this->getID());
	}

	void Texture2D::clear()
	{
		RenderManager::getEngine()->bindTexture2D(0);
	}

	void Texture2D::end()
	{
		Texture2D::clear();
	}

	void Texture2D::setFilter(TextureFilterMode min, TextureFilterMode mag)
	{

	}

	void Texture2D::genMipmap()
	{
		RenderManager::getEngine()->generateMipmap2D();
	}
}