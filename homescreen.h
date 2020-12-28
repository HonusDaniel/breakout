#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
/* ^^ these are the include guards */

/* Prototypes for the functions */
/* Sums two ints */
void home_screen(SDL_Renderer** renderer, int disp_width, int disp_height,SDL_Window** window);
void settings(SDL_Renderer** renderer, int disp_width, int disp_height,SDL_Window** window);

#endif
