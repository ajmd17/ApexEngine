#include "texture.h"
#include "rendermanager.h"

int Texture::genTexture()
{
	int res = RenderManager::getRenderer()->genTexture();
	return res;
}