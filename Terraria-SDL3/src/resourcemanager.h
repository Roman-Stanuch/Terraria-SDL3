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

		// Loads a texture from the given path. If a texture for "name" has already been loaded, it will be returned instead.
		SDL_Texture* LoadTexture(const char* name, const char* path, SDL_Renderer* renderer);
		void Deinit();

	private:
		ResourceManager() {}

		const char* m_PathToTextures = "../../../res/textures/";
		std::unordered_map<std::string, SDL_Texture*> m_TextureMap;

	public:
		// Sets the root directory for searching for textures.
		void SetTexturePath(const char* path) { m_PathToTextures = path; }

	};
}