#pragma once

#include "terraria.h"

#include <vector>
#include <string>

struct SDL_Renderer;

namespace Terraria
{
	class World
	{
	public:
		World(std::string worldName, uint32_t tileWidth = 16, uint32_t tileHeight = 16, std::string worldFolderPath = "../../../res/worlds/");
		
		// Renders the world based on the cameraPos parameters and the screen width/height. Only tiles in view will be rendered. cameraPos variables
		// should be the top left corner of the desired render area and will be clamped to 0,0 if negative.
		void Render(SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f);

		// Get a the tileID at the given coordinates. 0,0 is the top left of the world. An invalid coordinate will return 0.
		uint32_t GetTile(const uint32_t x, const uint32_t y);
		// Set a tile to the tileID at the given coordinates. 0,0 is the top left of the world. An invalid coordinate will do nothing.
		void SetTile(const uint32_t x, const uint32_t y, const uint32_t tileID);

		// Saves the world to the worldFolderPath in a file with the worldName as its name.
		void SaveWorld(std::string worldName, std::string worldFolderPath = "../../../res/worlds/");

	private:
		const uint32_t m_OverDraw = 2; // Draws beyond the edge of the screen to ensure enough tiles are drawn.

		uint32_t m_TileWidth = 16; // Width of one tile in pixels
		uint32_t m_TileHeight = 16; // Height of one tile in pixels

		std::vector<uint32_t> m_WorldData = {};
		uint32_t m_WorldWidth = 0; // Width of world in tiles
		uint32_t m_WorldHeight = 0; // Height of world in tiles

		// Gets the index in the m_WorldData vector for the tile at the given coordinates. Does not perform bound checks with the size of m_WorldData.
		uint32_t GetTileIndex(const uint32_t x, const uint32_t y) const;

	public:
		uint32_t GetWorldWidth() const { return m_WorldWidth; }
		uint32_t GetWorldHeight() const { return m_WorldHeight; }

		uint32_t GetWorldTileHeight() const { return m_TileHeight; }
		uint32_t GetWorldTileWidth() const { return m_TileWidth; }

	};
}