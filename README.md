# breakout
Just another breakout clone made with sdl in c

### font
https://github.com/TheRobotFactory/EightBit-Atari-Fonts

### installation
run `make` in the terminal
### dependencies
SDL2, SDL2_ttf, gcc

### ABOUT THE GAME
 * navigation in main menu using the UP and DOWN arrow keys
 * press space to select the mode you wish to play
 * pressing ESC quits the game
 * two game modes. 
 
 	*BREAKOUT* - normal breakout without the ball speeding up and a larger paddle
  
 	*SPEEDUP* - the ball moves faster the longer the player plays the game. The paddle is also smaller to increase difficulty. Hitting  a red brick increases the speed also.

### HOW TO PLAY
 * use mouse to move the paddle around
 * press space to launch the ball
 * ESC quits the game

### SCORE 
  I went with the following score approach; for every two rows of bricks there is a different score attached depending on far from the paddle they are:
  
    * RED and DARK ORANGE = 7 points
    
    * ORANGE and YELLOW = 4 points
    
    * GREEN and BLUE = 1 point
    
  Breaking all bricks while also not running out of balls is the goal of the
game.

<img src="https://raw.githubusercontent.com/HonusDaniel/personalsite/gh-pages/images/breakout.jpg" width="300" />
