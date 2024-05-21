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

void waitUntilEnd()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0)
             if(e.type == SDL_QUIT)

            return;
        SDL_Delay(100);
    }
}
int num_die = 0;
int STATUS = 0;

int main(int argc, char *argv[])
{
    Plane pilot;
    pilot.graphics.init();
    SDL_Texture* pilotTexture = pilot.graphics.loadTexture(PLANE_IMG);
    pilot.init(pilotTexture);

    Heart heart;
    heart.Init(pilot.graphics.renderer);

    SDL_Texture* startTexture = pilot.graphics.loadTexture("img\\start.jpg");
    pilot.graphics.renderTexture(startTexture, 0, 0);
    pilot.graphics.presentScene();
    SDL_Event event;
    int x, y;
    while (true) {
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x, &y);
        if(x > 511 && x < 811 && y > 543 && y < 620){
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                STATUS = 1;
                break;
            }
        }
        SDL_Delay(100);
    }


    ScrollingBackground background;
    background.setTexture(pilot.graphics.loadTexture(BACKGROUND_IMG));

    Mix_Music *gMusic = pilot.graphics.loadMusic("assets\\game.mp3");
    pilot.graphics.play(gMusic);
    Mix_Chunk *gJump = pilot.graphics.loadSound("assets\\blaster.wav");
    Mix_Chunk *gBoom = pilot.graphics.loadSound("assets\\boom.wav");
    Mix_Chunk *gChicken = pilot.graphics.loadSound("assets\\chicken_noise.wav");
    Mix_Chunk *winGame = pilot.graphics.loadSound("assets\\win.wav");
    Mix_Chunk *loseGame = pilot.graphics.loadSound("assets\\loseGame.wav");

    TTF_Font* font = pilot.graphics.loadFont("assets\\BebasNeue-Regular.ttf", 50);
    SDL_Color color = {255, 255, 255};

    bool quit = false;
    SDL_Event e;
    bool game_over;
    if(STATUS == 1){
        while( !quit && check == 0) {
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

            heart.Show(pilot.graphics.renderer);

            string str_time = "TIME: ";
            Uint32 time_val = SDL_GetTicks() / 1000;
            Uint32 val_time = 30 - time_val;
            if(val_time <= 0)
            {
                pilot.graphics.renderTexture(pilot.graphics.loadTexture("img\\youWin.jpg"), 0, 0);
                pilot.graphics.presentScene();
                pilot.graphics.play(winGame);
                waitUntilEnd();
                quit = true;
                break;
            }
            else
            {
                string str_val = to_string(val_time);
                str_time += str_val;
                SDL_Texture* timeText = pilot.graphics.renderText(str_time.c_str(), font, color);
                pilot.graphics.renderTexture(timeText, 1170, 5);
            }

            pilot.Collision();

            if(check){
                num_die++;
                heart.Decrease();
                if(num_die <= 3)
                {
                    pilot.graphics.clear_();
                    pilot.init(pilotTexture);
                    check = 0;
                    SDL_Delay(10);
                }
                else if(num_die > 3){
                    pilot.graphics.clear_();
                    pilot.graphics.renderTexture(pilot.graphics.loadTexture("img\\lose.jpg"), 0, 20);
                    pilot.graphics.renderTexture(pilot.graphics.loadTexture("img\\lose_button.png"), 410, 180);
                    pilot.graphics.presentScene();
                    pilot.graphics.play(loseGame);
                    waitUntilEnd();
                    quit = true;
                    break;
                }
            }

            pilot.graphics.presentScene();
            SDL_Delay(1);
        }

        if (gMusic != nullptr) Mix_FreeMusic( gMusic );
        if (loseGame != nullptr) Mix_FreeChunk( loseGame );
        if (winGame != nullptr)  Mix_FreeChunk( winGame );
        if (gJump != nullptr) Mix_FreeChunk(gJump);
        if (gBoom != nullptr) Mix_FreeChunk(gBoom);
        if (gChicken != nullptr) Mix_FreeChunk(gChicken);

        SDL_DestroyTexture(pilotTexture);
        SDL_DestroyTexture(background.texture);
        SDL_DestroyTexture(heart.texture);
        pilot.graphics.quit();
    }

    return 0;
}


