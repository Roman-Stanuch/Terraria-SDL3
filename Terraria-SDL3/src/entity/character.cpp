#include "character.h"
#include "helper/conversion.h"
#include "resourcemanager.h"
#include "world/world.h"
#include "input/input.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

#include "ImGui/imgui.h"

static const char* SPRITE_PATH = "character/character.png";

namespace Terraria
{
	void HandleCharacterInput(Character& character, float deltaTime);
	void HandleBlockPlacement(Character& character, World& world);

	void UpdateCharacter(Character& character, float deltaTime, World& world)
	{
		HandleCharacterInput(character, deltaTime);
		HandleBlockPlacement(character, world);
	}

	void RenderCharacter(CharacterSprite& characterSprite, SDL_Renderer* renderer)
	{
		auto texture = ResourceManager::Instance().LoadTexture("character", renderer);
		SDL_FRect dstRect = { characterSprite.posX, characterSprite.posY, characterSprite.width, characterSprite.height };
		SDL_RenderTextureRotated(renderer, texture, nullptr, &dstRect, 0.0, NULL, characterSprite.direction);
	}

	void HandleCharacterInput(Character& character, float deltaTime)
	{
		if (GetKeyDown(SDL_SCANCODE_W))
		{
			character.posY -= 50.f * deltaTime;
		}
		if (GetKeyDown(SDL_SCANCODE_S))
		{
			character.posY += 50.f * deltaTime;
		}
		if (GetKeyDown(SDL_SCANCODE_D))
		{
			character.posX += 50.f * deltaTime;
			character.sprite.direction = SDL_FLIP_NONE;
		}
		if (GetKeyDown(SDL_SCANCODE_A))
		{
			character.posX -= 50.f * deltaTime;
			character.sprite.direction = SDL_FLIP_HORIZONTAL;
		}
	}

	void HandleBlockPlacement(Character& character, World& world)
	{
		float mousePosX = 0;
		float mousePosY = 0;
		GetMousePosition(mousePosX, mousePosY);
		mousePosX += character.posX;
		mousePosY += character.posY;
		
		if (GetMouseButtonDown(MouseButtonLeft, true))
		{
			ScreenToTileCoordinates(mousePosX, mousePosY, world);
			SetWorldTile(world, (uint32_t)mousePosX, (uint32_t)mousePosY, 2);
		}
	}
}