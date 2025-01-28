#pragma once

#include "terraria.h"

#include <vector>

struct SDL_Renderer;

namespace Terraria
{
	class World
	{
	public:
		World(uint32_t worldWidth = 32, uint32_t worldHeight = 32, uint32_t tileWidth = 16, uint32_t tileHeight = 16);
		
		void Render(SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f);

	private:
		uint32_t m_WorldWidth = 32;
		uint32_t m_WorldHeight = 32;
		uint32_t m_TileWidth = 16;
		uint32_t m_TileHeight = 16;

		std::vector<std::vector<uint32_t>> m_WorldData = {};
	};
}