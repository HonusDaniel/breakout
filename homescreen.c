/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "homescreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

void home_screen(SDL_Renderer** renderer, int disp_width, int disp_height,SDL_Window** window)
{
    SDL_Event e;
    bool quit = false;
    int pos = 100;
    SDL_Rect rect;
    rect.x = disp_width/2 - 125;
    rect.y = disp_height/2 - 50;
    rect.w = 250;
    rect.h = 70;
    SDL_Rect rect2;
    rect2.x = disp_width/2 - 125;
    rect2.y = disp_height/2 + 50;
    rect2.w = 250;
    rect2.h = 70;
    int whiteBUT = 255;
    int grayBUT = 150;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {

            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_SPACE] && whiteBUT == 255)
            {
                printf("<space> pressed, starting game...");
                quit = true;
            }
            if (state[SDL_SCANCODE_UP])
            {
                printf("<up> pressed\n");
                whiteBUT = 255;
                grayBUT = 150;
            }
            if (state[SDL_SCANCODE_DOWN])
            {
                printf("<down> pressed\n");
                whiteBUT = 150;
                grayBUT = 255;
            }
            if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP])
            {
                printf("Right and Up Keys Pressed.\n");
            }

            SDL_RenderPresent(renderer);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 0, 20, 180);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, whiteBUT, whiteBUT, whiteBUT, whiteBUT);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_SetRenderDrawColor(renderer, grayBUT, grayBUT, grayBUT, grayBUT);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        pos++;

        SDL_RenderPresent(renderer);  // Prezentace kreslítka
    }

    SDL_RenderClear(renderer);

}



void settings(SDL_Renderer** renderer, int disp_width, int disp_height,SDL_Window** window)
{
    SDL_Renderer* renderer2 = SDL_CreateRenderer(
                                  window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                              );

    SDL_Event e;
    bool quit = false;
    int pos = 100;
    SDL_Rect rect;
    rect.x = disp_width/2 - 125;
    rect.y = disp_height/2 - 50;
    rect.w = 250;
    rect.h = 70;
    SDL_Rect rect2;
    rect2.x = disp_width/2 - 125;
    rect2.y = disp_height/2 + 50;
    rect2.w = 250;
    rect2.h = 70;
    int whiteBUT = 255;
    int grayBUT = 150;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {

            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_Q])
            {
                quit = true;
                printf("<Q> is pressed. Quitting...\n");
                printf("<Q> is pressed. Quitting...\n");
            }
            if (state[SDL_SCANCODE_UP])
            {
                printf("<right> pressed\n");
                whiteBUT = 2;
                grayBUT = 255;
            }
            if (state[SDL_SCANCODE_DOWN])
            {
                printf("<left> pressed\n");
                whiteBUT = 255;
                grayBUT = 2;
            }
            if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP])
            {
                printf("Right and Up Keys Pressed.\n");
            }

            SDL_RenderPresent(renderer2);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer2, 20, 0, 20, 180);
        SDL_RenderClear(renderer2);
        SDL_SetRenderDrawColor(renderer2, whiteBUT, whiteBUT, whiteBUT, whiteBUT);
        SDL_RenderFillRect(renderer2, &rect);
        SDL_SetRenderDrawColor(renderer2, 0, 0, 0, 255);

        SDL_SetRenderDrawColor(renderer2, grayBUT, grayBUT, grayBUT, grayBUT);
        SDL_RenderFillRect(renderer2, &rect2);
        SDL_SetRenderDrawColor(renderer2, 0, 0, 0, 255);

        pos++;

        SDL_RenderPresent(renderer2);  // Prezentace kreslítka
    }



}
