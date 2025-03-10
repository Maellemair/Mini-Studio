#include "Texture.h"

Texture::Texture(const char* path)
{
	if (!mTexture.loadFromFile(path))
	{
		std::cout << "Erreur de chargement de la texture" << std::endl;
		return;
	}
}
