#include "resourcemanager.h"

#include "SDL3/SDL_image.h"

#include <fstream>
#include <sstream>

static const char* TEXTURE_PACK_PATH = "../../../res/texture_packs/";

namespace Terraria
{
	ResourceManager& ResourceManager::Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	bool ResourceManager::LoadTexturePack(const std::string& name)
	{
		std::string texturePackRoot = TEXTURE_PACK_PATH + name + "/";
		std::string configPath = texturePackRoot + "config.txt";
		if (std::ifstream configFile = std::ifstream(configPath))
		{
			std::string rowData;
			while (std::getline(configFile, rowData))
			{
				std::istringstream sstream(rowData);
				std::string textureID;
				std::string textureName;
				sstream >> textureID;
				sstream >> textureName;
				m_IDToPathMap.insert({ textureID, texturePackRoot + textureName });
			}
			return true;
		}
		else
		{
			SDL_Log("Could not find config.txt file for texture pack %s", name.c_str());
			return false;
		}
	}

	SDL_Texture* ResourceManager::LoadTexture(const std::string& ID, SDL_Renderer* renderer)
	{
		// Return the texture if already loaded
		if (m_TextureMap.find(ID) != m_TextureMap.end())
		{
			return m_TextureMap[ID];
		}

		if (m_IDToPathMap.find(ID) != m_IDToPathMap.end())
		{
			m_TextureMap.insert({ ID, IMG_LoadTexture(renderer, m_IDToPathMap[ID].c_str())});
			return m_TextureMap[ID];
		}
		else
		{
			return nullptr;
		}
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