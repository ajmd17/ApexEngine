#include "texture2d.h"

void Texture2D::use()
{
	RenderManager::getRenderer()->bindTexture2D(this->getID());
}

void Texture2D::setFilter(TextureFilterMode min, TextureFilterMode mag)
{
	
}

void Texture2D::genMipmap()
{
	RenderManager::getRenderer()->generateMipmap2D();
}