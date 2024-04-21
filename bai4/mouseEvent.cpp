#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
using namespace std;

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    graphics.drawRect(300, 200, 450, 250);
    graphics.mouseEvent();
    graphics.quit();
    
    return 0;
}
