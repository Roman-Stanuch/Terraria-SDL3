#pragma once

#include "terraria.h"
#include "render/renderable.h"

#include <vector>
#include <string>

namespace Terraria
{
	class World : public IRenderable
	{
	public:
		World(std::string worldName, uint32_t tileWidth = 16, uint32_t tileHeight = 16, std::string worldFolderPath = "../../../res/worlds/");
		
		virtual void Render(SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f) override;

		void SetTile(const uint32_t x, const uint32_t y, const uint32_t tileID);

	private:
		const uint32_t m_OverDraw = 2; // Draws beyond to edge of the screen to ensure enough tiles are drawn.

		uint32_t m_TileWidth = 16; // Width of one tile in pixels
		uint32_t m_TileHeight = 16; // Height of one tile in pixels

		std::vector<std::vector<uint32_t>> m_WorldData = {};

	public:
		uint32_t GetWorldHeight() const { return (uint32_t)m_WorldData.size(); }
		uint32_t GetWorldWidth() const { return (m_WorldData.size() > 0) ? (uint32_t)m_WorldData[0].size() : 0; }
		uint32_t GetWorldTileHeight() const { return m_TileHeight; }
		uint32_t GetWorldTileWidth() const { return m_TileWidth; }

	};
}