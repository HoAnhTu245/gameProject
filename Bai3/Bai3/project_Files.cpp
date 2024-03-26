#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

using namespace std;



void windowStayUp()
{
    SDL_Event e;
    bool quit = false;
    while( quit == false ){
        while( SDL_PollEvent( &e ) ){
            if( e.type == SDL_QUIT  || e.type == SDL_KEYDOWN) quit = true;
        }
    }
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true){
        if(SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}


int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture("tunhi.jpg");
    graphics.draw(background);
    graphics.present();
    windowStayUp();


    SDL_Texture* img = graphics.loadTexture("Spongebob.png");
    graphics.renderTexture(img, 40, 400);
    graphics.present();
    windowStayUp();

    graphics.quit();
    return 0;
}
