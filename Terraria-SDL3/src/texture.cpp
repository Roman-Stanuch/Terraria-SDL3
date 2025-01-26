#include "texture.h"

#include "SDL3/SDL_image.h"


Terraria::Texture::Texture(const std::string& texturePath, SDL_Renderer* renderer) :
	m_Texture(nullptr), m_Width(0), m_Height(0)
{
    std::string completePath = m_PathToTextures + texturePath;
    m_Texture = IMG_LoadTexture(renderer, completePath.c_str());
    if (m_Texture)
    {
        m_Width = m_Texture->w;
        m_Height = m_Texture->h;
    }
    else
    {
        SDL_Log("Could not load texture at path: %s", completePath.c_str());
    }
}

Terraria::Texture::~Texture()
{
    Destroy();
}

void Terraria::Texture::Render(float x, float y, SDL_Renderer* renderer)
{
    if (m_Texture == nullptr)
    {
        SDL_Log("Attempted to render null texture");
        return;
    }

    SDL_FRect dstRect = { x, y, static_cast<float>(m_Width), static_cast<float>(m_Height) };
    SDL_RenderTexture(renderer, m_Texture, nullptr, &dstRect);
}

void Terraria::Texture::Destroy()
{
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
    m_Width = 0;
    m_Height = 0;
}
