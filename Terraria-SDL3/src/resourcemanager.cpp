#include "resourcemanager.h"

#include "SDL3/SDL_image.h"

#include <fstream>
#include <sstream>

static const char* TEXTURE_PACK_PATH = "../../../res/texture_packs/";

namespace Terraria
{
	static std::unordered_map<std::string, SDL_Texture*> textureMap; // Holds loaded texture objects
	static std::unordered_map<std::string, std::string> idToPathMap; // Holds ID/path pairs for finding unloaded textures

	bool Resource::LoadTexturePack(const std::string& name)
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
				idToPathMap.insert({ textureID, texturePackRoot + textureName });
			}
			return true;
		}
		else
		{
			SDL_Log("Could not find config.txt file for texture pack %s", name.c_str());
			return false;
		}
	}

	SDL_Texture* Resource::LoadTexture(const std::string& ID, SDL_Renderer* renderer)
	{
		// Return the texture if already loaded
		if (textureMap.find(ID) != textureMap.end())
		{
			return textureMap[ID];
		}

		if (idToPathMap.find(ID) != idToPathMap.end())
		{
			textureMap.insert({ ID, IMG_LoadTexture(renderer, idToPathMap[ID].c_str()) });
			return textureMap[ID];
		}
		else
		{
			return nullptr;
		}
	}

	void Resource::ClearResources()
	{
		for (auto& row : textureMap)
		{
			SDL_DestroyTexture(row.second);
		}
		textureMap.clear();
	}
}