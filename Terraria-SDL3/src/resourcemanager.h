#pragma once

#include "terraria.h"

#include <map>

struct SDL_Renderer;

namespace Terraria
{
	class Texture;

	typedef std::shared_ptr<Texture> TexturePtr;

	class ResourceManager
	{
	public:
		static ResourceManager& Instance();
		TexturePtr LoadTexture(const char* name, const char* path, SDL_Renderer* renderer);

	private:
		const char* m_PathToTextures = "../../../res/textures/";
		std::map<const char*, TexturePtr> m_TextureMap;

		ResourceManager() {};

	public:
		void SetTexturePath(const char* path) { m_PathToTextures = path; }
	};
}