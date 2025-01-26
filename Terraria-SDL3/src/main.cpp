#include "texture.h"
#include "terraria.h"
#include "resourcemanager.h"

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

const uint32_t screenWidth = 1920;
const uint32_t screenHeight = 1080;

bool Init();
void Close();

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

using namespace Terraria;

bool Init()
{
    bool success = true;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_CreateWindowAndRenderer("Terraria in SDL3", screenWidth, screenHeight, 0, &window, &renderer))
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

void Close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    int exitCode = 0;

    if (!Init())
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        TexturePtr texture = ResourceManager::Instance().LoadTexture("stone", "tiles/stone.png", renderer);

        bool quit = false;

        SDL_Event e;
        SDL_zero(e);

        while (quit == false)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_EVENT_QUIT)
                {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            texture->Render(0.f, 0.f, renderer);

            SDL_RenderPresent(renderer);
        }
    }

    Close();

    return exitCode;
}
