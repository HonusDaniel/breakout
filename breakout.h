#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "homescreen.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "SDL2/SDL_ttf.h"


void breakout(SDL_Renderer** renderer, int* disp_width, int* disp_height,SDL_Window** window,FILE** level, bool* progressive);

#endif
