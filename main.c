#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "homescreen.h"
#include "breakout.h"

//primitive functions
    void breakout(SDL_Renderer** renderer, int* disp_width, int* disp_height,SDL_Window** window,FILE** level, bool* progressive);
    void home_screen(SDL_Renderer** renderer, int* disp_width, int* disp_height, bool* quit_or_not, bool* progressive);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
//504 is devisible by 12 and 14, number of bricks I use
    int disp_width = 504;
    int disp_height = 720;
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    int screenw = dm.w;
    int screenh = dm.h;
    bool quit_or_not,progressive = true;

//the window will spawn in the center of the screen
    SDL_Window* window = SDL_CreateWindow(
                             "Breakout",
                             screenw/2 + disp_width,
                             screenh/2,
                             disp_width,
                             disp_height,
                             SDL_WINDOW_SHOWN
                         );

    SDL_Renderer* renderer = SDL_CreateRenderer(
                                 window,
                                 -1,
                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                             );
    SDL_SetWindowResizable(window,true);

    FILE* level;

    home_screen(&renderer, &disp_width, &disp_height, &quit_or_not, &progressive);

    //don't attempt to open file and run when quit in home_screen function
    if(quit_or_not)
    {
        level = fopen("goodlevel", "r+");
        breakout(&renderer, &disp_width, &disp_height, &window, &level, &progressive);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    fclose(level);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
