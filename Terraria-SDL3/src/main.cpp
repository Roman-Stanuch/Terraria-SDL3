
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

bool init();
void close();

SDL_Window* gWindow{ nullptr };
SDL_Surface* gScreenSurface{ nullptr };
SDL_Surface* gHelloWorld{ nullptr };

bool init()
{
    bool success{ true };

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0);
        if (gWindow == nullptr)
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

void close()
{
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    int exitCode{ 0 };

    if (!init())
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        bool quit{ false };

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
                if (e.key.key == SDLK_E)
                {
                    quit = true;
                }
            }

            //Fill the surface white
            SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));
            //Render image on screen
            SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
            //Update the surface
            SDL_UpdateWindowSurface(gWindow);
        }
    }

    close();

    return exitCode;
}
