#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED

#include <bits/stdc++.h>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 800
#define WINDOW_TITLE "Ho Anh Tu 23021700"
#define BACKGROUND_IMG "img\\background.png"

const char*  BIRD_SPRITE_FILE = "img\\nhanvat.jpg";
const int BIRD_CLIPS[][4] = {
    {0, 0, 4, 600},

    {181, 0, 400, 600},

    {364, 0, 400, 600},

    {547, 0, 400, 600},

    {728, 0, 400, 600},

    {0, 170, 400, 600},

    {181, 170, 400, 600},

    {364, 170, 400, 600},


};
const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;


#endif // COMMONFUNCTION_H_INCLUDED
