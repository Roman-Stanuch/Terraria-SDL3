#include "terraria.h"
#include "resourcemanager.h"
#include "world.h"

#include "SDL3/SDL.h"
#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"

const uint32_t screenWidth = 1920;
const uint32_t screenHeight = 1080;
const bool fullscreen = false;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
std::unique_ptr<Terraria::World> world = nullptr;

using namespace Terraria;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }
    
    if (!SDL_CreateWindowAndRenderer("Terraria in SDL3", screenWidth, screenHeight, 0, &window, &renderer))
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    SDL_SetWindowFullscreen(window, fullscreen);
    SDL_SetRenderVSync(renderer, 1);

    world = std::make_unique<World>(16, 32, 32, 32);

    return SDL_AppResult::SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    world->Render(renderer);

    SDL_RenderPresent(renderer);

    return SDL_AppResult::SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    ResourceManager::Instance().Deinit();
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
}
