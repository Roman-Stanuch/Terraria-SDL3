#pragma once

#include "terraria.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace Terraria::Resource
{
	// Loads the ID/path pairs from a texture pack's config.txt file for use when calling LoadTexture. The path should be relative to the texture pack's root directory.
	bool LoadTexturePack(const std::string& name);
	// Returns the texture for the associated ID. Returns nullptr if no texture pack has been loaded with a path to a texture for the ID.
	SDL_Texture* LoadTexture(const std::string& ID, SDL_Renderer* renderer);

	// Unloads all textures
	void ClearResources();
}