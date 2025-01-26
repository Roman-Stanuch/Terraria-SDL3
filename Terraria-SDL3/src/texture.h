#pragma once

#include "terraria.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace Terraria
{
	class Texture
	{
	public:
		Texture(const std::string& texturePath, SDL_Renderer* renderer);
		~Texture();

        void Render(float x, float y, SDL_Renderer* renderer);

    private:
        const char* m_PathToTextures = "../../../res/textures/";

        SDL_Texture* m_Texture;

        int m_Width;
        int m_Height;

        void Destroy();

    public:
        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
	};
}