#include <iostream>
#include "commonFile.h"
#include "BaseObject.h"

BaseObject gBackground;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
        {
            std::cout << "Warning: Linear texture filtering not enabled";
        }
        gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            std::cout << "Window could not be created! SDL error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL error: " << SDL_GetError() << std::endl;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!IMG_Init(imgFlags) && imgFlags)
                {
                    std::cout << "SDL_image could not initialize! SDL error: " << SDL_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadBackground()
{
    bool ret = gBackground.loadMedia("viewport.png", gRenderer);
    return ret;
}

void close()
{
    gBackground.Quit();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        std::cout << "Failed to initialize!\n";
        return -1;
    }
    if (!loadBackground())
    {
        std::cout << "Failed to load background!\n";
    }
    bool isQuit = false;
    SDL_Event e;
    while (!isQuit){
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                isQuit = true;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBackground.render(gRenderer, NULL);

        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}
