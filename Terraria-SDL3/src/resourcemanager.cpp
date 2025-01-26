#include "resourcemanager.h"
#include "texture.h"

#include <iostream>

namespace Terraria
{
	ResourceManager& ResourceManager::Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	TexturePtr ResourceManager::LoadTexture(const char* name, const char* path, SDL_Renderer* renderer)
	{
		// Return the texture if already loaded
		if (m_TextureMap.find(name) != m_TextureMap.end())
			return m_TextureMap[name];

		std::string completePath(m_PathToTextures);
		completePath += path;
		m_TextureMap[name] = std::make_shared<Texture>(completePath.c_str(), renderer);
		return m_TextureMap[name];
	}
}