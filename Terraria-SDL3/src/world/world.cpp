#include "world.h"
#include "resourcemanager.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

#include <algorithm>

namespace Terraria
{
	World::World(uint32_t worldWidth, uint32_t worldHeight, uint32_t tileWidth, uint32_t tileHeight) :
		m_WorldWidth(worldWidth), m_WorldHeight(worldHeight), m_TileWidth(tileWidth), m_TileHeight(tileHeight)
	{
		for (int row = 0; row < (int)m_WorldHeight; row++)
		{
			m_WorldData.push_back(std::vector<uint32_t>(m_WorldWidth, 0));
		}
	}

	void World::Render(SDL_Renderer* renderer, float cameraPosX, float cameraPosY)
	{
		int cameraRow = (int)std::max(cameraPosY / m_TileHeight, 0.f);
		int cameraColumn = (int)std::max(cameraPosX / m_TileWidth, 0.f);

		int screenWidth = 0;
		int screenHeight = 0;
		SDL_GetRenderOutputSize(renderer, &screenWidth, &screenHeight);

		int maxRow = cameraRow + m_OverDraw + (screenHeight / m_TileHeight);
		int maxColumn = cameraColumn + m_OverDraw + (screenWidth / m_TileWidth);

		SDL_Texture* texture = nullptr;

		for (int row = cameraRow; row < maxRow && row < m_WorldData.size(); row++)
		{
			for (int column = cameraColumn; column < maxColumn && column < m_WorldData[row].size(); column++)
			{
				switch (m_WorldData[row][column])
				{
				case 0:
					texture = ResourceManager::Instance().LoadTexture("stone", "tile/stone.png", renderer);
					break;
				case 1:
					texture = ResourceManager::Instance().LoadTexture("ice_stone", "tile/ice_stone.png", renderer);
					break;
				default:
					texture = nullptr;
				}

				if (texture != nullptr)
				{
					SDL_FRect dstRect = { column * (float)m_TileWidth - cameraPosX, row * (float)m_TileHeight - cameraPosY, (float)m_TileWidth, (float)m_TileHeight };
					SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
				}
				else
				{
					SDL_Log("Could not find valid texture for tile at Row: %i | Column: %i", row, column);
				}
			}
		}
	}
}