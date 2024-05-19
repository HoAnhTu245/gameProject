#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "MainObject.h"
using namespace std;








struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width; }
    }
};


struct Graphics
{

    SDL_Renderer *renderer;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        //Init SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }
    void clear_()
    {
        SDL_RenderClear(renderer);
    }

	void prepareScene(SDL_Texture * background = nullptr)
    {
        SDL_RenderClear(renderer);
        if (background != nullptr) SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    virtual SDL_Texture *loadTexture(const char *filename)
    {
        //screen = renderer;
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL , &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void render(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }



    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }

    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
        }

        SDL_FreeSurface( textSurface );
        return texture;
    }

};







SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
    //screen = renderer;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}



// ĐẠN
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
        y_ -= 5;
        if(y_ < 0) is_move = false;
    }

};


// MÁY BAY
struct Plane
{
    Graphics graphics;
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
            graphics.play(graphics.loadSound("assets\\blaster.wav"));
            Bullet* p_bullet = new Bullet();
            SDL_Texture* bulletTexture = loadTexture(BULLET_IMG, graphics.renderer);
            p_bullet->init(bulletTexture);
            p_bullet->set_x_(x + 27);
            p_bullet->set_y_(y - 20);
            /*p_bullet->x_ = x + 54;
            p_bullet->y_ = y - 20;*/
            bullet_list.push_back(p_bullet);
            //renderBullet(*p_bullet);
            //graphics.presentScene();
        }
    }
    void renderBullet(const Bullet& bullet)
    {
        SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        SDL_QueryTexture(bullet.texture, NULL, NULL, &dest.w, &dest.h);

        SDL_Rect renderQuad = {bullet.x_, bullet.y_, dest.w, dest.h};
        SDL_RenderCopy(graphics.renderer, bullet.texture , &dest, &renderQuad);
    }
    void handleBullet()
    {
        for(int i = 0; i < bullet_list.size(); i++)
        {
            Bullet* p_bullet = bullet_list.at(i);
            if(p_bullet != NULL)
            {
                if(p_bullet->y_ > 0)
                {

                    renderBullet(*p_bullet);
                    p_bullet->y_ -= 5;
                    //SDL_RenderPresent(renderer);
                }
                else{
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
void renderMainObject(const Plane& plane) {
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    SDL_QueryTexture(plane.texture, NULL, NULL, &dest.w, &dest.h);

    SDL_Rect renderQuad = {plane.x, plane.y, dest.w, dest.h};
    SDL_RenderCopy(plane.graphics.renderer, plane.texture , &dest, &renderQuad);
}



#endif // BASEOBJECT_H_INCLUDED
