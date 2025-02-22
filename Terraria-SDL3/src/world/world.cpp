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
			bool firstRow = true;
			uint32_t firstRowWidth = 0; // The length of the first row will be the length of all rows

			// Go through each line of the world file
			while (std::getline(worldStream, rowData))
			{
				std::istringstream sstream(rowData);
				uint32_t currentRowWidth = 0;

				// Load tiles until currentRowWidth is equal to the firstRowWidth (or all tiles if it is the first row)
				while (sstream >> currentTile && (currentRowWidth < firstRowWidth || firstRow == true))
				{
					m_WorldData.push_back(currentTile);

					if (firstRow) firstRowWidth++;
					currentRowWidth++;
				}

				// If not enough tiles were loaded to equal firstRowWidth, fill the rest of the row with 0
				while (currentRowWidth < firstRowWidth)
				{
					m_WorldData.push_back(0);
					currentRowWidth++;
				}

				firstRow = false;
			}

			m_WorldWidth = firstRowWidth;
			m_WorldHeight = m_WorldData.size() / m_WorldWidth;
		}
		else
		{
			SDL_Log("Could not load world");
		}
	}

	void World::Render(SDL_Renderer* renderer, float cameraPosX, float cameraPosY)
	{
		// Find the first visible row and column to the camera
		int cameraRow = (int)std::max(cameraPosY / m_TileHeight, 0.f);
		int cameraColumn = (int)std::max(cameraPosX / m_TileWidth, 0.f);

		int screenWidth = 0;
		int screenHeight = 0;
		SDL_GetRenderOutputSize(renderer, &screenWidth, &screenHeight);

		// Find the last visible row and column to the camera (plus some overdraw)
		int maxRow = cameraRow + m_OverDraw + (screenHeight / m_TileHeight);
		int maxColumn = cameraColumn + m_OverDraw + (screenWidth / m_TileWidth);

		SDL_Texture* texture = nullptr;

		for (int row = cameraRow; row < maxRow && row < GetWorldHeight(); row++)
		{
			for (int column = cameraColumn; column < maxColumn && column < GetWorldWidth(); column++)
			{
				uint32_t tileID = m_WorldData[GetTileIndex(column, row)];
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

	uint32_t World::GetTile(const uint32_t x, const uint32_t y)
	{
		uint32_t index = GetTileIndex(x, y);
		if (index < m_WorldData.size())
			return m_WorldData[index];
		else
			return 0;
	}

	void World::SetTile(const uint32_t x, const uint32_t y, const uint32_t tileID)
	{
		uint32_t index = GetTileIndex(x, y);
		if (index < m_WorldData.size())
			m_WorldData[index] = tileID;
		else
			return;
	}

	void World::SaveWorld(std::string worldName, std::string worldFolderPath)
	{
		std::ofstream worldStream(worldFolderPath + worldName);
		if (worldStream)
		{
			uint32_t currentColumn = 0;
			for (uint32_t tile : m_WorldData)
			{
				worldStream << tile;
				if (currentColumn == m_WorldWidth - 1)
				{
					worldStream << "\n";
					currentColumn = 0;
				}
				else
				{
					worldStream << " ";
					currentColumn++;
				}
			}

			worldStream.close();
		}
		else
		{
			SDL_Log("Could not save world");
		}
	}

	uint32_t World::GetTileIndex(const uint32_t x, const uint32_t y) const
	{
		return m_WorldWidth * y + x;
	}
}