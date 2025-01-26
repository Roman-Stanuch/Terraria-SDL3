#include "texture.h"

#include "SDL3/SDL_image.h"

Terraria::Texture::Texture(const char* texturePath, SDL_Renderer* renderer)
{
    m_Texture = IMG_LoadTexture(renderer, texturePath);
    if (m_Texture)
    {
        m_Width = m_Texture->w;
        m_Height = m_Texture->h;
    }
    else
    {
        SDL_Log("Could not load texture at path: %s", texturePath);
    }
}

Terraria::Texture::~Texture()
{
    SDL_DestroyTexture(m_Texture);
    m_Texture = nullptr;
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