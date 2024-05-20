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

int num_die = 0;
bool gameOver(const Plane& mouse) {
    return mouse.x < 0 || mouse.x >= SCREEN_WIDTH ||
           mouse.y < 0 || mouse.y >= SCREEN_HEIGHT || num_die > 3;
}

int main(int argc, char *argv[])
{
    Plane pilot;
    pilot.graphics.init();
    SDL_Texture* pilotTexture = pilot.graphics.loadTexture(PLANE_IMG);
    pilot.init(pilotTexture);

    ScrollingBackground background;
    background.setTexture(pilot.graphics.loadTexture(BACKGROUND_IMG));

    Mix_Music *gMusic = pilot.graphics.loadMusic("assets\\game.mp3");
    pilot.graphics.play(gMusic);
    Mix_Chunk *gJump = pilot.graphics.loadSound("assets\\blaster.wav");

    bool quit = false;
    SDL_Event e;
    bool game_over;
    while( !quit && !gameOver(pilot) && check == 0) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT) quit = true;
            pilot.handle();
        }
        pilot.move();

        background.scroll(1);
        pilot.graphics.render(background);

        pilot.initThreat();
        pilot.handleThreat();

        pilot.renderMainObject();

        pilot.handleBullet();

        pilot.Collision();
        if(check){
            num_die++;
            if(num_die <= 3)
            {
                pilot.init(pilotTexture);
                check = 0;
                SDL_Delay(10);
            }
            else quit = true;
        }

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


