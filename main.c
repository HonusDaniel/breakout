#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "homescreen.h"
int main()
{
    SDL_Init(SDL_INIT_VIDEO);   // Inicializace SDL
    int disp_width = 500;
    int disp_height = 720;
    // Vytvoření okna
    SDL_Window* window = SDL_CreateWindow(
        "Breakout",  // Název
        200,                // Souřadnice x
        200,                // Souřadnice y
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

    home_screen(renderer, disp_width, disp_height,window);

    //settings(renderer, disp_width, disp_height,window);
    breakout(renderer,disp_width, disp_height,window);
      // Uvolnění prostředků
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
