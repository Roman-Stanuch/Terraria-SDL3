#pragma once

#include "terraria.h"
#include "render/renderable.h"

#include <vector>

namespace Terraria
{
	class World : public IRenderable
	{
	public:
		World(uint32_t worldWidth = 32, uint32_t worldHeight = 32, uint32_t tileWidth = 16, uint32_t tileHeight = 16);
		
		virtual void Render(SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f) override;

	private:
		const uint32_t m_OverDraw = 2; // Draws beyond to edge of the screen to ensure enough tiles are drawn.

		uint32_t m_WorldWidth = 32; // Number of tiles in the X direction
		uint32_t m_WorldHeight = 32; // Number of tiles in the Y direction
		uint32_t m_TileWidth = 16; // Width of one tile in pixels
		uint32_t m_TileHeight = 16; // Height of one tile in pixels

		std::vector<std::vector<uint32_t>> m_WorldData = {};

	};
}