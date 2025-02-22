#include "terraria.h"
#include "resourcemanager.h"
#include "world/world.h"
#include "entity/character.h"
#include "user_interface/imguihelper.h"

#include "SDL3/SDL.h"
#define  SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"

const uint32_t SCREEN_WIDTH = 1920;
const uint32_t SCREEN_HEIGHT = 1080;
const bool     FULLSCREEN = false;
const uint32_t CHARACTER_Y_OFFSET = 100;

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
    
    if (!SDL_CreateWindowAndRenderer("Terraria in SDL3", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer))
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    SDL_SetWindowFullscreen(window, FULLSCREEN);
    SDL_SetRenderVSync(renderer, 1);

    InitializeImGui(window, renderer);

    InitializeWorld(world);
    InitializeCharacter(character);

    ResourceManager::Instance().LoadTexturePack("default");

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

    // Render UI
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);

    return SDL_AppResult::SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    world->SaveWorld("world.txt");
    ResourceManager::Instance().Deinit();

    DeinitializeImGui();

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
    characterPtr = std::make_unique<Character>((float)screenWidth * 0.5f, ((float)screenHeight * 0.5f) + CHARACTER_Y_OFFSET, renderer);
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
