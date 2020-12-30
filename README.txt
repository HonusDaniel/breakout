To successfully compile the game, the SDL2_ttf package must also be installed.

linker flags:
 -lSDL2 -lSDL2_ttf -lm

Arch Linux
 sdl2-2.0.14-1
 gcc-10.2.0-4
 extra/sdl2_ttf-2.0.15-2
 multilib/lib32-sdl2_ttf-2.0.15-1

# ABOUT THE GAME
 * navigation in main menu using the <UP> and <DOWN> arrow keys
 * press <space> to select the mode you wish to play
 * pressing <ESC> quits the game

# HOW TO PLAY
 * use mouse to move the paddle around
 * press <space> to launch the ball
 * <ESC> quits the game

# SCORE 
  I went with the following score approach; for every two rows of bricks there is a different score attached depending on far from the paddle they are:
    * RED and DARK ORANGE = 7 points
    * ORANGE and YELLOW = 4 points
    * GREEN and BLUE = 1 point
  Breaking all bricks while also not running out of balls is the goal of the
game.
