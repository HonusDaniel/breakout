#include "homescreen.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include <stdbool.h>

void top_scores(FILE** scores){

 //3 top scores
 if (*scores == NULL) {
        printf("first run of game");

    } else {
        printf("score file loaded");
;    }

fclose(*scores);
}

void home_screen(SDL_Renderer** renderer, int* disp_width, int* disp_height)
{

    SDL_Event e;
    bool quit = false;
    int pos = 100;
    SDL_Rect rect;
        rect.x = *disp_width/2 - 125;
        rect.y = *disp_height/2 - 50;
        rect.w = 250;
        rect.h = 70;
    SDL_Rect rect2;
        rect2.x = *disp_width/2 - 125;
        rect2.y = rect.y + rect.h + 10;
        rect2.w = 250;
        rect2.h = 70;
    SDL_Rect keybinding_rect;
        keybinding_rect.x = 10;
        keybinding_rect.y = *disp_height - 40;;
        keybinding_rect.w = 250;
        keybinding_rect.h = 30;
     SDL_Rect score_leaderboard;
        score_leaderboard.x = 20;
        score_leaderboard.y = 20;
        score_leaderboard.w = 250;
        score_leaderboard.h = 70;

    SDL_Color just_white = {240, 240, 240};
    TTF_Font* font = TTF_OpenFont("EightBit Atari-Block.ttf" /*path*/, 128 /*size*/);
    SDL_Surface* leaderboard = TTF_RenderText_Blended(font, "213 233 322", just_white);
    leaderboard = TTF_RenderText_Blended(font, "213 233 322", just_white);
    SDL_Texture* leaderboard_texture = SDL_CreateTextureFromSurface(*renderer, leaderboard);


    FILE* scores;
    scores = fopen("scores" , "r+");

    top_scores(&scores);

    int whiteBUT = 255;
    int grayBUT = 150;


    while (!quit)
    {
        SDL_Color c = {whiteBUT, whiteBUT, whiteBUT};
        SDL_Color c2 = {grayBUT, grayBUT, grayBUT};
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

            SDL_RenderPresent(*renderer);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }


        SDL_SetRenderDrawColor(*renderer, 20, 20, 20, 180);
        SDL_RenderClear(*renderer);
        SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);



SDL_Surface* keybindings = TTF_RenderText_Blended(font, "press <space> to select", just_white);
SDL_Surface* start_game = TTF_RenderText_Blended(font, "start game", c);
SDL_Surface* settings_menu = TTF_RenderText_Blended(font, "settings", c2);

    SDL_Texture* ONE = SDL_CreateTextureFromSurface(*renderer, start_game);
    SDL_Texture* TWO = SDL_CreateTextureFromSurface(*renderer, settings_menu);
    SDL_Texture* THREE = SDL_CreateTextureFromSurface(*renderer, keybindings);
    SDL_RenderCopy(*renderer, ONE, NULL, &rect);
    SDL_RenderCopy(*renderer, TWO, NULL, &rect2);
    SDL_RenderCopy(*renderer, THREE, NULL, &keybinding_rect);
    SDL_RenderCopy(*renderer, leaderboard_texture, NULL, &score_leaderboard);

    SDL_FreeSurface(start_game);
    SDL_FreeSurface(settings_menu);
    SDL_FreeSurface(keybindings);
    SDL_DestroyTexture(ONE);
    SDL_DestroyTexture(TWO);
    SDL_DestroyTexture(THREE);

        pos++;

        SDL_RenderPresent(*renderer);  // Prezentace kreslítka
    }

    SDL_FreeSurface(leaderboard);
    SDL_DestroyTexture(leaderboard_texture);

    TTF_CloseFont(font);

    SDL_RenderClear(*renderer);

}



