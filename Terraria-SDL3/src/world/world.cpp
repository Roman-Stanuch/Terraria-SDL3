#include "world.h"
#include "resourcemanager.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace Terraria
{
	World::World(std::string worldName, uint32_t tileWidth, uint32_t tileHeight, std::string worldFolderPath) :
		m_TileWidth(tileWidth), m_TileHeight(tileHeight)
	{
		std::ifstream worldStream(worldFolderPath + worldName);
		if (worldStream)
		{
			std::string rowData;
			uint32_t currentTile;

			while (std::getline(worldStream, rowData))
			{
				std::istringstream sstream(rowData);
				std::vector<uint32_t> constructedRow;
				while (sstream >> currentTile)
				{
					constructedRow.push_back(currentTile);
				}
				m_WorldData.push_back(constructedRow);
			}
		}
		else
		{
			SDL_Log("Could not load world");
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
				uint32_t tileID = m_WorldData[row][column];
				if (tileID == 0) continue; // 0 is an empty tile, don't render
				texture = ResourceManager::Instance().LoadTexture(std::to_string(tileID), renderer);

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

	void World::SetTile(const uint32_t x, const uint32_t y, const uint32_t tileID)
	{
		if (x < GetWorldWidth() && y < GetWorldHeight())
		{
			m_WorldData[y][x] = tileID;
		}
	}

	void World::SaveWorld(std::string worldName, std::string worldFolderPath)
	{
		std::ofstream worldStream(worldFolderPath + worldName);
		if (worldStream)
		{
			for (int row = 0; row < GetWorldHeight(); row++)
			{
				for (int column = 0; column < GetWorldWidth(); column++)
				{
					const char* separator = (column == m_WorldData[row].size() - 1) ? "\n" : " ";
					worldStream << m_WorldData[row][column] << separator;
				}
			}
			worldStream.close();
		}
		else
		{
			SDL_Log("Could not save world");
		}
	}
}