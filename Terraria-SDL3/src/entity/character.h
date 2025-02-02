#pragma once

#include "terraria.h"
#include "entity/entity.h"
#include "render/renderable.h"

#include "SDL3/SDL_surface.h"

struct SDL_Texture;

namespace Terraria
{
	class Character : public Entity, public IRenderable
	{
	public:
		// Creates a character centered on the screen based on the parameter values.
		Character(float centerScreenX, float centerScreenY, SDL_Renderer* renderer, float xPos = 0.f, float yPos = 0.f);

		virtual void Update(float deltaTime) override;
		// Renders the character in the center of the screen. Camera position variables ignored.
		virtual void Render(SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f) override;

	private:
		void HandleInput(float deltaTime); // Moves the character based on current Keyboard state.

		const char* m_SpritePath = "character/character.png";

		float m_Speed = 100.f;
		float m_PosX = 0.f; // X world position (somewhere in world)
		float m_PosY = 0.f; // Y world position (somewhere in world)
		float m_DrawX = 0.f; // X draw position (center of screen)
		float m_DrawY = 0.f; // Y draw position (center of screen)
		SDL_FlipMode m_Direction = SDL_FLIP_NONE;

	public:
		void GetPosition(float& x, float& y) { x = m_PosX; y = m_PosY; }

	};
}