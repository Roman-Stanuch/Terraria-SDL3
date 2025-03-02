#include "character.h"
#include "helper/conversion.h"
#include "resource/resources.h"
#include "world/world.h"
#include "input/input.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

static auto SPRITE_PATH = "character";

namespace Terraria
{
	void HandleCharacterInput(Character& character, float deltaTime);
	void HandleBlockPlacement(const Character& character, World& world);

	void UpdateCharacter(Character& character, const float deltaTime, World& world)
	{
		HandleCharacterInput(character, deltaTime);
		HandleBlockPlacement(character, world);
	}

	void RenderCharacter(const CharacterSprite& characterSprite, SDL_Renderer* renderer)
	{
		const auto texture = Resource::LoadTexture(SPRITE_PATH, renderer);
		const SDL_FRect dstRect = { characterSprite.posX, characterSprite.posY, characterSprite.width, characterSprite.height };
		SDL_RenderTextureRotated(renderer, texture, nullptr, &dstRect, 0.0, nullptr, characterSprite.direction);
	}

	void HandleCharacterInput(Character& character, const float deltaTime)
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

	void HandleBlockPlacement(const Character& character, World& world)
	{
		float mousePosX = 0, mousePosY = 0;
		GetMousePosition(mousePosX, mousePosY);
		mousePosX += character.posX;
		mousePosY += character.posY;
		ScreenToTileCoordinates(mousePosX, mousePosY, world);
		const auto mouseTilePosX = static_cast<uint32_t>(mousePosX);
		const auto mouseTilePosY = static_cast<uint32_t>(mousePosY);

		if (GetMouseButtonDown(MouseButtonLeft, true))
		{
			if (IsTileSurroundedByAir(world, mouseTilePosX, mouseTilePosY)) return;
			SetWorldTile(world, mouseTilePosX, mouseTilePosY, 2);
		}
		else if (GetMouseButtonDown(MouseButtonRight, true))
		{
			SetWorldTile(world, mouseTilePosX, mouseTilePosY, 0);
		}
	}
}