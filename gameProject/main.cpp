#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "BaseObject.h"
#include "CommonFunction.h"

using namespace std;
void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true){
        if(SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    /*Mouse mouse;
    mouse.x = 100;
    mouse.y = 400;

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture(BIRD_SPRITE_FILE);
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);

    bool quit = false;
    SDL_Event e;
    while( !quit && !gameOver(mouse)) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        if (currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        if (currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();

        mouse.move();

        bird.tick();

        graphics.prepareScene();

        graphics.render(mouse, bird);

        graphics.presentScene();

        /*background.scroll(1);

        graphics.render(background);

        //graphics.presentScene();

        SDL_Delay(10);
    }

    SDL_DestroyTexture( background.texture );
    graphics.quit();*/
    SDL_Texture* ironman = graphics.loadTexture("img//nhanvat.jpg");
    graphics.renderTexture(ironman, 0, 0);
    graphics.presentScene();
    waitUntilKeyPressed();
    return 0;
}
