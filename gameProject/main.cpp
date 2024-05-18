#include "BaseObject.h"
#include "CommonFunction.h"
#include "MainObject.h"
#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Plane pilot;
    SDL_Texture* pilotTexture = graphics.loadTexture(PLANE_IMG);
    pilot.init(pilotTexture);
    pilot.renderer = graphics.renderer;

    /*Chicken chicken;
    chicken.texture1 = graphics.loadTexture(CHICKEN1_IMG);
    chicken.texture2 = graphics.loadTexture(CHICKEN2_IMG);*/



    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    Mix_Music *gMusic = graphics.loadMusic("assets\\game.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("assets\\blaster.wav");

    bool quit = false;
    SDL_Event e;
    while( !quit && !gameOver(pilot)) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT) quit = true;
            pilot.handle();
        }

        //const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


        pilot.move();
        pilot.handleBullet();
        /*bullet.x_ = mouse.x + 54;
        bullet.y_ = mouse.y - 20;
        if (currentKeyStates[SDL_SCANCODE_SPACE]) {
            graphics.play(gJump);
            while(bullet.y_ > 0){
                graphics.clear_();

                background.scroll(1);
                graphics.render(background);
                graphics.render(mouse, pilot);

                graphics.render(bullet);
                graphics.presentScene();

                bullet.y_ -= 10;
            }
        }
        /*chicken.x = rand() % SCREEN_WIDTH;
        chicken.y = 0;
        while(chicken.y < SCREEN_HEIGHT){
            graphics.clear_();
            background.scroll(1);
            graphics.render(background);

            graphics.render(mouse, pilot);
            graphics.renderChicken(chicken);
            graphics.presentScene();
            chicken.y += 2;
        }*/


        background.scroll(1);
        graphics.render(background);

        renderMainObject(pilot, graphics);


        graphics.presentScene();


        SDL_Delay(1);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk(gJump);

    SDL_DestroyTexture(pilotTexture);
    SDL_DestroyTexture(background.texture);
    graphics.quit();


    return 0;
}


