#include "character.h"
#include "resourcemanager.h"
#include "world/world.h"
#include "helper/conversion.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

const char* m_SpritePath = "character/character.png";
const float m_SpriteWidth = 96.f;
const float m_SpriteHeight = 96.f;

namespace Terraria
{
	Character::Character(float centerScreenX, float centerScreenY, SDL_Renderer* renderer, float xPos, float yPos) :
		m_PosX(xPos), m_PosY(yPos)
	{
		auto texture = ResourceManager::Instance().LoadTexture("character", m_SpritePath, renderer);
		m_DrawX = centerScreenX - (m_SpriteWidth * 0.5f);
		m_DrawY = centerScreenY - (m_SpriteHeight * 0.5f);
	}

	void Character::Update(float deltaTime, World& world)
	{
		HandleInput(deltaTime);
		HandlePlacement(world);
	}

	void Character::Render(SDL_Renderer* renderer, float cameraPosX, float cameraPosY)
	{
		auto texture = ResourceManager::Instance().LoadTexture("character", m_SpritePath, renderer);
		SDL_FRect dstRect = { m_DrawX, m_DrawY, m_SpriteWidth, m_SpriteHeight };
		SDL_RenderTextureRotated(renderer, texture, nullptr, &dstRect, 0.0, NULL, m_Direction);
	}

	void Character::HandleInput(float deltaTime)
	{
		auto keyboardState = SDL_GetKeyboardState(NULL);

		if (keyboardState[SDL_SCANCODE_W])
		{
			m_PosY -= m_Speed * deltaTime;
		}
		if (keyboardState[SDL_SCANCODE_S])
		{
			m_PosY += m_Speed * deltaTime;
		}
		if (keyboardState[SDL_SCANCODE_D])
		{
			m_PosX += m_Speed * deltaTime;
			m_Direction = SDL_FLIP_NONE;
		}
		if (keyboardState[SDL_SCANCODE_A])
		{
			m_PosX -= m_Speed * deltaTime;
			m_Direction = SDL_FLIP_HORIZONTAL;
		}
	}

	void Character::HandlePlacement(World& world)
	{
		float mousePosX = 0;
		float mousePosY = 0;
		SDL_MouseButtonFlags mouseState = SDL_GetMouseState(&mousePosX, &mousePosY);
		mousePosX += m_PosX;
		mousePosY += m_PosY;

		if (mouseState & SDL_BUTTON_LMASK)
		{
			ScreenToTileCoordinates(mousePosX, mousePosY, world);
			world.SetTile((uint32_t)mousePosX, (uint32_t)mousePosY, 1);
		}
	}
}