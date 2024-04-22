#include "BaseObject.h"
#include "CommonFunction.h"
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

    Bullet bullet;
    SDL_Texture* bulletTexture = graphics.loadTexture(BULLET_IMG);
    bullet.init(bulletTexture);

    Mouse mouse;
    mouse.x = SCREEN_WIDTH/2 - 100;
    mouse.y = SCREEN_HEIGHT - 200;

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    Mix_Music *gMusic = graphics.loadMusic("assets\\space.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("assets\\blaster.wav");

    bool quit = false;
    SDL_Event e;
    while( !quit && !gameOver(mouse)) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT) quit = true;
        }

        bullet.x_ = mouse.x + 54;
        bullet.y_ = mouse.y - 20;

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();
        else mouse.remain();

        mouse.move();

        if (currentKeyStates[SDL_SCANCODE_SPACE]) {
            graphics.play(gJump);
            while(bullet.y_ > 0){
                /*SDL_Texture* bulletTexture = graphics.loadTexture(BULLET_IMG);
                graphics.prepareScene();
                graphics.renderTexture(bulletTexture, bullet.x_, bullet.y_);
                graphics.presentScene();*/
                graphics.render(bullet);
                graphics.presentScene();
                graphics.clear_();
                bullet.y_ -= 10;
            }
        }

        graphics.render(mouse, pilot);

        graphics.presentScene();



        background.scroll(1);
        graphics.render(background);

        SDL_Delay(1);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk(gJump);

    SDL_DestroyTexture(pilotTexture);
    SDL_DestroyTexture(background.texture);
    graphics.quit();


    /*Graphics graphics;
    graphics.init();

    TTF_Font* font = graphics.loadFont("assets/Purisa-BoldOblique.ttf", 100);

    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* helloText = graphics.renderText("Hello", font, color);

    graphics.renderTexture(helloText, 200, 200);

    graphics.presentScene();
    waitUntilKeyPressed();

	SDL_DestroyTexture( helloText );
    helloText = NULL;
    TTF_CloseFont( font );

    graphics.quit();*/
    return 0;
}
