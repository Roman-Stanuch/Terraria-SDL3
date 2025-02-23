#include "terraria.h"
#include "resourcemanager.h"
#include "world/world.h"
#include "entity/character.h"
#include "user_interface/imguihelper.h"
#include "user_interface/hud.h"
#include "input/input.h"

#include "SDL3/SDL.h"
#define  SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"

const uint32_t SCREEN_WIDTH = 1920;
const uint32_t SCREEN_HEIGHT = 1080;
const bool     FULLSCREEN = false;
const bool     LOG_FPS = false;
const uint32_t CHARACTER_Y_OFFSET = 100;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Terraria::World currentWorld;
Terraria::Character character;

float deltaTime = 0.f;
float timeLastFrame = 0.f;

bool showToolbar = true;

void InitializeCharacter(Terraria::Character& character);
void CalculateDeltaTime(float& dt);

using namespace Terraria;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }
    
    if (!SDL_CreateWindowAndRenderer("Terraria in SDL3", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer))
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    SDL_SetWindowFullscreen(window, FULLSCREEN);
    SDL_SetRenderVSync(renderer, 1);

    InitializeImGui(window, renderer);

    LoadWorld(currentWorld, "world.txt");
    InitializeCharacter(character);

    Resource::LoadTexturePack("default");

    return SDL_AppResult::SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    ImGui_ImplSDL3_ProcessEvent(event);

    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    // Update input
    PollInput(LOG_FPS);

    // Update world
    CalculateDeltaTime(deltaTime);
    UpdateCharacter(character, deltaTime, currentWorld);

    // Prepare rendering
    SDL_SetRenderDrawColor(renderer, 0x65, 0xB7, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Perform rendering
    RenderWorld(currentWorld, renderer, character.posX, character.posY);
    RenderCharacter(character.sprite, renderer);

    // Render UI
    StartImGuiFrameSDL();
    DrawItemBar(SCREEN_WIDTH * 0.04f, showToolbar, 0);
    EndImGuiFrameSDL(renderer);

    SDL_RenderPresent(renderer);

    return SDL_AppResult::SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    SaveWorld(currentWorld, "world.txt");
    Resource::ClearResources();

    DeinitializeImGui();

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
}

void InitializeCharacter(Character& character)
{
    int screenWidth = 0;
    int screenHeight = 0;
    SDL_GetRenderOutputSize(renderer, &screenWidth, &screenHeight);
    auto texture = Resource::LoadTexture("character", renderer);
    character.sprite.posX = (screenWidth * 0.5f) - (character.sprite.width * 0.5f);
    character.sprite.posY = (screenHeight * 0.5f) - (character.sprite.height * 0.5f) + CHARACTER_Y_OFFSET;
}

void CalculateDeltaTime(float& dt)
{
    float timeThisFrame = (float)SDL_GetTicks();
    dt = (timeThisFrame - timeLastFrame) * 0.01f;
    timeLastFrame = timeThisFrame;
}
