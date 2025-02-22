#pragma once

#include "terraria.h"
#include "SDL3/SDL_surface.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace Terraria
{
	class World;

	class Character
	{
	public:
		// Creates a character centered on the screen based on the parameter values.
		Character(float centerScreenX, float centerScreenY, SDL_Renderer* renderer, float xPos = 0.f, float yPos = 0.f);

		void Update(float deltaTime, World& world);

		// Renders the character in the center of the screen (based on constructor values).
		void Render(SDL_Renderer* renderer);

	private:
		void HandleInput(float deltaTime); // Moves the character based on current Keyboard state.
		void HandlePlacement(World& world); // Queries mouse for block placement.

		float m_Speed = 50.f;
		float m_PosX = 0.f; // X world position (somewhere in world)
		float m_PosY = 0.f; // Y world position (somewhere in world)
		float m_DrawX = 0.f; // X draw position (center of screen)
		float m_DrawY = 0.f; // Y draw position (center of screen)
		SDL_FlipMode m_Direction = SDL_FLIP_NONE; // Facing direction (NONE = right, HORIZONTAL = left)

	public:
		void GetPosition(float& x, float& y) { x = m_PosX; y = m_PosY; }

	};
}