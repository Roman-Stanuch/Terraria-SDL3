#include "character.h"
#include "resourcemanager.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

namespace Terraria
{
	Character::Character(float centerScreenX, float centerScreenY, SDL_Renderer* renderer, float xPos, float yPos) :
		m_PosX(xPos), m_PosY(yPos)
	{
		auto texture = ResourceManager::Instance().LoadTexture("character", "character/character.png", renderer);
		m_DrawX = centerScreenX - (texture->w * 0.5f);
		m_DrawY = centerScreenY - (texture->h * 0.5f);
	}

	void Character::Update(float deltaTime)
	{
		HandleInput(deltaTime);
	}

	void Character::Render(SDL_Renderer* renderer, float cameraPosX, float cameraPosY)
	{
		auto texture = ResourceManager::Instance().LoadTexture("character", "character/character.png", renderer);
		SDL_FRect dstRect = { (float)m_DrawX, (float)m_DrawY, (float)texture->w, (float)texture->h };
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
}