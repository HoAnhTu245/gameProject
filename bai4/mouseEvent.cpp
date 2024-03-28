#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
using namespace std;

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    SDL_Event e;
    int x, y;
    graphics.drawRect(300, 350, 450, 250);
    while(true)
    {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&e);
        switch(e.type)
        {
            case SDL_QUIT: case SDL_KEYDOWN:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                cout << "down at: " << x << ", " << y << endl;
                break;
            case SDL_MOUSEBUTTONUP:
                cout << "up at: " << x << ", " << y << endl;
                break;
        }

        /*switch(e.button)
        {
            case SDL_BUTTON_LEFT
                cout << "left" << endl;
                break;
            case SDL_BUTTON_RIGHT:
                cout << "right" << endl;
                break;

        }*/
    }
    graphics.quit();
    return 0;
}
