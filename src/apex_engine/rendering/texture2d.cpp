#include "texture2d.h"

void Texture2D::use()
{
	RenderManager::getEngine()->bindTexture2D(this->getID());
}

void Texture2D::setFilter(TextureFilterMode min, TextureFilterMode mag)
{
	
}

void Texture2D::genMipmap()
{
	RenderManager::getEngine()->generateMipmap2D();
}