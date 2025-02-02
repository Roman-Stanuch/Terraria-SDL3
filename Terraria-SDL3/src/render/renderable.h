#pragma once

struct SDL_Renderer;

namespace Terraria
{
	class IRenderable
	{
	public:
		IRenderable() {}
		virtual ~IRenderable() {}

		virtual void Render(SDL_Renderer* renderer, float cameraPosX = 0.f, float cameraPosY = 0.f) = 0;

	};
}