#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"


using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    bool quit = false;
    SDL_Event event;
    while (quit == false) {
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) {
                    quit = true;
            }
        }
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) quit = true;
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_UP]) cout << "up ";
        if(currentKeyStates[SDL_SCANCODE_DOWN]) cout << "down ";
        if(currentKeyStates[SDL_SCANCODE_RIGHT]) cout << "right ";
        if(currentKeyStates[SDL_SCANCODE_LEFT]) cout << "left ";
        cout << "." << endl;

        //}
        SDL_Delay(100);
        //}
    }
    graphics.quit();
    return 0;
}

