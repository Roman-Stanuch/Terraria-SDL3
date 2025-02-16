#pragma once

#include "terraria.h"

#include <unordered_map>

struct SDL_Texture;
struct SDL_Renderer;

namespace Terraria
{
	class ResourceManager
	{
	public:
		ResourceManager(const ResourceManager& obj) = delete;
		void operator=(const ResourceManager&) = delete;
		static ResourceManager& Instance();

		// Loads the ID/path pairs from a texture pack's config.txt file for use when calling LoadTexture. The path should be relative to the texture pack's root directory.
		bool LoadTexturePack(const std::string& name);
		// Returns the texture for the associated ID. Returns nullptr if no texture pack has been loaded with a path to a texture for the ID.
		SDL_Texture* LoadTexture(const std::string& ID, SDL_Renderer* renderer);
		void Deinit();

	private:
		ResourceManager() {}

		std::unordered_map<std::string, SDL_Texture*> m_TextureMap; // Holds loaded texture objects
		std::unordered_map<std::string, std::string> m_IDToPathMap; // Holds ID/path pairs for finding unloaded textures

	};
}