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
		SDL_Texture* LoadTexture(const char* name, const char* path, SDL_Renderer* renderer);
		void Deinit();

		// Singleton
		static ResourceManager& Instance();
		ResourceManager(const ResourceManager& obj) = delete;
		void operator=(const ResourceManager&) = delete;

	private:
		const char* m_PathToTextures = "../../../res/textures/";
		std::unordered_map<std::string, SDL_Texture*> m_TextureMap;

		ResourceManager() {}

	public:
		void SetTexturePath(const char* path) { m_PathToTextures = path; }

	};
}