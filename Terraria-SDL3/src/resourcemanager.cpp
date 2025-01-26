#include "resourcemanager.h"

#include "SDL3/SDL_image.h"

#include <iostream>

namespace Terraria
{
	ResourceManager& ResourceManager::Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	SDL_Texture* ResourceManager::LoadTexture(const char* name, const char* path, SDL_Renderer* renderer)
	{
		// Return the texture if already loaded
		if (m_TextureMap.find(name) != m_TextureMap.end())
		{
			return m_TextureMap[name];
		}

		std::string completePath(m_PathToTextures);
		completePath += path;
		m_TextureMap.insert({name, IMG_LoadTexture(renderer, completePath.c_str())});
		return m_TextureMap[name];
	}

	void ResourceManager::Deinit()
	{
		for (auto& row : m_TextureMap)
		{
			SDL_DestroyTexture(row.second);
		}
		m_TextureMap.clear();
	}
}