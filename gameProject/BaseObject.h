#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "CommonFunction.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0)
             if(e.type == SDL_MOUSEBUTTONDOWN)
            return;
        SDL_Delay(10);
    }
}

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

        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        //Init SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
        //Init sdl_ttf
        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
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
        renderTexture(background.texture,background.scrollingOffset, 0);
        renderTexture(background.texture,background.scrollingOffset - background.width, 0);
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
        return gFont;
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


////////////////////////////


SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}
//// SINH MỆNH CHO NHÂN VẬT
struct Heart
{
    int number_;
    int xHeart;
    int yHeart;
    SDL_Texture* texture;
    std::vector<int> pos_list_;
    void SetNum(const int& num){ number_ = num; }
    void Init(SDL_Renderer* renderer)
    {
        xHeart = 0; yHeart = 0;
        texture = loadTexture("img\\heart.png", renderer);
        number_ = 3;
        if(pos_list_.size() > 0)
        {
            pos_list_.clear();
        }
        AddPos(10);
        AddPos(60);
        AddPos(110);
    }
    void AddPos(const int& xp)
    {
        pos_list_.push_back(xp);
    }
    void Decrease()
    {
        number_--;
        pos_list_.pop_back();
    }
    void renderTexture(int x, int y, SDL_Renderer* renderer)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL , &dest);
    }
    void Show(SDL_Renderer* renderer)
    {
        for(int i = 0; i < pos_list_.size(); i++)
        {
            xHeart = pos_list_.at(i);
            yHeart = 5;
            renderTexture(xHeart, yHeart, renderer);
        }
    }
};







///// VỤ NỔ
struct Fire
{
    int pos_x;
    int pos_y;
    SDL_Texture* texture;
    void init(SDL_Texture* _texture)
    {
        texture = _texture;
    }

};



//// CHICKEN
struct Threat
{

    int x_val;
    int y_val;
    bool die;
    SDL_Texture* texture;
    void init(SDL_Texture* _texture)
    {
        texture = _texture;
    }
    Threat()
    {
        x_val = 0;
        y_val = 0;
        die = false;
    }
    void set(int x, int y)
    {
        x_val = x;
        y_val = y;
    }
    void HandleMove()
    {
        y_val += 1;
    }


};


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



/////////////////////////////////////////////////////////////////////////

// MÁY BAY

int check = 0;
int cnt = 0;
struct Plane
{
    Graphics graphics;
    Fire fire;

    vector<Bullet*> bullet_list;
    vector<Threat*> threat_list;
    vector<Heart*> heart_list;

    SDL_Texture* texture;
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;

    void init(SDL_Texture* _texture)
    {
        x = SCREEN_WIDTH/2 - 100;
        y = SCREEN_HEIGHT - 200;
        texture = _texture;
    }

