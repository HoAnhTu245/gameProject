#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
 using namespace std;

 void Error(const char* msg, const char* error)
 {
     SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
     SDL_Quit();
 }


 int main(int argc, char* argv[])
 {

     SDL_Window* window = SDL_CreateWindow);
     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
     SDL_Texture* texture = IMG_LoadTexture(renderer, "tunhi.jpg");
     SDL_RenderCopy(renderer, texture, NULL, NULL);
     //SDL_UpdateWindowSurface(window);
     SDL_RenderPresent( renderer );
     SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

 }
