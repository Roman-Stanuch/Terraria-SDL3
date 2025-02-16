#include "terraria.h"
#include "resourcemanager.h"
#include "world/world.h"
#include "entity/character.h"

#include "SDL3/SDL.h"
#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"

const uint32_t screenWidth = 1920;
const uint32_t screenHeight = 1080;
const bool fullscreen = false;
const uint32_t characterYOffset = 100;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
std::unique_ptr<Terraria::World> world = nullptr;
std::unique_ptr<Terraria::Character> character = nullptr;

float deltaTime = 0.f;
float timeLastFrame = 0.f;

void InitializeCharacter(std::unique_ptr<Terraria::Character>& characterPtr);
void InitializeWorld(std::unique_ptr<Terraria::World>& worldPtr);
void CalculateDeltaTime(float& dt);

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

    InitializeWorld(world);
    InitializeCharacter(character);

    ResourceManager::Instance().LoadTexturePack("default");

    return SDL_AppResult::SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    // Update world
    CalculateDeltaTime(deltaTime);
    character->Update(deltaTime, *world);

    // Prepare rendering
    SDL_SetRenderDrawColor(renderer, 0x65, 0xB7, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    float characterPosX;
    float characterPosY;
    character->GetPosition(characterPosX, characterPosY);

    // Perform rendering
    world->Render(renderer, characterPosX, characterPosY);
    character->Render(renderer);

    SDL_RenderPresent(renderer);

    return SDL_AppResult::SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    world->SaveWorld("world.txt");
    ResourceManager::Instance().Deinit();
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
}

void InitializeCharacter(std::unique_ptr<Terraria::Character>& characterPtr)
{
    int screenWidth = 0;
    int screenHeight = 0;
    SDL_GetRenderOutputSize(renderer, &screenWidth, &screenHeight);
    characterPtr = std::make_unique<Character>((float)screenWidth * 0.5f, ((float)screenHeight * 0.5f) + characterYOffset, renderer);
}

void InitializeWorld(std::unique_ptr<Terraria::World>& worldPtr)
{
    worldPtr = std::make_unique<World>("world.txt", 32, 32);
}

void CalculateDeltaTime(float& dt)
{
    float timeThisFrame = (float)SDL_GetTicks();
    dt = (timeThisFrame - timeLastFrame) * 0.01f;
    timeLastFrame = timeThisFrame;
}
