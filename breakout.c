/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "homescreen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

struct Bricks
{
    int color;
    bool broken;
};

void breakout(SDL_Renderer** renderer, int disp_width, int disp_height,SDL_Window** window)
{
    int pos = 100;

    SDL_Rect ball;
    ball.x = disp_width/2;
    ball.y = disp_height - 70;
    ball.w = 20;
    ball.h = 20;
    SDL_Rect paddle;
    paddle.x = disp_width/2-20;
    paddle.y = disp_height - 50;
    paddle.w = 70;
    paddle.h = 20;

    SDL_Event e;
    SDL_Surface *s;
    srand(time(NULL));
    float dirX;
    do
    {
        dirX = (rand() % 4) - (rand() % 3);
    }
    while (dirX == 0);
    float dirY = -3;
    int dt, mousex,mousey = 0;
    float speed_multiplier = 0.8;
    SDL_CaptureMouse(true);
    int lives = 3;

    bool quit,failed,playing = false;

    while (!quit)
    {
        SDL_GetMouseState(&mousex,NULL);
        if (mousex >= disp_width-40)
            mousex = disp_width-40;
        if (mousex <= 40)
            mousex = 40;

        paddle.x=mousex-(paddle.w/2);
        if (!playing)
            ball.x=mousex-(ball.w/2);
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        while ((SDL_PollEvent(&e)) != 0)
        {

            switch( e.type )
            {

            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( e.key.keysym.sym )
                {
                case SDLK_d:
                    break;
                case SDLK_SPACE:
                    playing = true;
                    break;
                case SDLK_s:
                    speed_multiplier+=0.2;
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                }
            }

        }
        //SDL_RenderPresent(renderer);

        SDL_SetRenderDrawColor(renderer, 20, 0, 20, 180);
        SDL_RenderClear(renderer);

        /* Declaring the surface. */

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Nastavení barvy na červenou
        SDL_RenderFillRect(renderer, &ball);

        SDL_SetRenderDrawColor(renderer,194, 194, 194,255);
        SDL_RenderFillRect(renderer, &paddle);

        //handle collision with walls and losing ball
        if (ball.x <= 0 || ball.x >= disp_width - ball.w)
            dirX= dirX * -1;
        if (ball.y <= 0)
            dirY = dirY * -1;

        //SHIIIIIIT
        if (ball.y >= disp_height - ball.h - 49 && !failed)
            if (ball.x >= (paddle.x-ball.w) && ball.x <= (paddle.x + paddle.w) && !failed)
            {
                dirY = dirY * -1;
                if (ball.x < (paddle.x + paddle.w/3))
                    dirX = -2;
                if (ball.x > (paddle.x + paddle.w/3) && ball.x < (paddle.x + 2*(paddle.w/3)) )
                    dirX = 0;
                if (ball.x > (paddle.x + 2*paddle.w/3))
                    dirX = 2;
            }
        //if ball falls through
            else
            {
                speed_multiplier = 0.8;
                playing = false;
                lives--;
                dirY = dirY * -1;
                ball.x = disp_width/2;
                ball.y = disp_height - 70;
            }
        //if (lives == 0)

        if (playing == true)
        {
            ball.x += dirX *2 * speed_multiplier;
            ball.y += dirY *2 * speed_multiplier;
        }





        SDL_RenderPresent(renderer);  // Prezentace kreslítka
    }

    SDL_DestroyRenderer(renderer);

}
