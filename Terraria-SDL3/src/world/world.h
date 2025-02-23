#pragma once

#include "terraria.h"

#include <vector>
#include <string>

struct SDL_Renderer;

namespace Terraria
{
	struct World
	{
		uint32_t width = 0; // Width of world in tiles
		uint32_t height = 0; // Height of world in tiles
		const uint32_t tileWidth = 32; // Width of one tile in pixels
		const uint32_t tileHeight = 32; // Height of one tile in pixels
		const uint32_t overdrawAmount = 2; // How many extra tiles are drawn beyond the edge of the viewing area

		std::vector<uint32_t> tileData = {};
	};

	// Attempts to load a world file into outWorld.
	bool LoadWorld(World& outWorld, std::string worldName, std::string worldFolderPath = "../../../res/worlds/");
	// Saves the tileData of the current world to a worldName.txt file in worldFolderPath
	bool SaveWorld(World& world, std::string worldName, std::string worldFolderPath = "../../../res/worlds/");

	void RenderWorld(World& world, SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f);

	// Sets the tile at the given coordinates (in tile coordinates with 0,0 being the top left of the world).
	// Will do nothing if the coordinates are out of the world's width or height.
	void SetWorldTile(World& world, const uint32_t x, const uint32_t y, const uint32_t tileID);
	// Gets the tile at the given coordinates (in tile coordinates with 0,0 being the top left of the world).
	// Will return 0 (air) if the coordinates are out of the world's width or height.
	uint32_t GetWorldTile(const World& world, const uint32_t x, const uint32_t y);
	
	// Returns true if the four tiles surrounding the given tile coordinate are air (0)
	bool IsTileSurroundedByAir(const World& world, uint32_t x, uint32_t y);

}