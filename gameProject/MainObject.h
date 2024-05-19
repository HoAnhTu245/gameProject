#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED


/*#include "CommonFunction.h"
#include "BaseObject.h"

using namespace std;
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
    //screen = renderer;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}
struct Bullet
{
    int x_;
    int y_ ;
    bool is_move;
    SDL_Texture* texture;
    void init(SDL_Texture* _texture)
    {
        texture = _texture;
    }
    Bullet()
    {
        x_ = 0;
        y_ = 0;
        is_move = false;
    }
    void set_x_( int xVal) {x_ = xVal;}
    void set_y_( int yVal) {y_ = yVal;}
    int get_x_() {return x_;}
    int get_y_() {return y_;}
    void set_is_move(const bool& isMove) {is_move = isMove;}
    bool get_is_move() {return is_move;}

    void HandleMove()
    {
        y_ -= 10;
        if(y_ < 0) is_move = false;
    }

};



struct Plane
{
    SDL_Renderer *renderer;
    vector<Bullet*> bullet_list;
    SDL_Texture* texture;
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    void set_bullet_list(vector<Bullet*> list)
    {
        bullet_list = list;
    }
    vector<Bullet*> get_bullet_list() {return bullet_list;}

    void init(SDL_Texture* _texture)
    {
        x = SCREEN_WIDTH/2 - 100;
        y = SCREEN_HEIGHT - 200;
        texture = _texture;
    }
    void move() {
        x += dx;
        y += dy;
    }
    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy = speed;
        dx = 0;
    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }
    void remain(){
        dx = 0;
        dy = 0;
    }
    void handle()
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) turnNorth();
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) turnSouth();
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) turnWest();
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) turnEast();
        else remain();
        if (currentKeyStates[SDL_SCANCODE_SPACE]) {
            //graphics.play(gJump);
            Bullet* p_bullet = new Bullet();
            SDL_Texture* bulletTexture = loadTexture(BULLET_IMG, renderer);
            p_bullet->set_x_(x);
            p_bullet->set_y_(y);
            /*p_bullet->x_ = x + 54;
            p_bullet->y_ = y - 20;
            p_bullet->init(bulletTexture);
            bullet_list.push_back(p_bullet);
        }
    }
    void handleBullet()
    {
        for(int i = 0; i < bullet_list.size(); i++)
        {
            Bullet* p_bullet = bullet_list.at(i);
            if(p_bullet != NULL)
            {
                while(p_bullet->get_is_move() == true)
                {
                    p_bullet->HandleMove();

                    renderBullet(*p_bullet);
                    //SDL_RenderPresent(renderer);
                }
                /*else{
                    bullet_list.erase(bullet_list.begin() + i);
                    if(p_bullet != NULL){
                        delete p_bullet;
                        p_bullet = NULL;
                    }
                }
            }
        }
    }

};


bool gameOver(const Plane& mouse) {
    return mouse.x < 0 || mouse.x >= SCREEN_WIDTH ||
           mouse.y < 0 || mouse.y >= SCREEN_HEIGHT;
}
*/


#endif
