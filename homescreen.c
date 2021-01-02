#include "homescreen.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include <stdbool.h>


void home_screen(SDL_Renderer** renderer, int* disp_width, int* disp_height, bool* quit_or_not,bool* progressive)
{
//bunch of variables and SDL rectangles to hold text
    SDL_Event e;
    bool quit = false;
    SDL_Rect rect;
        rect.x = *disp_width/2 - 125;
        rect.y = *disp_height/2 - 50;
        rect.w = 250;
        rect.h = 70;
    SDL_Rect rect2;
        rect2.x = *disp_width/2 - 200;
        rect2.y = rect.y + rect.h + 10;
        rect2.w = 400;
        rect2.h = 70;
    SDL_Rect keybinding_rect;
        keybinding_rect.x = 10;
        keybinding_rect.y = *disp_height - 40;
        keybinding_rect.w = 250;
        keybinding_rect.h = 30;
    SDL_Rect words;
        words.x = *disp_width/2 - 80;
        words.y = 10;
        words.w = 160;
        words.h = 30;
    SDL_Rect score_leaderboard;
        score_leaderboard.x = *disp_width/2 - 50;
        score_leaderboard.y = 40;
        score_leaderboard.w = 100;
        score_leaderboard.h = 50;
    SDL_Rect score_leaderboard2;
        score_leaderboard2.x = *disp_width/2 - 50;
        score_leaderboard2.y = 90;
        score_leaderboard2.w = 100;
        score_leaderboard2.h = 50;
    SDL_Rect score_leaderboard3;
        score_leaderboard3.x = *disp_width/2 - 50;
        score_leaderboard3.y = 140;
        score_leaderboard3.w = 100;
        score_leaderboard3.h = 50;

    SDL_Color just_white = {240, 240, 240};
    SDL_Color grayish = {250, 200, 70};
    SDL_Color red = {200, 0, 0};

//open license font from https://github.com/TheRobotFactory/EightBit-Atari-Fonts
    TTF_Font* font = TTF_OpenFont("EightBit Atari-Block.ttf" /*path*/, 128 /*size*/);

    int whiteBUT = 255;
    int grayBUT = 150;
    char stri0[16] = "000";
    char stri1[16] = "000";
    char stri2[16] = "000";

    char scores_array[2][16];

    FILE* score;
    score = fopen("top_scores","a+");

        fscanf(score, "%15s ", stri0);
        strcpy(scores_array[0], stri0);
        fscanf(score, "%15s ", stri1);
        strcpy(scores_array[1], stri1);
        fscanf(score, "%15s ", stri2);
        strcpy(scores_array[2], stri2);

    fclose(score);

    SDL_Surface* leaderboard = TTF_RenderText_Blended(font, scores_array[0], grayish);
    SDL_Surface* leaderboard2 = TTF_RenderText_Blended(font, scores_array[1], grayish);
    SDL_Surface* leaderboard3 = TTF_RenderText_Blended(font, scores_array[2], grayish);
    SDL_Texture* leaderboard_texture = SDL_CreateTextureFromSurface(*renderer, leaderboard);
    SDL_Texture* leaderboard_texture2 = SDL_CreateTextureFromSurface(*renderer, leaderboard2);
    SDL_Texture* leaderboard_texture3 = SDL_CreateTextureFromSurface(*renderer, leaderboard3);

    while (!quit)
    {
        SDL_Color c = {whiteBUT, whiteBUT, whiteBUT};
        SDL_Color c2 = {grayBUT, grayBUT, grayBUT};
        while (SDL_PollEvent(&e))
        {

            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_SPACE] && whiteBUT == 255)
            {
            //this starts the normal game mode
                quit = true;
                *quit_or_not = true;
                *progressive = false;
            }
            if (state[SDL_SCANCODE_SPACE] && whiteBUT == 150)
            {
            //and the fast one
                quit = true;
                *quit_or_not = true;
                *progressive = true;
            }
            if (state[SDL_SCANCODE_ESCAPE])
            {
            //quits program
                quit = true;
                *quit_or_not = false;
            }
            if (state[SDL_SCANCODE_UP])
            {
            // only two buttons, so simple color change
                whiteBUT = 255;
                grayBUT = 150;
            }
            if (state[SDL_SCANCODE_DOWN])
            {
                whiteBUT = 150;
                grayBUT = 255;
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

    //create surfaces for main menu
        SDL_Surface* keybindings = TTF_RenderText_Blended(font, "press <space> to select", just_white);
        SDL_Surface* word = TTF_RenderText_Blended(font, "TOP SCORES", red);
        SDL_Surface* start_game = TTF_RenderText_Blended(font, "start game", c);
        SDL_Surface* settings_menu = TTF_RenderText_Blended(font, "start game mode 2", c2);

    //create textures from surfaces
        SDL_Texture* ONE = SDL_CreateTextureFromSurface(*renderer, start_game);
        SDL_Texture* TWO = SDL_CreateTextureFromSurface(*renderer, settings_menu);
        SDL_Texture* THREE = SDL_CreateTextureFromSurface(*renderer, keybindings);
        SDL_Texture* FOUR = SDL_CreateTextureFromSurface(*renderer, word);

    //render the generated textures
        SDL_RenderCopy(*renderer, ONE, NULL, &rect);
        SDL_RenderCopy(*renderer, TWO, NULL, &rect2);
        SDL_RenderCopy(*renderer, THREE, NULL, &keybinding_rect);
        SDL_RenderCopy(*renderer, FOUR, NULL, &words);

        SDL_RenderCopy(*renderer, leaderboard_texture, NULL, &score_leaderboard);
        SDL_RenderCopy(*renderer, leaderboard_texture2, NULL, &score_leaderboard2);
        SDL_RenderCopy(*renderer, leaderboard_texture3, NULL, &score_leaderboard3);

    //free the surfaces
        SDL_FreeSurface(start_game);
        SDL_FreeSurface(settings_menu);
        SDL_FreeSurface(keybindings);

        SDL_DestroyTexture(ONE);
        SDL_DestroyTexture(TWO);
        SDL_DestroyTexture(THREE);
        SDL_DestroyTexture(FOUR);


        SDL_RenderPresent(*renderer);
    }
//free the leaderboard
    SDL_FreeSurface(leaderboard);
    SDL_FreeSurface(leaderboard2);
    SDL_FreeSurface(leaderboard3);
    SDL_DestroyTexture(leaderboard_texture);
    SDL_DestroyTexture(leaderboard_texture2);
    SDL_DestroyTexture(leaderboard_texture3);

    TTF_CloseFont(font);

    SDL_RenderClear(*renderer);
}
