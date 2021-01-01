#include "homescreen.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/*

    EXTRA FILE WITH TOP SCORE
    ADD THE ONE MODE or whatever...

*/

typedef struct{
//color
    unsigned int R;
    unsigned int G;
    unsigned int B;
    bool broken;
//dimensions and position
    float w;
    float h;
    float x;
    float y;
} brick_type;

void breakout(SDL_Renderer** renderer, int* disp_width, int* disp_height,SDL_Window** window,FILE** level)
{
    TTF_Font* font = TTF_OpenFont("EightBit Atari-Block.ttf", 128);
    SDL_Color just_white = {240, 240, 240};

    int whatnot = 144;

    SDL_Rect paddle;
    paddle.x = *disp_width/2-20;
    paddle.y = *disp_height - 50;
    paddle.w = 70;
    paddle.h = 12;
    SDL_Rect ball;
    ball.x = *disp_width/2;
    ball.y = paddle.y - paddle.h;
    ball.w = 11;
    ball.h = 11;
    //the sdl2 brick, separate from custom brick_type
    SDL_Rect brick;
        brick.w = *disp_width/14;
        brick.h = brick.w / 2;
        brick.x = brick.w;
        brick.y = 30;
    SDL_Rect top_bar;
    top_bar.w = *disp_width;
    top_bar.h = 65;
    top_bar.x = 0;
    top_bar.y = 0;
    SDL_Rect score;
    score.w = *disp_width/4;
    score.h = 32;
    score.x = 10;
    score.y = top_bar.h/2 - score.h /2;
    SDL_Rect gametype;
    gametype.w = 32;
    gametype.h = 32;
    gametype.x = *disp_width-*disp_width/5;
    gametype.y = top_bar.h/2 - score.h /2;
    SDL_Rect lives_rect;
    lives_rect.w = 32;
    lives_rect.h = 32;
    lives_rect.x = *disp_width-*disp_width/3;
    lives_rect.y = top_bar.h/2 - score.h /2;
    SDL_Rect centered_message;
    centered_message.w = 250;
    centered_message.h = 35;
    centered_message.x = (*disp_width/2) - centered_message.w/2;
    centered_message.y = (*disp_height/2)+centered_message.h;

    //initilize the array of bricks / level
    brick_type bricks[14][14];

    int bool_temp;

    //load bricks from file to array
    for (int i = 0; i <= 13; i++)
    {
        for (int j = 0; j <= 13; j++)
        {
            fscanf(*level, "%d", &bricks[i][j].R);
            fscanf(*level, "%d", &bricks[i][j].G);
            fscanf(*level, "%d", &bricks[i][j].B);
            fscanf(*level, "%d", &bool_temp);
            if(bool_temp == 0)
                bricks[i][j].broken = false;
            else bricks[j][i].broken = true;
        }

    }

    //random direction of ball from the paddle
    srand(time(NULL));
    float dirX;
    do
    {
        dirX = (rand() % 4) - (rand() % 3);
    }
    while (dirX == 0);

    SDL_Event e;

    //bunch of variables
    float dirY = -3;
    int lives = 3;
    char lives_char[2] ;
    int mousex = 0;
    float speed_multiplier = 0.6;
    SDL_CaptureMouse(true);
    float  minX,minY,maxY,maxX,workX,workY;
    bool quit,failed,playing = false;
    bool already = true;
    int score_int = 0;
    char score_char[10];
    char message_char[32] = "press <space> to start";
    char gameover_message[32] = "game over";
    char game_cleared[32] = "all bricks cleared";

    char tempo[32];


    //main game loop
    while (!quit)
    {
        sprintf(lives_char, "%d", lives);
        //score!
        if (score_int < 100)
        {
            if (score_int < 10)
            {
                sprintf(score_char, "00%d",score_int);
            }
            else
                sprintf(score_char, "0%d",score_int);
        }
        else sprintf(score_char, "%d", score_int);

        //mouse to paddle/ball position
        SDL_GetMouseState(&mousex,NULL);
        if (mousex >= *disp_width-40)
            mousex = *disp_width-40;
        if (mousex <= 40)
            mousex = 40;
        paddle.x=mousex-(paddle.w/2);
        if (!playing)
            ball.x=mousex -(ball.h/2);
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        while ((SDL_PollEvent(&e)) != 0)
        {
            switch( e.type )
            {

            // look for keys pressed
            case SDL_KEYDOWN:
                // do the thing
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

        SDL_SetRenderDrawColor(*renderer, 20, 20, 20, 180);
        SDL_RenderClear(*renderer);

        SDL_SetRenderDrawColor(*renderer, 40,40, 40, 255);
        SDL_RenderFillRect(*renderer, &top_bar);

        SDL_Surface* message;

        if (lives == 0)
            message = TTF_RenderText_Blended(font, gameover_message, just_white);
        else if (whatnot == 0)
            message = TTF_RenderText_Blended(font, game_cleared, just_white);
        else
            message = TTF_RenderText_Blended(font, message_char, just_white);


        SDL_Surface* start_game = TTF_RenderText_Blended(font, score_char, just_white);
        SDL_Surface* game_type = TTF_RenderText_Blended(font, "1", just_white);
        SDL_Surface* live = TTF_RenderText_Blended(font, lives_char, just_white);

        SDL_Texture* ONE = SDL_CreateTextureFromSurface(*renderer, start_game);
        SDL_Texture* TWO = SDL_CreateTextureFromSurface(*renderer, game_type);
        SDL_Texture* THREE = SDL_CreateTextureFromSurface(*renderer, live);
        SDL_Texture* FOUR = SDL_CreateTextureFromSurface(*renderer, message);

        SDL_RenderCopy(*renderer, ONE, NULL, &score);
        SDL_RenderCopy(*renderer, TWO, NULL, &gametype);
        SDL_RenderCopy(*renderer, THREE, NULL, &lives_rect);
        if ((!playing && score_int == 0) || lives == 0 || whatnot ==0)
            SDL_RenderCopy(*renderer, FOUR, NULL, &centered_message);

        SDL_SetRenderDrawColor(*renderer, 180, 0, 0, 255);

        if (whatnot == 0)
            paddle.w=0;

        whatnot = 0;

        for (int i = 0; i <= 13; i++)
        {
            brick.x = i * brick.w;
            //SDL_RenderDrawRect(renderer, &brick);

            for (int j = 0; j <=13; j++)
            {
                if(!bricks[i][j].broken)
                    whatnot++;

                brick.y = (j * brick.h) + 80;
                //ball within range of brick on y
                if (ball.y > brick.y && (ball.y+ball.h < brick.y+brick.h))
                {
                    minY = ball.y;
                    maxY = ball.y+ball.h;
                }
                //ball on the right of brick
                else
                {
                    if (ball.y <= brick.y)
                    {
                        minY = brick.y;
                        maxY = ball.y+ball.h;
                        //ball on the left of brick
                    }
                    else
                        minY = ball.y;
                    maxY = brick.y+brick.h;
                }
                //ball within range of brick on x
                if (ball.x > brick.x && (ball.x+ball.w < brick.x + brick.w))
                {
                    minX = ball.x;
                    maxX = ball.x+ball.w;
                }
                else
                {
                    //ball on the top of brick
                    if (ball.x <= brick.x)
                    {
                        minX = brick.x;
                        maxX = ball.x+ball.w;
                        //ball on the bottom
                    }

                    else
                    {
                        minX = ball.x;
                        maxX = brick.x+brick.w;
                    }
                }

                workX = maxX - minX;
                workY = maxY - minY;

                //collision check
                if (!bricks[i][j].broken && already)
                    if (((ball.x >= brick.x) && (ball.x <= brick.x + brick.w)) || ((ball.x + ball.w >= brick.x) && (ball.x+ball.w <= brick.x+brick.w)))
                        if ((ball.y > brick.y) && (ball.y < brick.y + brick.h) || ((ball.y + ball.h > brick.y) && ((ball.y+ball.h) < brick.y + brick.h)))
                        {
                            speed_multiplier+=0.004;
                            already = false;
                            printf("workX%f workY%f", workX, workY);

                            //SCORE!!
                            if ((bricks[i][j].R == 180 && bricks[i][j].G == 10) || (bricks[i][j].R == 200 && bricks[i][j].G == 50) )
                                score_int+=7;
                            if ((bricks[i][j].R == 180 && bricks[i][j].G == 70) || (bricks[i][j].R == 255 && bricks[i][j].G == 200) )
                                score_int+=4;
                            if ((bricks[i][j].R == 50 && bricks[i][j].G == 200) || (bricks[i][j].R == 50 && bricks[i][j].G == 70) )
                                score_int+=1;

                            //set new direction after collision
                            if (workY <= workX)
                            {
                                if(ball.x + ball.h/2 > brick.x + brick.h/2 && ball.y > brick.y+brick.h/2)
                                {
                                    //bottom
                                    ball.y +=workY+0.0001;
                                    dirY = dirY * -1;
                                    sprintf(tempo, "%s","bottom");
                                }
                                else
                                {
                                    ball.y+=(workY);
                                    sprintf(tempo, "%s","top1");
                                    dirY = dirY * -1;
                                }
                            }
                            else
                            {
                                if(ball.x + ball.w/2 < brick.x + brick.w/2 && ball.x+ball.w/2 < brick.x)
                                {
                                    ball.x = brick.x-ball.w-0.001  ;
                                    dirX = dirX * -1;
                                    sprintf(tempo, "%s","left");
                                }
                                else if (ball.x+ball.w/2 > brick.x && ball.x+ball.w/2 < brick.x )
                                {
                                    ball.x = brick.x+brick.w+0.001;
                                    dirX = dirX * -1;
                                    sprintf(tempo, "%s","four");
                                }
                                else if (ball.y+ball.h/2 > brick.y)
                                {
                                    dirX=dirX*-1;
                                    ball.x +=(workX+0.0001);
                                    sprintf(tempo, "%s","right");
                                }
                                else
                                {
                                    dirY=dirY*-1;
                                    ball.y -=workY;
                                    sprintf(tempo, "%s","top");
                                }
                            }

                            bricks[i][j].broken = true;
                        }

                //draw bricks, if broken draw empty spot
                if (!bricks[i][j].broken)
                {
                    SDL_SetRenderDrawColor(*renderer, bricks[i][j].R, bricks[i][j].G, bricks[i][j].B, 255);
                    SDL_RenderFillRect(*renderer, &brick);
                    SDL_SetRenderDrawColor(*renderer, 20, 0, 20, 180);
                    SDL_RenderDrawRect(*renderer, &brick);
                }
                else
                {
                    SDL_SetRenderDrawColor(*renderer, 20, 20, 20, 180);
                    SDL_RenderFillRect(*renderer, &brick);
                    SDL_SetRenderDrawColor(*renderer, 180, 0, 0, 255);
                }
            }
        }

        //draw ball and paddle

        SDL_SetRenderDrawColor(*renderer,194, 194, 194,255);
        SDL_RenderFillRect(*renderer, &paddle);

        SDL_SetRenderDrawColor(*renderer, 20,140, 120, 255);
        SDL_RenderFillRect(*renderer, &ball);

        //handle collision with walls and losing ball
        if (ball.x <= 0 || ball.x >= *disp_width - ball.w)
            dirX= dirX * -1;
        if (ball.y <= 67)
            if (dirY < 0)
                dirY = dirY * -1;

        if (ball.y >= *disp_height - ball.h - 49 && !failed)
            if (ball.x >= (paddle.x-ball.w) && ball.x <= (paddle.x + paddle.w) && !failed)
            {
                //paddle collion new direction on x and y
            if ((ball.x + (float)ball.w/2) > paddle.x+((float)paddle.w/2))
                dirX = 2 - (1.2* (((float)paddle.x + paddle.w) - (ball.x + (float)ball.w/2)) / ((float)paddle.w /2));
            else
                dirX = -2 - (1.2* (((float)paddle.x) - (ball.x + (float)ball.w/2)) / ((float)paddle.w /2));
            dirY = dirY * -1;
            }

            //if ball falls through
            else if (whatnot != 0)
            {
                speed_multiplier = 0.6;
                playing = false;
                lives--;
                dirY = dirY * -1;
                ball.x = *disp_width/2;
                ball.y = paddle.y - paddle.h;
            }
            else dirY = dirY*-1;

        //if lives run out
        if (lives == 0)
        {
            playing=false;
        }

        //move ball
        if (playing == true)
        {
            //weird number for accuracy
            ball.x += dirX *2*1.048592343 * speed_multiplier;
            ball.y += dirY *2*1.048592343 * speed_multiplier;
            already = true;
        }

        SDL_RenderPresent(*renderer);
        SDL_FreeSurface(start_game);
        SDL_FreeSurface(game_type);
        SDL_FreeSurface(live);
        SDL_FreeSurface(message);
        SDL_DestroyTexture(ONE);
        SDL_DestroyTexture(TWO);
        SDL_DestroyTexture(THREE);
        SDL_DestroyTexture(FOUR);
    }

    TTF_CloseFont(font);

}
