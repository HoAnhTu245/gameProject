#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED


#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }
    void init()
    {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0) logErrorAndExit("SDL_init",SDL_GetError());
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
        if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) logErrorAndExit("Image_Error", IMG_GetError());


        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    void draw(SDL_Texture* background)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);

    }
    void present()
    {
        SDL_RenderPresent(renderer);
    }
    SDL_Texture* loadTexture(const char* filename)
    {
        SDL_Texture* texture = IMG_LoadTexture(renderer, filename);

        return texture;
    }
    void renderTexture(SDL_Texture* texture, int x, int y)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void quit()
    {
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};




#endif // GRAPHICS_H_INCLUDED
