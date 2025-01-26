#pragma once

#include "terraria.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace Terraria
{
	class Texture
	{
	public:
		Texture(const char* texturePath, SDL_Renderer* renderer);
		~Texture();

        void Render(float x, float y, SDL_Renderer* renderer);

    private:
        SDL_Texture* m_Texture = nullptr;
        int m_Width = 0;
        int m_Height = 0;

    public:
        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

	};
}