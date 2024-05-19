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
    /*Graphics graphics;
    graphics.init();*/

    Plane pilot;
    pilot.graphics.init();
    SDL_Texture* pilotTexture = pilot.graphics.loadTexture(PLANE_IMG);
    pilot.init(pilotTexture);

    /*Chicken chicken;
    chicken.texture1 = graphics.loadTexture(CHICKEN1_IMG);
    chicken.texture2 = graphics.loadTexture(CHICKEN2_IMG);*/



    ScrollingBackground background;
    background.setTexture(pilot.graphics.loadTexture(BACKGROUND_IMG));

    Mix_Music *gMusic = pilot.graphics.loadMusic("assets\\game.mp3");
    pilot.graphics.play(gMusic);

    Mix_Chunk *gJump = pilot.graphics.loadSound("assets\\blaster.wav");

    bool quit = false;
    SDL_Event e;
    while( !quit && !gameOver(pilot)) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT) quit = true;
            pilot.handle();
        }
        pilot.move();
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
        pilot.graphics.render(background);

        renderMainObject(pilot);
        pilot.handleBullet();

        pilot.graphics.presentScene();


        SDL_Delay(1);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk(gJump);

    SDL_DestroyTexture(pilotTexture);
    SDL_DestroyTexture(background.texture);
    pilot.graphics.quit();


    return 0;
}


