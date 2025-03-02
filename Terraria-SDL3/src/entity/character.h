#pragma once

#include "SDL3/SDL_surface.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace Terraria
{
	struct World;

	struct CharacterSprite
	{
		float posX = 0.f;
		float posY = 0.f;
		float width = 96.f;
		float height = 96.f;
		SDL_FlipMode direction = SDL_FLIP_NONE;
	};

	struct Character
	{
		CharacterSprite sprite;
		float posX = 0.f;
		float posY = 0.f;
	};

	void UpdateCharacter(Character& character, float deltaTime, World& world);
	void RenderCharacter(const CharacterSprite& characterSprite, SDL_Renderer* renderer);
}