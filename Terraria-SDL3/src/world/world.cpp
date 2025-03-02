#include "world.h"
#include "resource/resources.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace Terraria
{
	uint32_t GetTileIndex(const World& world, uint32_t x, uint32_t y);

	bool LoadWorld(World& outWorld, const std::string &worldName, const std::string &worldFolderPath)
	{
		if (std::ifstream worldStream(worldFolderPath + worldName); worldStream)
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
					outWorld.tileData.push_back(currentTile);

					if (firstRow) firstRowWidth++;
					currentRowWidth++;
				}

				// If not enough tiles were loaded to equal firstRowWidth, fill the rest of the row with 0
				while (currentRowWidth < firstRowWidth)
				{
					outWorld.tileData.push_back(0);
					currentRowWidth++;
				}

				firstRow = false;
			}

			if (outWorld.tileData.empty())
			{
				SDL_Log("World \"%s\" contained no data", worldName.c_str());
				return false;
			}

			outWorld.width = firstRowWidth;
			outWorld.height = static_cast<uint32_t>(outWorld.tileData.size() / outWorld.width);

			return true;
		}
		else
		{
			SDL_Log("Could not open world file: %s", worldName.c_str());
			return false;
		}
	}

	bool SaveWorld(World& world, const std::string &worldName, const std::string &worldFolderPath)
	{
		if (std::ofstream worldStream(worldFolderPath + worldName); worldStream)
		{
			uint32_t currentColumn = 0;
			for (const uint32_t tile : world.tileData)
			{
				worldStream << tile;
				if (currentColumn == world.width - 1)
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
			return true;
		}
		else
		{
			SDL_Log("Could not save world");
			return false;
		}
	}

	void RenderWorld(const World &world, SDL_Renderer* renderer, const float cameraPosX, const float cameraPosY)
	{
		// Cache the world's tile size
		const auto worldTileWidth = static_cast<float>(world.tileWidth);
		const auto worldTileHeight = static_cast<float>(world.tileHeight);

		// Find the first visible row and column to the camera
		const int cameraRow = static_cast<int>(std::max(cameraPosY / worldTileHeight, 0.f));
		const int cameraColumn = static_cast<int>(std::max(cameraPosX / worldTileWidth, 0.f));

		int screenWidth = 0;
		int screenHeight = 0;
		SDL_GetRenderOutputSize(renderer, &screenWidth, &screenHeight);

		// Find the last visible row and column to the camera (plus some overdraw)
		const uint32_t maxRow = cameraRow + world.overdrawAmount + (screenHeight / world.tileHeight);
		const uint32_t maxColumn = cameraColumn + world.overdrawAmount + (screenWidth / world.tileWidth);

		SDL_Texture* texture = nullptr;

		for (uint32_t row = cameraRow; row < maxRow && row < world.height; row++)
		{
			for (uint32_t column = cameraColumn; column < maxColumn && column < world.width; column++)
			{
				const uint32_t tileID = world.tileData[GetTileIndex(world, column, row)];
				if (tileID == 0) continue; // 0 is an empty tile, don't render
				texture = Resource::LoadTexture(std::to_string(tileID), renderer);

				if (texture != nullptr)
				{
					SDL_FRect dstRect = { static_cast<float>(column) * worldTileWidth - cameraPosX, static_cast<float>(row) * worldTileHeight - cameraPosY, worldTileWidth, worldTileHeight };
					SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
				}
				else
				{
					SDL_Log("Could not find valid texture for tile at Row: %i | Column: %i", row, column);
				}
			}
		}
	}

	void SetWorldTile(World& world, const uint32_t x, const uint32_t y, const uint32_t tileID)
	{
		if (x > world.width || y > world.height) return;

		uint32_t index = GetTileIndex(world, x, y);
		if (index < world.tileData.size())
			world.tileData[index] = tileID;
		else
			return;
	}

	uint32_t GetWorldTile(const World& world, const uint32_t x, const uint32_t y)
	{
		if (x > world.width || y > world.height) return 0;

		uint32_t index = GetTileIndex(world, x, y);
		if (index < world.tileData.size())
			return world.tileData[index];
		else
			return 0;
	}

	bool IsTileSurroundedByAir(const World& world, const uint32_t x, const uint32_t y)
	{
		if (GetWorldTile(world, x, y - 1)) return false;
		if (GetWorldTile(world, x, y + 1)) return false;
		if (GetWorldTile(world, x - 1, y)) return false;
		if (GetWorldTile(world, x + 1, y)) return false;

		return true;
	}

	uint32_t GetTileIndex(const World& world, const uint32_t x, const uint32_t y)
	{
		return world.width * y + x;
	}
}