    void renderMainObject() {
        SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_Rect renderQuad = {x, y, dest.w, dest.h};
        SDL_RenderCopy(graphics.renderer, texture , &dest, &renderQuad);
    }
    void renderFire(const Fire& fire) {
        SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        SDL_QueryTexture(fire.texture, NULL, NULL, &dest.w, &dest.h);

        SDL_Rect renderQuad = {fire.pos_x, fire.pos_y, dest.w, dest.h};
        SDL_RenderCopy(graphics.renderer, fire.texture , &dest, &renderQuad);
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

        if (y > 0 && currentKeyStates[SDL_SCANCODE_UP]) turnNorth();
        else if (y + 117 < SCREEN_HEIGHT && currentKeyStates[SDL_SCANCODE_DOWN]) turnSouth();
        else if (x > 0 && currentKeyStates[SDL_SCANCODE_LEFT]) turnWest();
        else if (x + 81 < SCREEN_WIDTH && currentKeyStates[SDL_SCANCODE_RIGHT]) turnEast();
        else remain();
        if (currentKeyStates[SDL_SCANCODE_SPACE]) {
            graphics.play(graphics.loadSound("assets\\blaster.wav"));
            Bullet* p_bullet = new Bullet();
            SDL_Texture* bulletTexture = loadTexture(BULLET_IMG, graphics.renderer);
            p_bullet->init(bulletTexture);
            p_bullet->set_x_(x + 27);
            p_bullet->set_y_(y - 20);
            if(bullet_list.size() < 7){
                bullet_list.push_back(p_bullet);
            }
        }
    }
    void setFire(int x1, int y1)
    {
        SDL_Texture* FireTexture = loadTexture(FIRE_IMG, graphics.renderer);
        fire.init(FireTexture);
        fire.pos_x = x1;
        fire.pos_y = y1;
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

    void initThreat()
    {
        Threat* p_threat = new Threat();
        if(p_threat != NULL)
        {
            SDL_Texture* threatTexture;
            if(x % 3 == 0) threatTexture = loadTexture(CHICKEN1_IMG, graphics.renderer);
            else if(x % 3 == 1) threatTexture = loadTexture(CHICKEN2_IMG, graphics.renderer);
            else if(x % 3 == 2) threatTexture = loadTexture(CHICKEN3_IMG, graphics.renderer);
            p_threat->init(threatTexture);
            p_threat->set(rand() % (1200 - 100 + 1) + 100, 0);

            if(cnt < 4) {
                threat_list.push_back(p_threat);
                cnt++;
            }
        }
    }
    void renderThreat(const Threat& threat)
    {
        SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        SDL_QueryTexture(threat.texture, NULL, NULL, &dest.w, &dest.h);

        SDL_Rect renderQuad = {threat.x_val, threat.y_val, dest.w, dest.h};
        SDL_RenderCopy(graphics.renderer, threat.texture , &dest, &renderQuad);
    }

    int k = 0;
    void handleThreat()
    {
        for(int i = 0; i < threat_list.size(); i++)
        {
            Threat* p_threat = threat_list.at(i);
            if(p_threat != NULL)
            {
                if(p_threat->y_val < SCREEN_HEIGHT )
                {
                    renderThreat(*p_threat);
                    p_threat->y_val += 2;
                    if(p_threat->x_val < x && p_threat->x_val + 130 > x &&
                        p_threat->y_val < y && p_threat->y_val + 122 > y)
                        {
                            graphics.play(graphics.loadSound("assets\\boom.wav"));
                            setFire(p_threat->x_val, p_threat->y_val);
                            renderFire(fire);
                            graphics.presentScene();
                            delete p_threat;
                            threat_list.erase(threat_list.begin() + i);
                            --cnt;
                            waitUntilKeyPressed();
                            check = 1;
                            break;
                        }
                }

                else{
                    threat_list.erase(threat_list.begin() + i);
                    if(p_threat != NULL){
                        p_threat->die = true;
                        delete p_threat;
                        p_threat = NULL;
                        check = 1;
                    }
                    cnt--;
                }

            }
        }
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
                    p_bullet->y_ -= 10;
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

    void Collision()
    {
        for(int i = 0; i < bullet_list.size(); i++)
        {
            Bullet* p_bullet = bullet_list.at(i);
            if(p_bullet != NULL)
            {
                for(int j = 0; j < threat_list.size(); j++)
                {
                    Threat* p_threat = threat_list.at(j);
                    if(p_threat != NULL)
                    {
                        if(p_threat->x_val < p_bullet->x_ && p_threat->x_val + 130 > p_bullet->x_ &&
                               p_threat->y_val < p_bullet->y_ && p_threat->y_val + 122 > p_bullet->y_)
                        {
                            graphics.play(graphics.loadSound("assets\\chicken_noise.wav"));
                            setFire(p_threat->x_val, p_threat->y_val);
                            renderFire(fire);
                            delete p_threat;
                            threat_list.erase(threat_list.begin() + j);
                            --cnt;
                        }
                    }
                }

            }
        }
    }
    void Endgame()
    {
        SDL_Texture* threatTexture1 = loadTexture(CHICKEN1_IMG, graphics.renderer);
        SDL_Texture* threatTexture2 = loadTexture(CHICKEN2_IMG, graphics.renderer);
        SDL_Texture* threatTexture3 = loadTexture(CHICKEN3_IMG, graphics.renderer);
        SDL_Texture* FireTexture = loadTexture(FIRE_IMG, graphics.renderer);
        SDL_Texture* bulletTexture = loadTexture(BULLET_IMG, graphics.renderer);
        SDL_DestroyTexture(threatTexture1);
        SDL_DestroyTexture(threatTexture2);
        SDL_DestroyTexture(threatTexture3);
        SDL_DestroyTexture(FireTexture);
        SDL_DestroyTexture(bulletTexture);
    }

};


#endif // BASEOBJECT_H_INCLUDED
