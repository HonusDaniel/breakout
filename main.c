#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#include <stdbool.h>
#include "homescreen.h"
int main()
{
    SDL_Init(SDL_INIT_VIDEO);   // Inicializace SDL
    TTF_Init();
    int disp_width = 504;
    int disp_height = 720;
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    int screenw = dm.w;
    int screenh = dm.h;
    // Vytvoření okna
    SDL_Window* window = SDL_CreateWindow(
        "Breakout",  // Název
        screenw/2 + disp_width,     // Souřadnice x
        screenh/2 ,                // Souřadnice y
        disp_width,                // Šířka
        disp_height,                // Výška
        SDL_WINDOW_SHOWN
    );
    // Vytvoření kreslítka
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
SDL_SetWindowResizable(window,true);

    FILE* level;
    level = fopen("goodlevel" , "r+");


    home_screen(renderer, disp_width, disp_height,window);

    //settings(renderer, disp_width, disp_height,window);
    breakout(renderer,disp_width, disp_height,window,level);
      // Uvolnění prostředků
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    fclose(level);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
